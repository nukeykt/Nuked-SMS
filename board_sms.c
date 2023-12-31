#include <stdio.h>
#include <stdint.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "z80.h"
#include "vdp_sms.h"
#include "fm_opll.h"
#include "io_smsu.h"
#include "video.h"
#include "cartridge.h"
#include "controller.h"

unsigned char ram[8192];

unsigned char bios[8192];

unsigned char vram[16384];
int vram_address;
int vram_ce_o;
int vram_ad;

int address;
int data;
int iorq;
int mreq;
int wr;
int rd;
int reset;
int csync;
int nmi; // pause button
int pal = 0;

z80_t z80;
vdpsms_t vdp;
io_smsu_t io;
fm_opll_t fm;

uint64_t mcycles;

float psg_sum;
int fm_sum[2];
int fm_sample[2];
int psg_sample;
short snd_buf[16 * 1024];
int snd_buf_cnt = 0;

FILE *audio_out;


#define ROM_BIOS_SIZE 8192

int load_bios_rom(char *filename)
{
    size_t ret;
    FILE* romf;

    romf = fopen(filename, "rb");
    if (!romf)
        return 1;

    fseek(romf, 0, SEEK_END);
    size_t siz = ftell(romf);
    rewind(romf);
    if (siz < ROM_BIOS_SIZE)
    {
        fclose(romf);
        return 1;
    }

    ret = fread(bios, 1, ROM_BIOS_SIZE, romf);
    if (ret < ROM_BIOS_SIZE)
    {
        fclose(romf);
        return 1;
    }

    fclose(romf);
    return 0;
}

static void emu_loop(void)
{
    int i;

    const int frame_div = 1789772 / 5;
    const int psg_div = 6 * 16;
    const int fm_div = 6 * 72;

    for (i = 0; i < 2; i++)
    {

        // z80
        z80.input.ext_data_i = data;
        z80.input.i_int = !vdp.o_int;
        z80.input.i_nmi = !vdp.o_nmi;
        z80.input.i_wait = 0; // TODO
        z80.input.i_reset = !reset;
        z80.input.i_busrq = 0; // TODO
        Z80_Clock2(&z80, vdp.o_zclk);

        iorq = 1;
        if (z80.o_iorq != state_z)
            iorq = !z80.o_iorq;
        mreq = 1;
        if (z80.o_mreq != state_z)
            mreq = !z80.o_mreq;
        if (z80.o_wr != state_z)
            wr = !z80.o_wr;
        if (z80.o_rd != state_z)
            rd = !z80.o_rd;
        if (!z80.o_addr_high)
            address = z80.o_addr;


        if (!z80.ext_data_o_high)
            data = z80.ext_data_o;
        if (!vdp.o_data_z)
            data = vdp.o_data;
        if (!io.o_data_dir)
            data = io.o_data;
        if (!io.o_ce0 && !vdp.o_exm2)
            data = bios[address & 8191];
        if (!io.o_ce1 && !rd)
            data = ram[address & 8191];

        if (!io.o_ce1 && !wr)
            ram[address & 8191] = data;

        if (vdp.o_csync != state_z)
            csync = vdp.o_csync;

        // ym2602
        vdp.input.xin = mcycles & 1;
        vdp.input.reset = reset;
        vdp.input.ad_i = vram_ad; // TODO
        vdp.input.hl = io.o_hl;
        vdp.input.pal = pal;
        vdp.input.rd = rd;
        vdp.input.wr = wr;
        vdp.input.iorq = iorq;
        vdp.input.a0 = (address & 1) != 0;
        vdp.input.a6 = (address & 64) != 0;
        vdp.input.a7 = (address & 128) != 0;
        vdp.input.a14 = (address & 0x4000) != 0;
        vdp.input.a15 = (address & 0x8000) != 0;
        vdp.input.csync = csync;
        vdp.input.nmi = nmi;
        vdp.input.mreq = mreq;
        vdp.input.data = data;
        VDPSMS_Clock2(&vdp);

        // vram

        if (!vdp.o_ad_z)
            vram_ad = vdp.o_ad;

        if (!vdp.o_ce && vram_ce_o)
            vram_address = vram_ad & 8191;
        if (!vdp.o_ce && !vdp.o_we0)
            vram[vram_address*2+0] = vram_ad & 255;
        if (!vdp.o_ce && !vdp.o_we1)
            vram[vram_address*2+1] = (vram_ad >> 8) & 255;
        if (!vdp.o_ce && !vdp.o_oe)
            vram_ad = (vram[vram_address*2+1] << 8) | vram[vram_address*2+0];
        vram_ce_o = vdp.o_ce;

#if 0
        {
            static int o;
            static int va;
            static int vd;

            if (!o && ((vdp.o_we0 && vdp.o_we1) || vdp.o_ce))
            {
                printf("write %x %x\n", va, vd);
            }

            if (!vdp.o_we0)
            {
                va = vram_address * 2 + 0;
                vd = (vram_ad >> 0) & 255;
            }
            if (!vdp.o_we1)
            {
                va = vram_address * 2 + 1;
                vd = (vram_ad >> 8) & 255;
            }

            o = (vdp.o_we0 && vdp.o_we1) || vdp.o_ce;
        }
#endif

        // 315-5216
        io.input.data = data;
        io.input.a0 = (address & 1) != 0;
        io.input.a6 = (address & 64) != 0;
        io.input.a7 = (address & 128) != 0;
        io.input.wr = wr;
        io.input.rd = rd;
        io.input.iorq = iorq;
        io.input.mreq = mreq;
        io.input.cont1 = 1; // FIXME
        io.input.cont2 = 1; // FIXME
        io.input.killga = 0;
        io.input.csram = vdp.o_csram;
        io.input.reset = reset;
        io.input.port_a = controller_handle_3button((io.o_port_a & 64) != 0 || (io.o_port_a_d & 64) != 0, 0);
        io.input.port_b = controller_handle_3button((io.o_port_b & 64) != 0 || (io.o_port_b_d & 64) != 0, 0);

        IO_SMSU_Clock2(&io);

        // ym2413 (FM sound unit)

        fm.input.mclk = vdp.o_zclk;
        fm.input.in_data = data;
        fm.input.a0 = address & 1;
        fm.input.we = wr;
        fm.input.cs = (address & 0xfe) != 0xf0 || iorq;
        fm.input.ic = !reset;
        FMOPLL_Clock2(&fm);

        cart_handle();
    }

    {
        fm_sum[0] += fm.out_m;
        fm_sum[1] += fm.out_r;
        if ((mcycles % fm_div) == 0)
        {
#define FM_DIVIDE 2
            fm_sample[0] = fm_sum[0] / FM_DIVIDE;
            fm_sample[1] = fm_sum[1] / FM_DIVIDE;
            fm_sum[0] = fm_sum[1] = 0;
        }
        psg_sum += vdp.psg.o_dac * 30.f;
        if ((mcycles % psg_div) == 0)
        {
            int suml = 0, sumr = 0;
            psg_sample = (int)psg_sum;
            suml = fm_sample[0] + fm_sample[1] + psg_sample;
            sumr = fm_sample[0] + fm_sample[1] + psg_sample;
            if (suml < -32768)
                suml = -32768;
            else if (suml > 32767)
                suml = 32767;
            if (sumr < -32768)
                sumr = -32768;
            else if (sumr > 32767)
                sumr = 32767;
            snd_buf[snd_buf_cnt] = suml;
            snd_buf_cnt++;
            snd_buf[snd_buf_cnt] = sumr;
            snd_buf_cnt++;
            if (snd_buf_cnt == 16 * 1024)
            {
                snd_buf_cnt = 0;
                if (audio_out)
                {
                    fwrite(snd_buf, 1, sizeof(snd_buf), audio_out);
                    fflush(audio_out);
                }
            }
            psg_sum = 0;
        }
    }

    if ((mcycles % frame_div) == 0)
    {
        printf("frame %lld\n", (long long)(mcycles / frame_div));
    }

    if (mcycles & 1)
        Video_PlotVDP();

    if (mcycles > 100000)
        reset = 1;

    mcycles++;
}

