#include <stdio.h>
#include <memory.h>
#include "cartridge.h"
#include "io_smsu.h"
#include "vdp_sms.h"

#define ROM_SIZE (4 * 1024 * 1024)

unsigned char rom[ROM_SIZE];

int m3_mapper_enable;
int m3_mapper_data;
int m3_mapper_page[3];
unsigned char m3_mapper_ram[0x4000];

extern io_smsu_t io;
extern vdpsms_t vdp;
extern int data, address;
extern int wr, rd;

int cart_load_game_rom(char *filename)
{
    size_t ret;
    FILE* romfile;

    romfile = fopen(filename, "rb");
    if (!romfile)
        return 1;

    fseek(romfile, 0, SEEK_END);
    size_t siz = ftell(romfile);
    rewind(romfile);

    if (siz > 0x8000)
    {
        m3_mapper_enable = 1;
        m3_mapper_page[0] = 0;
        m3_mapper_page[1] = 1 << 14;
        m3_mapper_page[2] = 2 << 14;
    }
    else
    {
        m3_mapper_enable = 0;
    }

    memset(rom, 0, sizeof(rom));
    ret = fread(rom, 1, siz, romfile);
    if (ret < siz)
    {
        fclose(romfile);
        return 1;
    }
    fclose(romfile);
    return 0;
}

void cart_handle(void)
{
    // M3
    if (!io.o_ce3) // cart chip enable
    {
        if (!rd)
        {
            int address_;
            int enable = 0;
            if (!m3_mapper_enable)
            {
                address_ = address & 0x7fff;
                enable = !vdp.o_exm2;
            }
            else
            {
                address_ = address & 0x3fff;
                if (!vdp.o_exm2)
                {
                    address_ |= m3_mapper_page[(address >> 14) & 1];
                    enable = 1;
                }
                else if (!vdp.o_exm1)
                {
                    if (m3_mapper_data & 8)
                    {
                        data = m3_mapper_ram[address_];
                    }
                    else
                    {
                        address_ |= m3_mapper_page[2];
                        enable = 1;
                    }
                }
                address_ &= (ROM_SIZE-1);
            }
            if (enable)
            {
                data = rom[address_];
            }
        }
        if (!wr)
        {
            if (m3_mapper_enable)
            {
                if (!vdp.o_exm1)
                {
                    if (m3_mapper_data & 8)
                    {
                        m3_mapper_ram[address & 0x3fff] = data & 0xff;
                    }
                }
                if ((address & 0xffff) >= 0xfffc)
                {
                    int page;

                    // GPGX
                    page = data & 255;
                    if (m3_mapper_data & 3)
                        page = (page + ((4 - (m3_mapper_data & 3)) << 3)) & 255;
                    if ((address & 3) == 0)
                        m3_mapper_data = data & 0xff;
                    if ((address & 3) == 1)
                        m3_mapper_page[0] = page << 14;
                    if ((address & 3) == 2)
                        m3_mapper_page[1] = page << 14;
                    if ((address & 3) == 3)
                        m3_mapper_page[2] = page << 14;
                }
            }
        }
    }
}