static void emu_initstate(void)
{
    int i;


    nmi = 1;
    reset = 0;
    mcycles = 0;

    vdp.reg_ct = 255; // HACK
    vdp.reg_bg = 7; // HACK

    for (i = 0; i < 12; i++) // HACK
    {
        z80.regs_[i][0] = 0x0000;
        z80.regs_[i][1] = 0xffff;
    }
}

int main(int argc, char *argv[])
{
    emu_initstate();
    load_bios_rom("bios.bin");
    //bios[0x12e] = 0xc9;
    //load_bios_rom("rom_md.sms");

    //cart_load_game_rom("sonic.sms");

    audio_out = fopen("testaud.raw", "wb");

    Video_Init("testvid.raw");

    int quit_signal = 0;

    while (!quit_signal)
    {
        emu_loop();
        int bm = 0;
        if (!z80.ext_data_o_high)
            bm |= 16;
        if (!vdp.o_data_z)
            bm |= 1;
        if (!io.o_data_dir)
            bm |= 2;
        if (!io.o_ce0 && !vdp.o_exm2)
            bm |= 4;
        if (!io.o_ce1 && !rd)
            bm |= 8;

        // Handle events

        SDL_Event sdl_event;
        while (SDL_PollEvent(&sdl_event))
        {
            switch (sdl_event.type)
            {
            case SDL_QUIT:
                quit_signal = 1;
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                controller_sdl_event(sdl_event.key.keysym.scancode, sdl_event.type == SDL_KEYDOWN);
                break;
            default:
                break;
            }
        }

        //Video_Blit();

        //if (reset)
        //    printf("cycle: %llu rst: %i zclk: %i addr: %x data %x bm %x\n", mcycles, reset, vdp.o_zclk, address, data, bm);
    }

    fclose(audio_out);
    Video_Shutdown();

    SDL_Quit();

    return 0;
}
