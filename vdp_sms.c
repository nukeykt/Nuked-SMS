// YM2602 core

#include <string.h>
#include "common.h"
#include "vdp_sms.h"
#include <stdio.h>

static void VDPSMS_ClockSprite1(vdpsms_t *chip, vdpsms_spriteunit1_t *spr);
static void VDPSMS_ClockSprite2(vdpsms_t *chip, vdpsms_spriteunit2_t *spr);

static int tms_color[16] = {
    0b000000,
    0b000000,
    0b001000,
    0b001100,
    0b010000,
    0b110000,
    0b000001,
    0b111100,
    0b000010,
    0b000011,
    0b000101,
    0b001111,
    0b000100,
    0b110011,
    0b010101,
    0b111111
};

static int dac_lut_rg[4] = {
    0, 85, 170, 255
};

static int dac_lut_b[4] = {
    0, 103, 170, 255
};

static void VDPSMS_VRAMAddressCalc(vdpsms_t *chip);
static void SMSVDP_ClockPSG(vdpsms_psg_t *chip);

void VDPSMS_Clock(vdpsms_t *chip)
{
    chip->clk1 = !chip->input.xin;
    chip->clk2 = chip->input.xin;

    if (chip->clk2)
        chip->w723[0] = chip->input.reset;
    if (chip->clk1)
        chip->w723[1] = chip->w723[0];

    if (chip->clk2)
        chip->w724[0] = chip->w723[1];
    if (chip->clk1)
        chip->w724[1] = !chip->w724[0];
    
    if (chip->clk2)
        chip->w725 = chip->w724[1] || chip->input.reset;
    if (chip->clk1)
        chip->w726 = !chip->w725;

    chip->w727 = !(chip->w726 || chip->w728[1] || chip->w729[1]);

    if (chip->clk2)
        chip->w728[0] = chip->w727;
    if (chip->clk1)
        chip->w728[1] = chip->w728[0];

    if (chip->clk2)
        chip->w729[0] = chip->w728[1];
    if (chip->clk1)
        chip->w729[1] = chip->w729[0];

    if (chip->clk2)
        chip->w730[0] = chip->w729[1];
    if (chip->clk1)
        chip->w730[1] = chip->w730[0];

    if (chip->clk2)
        chip->w731 = chip->w728[1];

    if (chip->w731)
        chip->zclk = 0;
    else if (chip->w730[1])
        chip->zclk = 1;

    chip->o_zclk = chip->zclk;

    if (chip->clk1)
        chip->w739 = !chip->w725;
    if (chip->clk1)
        chip->w741 = !chip->w740;
    if (chip->clk2)
        chip->w740 = chip->w739 || chip->w741;
    if (chip->clk1)
        chip->w742[0] = chip->w740;
    if (chip->clk2)
        chip->w742[1] = !chip->w742[0];

    chip->hclk1 = chip->w742[1];
    chip->hclk2 = !chip->w742[1];

    if (chip->hclk2)
        chip->w732 = chip->input.reset;

    chip->w733 = !chip->w728[1];

    if (chip->hclk2)
        chip->w734[0] = chip->w733;
    if (chip->hclk1)
        chip->w734[1] = chip->w734[0];

    if (chip->hclk2)
        chip->w735[0] = chip->w734[1];
    if (chip->hclk1)
        chip->w735[1] = !chip->w735[0];

    chip->w736 = chip->w735[1] ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w737 = chip->w732;

    if (chip->w736)
        chip->w738 = chip->w737;

    chip->reset1 = !chip->w738;

    if (chip->hclk2)
        chip->w1 = chip->input.ad_i;
    if (chip->hclk1)
    {
        chip->w2_h = (chip->w1 >> 8) & 255;
        chip->w2_l = (chip->w1 >> 0) & 255;
    }
    if (chip->w32)
        chip->vram_data = chip->w2_h;
    if (chip->w34)
        chip->vram_data = chip->w2_l;

    if (chip->w25)
        chip->w3 = (chip->input.ad_i >> 8) & 255;

    if (chip->hclk2)
        chip->w4 = (chip->vram_data & 255) | ((chip->vram_data & 255) << 8);
    if (chip->w30)
        chip->w5 = chip->w4;

    if (chip->w30)
        chip->w6 = (chip->vram_address >> 1) & 0x1fff;

    if (chip->w48)
        chip->w7 = chip->w5;
    if (chip->w47)
        chip->w7 = chip->w6;

    if (chip->w46)
    {
        chip->o_ad_z = 1;
    }
    else
    {
        chip->o_ad_z = 0;
        chip->o_ad = chip->w7;
    }

    chip->w8 = !(chip->w11 && chip->w15);
    chip->o_oe = chip->w8;

    chip->w9 = !(chip->w14 && chip->w15);
    chip->o_we1 = chip->w9;

    chip->w10 = !(chip->w13 && chip->w15);
    chip->o_we0 = chip->w10;

    if (chip->hclk2)
        chip->w11 = !chip->w24;

    if (chip->hclk2)
        chip->w12 = chip->w28;

    chip->w13 = !(chip->w11 || chip->w12);

    chip->w14 = !(chip->w11 || !chip->w12);

    if (chip->clk1)
        chip->w15 = chip->w20;

    if (chip->hclk1)
        chip->w16 = !chip->w343[0];

    if (chip->clk1)
        chip->w17 = !chip->w16;

    if (chip->clk2)
        chip->w18 = !chip->w17;

    if (chip->clk1)
        chip->w19 = !chip->w18;

    if (chip->clk2)
        chip->w20 = chip->w19;

    chip->w21 = !(chip->w19 || chip->w20);
    chip->o_ce = chip->w21;

    if (chip->hclk1)
        chip->w22[0] = chip->w208;
    if (chip->hclk2)
        chip->w22[1] = chip->w22[0];

    chip->w23 = !(chip->w208 || chip->w22[1]);

    if (chip->hclk1)
        chip->w24 = !chip->w23;

    chip->w25 = chip->w27[1] ? chip->hclk2 : 0;

    if (chip->hclk2)
        chip->w26[0] = chip->w544;
    if (chip->hclk1)
        chip->w26[1] = chip->w26[0];
    if (chip->hclk2)
        chip->w27[0] = chip->w26[1];
    if (chip->hclk1)
        chip->w27[1] = chip->w27[0];

    if (chip->w30)
        chip->w28 = chip->vram_address & 1;

    if (chip->hclk1)
        chip->w29[0] = !chip->w343[0];
    if (chip->hclk2)
        chip->w29[1] = chip->w29[0];

    chip->w30 = chip->w29[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w31 = !chip->w35[2] && chip->w343[0];

    chip->w32 = chip->w31 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w33 = chip->w35[2] && chip->w343[0];

    chip->w34 = chip->w33 ? chip->hclk2 : 0;

    if (chip->hclk2)
    {
        chip->w35[0] = !(chip->w28 && chip->w38[1]);
        chip->w35[2] = chip->w35[1];
    }
    if (chip->hclk1)
        chip->w35[1] = chip->w35[0];

    if (chip->hclk1)
        chip->w36 = !chip->w343[10];

    chip->w37 = !(chip->w36 || !chip->reg_80_b2);

    if (chip->hclk2)
        chip->w38[0] = !chip->w37;
    if (chip->hclk1)
        chip->w38[1] = chip->w38[0];

    if (chip->hclk2)
        chip->w39 = chip->w538 && !chip->reg_81_b1;
    chip->w40 = chip->w39 ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w41 = chip->w538;
    chip->w42 = chip->w41 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w43[0] = chip->w343[0];
    if (chip->clk1)
        chip->w43[1] = chip->w43[0];

    if (chip->clk2)
        chip->w44[0] = chip->w43[1];
    if (chip->clk1)
        chip->w44[1] = chip->w44[0];

    chip->w45 = !(chip->w44[1] ? chip->w24 : chip->w43[1]);

    if (chip->clk2)
        chip->w46 = chip->w45;

    if (chip->clk2)
        chip->w47 = !chip->w44[1];

    if (chip->clk2)
        chip->w48 = chip->w44[1];

    if (chip->reset1)
        chip->reg_hit = 0;
    else if (chip->reg_sel[10])
        chip->reg_hit = (chip->reg_addr & 255) ^ 255;

    chip->w49 = (chip->w53 ? chip->reg_hit : chip->w51) ^ 255;

    if (chip->hclk1)
        chip->w50 = chip->w49;
    if (chip->hclk2)
        chip->w51 = ((chip->w50 ^ 255) + !chip->w54) & 255;

    chip->w52 = !(chip->w160 || chip->w159);

    chip->w53 = chip->w52 || chip->w55[1];

    if (chip->hclk1)
        chip->w54 = !chip->w370[1];

    if (chip->hclk1)
        chip->w55[0] = chip->w56;
    if (chip->hclk2)
        chip->w55[1] = chip->w55[0];

    chip->w56 = !(chip->w52 || !chip->w370[1] || chip->w49 != 0);

    chip->w743 = !chip->input.hl;

    if (chip->hclk1)
        chip->w744[0] = chip->w743;
    if (chip->hclk2)
        chip->w744[1] = chip->w744[0];

    if (chip->hclk1)
        chip->w745[0] = chip->w744[1];
    if (chip->hclk2)
        chip->w745[1] = !chip->w745[0];

    chip->w746 = !(chip->w745[1] && chip->w744[1]);

    if (chip->hclk1)
        chip->w57 = !chip->w746;
    if (chip->hclk2)
        chip->w58 = chip->w57;

    chip->w59 = chip->w58 ? chip->hclk1 : 0;

    if (chip->w59)
        chip->w60 = (chip->w313 >> 1) & 255;
    else if (chip->hclk2)
        chip->w60 = chip->w60;

    if (!chip->w164_)
    {
        chip->io_data = chip->cpu_a0 ? chip->w60 : (chip->w145 & 255);
    }

    if (chip->hclk1)
        chip->w62 = (chip->w74 || chip->w80) ? 0 : ((chip->w63 + chip->w76) & 255);
    if (chip->hclk2)
        chip->w63 = chip->w62 | (chip->w65 & chip->w66);

    if (chip->w81)
        chip->w64 = chip->w63;

    if (chip->hclk1)
        chip->w65 = chip->w64;
    if (chip->hclk1)
        chip->w66 = chip->w80 ? 255 : 0;

    chip->w67 = chip->w85[1] ? ((chip->w63 >> 5) & 3) : 0;

    if (chip->hclk1)
        chip->w68 = !chip->w160;
    if (chip->hclk2)
        chip->w69 = !chip->w68;
    if (chip->hclk1)
        chip->w70 = chip->w69;
    if (chip->hclk2)
        chip->w71 = !(chip->w70 || chip->w68);

    chip->w72 = !(chip->w71 || chip->reset1 || (chip->w370[1] && chip->w467));

    if (chip->hclk1)
        chip->w73 = chip->w72;
    if (chip->hclk2)
        chip->w74 = !chip->w73;

    chip->w75 = !(chip->w77 ? chip->w78 : chip->w79);

    if (chip->hclk2)
        chip->w76 = !chip->w75;

    if (chip->hclk1)
        chip->w77 = chip->w467;
    if (chip->hclk1)
        chip->w78 = chip->w343[2];
    if (chip->hclk1)
        chip->w79 = chip->w94;

    chip->w80 = !(chip->w146 || !chip->w379[1]);

    chip->w81 = chip->w378[1];

    if (chip->hclk2)
        chip->w82 = chip->w84;
    chip->w83 = chip->w82 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w84 = !(!chip->reg_80_b2 || chip->w163);

    if (chip->hclk1)
        chip->w85[0] = chip->w343[11];
    if (chip->hclk2)
        chip->w85[1] = chip->w85[0];

    chip->w86 = !(chip->reg_80_b2 || !chip->w343[11]);

    if (chip->hclk1)
        chip->w87[0] = chip->w86;
    if (chip->hclk2)
        chip->w87[1] = chip->w87[0];

    chip->w88 = chip->w87[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w89[0] = chip->w343[1];
    if (chip->hclk2)
        chip->w89[1] = chip->w89[0];

    if (chip->hclk1)
        chip->w90[0] = chip->w74 ? 0 : ((chip->w90[1] + chip->w89[1]) & 3);
    if (chip->hclk2)
        chip->w90[1] = chip->w90[0];

    chip->w91 = !((chip->w90[1] & 2) != 0 || (chip->w90[1] & 1) == 0 || !chip->w89[1]);
    chip->w92 = !((chip->w90[1] & 2) == 0 || (chip->w90[1] & 1) == 0 || !chip->w89[1]);

    chip->w93 = chip->w91;
    chip->w94 = chip->w92;

    chip->w95 = !(chip->w98 || chip->reg_80_b2);

    if (chip->hclk1)
        chip->w96[0] = chip->w95;
    if (chip->hclk2)
        chip->w96[1] = chip->w96[0];

    chip->w97 = chip->w96[1] ? chip->hclk1 : 0;

    chip->w98 = !chip->w343[2];

    chip->w99 = !(chip->w98 || chip->w343[1] || chip->reg_80_b2);

    chip->w100 = !chip->w343[1];

    chip->w101 = !(chip->w100 || chip->reg_80_b2);

    if (chip->hclk1)
        chip->w102[0] = chip->w99;
    if (chip->hclk2)
        chip->w102[1] = chip->w102[0];

    chip->w103 = chip->w102[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w104[0] = chip->w101;
    if (chip->hclk2)
        chip->w104[1] = chip->w104[0];

    chip->w105 = chip->w104[1] ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w106 = chip->w538;
    chip->w107 = chip->w106 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w108 = !chip->w519;

    if (chip->hclk1)
        chip->w109 = chip->w496 & 15;

    if (chip->hclk2)
        chip->w110[0] = chip->w108 ? chip->w109 : chip->w110[1];
    if (chip->hclk1)
        chip->w110[1] = chip->w110[0];

    if (chip->hclk2)
        chip->w111[0] = chip->w108 ? chip->w110[1] : chip->w111[1];
    if (chip->hclk1)
        chip->w111[1] = chip->w111[0];

    if (chip->hclk2)
        chip->w112[0] = chip->w108 ? chip->w111[1] : chip->w112[1];
    if (chip->hclk1)
        chip->w112[1] = chip->w112[0];

    if (chip->hclk2)
        chip->w113[0] = chip->w108 ? chip->w112[1] : chip->w113[1];
    if (chip->hclk1)
        chip->w113[1] = chip->w113[0];

    if (chip->hclk2)
        chip->w114[0] = chip->w108 ? chip->w113[1] : chip->w114[1];
    if (chip->hclk1)
        chip->w114[1] = chip->w114[0];

    if (chip->hclk2)
        chip->w115[0] = chip->w108 ? chip->w114[1] : chip->w115[1];
    if (chip->hclk1)
        chip->w115[1] = chip->w115[0];

    if (chip->hclk2)
        chip->w116[0] = chip->w108 ? chip->w115[1] : chip->w116[1];
    if (chip->hclk1)
        chip->w116[1] = chip->w116[0];

    if (chip->hclk2)
        chip->w117[0] = chip->w108 ? chip->w116[1] : chip->w117[1];
    if (chip->hclk1)
        chip->w117[1] = chip->w117[0];

    if (chip->hclk1)
        chip->w118 = !chip->w518;

    if (chip->hclk2)
        chip->w119[0] = chip->w108 ? (((chip->w119[1] << 1) | chip->w118) & 255) : chip->w119[1];
    if (chip->hclk1)
        chip->w119[1] = chip->w119[0];

    chip->w120 = (chip->w119[0] >> 7) & 1;

    chip->w121 = !((chip->w119[0] & 8) == 0 || chip->reg_80_b2);

    chip->w122 = !((chip->w119[0] & 16) == 0 || chip->reg_80_b2);

    chip->w123 = !(chip->w121 || (chip->reg_80_b2 && chip->w120));

    if (chip->hclk2)
        chip->w124 = chip->w538 && chip->reg_81_b1;
    chip->w125 = chip->w124 ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w126[0] = chip->w532 & 31;
    if (chip->hclk1)
        chip->w126[1] = chip->w126[0];

    if (chip->hclk1)
        chip->w127 = !chip->w343[0];

    if (chip->hclk2)
        chip->w128[0] = chip->w108 ? ((chip->w126[1] << 1) | chip->w127) : chip->w128[1];
    if (chip->hclk1)
        chip->w128[1] = chip->w128[0];

    if (chip->hclk2)
        chip->w129[0] = chip->w108 ? chip->w128[1] : chip->w129[1];
    if (chip->hclk1)
        chip->w129[1] = chip->w129[0];

    if (chip->hclk2)
        chip->w130[0] = chip->w108 ? chip->w129[1] : chip->w130[1];
    if (chip->hclk1)
        chip->w130[1] = chip->w130[0];

    if (chip->hclk2)
        chip->w131[0] = chip->w108 ? chip->w130[1] : chip->w131[1];
    if (chip->hclk1)
        chip->w131[1] = chip->w131[0];

    if (chip->hclk2)
        chip->w132[0] = chip->w108 ? chip->w131[1] : chip->w132[1];
    if (chip->hclk1)
        chip->w132[1] = chip->w132[0];

    if (chip->hclk2)
        chip->w133[0] = chip->w108 ? chip->w132[1] : chip->w133[1];
    if (chip->hclk1)
        chip->w133[1] = chip->w133[0];

    if (chip->hclk2)
        chip->w134[0] = chip->w108 ? chip->w133[1] : chip->w134[1];
    if (chip->hclk1)
        chip->w134[1] = chip->w134[0];

    if (chip->hclk2)
        chip->w135[0] = chip->w108 ? chip->w134[1] : chip->w135[1];
    if (chip->hclk1)
        chip->w135[1] = chip->w135[0];

    if (chip->hclk2)
        chip->w136 = chip->w544;
    chip->w137 = chip->w136 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w138 = chip->w343[3] && !chip->reg_80_b2;
    if (chip->hclk2)
        chip->w139 = chip->w138;
    chip->w140 = chip->w139 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w141 = chip->w370[1];

    if (chip->hclk2)
    {
        chip->w142 = chip->w162 ? 0 : ((chip->w143 + chip->w141) & 511);
        chip->w144 = chip->w162;
    }
    {
        int loadval = 0;
        loadval |= 256 + 128 + 16;
        if (chip->cpu_pal)
            loadval |= 32 + 8 + 2;
        else
            loadval |= 64 + 4 + 1;
        chip->w145 = chip->w142 | (chip->w144 ? loadval : 0);
    }
    if (chip->hclk1)
        chip->w143 = chip->w145;

    if (chip->hclk1)
    {
        chip->v_pla[0] = (chip->w145 & 0x107) == 0x7;
        chip->v_pla[1] = chip->cpu_pal && chip->w145 == 0x1bd;
        chip->v_pla[2] = !chip->cpu_pal && chip->w145 == 0x1d8;
        chip->v_pla[3] = chip->cpu_pal && chip->w145 == 0x1ba;
        chip->v_pla[4] = !chip->cpu_pal && chip->w145 == 0x1d5;
        chip->v_pla[5] = chip->cpu_pal && chip->w145 == 0x1ca;
        chip->v_pla[6] = !chip->cpu_pal && chip->w145 == 0x1e5;
        chip->v_pla[7] = chip->cpu_pal && chip->w145 == 0xf0;
        chip->v_pla[8] = !chip->cpu_pal && chip->w145 == 0xd8;
        chip->v_pla[9] = chip->w145 == 0xc0;
        chip->v_pla[10] = chip->w145 == 0x0;
        chip->v_pla[11] = chip->w145 == 0x1ff;
        chip->v_pla[12] = chip->cpu_pal && chip->w145 == 0xf2;
        chip->v_pla[13] = !chip->cpu_pal && chip->w145 == 0xda;
    }

    chip->cpu_pal = chip->input.pal;

    if (chip->hclk2)
    {
        chip->w146 = chip->v_pla[0];
        chip->w147 = chip->v_pla[1];
        chip->w148 = chip->v_pla[2];
        chip->w149 = chip->v_pla[3];
        chip->w150 = chip->v_pla[4];
        chip->w152 = chip->v_pla[5];
        chip->w153 = chip->v_pla[6];
        chip->w154 = chip->v_pla[7];
        chip->w155 = chip->v_pla[8];
        chip->w157 = chip->v_pla[9];
        chip->w158 = chip->v_pla[10];
        chip->w160 = chip->v_pla[11];
        chip->w161 = chip->v_pla[12] || chip->v_pla[13];
    }

    if (chip->reset1 || chip->w150 || chip->w149)
        chip->w151 = 1;
    else if (chip->w148 || chip->w147)
        chip->w151 = 0;

    if (chip->reset1 || chip->w155 || chip->w154)
        chip->w156 = 1;
    else if (chip->w153 || chip->w152)
        chip->w156 = 0;

    if (chip->w158)
        chip->w159 = 1;
    else if (chip->reset1 || chip->w157)
        chip->w159 = 0;


    if (chip->hclk1)
        chip->w162 = chip->w331 || (chip->w161 && chip->w370[1]);

    chip->w163 = !chip->w343[2];

    chip->w164 = chip->w159 || chip->w160;

    chip->cpu_rd = chip->input.rd;
    chip->cpu_wr = chip->input.wr;
    chip->cpu_iorq = chip->input.iorq;
    chip->cpu_a0 = chip->input.a0;
    chip->cpu_a6 = chip->input.a6;
    chip->cpu_a7 = chip->input.a7;


    chip->w164_ = !chip->cpu_a6 || chip->cpu_iorq || chip->cpu_a7 || chip->cpu_rd;

    chip->w165 = !(chip->cpu_rd || chip->cpu_iorq || chip->cpu_a6 || !chip->cpu_a7);
    chip->w166 = !chip->w165;

    chip->w167 = !(chip->cpu_wr || chip->cpu_iorq || chip->cpu_a6 || !chip->cpu_a7);
    chip->w168 = !chip->w167;

    chip->w169 = chip->w165 || chip->w167;

    if (chip->w166)
        chip->w170 = chip->cpu_a0;

    chip->w171 = !(chip->w166 || chip->w170);

    if (chip->w168)
        chip->w172 = !chip->cpu_a0;

    chip->w173 = !(chip->w166 || !chip->cpu_a0);
    chip->w174 = !(chip->w166 || chip->cpu_a0);

    chip->w175 = !(chip->w168 || !chip->w172);
    chip->w176 = !(chip->w168 || chip->w172 || chip->w186);
    chip->w177 = !(chip->w168 || chip->w172 || chip->w186n);

    chip->w178 = chip->w173;
    chip->w179 = chip->w174;
    chip->w180 = chip->w175;

    chip->w181 = !(chip->w178 || chip->w179 || chip->w180 || chip->w177);

    chip->w182 = !chip->w177;

    chip->w183 = !chip->w176;

    if (chip->w177)
        chip->w184 = 0;
    else if (chip->reset1 || chip->w194[1])
        chip->w184 = 1;

    if (chip->reset1 || chip->w188)
        chip->w185 = 0;
    else if (chip->w176)
        chip->w185 = 1;
    if (chip->w176)
        chip->w185n = 0;
    else if (chip->reset1 || chip->w188)
        chip->w185n = 1;

    if (chip->reset1 || (chip->w194[1] && chip->w185n))
        chip->w186 = 0;
    else if (chip->w194[1] && chip->w185)
        chip->w186 = 1;
    if (chip->w194[1] && chip->w185)
        chip->w186n = 0;
    else if (chip->reset1 || (chip->w194[1] && chip->w185n))
        chip->w186n = 1;

    if (chip->w169)
        chip->w187 = 0;
    else if (chip->reset1 || !chip->w191[1])
        chip->w187 = 1;

    chip->w188 = !chip->w181;

    if (chip->hclk1)
        chip->w189 = chip->w187;
    if (chip->hclk2)
        chip->w190 = !chip->w189;

    if (chip->hclk1)
        chip->w191[0] = !chip->w190;
    if (chip->hclk2)
        chip->w191[1] = chip->w191[0];

    chip->w192 = !(chip->reset1 || chip->w190 || chip->w191[1]);

    if (chip->hclk1)
        chip->w193[0] = chip->w192;
    if (chip->hclk2)
        chip->w193[1] = chip->w193[0];

    if (chip->hclk1)
        chip->w194[0] = chip->w193[1];
    if (chip->hclk2)
        chip->w194[1] = chip->w194[0];

    chip->w195 = chip->w192 && chip->reg_code == 0 && !chip->w184;

    if (chip->w195 || chip->w180 || chip->w171)
        chip->w196 = 0;
    else if (chip->w201_[1] || chip->reset1)
        chip->w196 = 1;

    if (chip->hclk2)
        chip->w197 = !chip->w194[0];

    chip->w198 = !(chip->w196 || chip->w197);

    if (chip->w198)
        chip->w199 = 0;
    else if (chip->w201_[1] || chip->reset1)
        chip->w199 = 1;

    chip->w200 = !(chip->w199 || chip->w343[10]);

    chip->w201 = !chip->w200;

    if (chip->hclk1)
        chip->w201_[0] = chip->w200;
    if (chip->hclk2)
        chip->w201_[1] = chip->w201_[0];

    if (chip->hclk1)
        chip->w202[0] = chip->w201_[1];
    if (chip->hclk2)
        chip->w202[1] = chip->w202[0];

    chip->w203 = !chip->w202[1];

    if (chip->hclk1)
        chip->w204[0] = chip->w202[1];
    if (chip->hclk2)
        chip->w204[1] = chip->w204[0];

    if (chip->hclk1)
        chip->w205[0] = chip->w204[1];
    if (chip->hclk2)
        chip->w205[1] = chip->w205[0];

    if (chip->w180)
        chip->w206 = 0;
    else if (chip->reset1 || chip->w205[1])
        chip->w206 = 1;
    if (chip->reset1 || chip->w205[1])
        chip->w206n = 0;
    else if (chip->w180)
        chip->w206n = 1;

    chip->w207 = chip->w206 && chip->w204[1];

    chip->w208 = chip->w206n && chip->w212 && chip->w201_[1];
    chip->w209 = chip->w206n && !chip->w212 && chip->w201_[1];

    chip->w210 = !(chip->w194[1] || chip->w193[1]);

    chip->w211 = chip->reg_code == 2 && !chip->w184 && !chip->w210;

    chip->w212 = chip->reg_code != 3;

    if (!chip->w183)
    {
        chip->w214 = chip->w213 = chip->io_data & 255;
        chip->dbg_address &= ~255;
        chip->dbg_address |= (chip->io_data) & 255;
    }
    else
    {
        int i;
        int bit = chip->w215[1];
        for (i = 0; i < 8; i++)
        {
            int shift = 1 << i;
            if (bit)
            {
                chip->w213 &= ~shift;
                chip->w213 |= (chip->w214 & shift) ^ shift;
            }
            else
            {
                chip->w214 &= ~shift;
                chip->w214 |= chip->w213 & shift;
            }
            bit = (chip->w214 >> i) & 1;
        }
    }

    if (chip->hclk1)
        chip->w215[0] = chip->w203;
    if (chip->hclk2)
        chip->w215[1] = chip->w215[0];

    if (!chip->w182)
    {
        chip->w217 = chip->w216 = chip->io_data & 63;
        chip->reg_code = (chip->io_data >> 6) & 3;
        chip->dbg_address &= ~0x3f00;
        chip->dbg_address |= (chip->io_data << 8) & 0x3f00;
    }
    else
    {
        int i;
        int bit = (chip->w214 >> 7) & 1;
        for (i = 0; i < 6; i++)
        {
            int shift = 1 << i;
            if (bit)
            {
                chip->w216 &= ~shift;
                chip->w216 |= (chip->w217 & shift) ^ shift;
            }
            else
            {
                chip->w217 &= ~shift;
                chip->w217 |= chip->w216 & shift;
            }
            bit = (chip->w217 >> i) & 1;
        }
    }

    chip->reg_addr = (chip->w217 << 8) | chip->w214;

    chip->reg_sel[0] = (chip->reg_addr & 0xf00) == 0x000 && chip->w211;
    chip->reg_sel[1] = (chip->reg_addr & 0xf00) == 0x100 && chip->w211;
    chip->reg_sel[2] = (chip->reg_addr & 0xf00) == 0x200 && chip->w211;
    chip->reg_sel[3] = (chip->reg_addr & 0xf00) == 0x300 && chip->w211;
    chip->reg_sel[4] = (chip->reg_addr & 0xf00) == 0x400 && chip->w211;
    chip->reg_sel[5] = (chip->reg_addr & 0xf00) == 0x500 && chip->w211;
    chip->reg_sel[6] = (chip->reg_addr & 0xf00) == 0x600 && chip->w211;
    chip->reg_sel[7] = (chip->reg_addr & 0xf00) == 0x700 && chip->w211;
    chip->reg_sel[8] = (chip->reg_addr & 0xf00) == 0x800 && chip->w211;
    chip->reg_sel[9] = (chip->reg_addr & 0xf00) == 0x900 && chip->w211;
    chip->reg_sel[10] = (chip->reg_addr & 0xf00) == 0xa00 && chip->w211;

    if (chip->reg_sel[0])
    {
        chip->reg_80_b0 = (chip->reg_addr >> 0) & 1;
        chip->reg_80_b1 = (chip->reg_addr >> 1) & 1;
        chip->reg_80_b2 = (chip->reg_addr >> 2) & 1;
        chip->reg_80_b3 = (chip->reg_addr >> 3) & 1;
        chip->reg_80_b4 = (chip->reg_addr >> 4) & 1;
        chip->reg_80_b5 = (chip->reg_addr >> 5) & 1;
        chip->reg_80_b6 = (chip->reg_addr >> 6) & 1;
        chip->reg_80_b7 = (chip->reg_addr >> 7) & 1;
    }
    else if (chip->reset1)
    {
        chip->reg_80_b0 = 0;
        chip->reg_80_b1 = 0;
        chip->reg_80_b2 = 0;
        chip->reg_80_b3 = 0;
        chip->reg_80_b4 = 0;
        chip->reg_80_b5 = 0;
        chip->reg_80_b6 = 0;
        chip->reg_80_b7 = 0;
    }

    if (chip->reg_sel[1])
    {
        chip->reg_81_b0 = (chip->reg_addr >> 0) & 1;
        chip->reg_81_b1 = (chip->reg_addr >> 1) & 1;
        chip->reg_81_b2 = (chip->reg_addr >> 2) & 1;
        chip->reg_81_b3 = (chip->reg_addr >> 3) & 1;
        chip->reg_81_b4 = (chip->reg_addr >> 4) & 1;
        chip->reg_81_b5 = (chip->reg_addr >> 5) & 1;
        chip->reg_81_b6 = (chip->reg_addr >> 6) & 1;
    }
    else if (chip->reset1)
    {
        chip->reg_81_b0 = 0;
        chip->reg_81_b1 = 0;
        chip->reg_81_b2 = 0;
        chip->reg_81_b3 = 0;
        chip->reg_81_b4 = 0;
        chip->reg_81_b5 = 0;
        chip->reg_81_b6 = 0;
    }

    if (chip->reg_sel[2])
    {
        chip->reg_nt = (chip->reg_addr >> 0) & 15;
    }

    if (chip->reg_sel[3])
    {
        chip->reg_ct = (chip->reg_addr >> 0) & 255;
    }

    if (chip->reg_sel[4])
    {
        chip->reg_bg = (chip->reg_addr >> 0) & 7;
    }

    if (chip->reg_sel[5])
    {
        chip->reg_sat = (chip->reg_addr >> 0) & 127;
    }

    if (chip->reg_sel[6])
    {
        chip->reg_spr = (chip->reg_addr >> 0) & 7;
    }

    if (chip->hclk1)
        chip->w218[0] = chip->w343[6];
    if (chip->hclk2)
        chip->w218[1] = chip->w218[0];
    chip->w219 = chip->w218[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w220 = chip->w343[4];
    if (chip->hclk2)
        chip->w221 = (chip->w220 && !chip->reg_80_b2) || (chip->w542 && chip->reg_80_b2);
    chip->w222 = chip->w221 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w223[0] = chip->w343[7];
    if (chip->hclk2)
        chip->w223[1] = chip->w223[0];

    chip->w224 = chip->w223[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w225[0] = chip->w343[5];
    if (chip->hclk2)
        chip->w225[1] = chip->w225[0];

    chip->w226 = chip->w225[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w227 = chip->w343[8];
    if (chip->hclk2)
        chip->w228 = (chip->w227 && !chip->reg_80_b2) || (chip->reg_80_b2 && chip->w538);
    chip->w229 = chip->w228 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w230[0] = !chip->w201;
    if (chip->hclk2)
        chip->w230[1] = chip->w230[0];
    chip->w231 = chip->w230[1] ? chip->hclk1 : 0;

    chip->w232 = !(chip->w240 || chip->reg_80_b2 || !chip->w343[6]);

    if (chip->hclk1)
        chip->w233[0] = chip->w232;
    if (chip->hclk2)
        chip->w233[1] = chip->w233[0];

    chip->w234 = chip->w233[1] ? chip->hclk1 : 0;

    chip->w235 = !(!chip->w343[12] || chip->reg_80_b2);

    if (chip->hclk1)
        chip->w236[0] = chip->w235;
    if (chip->hclk2)
        chip->w236[1] = chip->w236[0];

    chip->w237 = chip->w236[1] ? chip->hclk1 : 0;

    chip->w238 = !chip->w464;

    chip->w239 = !chip->w343[7];

    chip->w240 = !chip->reg_80_b1;

    chip->w241 = !(chip->w239 || chip->reg_80_b2 || chip->w240);

    if (chip->hclk1)
        chip->w242[0] = chip->w241;
    if (chip->hclk2)
        chip->w242[1] = chip->w242[0];

    chip->w243 = chip->w242[1] ? chip->hclk1 : 0;

    chip->w244 = !(chip->reg_80_b2 || chip->w464 || chip->w239);

    if (chip->hclk1)
        chip->w245[0] = chip->w244;
    if (chip->hclk2)
        chip->w245[1] = chip->w245[0];

    chip->w246 = chip->w245[1] ? chip->hclk1 : 0;

    chip->w247 = !(chip->w238 || chip->w239 || chip->reg_80_b2);

    if (chip->hclk1)
        chip->w248[0] = chip->w247;
    if (chip->hclk2)
        chip->w248[1] = chip->w248[0];

    chip->w249 = chip->w248[1] ? chip->hclk1 : 0;

    if (chip->w300)
        chip->w250 = 1;
    else if (chip->w263)
        chip->w250 = 0;

    if (chip->w258)
        chip->w251 = 1;
    else if (chip->w263)
        chip->w251 = 0;

    if (chip->w255)
        chip->w252 = 1;
    else if (chip->w263)
        chip->w252 = 0;

    if (!chip->w254)
    {
        chip->io_data &= ~0xe0;
        chip->io_data |= chip->w250 << 5;
        chip->io_data |= chip->w251 << 6;
        chip->io_data |= chip->w252 << 7;
    }

    chip->w253 = chip->w251;

    chip->w254 = !chip->w178;

    chip->w255 = chip->w157 && chip->w370[1];

    chip->w257 = !chip->w252;

    chip->w256 = chip->w257 || !chip->reg_81_b5;

    chip->w258 = !(!chip->w257 || !chip->w516);

    if (chip->w178 || chip->reset1)
        chip->w259 = 0;
    else if (!chip->w261[1])
        chip->w259 = 1;

    if (chip->hclk1)
        chip->w260[0] = !chip->w259;
    if (chip->hclk2)
        chip->w260[1] = chip->w260[0];

    if (chip->hclk1)
        chip->w261[0] = !chip->w260[1];
    if (chip->hclk2)
        chip->w261[1] = chip->w261[0];

    chip->w262 = !(chip->reset1 || chip->w261[1] || chip->w260[1]);

    if (chip->hclk1)
        chip->w263 = chip->w262;

    if (chip->hclk1)
        chip->w264 = !chip->w343[0];

    chip->w265 = chip->w264 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w266 = chip->w207;
    chip->w267 = chip->w266 ? chip->hclk2 : 0;

    chip->w268 = !(chip->w267 || chip->w180);

    chip->w269 = !chip->w179;

    if (chip->w180)
        chip->w270 = chip->io_data & 255;
    else if (chip->w267)
        chip->w270 = chip->vram_data & 255;
    else if (chip->w268)
        chip->w270 = chip->w270;

    if (chip->w265)
        chip->vram_data = chip->w270;
    if (!chip->w269)
        chip->io_data = chip->w270;

#if 0
    {
        static int sss;
        static int sss2;
        extern unsigned char vram[];
        if (!chip->w269)
            sss2 = chip->w270;
        if (!sss && chip->w269)
        {
            printf("read: %x %x %x\n", chip->dbg_address, sss2, vram[chip->dbg_address]);
        }
        sss = chip->w269;
    }
#endif

    chip->w271 = !(chip->reg_81_b2 || chip->w253);

    if (chip->hclk1)
        chip->w272 = chip->reg_81_b2;

    chip->w273 = chip->w272 ? chip->hclk2 : 0;

    chip->w274 = !(chip->w273 || chip->w271);

    if (chip->w273)
        chip->w275 = (chip->color_index & 15) | ((chip->color_palette & 1) << 4);
    else if (chip->w271)
        chip->w275 = chip->w533 & 31;
    else if (chip->w274)
        chip->w275 = chip->w275;

    if (!chip->w254)
    {
        chip->io_data &= ~31;
        chip->io_data |= chip->w275 & 31;
    }

    chip->w276 = !chip->reg_80_b2;

    if (chip->hclk1)
        chip->w277 = (chip->w276 && chip->w464 && chip->w359[1]) || (chip->w276 && !chip->w464 && chip->w358[1]);

    chip->w278 = chip->w277 ? chip->hclk2 : 0;

    if (chip->w278)
        chip->w279 = chip->vram_data;
    else if (chip->hclk1)
        chip->w279 = chip->w279;

    chip->w280 = (chip->w279 & 15) == 0;
    chip->w281 = (chip->w279 & 240) == 0;

    if (chip->w285)
        chip->w282 = chip->w280;
    else if (chip->hclk1)
        chip->w282 = chip->w282;

    if (chip->w285)
        chip->w283 = chip->w281;
    else if (chip->hclk1)
        chip->w283 = chip->w283;

    if (chip->hclk1)
        chip->w284 = chip->w289;
    chip->w285 = chip->w284 ? chip->hclk2 : 0;

    if (chip->w291)
        chip->w286 = chip->w279;
    else if (chip->hclk2)
        chip->w286 = chip->w286;

    if (chip->hclk1)
        chip->w287 = chip->w276;

    if (chip->hclk1)
        chip->w288 = chip->w359[1];

    if (chip->hclk2)
        chip->w289 = chip->w288 && chip->w287;

    if (chip->hclk1)
        chip->w290[0] = chip->w289;
    if (chip->hclk2)
        chip->w290[1] = chip->w290[0];
    if (chip->hclk1)
        chip->w290[2] = chip->w290[1];
    if (chip->hclk2)
        chip->w290[3] = chip->w290[2];

    chip->w291 = chip->w290[3] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w292 = chip->w560[0][1];
    chip->w293 = chip->w292 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w294 = chip->w560[1][1];
    chip->w295 = chip->w294 ? chip->hclk2 : 0;

    if (chip->w293)
        chip->color_index = (chip->w286 >> 4) & 15;

    if (chip->w295)
        chip->color_index = (chip->w286 >> 0) & 15;

    if (chip->hclk1)
        chip->color_index = 15;

    if (chip->hclk1)
        chip->w296 = chip->w357[1];

    if (chip->hclk2)
        chip->w297 = chip->w296 && !chip->reg_80_b2;

    int spr_mask = 0;
    if (chip->sprite1[0].w604)
        spr_mask |= 1;
    if (chip->sprite1[1].w604)
        spr_mask |= 2;
    if (chip->sprite1[2].w604)
        spr_mask |= 4;
    if (chip->sprite1[3].w604)
        spr_mask |= 8;
    if (chip->sprite2[0].w636)
        spr_mask |= 16;
    if (chip->sprite2[1].w636)
        spr_mask |= 32;
    if (chip->sprite2[2].w636)
        spr_mask |= 64;
    if (chip->sprite2[3].w636)
        spr_mask |= 128;

    int spr_mask2 = 0;
    if (chip->sprite1[0].w566)
        spr_mask2 |= 1;
    if (chip->sprite1[1].w566)
        spr_mask2 |= 2;
    if (chip->sprite1[2].w566)
        spr_mask2 |= 4;
    if (chip->sprite1[3].w566)
        spr_mask2 |= 8;

    if (chip->hclk2)
        chip->w298 = 1;
    if (chip->hclk1)
    {
        if (chip->w559)
            chip->w298 = 0;
        else if ((spr_mask & 254) == 254)
            chip->w298 = 0;
        else if ((spr_mask & 253) == 253)
            chip->w298 = 0;
        else if ((spr_mask & 251) == 251)
            chip->w298 = 0;
        else if ((spr_mask & 247) == 247)
            chip->w298 = 0;
        else if ((spr_mask & 239) == 239)
            chip->w298 = 0;
        else if ((spr_mask & 223) == 223)
            chip->w298 = 0;
        else if ((spr_mask & 191) == 191)
            chip->w298 = 0;
        else if ((spr_mask & 127) == 127)
            chip->w298 = 0;
    }

    if (chip->hclk1)
        chip->w299 = chip->w298;
    if (chip->hclk2)
        chip->w300 = chip->w299;

    chip->w301[0] = !(chip->w559 || chip->w469 || chip->w444 || (spr_mask & 1) != 0 || (spr_mask2 & 1) != 0);
    chip->w301[1] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || (spr_mask & 2) != 0 || (spr_mask2 & 2) != 0);
    chip->w301[2] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || (spr_mask & 4) != 0 || (spr_mask2 & 4) != 0);
    chip->w301[3] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || chip->w301[2] || (spr_mask & 8) != 0 || (spr_mask2 & 8) != 0);
    chip->w301[4] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || chip->w301[2] || chip->w301[3] || (spr_mask & 16) != 0);
    chip->w301[5] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || chip->w301[2] || chip->w301[3] || chip->w301[4] || (spr_mask & 32) != 0);
    chip->w301[6] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || chip->w301[2] || chip->w301[3] || chip->w301[4] || chip->w301[5] || (spr_mask & 64) != 0);
    chip->w301[7] = !(chip->w559 || chip->w469 || chip->w444 || chip->w301[0] || chip->w301[1] || chip->w301[2] || chip->w301[3] || chip->w301[4] || chip->w301[5] || chip->w301[6] || (spr_mask & 128) != 0);
    chip->w301[8] = !(chip->w301[0] || chip->w301[1] || chip->w301[2] || chip->w301[3] || chip->w301[4] || chip->w301[5] || chip->w301[6] || chip->w301[7]);

    chip->w302 = !chip->w301[8];

    if (chip->hclk1)
    {
        int i;
        chip->w303[0] = 0;
        for (i = 0; i < 8; i++)
        {
            if (chip->w301[i])
                chip->w303[0] |= 1 << i;
        }
    }
    if (chip->hclk2)
    {
        chip->w303[1] = chip->w303[0];
    }

    if (chip->hclk1)
        chip->w304 = !chip->w317;
    if (chip->hclk2)
        chip->w305 = chip->w304;

    if (chip->hclk2)
        chip->w306[0] = chip->w304 ? 0 : ((chip->w306[1] + 1) & 7);
    chip->w307 = chip->w306[0] | (chip->w305 ? (chip->w315[1] * 2) : 0);
    if (chip->hclk1)
        chip->w306[1] = chip->w307;

    if (chip->hclk1)
        chip->w308 = !chip->w320;
    if (chip->hclk2)
        chip->w309 = chip->w308;

    if (chip->hclk2)
        chip->w310[0] = chip->w308 ? 0 : ((chip->w310[1] + !chip->w312) & 63);
    chip->w311 = chip->w310[0] | (chip->w309 ? (chip->w314[1] + chip->w315[1] * (2 + 8 + 16) + 32) : 0);
    if (chip->hclk1)
        chip->w310[1] = chip->w311;

    if (chip->hclk1)
        chip->w312 = chip->w318;

    chip->w313 = ((chip->w311 & 63) << 3) | (chip->w307 & 7);

    if (chip->hclk1)
        chip->w314[0] = chip->w381[1];
    if (chip->hclk2)
        chip->w314[1] = chip->w314[0];

    if (chip->hclk1)
        chip->w315[0] = chip->w333;
    if (chip->hclk2)
        chip->w315[1] = chip->w315[0];

    chip->w316 = chip->w315[0];

    chip->w317 = !(chip->w319 || chip->w381[1] || chip->w333);

    chip->w318 = !((chip->w337 && chip->w336) || chip->w319);

    chip->w319 = chip->w335[1] && chip->w321;

    chip->w320 = !(chip->w333 || chip->w381[1]);

    chip->w321 = !(!chip->w380[1] || chip->w338[1]);

    if (chip->hclk1)
        chip->w322[0] = !chip->w321;
    if (chip->hclk2)
        chip->w322[1] = chip->w322[0];

    if (chip->hclk1)
        chip->w323 = chip->w322[1] || chip->w338[1];

    if (chip->hclk1)
        chip->w324[0] = !chip->w328[1];
    if (chip->hclk2)
        chip->w324[1] = chip->w324[0];

    chip->w325 = !(chip->w328[1] || chip->w324[1] || chip->w326);

    chip->w747 = chip->input.csync;
    if (chip->hclk1)
        chip->w748[0] = chip->w747;
    if (chip->hclk2)
        chip->w748[1] = chip->w748[0];

    chip->w326 = !chip->reg_80_b0;
    chip->w327 = !(chip->reg_80_b0 && chip->w748[1]);

    if (chip->hclk1)
        chip->w328[0] = chip->w327;
    if (chip->hclk2)
        chip->w328[1] = chip->w328[0];

    chip->w329 = !(chip->w326 || !chip->w368[1] || chip->w328[1]);

    if (chip->hclk1)
        chip->w330[0] = chip->reset1;
    if (chip->hclk2)
        chip->w330[1] = chip->w330[0];

    chip->w331 = chip->w330[1] || chip->w329;

    chip->w332 = chip->w330[1] || chip->w325;

    chip->w333 = chip->w332 || (chip->w382[1] && chip->w327);

    chip->w334 = !chip->w339;

    if (chip->hclk1)
        chip->w335[0] = chip->w334;
    if (chip->hclk2)
        chip->w335[1] = chip->w335[0];

    chip->w336 = !(chip->w335[1] || chip->w333 || chip->w338[1]);

    if (chip->hclk2)
        chip->w337 = !chip->w323;

    if (chip->hclk1)
        chip->w338[0] = chip->w333;
    if (chip->hclk2)
        chip->w338[1] = chip->w338[0];

    if (chip->w379[1] || chip->w338[1])
        chip->w339 = 1;
    else if (chip->w378[1] && chip->w469)
        chip->w339 = 0;

    chip->w749 = chip->reg_80_b2 || chip->w122;
    chip->w750 = chip->reg_80_b2 || chip->w121;

    chip->hpla[0] = (chip->w313 & 0b111111101) == 0b111101000 && chip->reg_80_b2;
    chip->hpla[1] = (chip->w313 & 0b100010111) == 0b000010010 && !chip->w468;
    chip->hpla[2] = (chip->w313 & 0b100011111) == 0b000001010 && !chip->w468;
    chip->hpla[3] = (chip->w313 & 0b000000001) == 0b000000001;
    chip->hpla[4] = (chip->w313 & 0b111110001) == 0b111110000 && !chip->w468;
    chip->hpla[5] = (chip->w313 & 0b111111101) == 0b100000100 && !chip->w468 && !chip->reg_80_b2;
    chip->hpla[6] = (chip->w313 & 0b111111101) == 0b100001000 && !chip->w468;
    chip->hpla[7] = (chip->w313 & 0b111111001) == 0b100010000 && !chip->w468;
    chip->hpla[8] = (chip->w313 & 0b111111101) == 0b100011100 && !chip->w468;
    chip->hpla[9] = (chip->w313 & 0b111111101) == 0b111010100 && !chip->w468;
    chip->hpla[10] = (chip->w313 & 0b111111101) == 0b111011100 && !chip->w468;
    chip->hpla[11] = (chip->w313 & 0b111111101) == 0b111100000 && !chip->w468;

    chip->hpla[12] = (chip->w313 & 0b100000011) == 0b000000000 && !chip->w466;
    chip->hpla[13] = (chip->w313 & 0b000000111) == 0b000000000 && chip->w334;
    chip->hpla[14] = (chip->w313 & 0b111111101) == 0b100001100 && !chip->w468;
    chip->hpla[15] = (chip->w313 & 0b100000111) == 0b000000000 && !chip->w468;
    chip->hpla[16] = (chip->w313 & 0b111111101) == 0b100011000 && !chip->w468;
    chip->hpla[17] = (chip->w313 & 0b100000111) == 0b000000100 && !chip->w468;
    chip->hpla[18] = (chip->w313 & 0b100000111) == 0b000000110 && !chip->w468;
    chip->hpla[19] = (chip->w313 & 0b000000111) == 0b000000100 && chip->w334;
    chip->hpla[20] = (chip->w313 & 0b111111101) == 0b111011000 && !chip->w468;
    chip->hpla[21] = (chip->w313 & 0b111111101) == 0b111100100 && !chip->w468;

    chip->hpla[22] = (chip->w313 & 0b111111111) == 0b111100111 && !chip->w749;
    chip->hpla[23] = (chip->w313 & 0b111111111) == 0b111100101;
    chip->hpla[24] = (chip->w313 & 0b111111111) == 0b111100001 && !chip->w750;
    chip->hpla[25] = (chip->w313 & 0b111111111) == 0b111011011 && !chip->w749;
    chip->hpla[26] = (chip->w313 & 0b111111111) == 0b111011001;
    chip->hpla[27] = (chip->w313 & 0b111111111) == 0b100100001 && !chip->w750;
    chip->hpla[28] = (chip->w313 & 0b111111111) == 0b100011011 && !chip->w749;
    chip->hpla[29] = (chip->w313 & 0b111111111) == 0b100011001;
    chip->hpla[30] = (chip->w313 & 0b111111111) == 0b100010101 && !chip->w750;
    chip->hpla[31] = (chip->w313 & 0b111111111) == 0b100001111 && !chip->w749;

    chip->hpla[32] = (chip->w313 & 0b111111111) == 0b100001101;
    chip->hpla[33] = (chip->w313 & 0b111111111) == 0b100001001 && !chip->w750;
    chip->hpla[34] = (chip->w313 & 0b111111111) == 0b000001001;
    chip->hpla[35] = (chip->w313 & 0b111111111) == 0b111101001;
    chip->hpla[36] = (chip->w313 & 0b000000111) == 0b000000111;
    chip->hpla[37] = (chip->w313 & 0b000000111) == 0b000000001;
    chip->hpla[38] = (chip->w313 & 0b111111111) == 0b111010111;
    chip->hpla[39] = (chip->w313 & 0b111111111) == 0b100010111;
    chip->hpla[40] = (chip->w313 & 0b000000111) == 0b000000011;
    chip->hpla[41] = (chip->w313 & 0b100010000) == 0b100010000 && !chip->w469;

    chip->hpla[42] = (chip->w313 & 0b111111111) == 0b111111000;
    chip->hpla[43] = (chip->w313 & 0b111111111) == 0b111101010;
    chip->hpla[44] = (chip->w313 & 0b111111111) == 0b111101000;
    chip->hpla[45] = (chip->w313 & 0b111111111) == 0b100100100;
    chip->hpla[46] = (chip->w313 & 0b111111111) == 0b000000000;
    chip->hpla[47] = (chip->w313 & 0b111111111) == 0b100011100;
    chip->hpla[48] = (chip->w313 & 0b111111111) == 0b100001010;

    chip->hpla[49] = (chip->w313 & 0b111111111) == 0b101011000;
    chip->hpla[50] = (chip->w313 & 0b111111111) == 0b000010010;
    chip->hpla[51] = (chip->w313 & 0b111111111) == 0b000001010;
    chip->hpla[52] = (chip->w313 & 0b111111111) == 0b101000100;
    chip->hpla[53] = (chip->w313 & 0b111111111) == 0b000000110;
    chip->hpla[54] = (chip->w313 & 0b000000111) == 0b000000100;
    chip->hpla[55] = (chip->w313 & 0b111111111) == 0b101011110;
    chip->hpla[56] = (chip->w313 & 0b111111111) == 0b100100110;

    if (chip->hclk1)
    {
        int i;
        for (i = 0; i < 22; i++)
        {
            chip->w340[i] = chip->hpla[i];
        }
    }

    chip->w341[0] = chip->w340[1] || chip->w340[2];
    chip->w341[1] = chip->w340[0];
    chip->w341[2] = chip->w340[3];
    chip->w341[3] = chip->w340[4];
    chip->w341[4] = chip->w340[5];
    chip->w341[5] = chip->w340[6];
    chip->w341[6] = chip->w340[7];
    chip->w341[7] = chip->w340[8];
    chip->w341[8] = chip->w340[9];
    chip->w341[9] = chip->w340[10];
    chip->w341[10] = chip->w340[11];
    chip->w341[11] = chip->w340[12];
    chip->w341[12] = chip->w340[13];
    chip->w341[13] = chip->w340[14];
    chip->w341[14] = chip->w340[15];
    chip->w341[15] = chip->w340[16];
    chip->w341[16] = chip->w340[17];
    chip->w341[17] = chip->w340[18];
    chip->w341[18] = chip->w340[19];
    chip->w341[19] = chip->w340[20];
    chip->w341[20] = chip->w340[21];

    chip->w342[0] = chip->w341[2];
    chip->w342[1] = chip->w341[4] || chip->w341[5] || chip->w341[6] || chip->w341[7] || chip->w341[8]
        || chip->w341[9] || chip->w341[10] || chip->w341[11] || chip->w341[12];
    chip->w342[2] = chip->w341[0] || chip->w341[3] || chip->w341[11] || chip->w341[12];
    chip->w342[3] = chip->w341[4] || chip->w341[5] || chip->w341[6] || chip->w341[7] || chip->w341[8]
        || chip->w341[9] || chip->w341[10];
    chip->w342[4] = chip->w341[0] || chip->w341[3] || chip->w341[4] || chip->w341[5] || chip->w341[6]
        || chip->w341[7] || chip->w341[8] || chip->w341[9] || chip->w341[10];
    chip->w342[5] = chip->w341[12] || chip->w341[14];
    chip->w342[6] = chip->w341[16];
    chip->w342[7] = chip->w341[17] || chip->w341[18];
    chip->w342[8] = chip->w341[1] || chip->w341[13] || chip->w341[15] || chip->w341[19] || chip->w341[20];
    chip->w342[9] = chip->w341[13] || chip->w341[15] || chip->w341[17] || chip->w341[18] || chip->w341[19]
        || chip->w341[20];
    chip->w342[10] = chip->w341[0] || chip->w341[1] || chip->w341[2] || chip->w341[3] || chip->w341[4]
        || chip->w341[5] || chip->w341[6] || chip->w341[7] || chip->w341[8] || chip->w341[9]
        || chip->w341[10] || chip->w341[11] || chip->w341[12] || chip->w341[13] || chip->w341[14]
        || chip->w341[15] || chip->w341[16] || chip->w341[17] || chip->w341[18] || chip->w341[19]
        || chip->w341[20] || chip->w316;
    chip->w342[11] = chip->w341[11] || chip->w341[12];
    chip->w342[12] = chip->w341[14];

    if (chip->hclk2)
    {
        int i;
        for (i = 0; i < 13; i++)
        {
            chip->w343[i] = chip->w342[i];
        }
    }

    if (chip->hclk1)
    {
        chip->w344[0] = chip->hpla[22];
        chip->w345[0] = chip->hpla[23];
        chip->w346[0] = chip->hpla[24];
        chip->w347[0] = chip->hpla[25];
        chip->w348[0] = chip->hpla[26];
        chip->w349[0] = chip->hpla[27];
        chip->w350[0] = chip->hpla[28];
        chip->w351[0] = chip->hpla[29];
        chip->w352[0] = chip->hpla[30];
        chip->w353[0] = chip->hpla[31];
        chip->w354[0] = chip->hpla[32];
        chip->w355[0] = chip->hpla[33];
        chip->w356[0] = chip->hpla[34];
        chip->w357[0] = chip->hpla[35];
        chip->w358[0] = chip->hpla[36];
        chip->w359[0] = chip->hpla[37];
        chip->w360 = chip->hpla[38];
        chip->w361 = chip->hpla[39];
        chip->w362 = chip->hpla[40];
        chip->w363 = chip->hpla[41];
    }
    if (chip->hclk2)
    {
        chip->w344[1] = chip->w344[0];
        chip->w345[1] = chip->w345[0];
        chip->w346[1] = chip->w346[0];
        chip->w347[1] = chip->w347[0];
        chip->w348[1] = chip->w348[0];
        chip->w349[1] = chip->w349[0];
        chip->w350[1] = chip->w350[0];
        chip->w351[1] = chip->w351[0];
        chip->w352[1] = chip->w352[0];
        chip->w353[1] = chip->w353[0];
        chip->w354[1] = chip->w354[0];
        chip->w355[1] = chip->w355[0];
        chip->w356[1] = chip->w356[0];
        chip->w357[1] = chip->w357[0];
        chip->w358[1] = chip->w358[0];
        chip->w359[1] = chip->w359[0];
        chip->w364 = chip->w360 || chip->w361 || (chip->w362 && !chip->w363);
    }

    chip->w365 = chip->reg_80_b3 ? chip->w367[1] : chip->w356[1];

    if (chip->hclk1)
        chip->w366[0] = chip->w365;
    if (chip->hclk2)
        chip->w366[1] = chip->w366[0];
    
    if (chip->hclk1)
        chip->w367[0] = chip->w372[1];
    if (chip->hclk2)
        chip->w367[1] = chip->w367[0];

    if (chip->hclk1)
    {
        chip->w368[0] = chip->hpla[42];
        chip->w369[0] = chip->hpla[43];
        chip->w370[0] = chip->hpla[44];
        chip->w371[0] = chip->hpla[45];
        chip->w372[0] = chip->hpla[46];
        chip->w373[0] = chip->hpla[47];
        chip->w374[0] = chip->hpla[48];
        chip->w375[0] = chip->hpla[49];
        chip->w376[0] = chip->hpla[50];
        chip->w377[0] = chip->hpla[51];
        chip->w378[0] = chip->hpla[53];
        chip->w379[0] = chip->hpla[52];
        chip->w380[0] = chip->hpla[54];
        chip->w381[0] = chip->hpla[55];
        chip->w382[0] = chip->hpla[56];
    }
    if (chip->hclk2)
    {
        chip->w368[1] = chip->w368[0];
        chip->w369[1] = chip->w369[0];
        chip->w370[1] = chip->w370[0];
        chip->w371[1] = chip->w371[0];
        chip->w372[1] = chip->w372[0];
        chip->w373[1] = chip->w373[0];
        chip->w374[1] = chip->w374[0];
        chip->w375[1] = chip->w375[0];
        chip->w376[1] = chip->w376[0];
        chip->w377[1] = chip->w377[0];
        chip->w378[1] = chip->w378[0];
        chip->w379[1] = chip->w379[0];
        chip->w380[1] = chip->w380[0];
        chip->w381[1] = chip->w381[0];
        chip->w382[1] = chip->w382[0];
    }

    if (chip->w369[1])
        chip->w383 = 1;
    else if (chip->w368[1])
        chip->w383 = 0;

    if (chip->w371[1] && !chip->w334)
        chip->w384 = 1;
    else if (chip->w370[1])
        chip->w384 = 0;

    if (chip->w373[1] && !chip->w334)
        chip->w385 = 1;
    else if (chip->w372[1])
        chip->w385 = 0;

    if (chip->w375[1] || (chip->w374[1] && !chip->w334))
        chip->w386 = 0;
    else if (chip->w376[1] || (!chip->w334 && chip->w377[1] && !chip->reg_80_b5))
        chip->w386 = 1;

    chip->w387 = chip->w386 && chip->reg_81_b6 && chip->w159;

    if (chip->reg_sel[8])
        chip->w388 = chip->reg_addr & 255;
    else if (chip->reset1)
        chip->w388 = 0;

    if (chip->w370[1])
        chip->w389 = chip->w388;

    chip->w390 = chip->w404 ? 0 : chip->w389;

    if (chip->hclk1)
        chip->w391 = (chip->w390 & 7) == (chip->w313 & 7);

    chip->w392 = !(chip->w391 && chip->reg_80_b2);

    if (chip->hclk1)
        chip->w393 = chip->w343[12];

    if (chip->hclk2)
        chip->w394 = chip->w393 && chip->reg_80_b2;

    chip->w395 = chip->w394 ? chip->hclk1 : 0;

    chip->w396 = ((chip->w313 >> 3) + ((chip->w390 >> 3) ^ 31) + 1) & 31;

    if (chip->reg_sel[9])
        chip->w397 = chip->reg_addr & 255;
    else if (chip->reset1)
        chip->w397 = 0;

    if (chip->w403)
        chip->w398 = chip->w397;

    chip->w399 = !(chip->reg_80_b7 && (chip->w313 & 192) == 192);

    if (chip->hclk1)
        chip->w400[0] = chip->w399;
    if (chip->hclk2)
        chip->w400[1] = chip->w400[0];

    chip->w401 = chip->w400[1] ? chip->w398 : 0;

    chip->w402 = (chip->w401 & 255) + (chip->w143 & 255);

    chip->w403 = chip->w370[1] && chip->w160;

    chip->w404 = chip->reg_80_b6 && (chip->w143 & 240) == 0;

    if (chip->hclk1)
        chip->w405[0] = chip->w343[7];
    if (chip->hclk2)
        chip->w405[1] = chip->w405[0];

    chip->w406 = (chip->w431 & 2) == 0 ? ((chip->w402 ^ 7) & 7) : (chip->w402 & 7);

    chip->w407 = !(chip->reg_80_b2 && (chip->w343[6] || chip->w343[7]));

    if (chip->hclk1)
        chip->w408[0] = !chip->w407;
    if (chip->hclk2)
        chip->w408[1] = chip->w408[0];

    chip->w409 = chip->w408[1] ? chip->hclk1 : 0;

    chip->w410 = (chip->w402 & 256) == 0 && (chip->w402 & 224) != 224;

    chip->w411 = ((chip->w402 >> 5) + !chip->w410) & 7;

    if (chip->hclk1)
        chip->w412 = chip->w445;
    chip->w413 = chip->w412 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w414 = chip->w446;
    chip->w415 = chip->w414 ? chip->hclk2 : 0;

    chip->w416 = (chip->w431 & 1) != 0;

    if (chip->hclk2)
        chip->w417 = !chip->w392;

    if (chip->hclk1)
    {
        chip->w418[0] = chip->w417;
        chip->w418[2] = chip->w418[1];
    }
    if (chip->hclk2)
    {
        chip->w418[1] = chip->w418[0];
        chip->w418[3] = chip->w418[2];
    }

    chip->vram_data2 = (chip->vram_data & 255) | ((chip->w2_h & 255) << 8);

    if (chip->w416)
    {
        chip->w419 = chip->vram_data2;
    }
    else
    {
        int i, bit, bit2;
        chip->w419 = 0;
        for (i = 0; i < 8; i++)
        {
            bit = 1 << i;
            bit2 = 128 >> i;
            if (chip->vram_data & bit)
                chip->w419 |= bit2;
            if (chip->w2_h & bit)
                chip->w419 |= bit2 << 8;
        }
    }

    if (chip->w413)
        chip->w420 = chip->w419;

    if (chip->w415)
        chip->w421 = chip->w419;

    if (chip->hclk2)
    {
        chip->w422 = (chip->w424 << 1) & 0xfefe;
        chip->w439 = 0;
        if (chip->w424 & 128)
            chip->w439 |= 1;
        if (chip->w424 & 32768)
            chip->w439 |= 2;
    }

    if (chip->hclk2)
    {
        chip->w423 = (chip->w425 << 1) & 0xfefe;
        chip->w440 = 0;
        if (chip->w425 & 128)
            chip->w440 |= 4;
        if (chip->w425 & 32768)
            chip->w440 |= 8;
    }

    if (chip->hclk1)
        chip->w424 = chip->w417 ? chip->w420 : chip->w422;

    if (chip->hclk1)
        chip->w425 = chip->w418[3] ? chip->w421 : chip->w423;

    if (chip->w415)
        chip->w426 = ((chip->w431 >> 2) & 3) ^ 3;

    if (chip->hclk1)
        chip->w427[0] = chip->w418[3] ? chip->w426 : chip->w427[1];
    if (chip->hclk2)
        chip->w427[1] = chip->w427[0];

    if (chip->hclk1)
        chip->w428 = chip->reg_80_b2 && chip->w364;
    chip->w429 = chip->w428 ? chip->hclk2 : 0;

    if (chip->w429)
    {
        chip->w430 = chip->vram_data2 & 511;
        chip->w431 = ((chip->vram_data2 >> 9) & 15) ^ 15;
    }

    if (chip->hclk1)
        chip->w432 = !(chip->reg_80_b2 && (chip->w343[6] || chip->w343[7]));

    if (chip->hclk2)
        chip->w433 = !chip->w432;
    chip->w434 = chip->w433 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w435[0] = (chip->w427[1] & 1) == 0;
    if (chip->hclk2)
        chip->w435[1] = chip->w435[0];

    chip->w436 = !(chip->w560[3][1] && chip->w435[1]);

    if (chip->hclk1)
        chip->color_palette = chip->w436;

    if (chip->hclk1)
        chip->w437 = chip->w560[3][1];
    chip->w438 = chip->w437 ? chip->hclk2 : 0;

    if (chip->hclk2)
    {
        chip->w438_[0] = chip->w439;
        chip->w438_[2] = chip->w438_[1];
    }
    if (chip->hclk1)
    {
        chip->w438_[1] = chip->w438_[0];
        chip->w438_[3] = chip->w438_[2];
    }

    chip->w441 = chip->w438_[3] | chip->w440;

    if (chip->hclk2)
    {
        chip->w442[0] = chip->w441;
        chip->w442[2] = chip->w442[1];
    }
    if (chip->hclk1)
    {
        chip->w442[1] = chip->w442[0];
        chip->w442[3] = chip->w442[2];
    }

    if (chip->w438)
    {
        chip->color_index = chip->w442[3];
    }

    if (chip->hclk2)
        chip->w443 = chip->w441 == 0;

    chip->w444 = !(chip->w443 || (chip->w427[1] & 2) == 0);

    chip->w445 = chip->reg_80_b2 && chip->w358[1];
    chip->w446 = chip->reg_80_b2 && chip->w359[1];

    if (chip->hclk1)
        chip->w447 = chip->w364;
    chip->w448 = chip->w447 ? chip->hclk2 : 0;

    if (chip->w448)
        chip->w449 = chip->vram_data;
    else if (chip->hclk1)
        chip->w449 = chip->w449;

    if (chip->hclk1)
        chip->w450 = !chip->reg_80_b2 && ((chip->reg_80_b1 && chip->w343[6]) || chip->w343[9]);
    if (chip->hclk2)
        chip->w451 = chip->w450;
    chip->w452 = chip->w451 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w453 = !chip->reg_80_b2 && ((chip->reg_80_b1 && chip->w343[6]) || chip->w343[7] || (!chip->reg_81_b1 && chip->w343[8]));
    if (chip->hclk2)
        chip->w454 = chip->w453;
    chip->w455 = chip->w454 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w456 = !chip->reg_80_b2 && !chip->reg_80_b1 && chip->w343[6];
    if (chip->hclk2)
        chip->w457 = chip->w456;
    chip->w458 = chip->w457 ? chip->hclk1 : 0;

    if (chip->reg_sel[7])
    {
        chip->reg_bc = chip->reg_addr & 15;
        chip->reg_fc = (chip->reg_addr >> 4) & 15;
    }
    else if (chip->reset1)
    {
        chip->reg_bc = 0;
        chip->reg_fc = 0;
    }

    chip->w459 = chip->reg_fc != 0;

    if (chip->hclk1)
        chip->w460 = chip->w560[4][1];
    chip->w461 = chip->w460 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w462 = chip->w560[2][1];
    chip->w463 = chip->w462 ? chip->hclk2 : 0;

    if (chip->w461)
        chip->color_index = chip->reg_bc;

    if (chip->w463)
        chip->color_index = chip->reg_fc;

    chip->w464 = !(chip->w465 || !chip->reg_81_b3);

    chip->w465 = !(chip->reg_81_b6 && chip->w164);

    chip->w466 = !chip->w465;

    chip->w467 = !chip->reg_81_b4 && !chip->w465;

    chip->w468 = !chip->w467;

    chip->w469 = !chip->w465 && chip->reg_81_b4;

    chip->w470 = !chip->reg_80_b2;

    if (chip->hclk1)
        chip->w471 = !(chip->w359[1] && chip->w470);

    chip->w472 = !(chip->w359[1] && chip->w470);


    if (chip->hclk1)
        chip->w473 = !(chip->w472 || chip->w464);


    if (chip->hclk1)
        chip->w474 = !(chip->w472 || !chip->w464);

    chip->w475 = chip->w471 ? chip->hclk2 : 0;
    chip->w476 = chip->w473 ? chip->hclk2 : 0;
    chip->w477 = chip->w474 ? chip->hclk2 : 0;

    if (chip->w476)
        chip->w478 = chip->vram_data;
    else if (chip->w477)
        chip->w478 = 0xf0;
    else if (chip->w475)
        chip->w478 = (chip->w479 << 1) & 254;

    if (chip->hclk1)
        chip->w479 = chip->w478;

    if (chip->hclk2)
        chip->w480 = (chip->w479 & 128) == 0;

    chip->w481 = chip->w93 || chip->w501[3];
    if (chip->hclk1)
        chip->w482 = chip->w481;
    chip->w483 = chip->w482 ? chip->hclk2 : 0;

    if (chip->w483)
    {
        chip->w484 = chip->vram_data2 & 255;
        chip->w485 = (chip->vram_data2 >> 8) & 255;
    }

    if (chip->hclk1)
    {
        chip->w486[0] = chip->w487;
        chip->w486[2] = chip->w486[1];
    }

    if (chip->hclk2)
    {
        chip->w486[1] = chip->w486[0];
        chip->w486[3] = chip->w486[2];
    }

    chip->w487 = chip->w481 && chip->reg_80_b2;

    chip->w488 = chip->w486[3] ? chip->w485 : chip->w484;

    chip->w489 = chip->w488 == 208 && !chip->w505;

    chip->w490 = (chip->w145 & 31) + ((chip->w488 & 31) ^ 31) + 1;

    if (chip->hclk1)
        chip->w491 = (chip->w490 & 32) != 0;

    if (chip->hclk1)
        chip->w492 = (chip->w488 >> 5) & 7;

    if (chip->hclk1)
        chip->w493 = chip->w490 & 31;

    chip->w494 = (((chip->w145 >> 5) & 7) + (chip->w492 ^ 7) + chip->w491) & 7;

    chip->w495 = chip->w494 == 0 && !chip->w506 && (!chip->w497 || (chip->w493 & 16) == 0) && (!chip->w498 || (chip->w493 & 8) == 0);

    if (chip->hclk2)
        chip->w496 = chip->reg_81_b0 ? ((chip->w493 >> 1) & 15) : (chip->w493 & 15);

    chip->w497 = !(chip->reg_81_b0 && chip->reg_81_b1);

    chip->w498 = !(chip->reg_81_b0 || chip->reg_81_b1);

    chip->w499 = (chip->w160 || chip->w159) && chip->w500[1];

    if (chip->hclk1)
        chip->w500[0] = chip->w343[2];
    if (chip->hclk2)
        chip->w500[1] = chip->w500[0];

    if (chip->hclk1)
    {
        chip->w501[0] = chip->w499;
        chip->w501[2] = chip->w501[1];
        chip->w501[4] = chip->w501[3];
    }
    if (chip->hclk2)
    {
        chip->w501[1] = chip->w501[0];
        chip->w501[3] = chip->w501[2];
        chip->w501[5] = chip->w501[4];
    }

    chip->w502 = !chip->w499 && !chip->w501[3];

    chip->w503 = !(chip->w501[5] && chip->reg_80_b2);

    if (chip->hclk1)
        chip->w504[0] = !chip->w503;
    if (chip->hclk2)
        chip->w504[1] = chip->w504[0];

    chip->w505 = !(chip->w504[1] || chip->w501[5]);

    if (chip->hclk1)
        chip->w506 = chip->w505 || !chip->w510;

    if (chip->hclk2)
        chip->w507 = !chip->w495;

    chip->w508 = !chip->w507 && !chip->w123;

    chip->w509 = chip->w123 && !chip->w507;

    if (chip->w512[1] || chip->w520[1])
        chip->w510 = 0;
    else if (chip->w515[1])
        chip->w510 = 1;

    chip->w511 = chip->w509 || !chip->w510 || chip->w502;

    if (chip->hclk1)
        chip->w512[0] = chip->w509;
    if (chip->hclk2)
        chip->w512[1] = chip->w512[0];

    if (chip->w512[1])
        chip->w513 = 0;
    else if (chip->w515[1])
        chip->w513 = 1;

    chip->w514 = !chip->w370[1];

    if (chip->hclk1)
        chip->w515[0] = !chip->w514;
    if (chip->hclk2)
        chip->w515[1] = chip->w515[0];

    chip->w516 = !(chip->w513 || chip->w514);

    chip->w517 = !(chip->w546[1] || (chip->w94 && !chip->reg_80_b2));

    chip->w518 = chip->w517;

    chip->w519 = chip->w518 && !chip->w508;

    if (chip->hclk1)
        chip->w520[0] = chip->w489;
    if (chip->hclk2)
        chip->w520[1] = chip->w520[0];

    if (chip->hclk1)
    {
        chip->w521[0] = chip->w481;
        chip->w521[2] = chip->w521[1];
    }
    if (chip->hclk2)
    {
        chip->w521[1] = chip->w521[0];
        chip->w521[3] = chip->w521[2];
    }

    if (chip->hclk1)
        chip->w522[0] = chip->w521[3] ? chip->w496 : chip->w522[1];
    if (chip->hclk2)
        chip->w522[1] = chip->w522[0];

    chip->w523 = !(!chip->reg_80_b2 && chip->w343[8]);

    if (chip->hclk1)
        chip->w524[0] = !chip->w523;
    if (chip->hclk2)
        chip->w524[1] = chip->w524[0];
    chip->w525 = chip->w524[1] ? chip->hclk1 : 0;

    chip->w526 = !(!chip->reg_80_b2 && chip->w343[8] && chip->reg_81_b1);

    if (chip->hclk1)
        chip->w527[0] = !chip->w526;
    if (chip->hclk2)
        chip->w527[1] = chip->w527[0];
    chip->w528 = chip->w527[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w529 = chip->w511;

    if (chip->hclk2)
        chip->w530[0] = chip->w529 ? chip->w530[1] : chip->w535;
    if (chip->hclk1)
        chip->w530[1] = chip->w530[0];

    if (chip->hclk2)
        chip->w531[0] = chip->w529 ? chip->w531[1] : chip->w530[1];
    if (chip->hclk1)
        chip->w531[1] = chip->w531[0];

    chip->w532 = chip->w531[1];
    chip->w533 = chip->w531[0];

    chip->w534 = chip->reg_80_b2 ? ((chip->vram_address >> 1) & 31) : ((chip->vram_address >> 2) & 31);

    if (chip->hclk1)
        chip->w535 = chip->w534;

    chip->w536 = !(chip->reg_80_b2 && (chip->w343[3] || chip->w343[8]));

    if (chip->hclk1)
        chip->w537[0] = chip->w548 ? 0 : ((chip->w537[1] + !chip->w536) & 3);
    if (chip->hclk2)
        chip->w537[1] = chip->w537[0];

    if (chip->hclk1)
        chip->w538 = chip->w545[1] || chip->w545[2];
    if (chip->hclk2)
        chip->w539 = chip->w538;

    chip->w540 = chip->w539 ? chip->hclk1 : 0;

    chip->w541 = !(chip->w545[3] || (chip->w343[4] && !chip->w343[3]));

    if (chip->hclk1)
        chip->w542 = !chip->w541;

    chip->w543 = !chip->w545[3];

    if (chip->hclk1)
        chip->w544 = !chip->w543;

    chip->w545[0] = !chip->w536 && (chip->w537[1] & 2) != 0;
    chip->w545[1] = !chip->w536 && (chip->w537[1] & 2) != 0;
    chip->w545[2] = !chip->w536 && (chip->w537[1] & 1) != 0;
    chip->w545[3] = !chip->w536 && (chip->w537[1] & 3) == 0;
    chip->w545[4] = !chip->w536 && (chip->w537[1] & 1) != 0 && !chip->w120;

    if (chip->hclk1)
        chip->w546[0] = chip->w545[0];
    if (chip->hclk2)
        chip->w546[1] = chip->w546[0];

    if (chip->hclk1)
    {
        chip->w547[0] = chip->w370[1];
        chip->w547[2] = chip->w547[1];
    }
    if (chip->hclk2)
    {
        chip->w547[1] = chip->w547[0];
        chip->w547[3] = chip->w547[2];
    }

    chip->w548 = !(!chip->w547[3] && !chip->w545[0]);

    if (chip->hclk1)
        chip->w549[0] = chip->w547[3] ? 0 : ((chip->w549[1] + chip->w545[0]) & 7);
    if (chip->hclk2)
        chip->w549[1] = chip->w549[0];

    chip->w550[0] = chip->w549[1] == 0 && chip->w545[4];
    chip->w550[1] = chip->w549[1] == 1 && chip->w545[4];
    chip->w550[2] = chip->w549[1] == 2 && chip->w545[4];
    chip->w550[3] = chip->w549[1] == 3 && chip->w545[4];
    chip->w550[4] = chip->w549[1] == 4 && chip->w545[4];
    chip->w550[5] = chip->w549[1] == 5 && chip->w545[4];
    chip->w550[6] = chip->w549[1] == 6 && chip->w545[4];
    chip->w550[7] = chip->w549[1] == 7 && chip->w545[4];

    if (chip->hclk1)
    {
        int i;
        for (i = 0; i < 8; i++)
            chip->w551[i][0] = chip->w550[i];
        for (i = 0; i < 8; i++)
        {
            chip->w553[i][0] = chip->w551[i][1];
            chip->w553[i][2] = chip->w553[i][1];
        }
    }
    if (chip->hclk2)
    {
        int i;
        for (i = 0; i < 8; i++)
            chip->w551[i][1] = chip->w551[i][0];
        for (i = 0; i < 8; i++)
        {
            chip->w553[i][1] = chip->w553[i][0];
            chip->w553[i][3] = chip->w553[i][2];
        }
    }

    chip->w552[0] = chip->w551[0][1] || chip->w355[1];
    chip->w552[1] = chip->w551[1][1] || chip->w352[1];
    chip->w552[2] = chip->w551[2][1] || chip->w349[1];
    chip->w552[3] = chip->w551[3][1] || chip->w346[1];

    chip->w554[0] = chip->w553[0][3] || chip->w353[1];
    chip->w554[1] = chip->w553[1][3] || chip->w350[1];
    chip->w554[2] = chip->w553[2][3] || chip->w347[1];
    chip->w554[3] = chip->w553[3][3] || chip->w344[1];

    chip->w555[0] = !chip->w302 && !chip->w283 && !chip->w480 && !chip->w469 && !chip->w557[1] && !chip->reg_80_b2;
    chip->w555[1] = !chip->w302 && !chip->w282 && chip->w480 && !chip->w469 && !chip->w557[1] && !chip->reg_80_b2;
    chip->w555[2] = !chip->w302 && chip->w459 && !chip->w480 && chip->w469 && !chip->w557[1] && !chip->reg_80_b2;
    chip->w555[3] = !chip->w302 && !chip->w557[1] && chip->reg_80_b2;

    chip->w556 = !chip->w387;

    if (chip->hclk1)
        chip->w557[0] = chip->w556;
    if (chip->hclk2)
        chip->w557[1] = chip->w557[0];

    chip->w558 = !chip->w302 && !chip->w555[0] && !chip->w555[1] && !chip->w555[2] && !chip->w555[3];

    chip->w559 = chip->w557[1];

    if (chip->hclk1)
    {
        chip->w560[0][0] = chip->w555[0];
        chip->w560[1][0] = chip->w555[1];
        chip->w560[2][0] = chip->w555[2];
        chip->w560[3][0] = chip->w555[3];
        chip->w560[4][0] = chip->w558;
    }
    if (chip->hclk2)
    {
        chip->w560[0][1] = chip->w560[0][0];
        chip->w560[1][1] = chip->w560[1][0];
        chip->w560[2][1] = chip->w560[2][0];
        chip->w560[3][1] = chip->w560[3][0];
        chip->w560[4][1] = chip->w560[4][0];
    }

    chip->sprite1[0].i1 = chip->w354[1];
    chip->sprite1[1].i1 = chip->w351[1];
    chip->sprite1[2].i1 = chip->w348[1];
    chip->sprite1[3].i1 = chip->w345[1];
    chip->sprite1[0].i2 = (chip->w303[1] & 1) != 0;
    chip->sprite1[1].i2 = (chip->w303[1] & 2) != 0;
    chip->sprite1[2].i2 = (chip->w303[1] & 4) != 0;
    chip->sprite1[3].i2 = (chip->w303[1] & 8) != 0;
    chip->sprite1[0].i3 = chip->w552[0];
    chip->sprite1[1].i3 = chip->w552[1];
    chip->sprite1[2].i3 = chip->w552[2];
    chip->sprite1[3].i3 = chip->w552[3];
    chip->sprite1[0].i4 = chip->w554[0];
    chip->sprite1[1].i4 = chip->w554[1];
    chip->sprite1[2].i4 = chip->w554[2];
    chip->sprite1[3].i4 = chip->w554[3];

    chip->w588 = !(chip->reg_81_b1 && !chip->reg_80_b2);

    VDPSMS_ClockSprite1(chip, &chip->sprite1[0]);
    VDPSMS_ClockSprite1(chip, &chip->sprite1[1]);
    VDPSMS_ClockSprite1(chip, &chip->sprite1[2]);
    VDPSMS_ClockSprite1(chip, &chip->sprite1[3]);

    chip->sprite2[0].i1 = chip->w551[4][1];
    chip->sprite2[1].i1 = chip->w551[5][1];
    chip->sprite2[2].i1 = chip->w551[6][1];
    chip->sprite2[3].i1 = chip->w551[7][1];
    chip->sprite2[0].i2 = chip->w553[4][3];
    chip->sprite2[1].i2 = chip->w553[5][3];
    chip->sprite2[2].i2 = chip->w553[6][3];
    chip->sprite2[3].i2 = chip->w553[7][3];
    chip->sprite2[0].i3 = (chip->w303[1] & 16) != 0;
    chip->sprite2[1].i3 = (chip->w303[1] & 32) != 0;
    chip->sprite2[2].i3 = (chip->w303[1] & 64) != 0;
    chip->sprite2[3].i3 = (chip->w303[1] & 128) != 0;

    VDPSMS_ClockSprite2(chip, &chip->sprite2[0]);
    VDPSMS_ClockSprite2(chip, &chip->sprite2[1]);
    VDPSMS_ClockSprite2(chip, &chip->sprite2[2]);
    VDPSMS_ClockSprite2(chip, &chip->sprite2[3]);

    if (chip->sprite1[0].w564)
        chip->color_index = chip->sprite1[0].w568;
    if (chip->sprite1[0].w606)
        chip->color_index = chip->sprite1[0].w639[2];
    if (chip->sprite1[1].w564)
        chip->color_index = chip->sprite1[1].w568;
    if (chip->sprite1[1].w606)
        chip->color_index = chip->sprite1[1].w639[2];
    if (chip->sprite1[2].w564)
        chip->color_index = chip->sprite1[2].w568;
    if (chip->sprite1[2].w606)
        chip->color_index = chip->sprite1[2].w639[2];
    if (chip->sprite1[3].w564)
        chip->color_index = chip->sprite1[3].w568;
    if (chip->sprite1[3].w606)
        chip->color_index = chip->sprite1[3].w639[2];
    if (chip->sprite2[0].w638)
        chip->color_index = chip->sprite2[0].w637[2];
    if (chip->sprite2[1].w638)
        chip->color_index = chip->sprite2[1].w637[2];
    if (chip->sprite2[2].w638)
        chip->color_index = chip->sprite2[2].w637[2];
    if (chip->sprite2[3].w638)
        chip->color_index = chip->sprite2[3].w637[2];

    if (chip->hclk2)
        chip->w641 = (chip->color_palette << 4) | chip->color_index;

    chip->w642 = chip->w209;
    chip->w643 = !chip->w642 && !chip->w385 && !chip->w156;
    chip->w644 = !chip->w642 && !chip->w643;

    if (chip->w642)
        chip->w645 = chip->reg_addr & 31;
    else if (chip->w643)
        chip->w645 = chip->w641;
    else if (chip->w644)
        chip->w645 = (chip->w313 >> 1) & 15;

    if (chip->hclk1)
        chip->color_ram_index = chip->w645;

    if (chip->hclk2)
        chip->w646[0] = chip->vram_data & 63;
    if (chip->hclk1)
        chip->w646[1] = chip->w646[0];

    if (chip->hclk1)
        chip->w649 = !chip->w209;

    //chip->w647 = !chip->hclk1 && (chip->color_ram_index & 16) == 0 && !chip->w649;
    //chip->w648 = !chip->hclk1 && (chip->color_ram_index & 16) != 0 && !chip->w649;
    chip->color_ram_write = !chip->w649;

    if (chip->hclk2)
    {
        if (chip->color_ram_write)
            chip->color_ram[chip->color_ram_index] = chip->w646[1];

        chip->w650 = chip->color_ram[chip->color_ram_index] & 63;
    }

    chip->w651 = chip->reg_80_b2 ? chip->w650 : 0;

    if (chip->hclk2)
        chip->w652[0] = chip->color_index;
    if (chip->hclk1)
        chip->w652[1] = chip->w652[0];

    chip->w653 = chip->reg_80_b2 ? 0 : chip->w652[1];

    chip->w654 = chip->w652[1] != 0;

    if (chip->hclk1)
        chip->w655 = chip->w385 || chip->w156;

    if (chip->hclk2)
        chip->w656 = chip->w654 || chip->w655;

    if (chip->hclk2)
        chip->w657[0] = chip->w655;
    if (chip->hclk1)
        chip->w657[1] = chip->w657[0];

    if (chip->hclk1)
        chip->w658 = !(chip->w384 || chip->w151);

    if (chip->hclk1)
        chip->w659 = !(chip->w156 || !chip->w383);

    if (chip->hclk2)
        chip->w660 = chip->w653;

    if (chip->hclk1)
        chip->w661 = chip->w651 | tms_color[chip->w660 & 15];

    chip->w662 = chip->w657[1] ? 0 : chip->w661;

    if (chip->hclk2)
        chip->dac_sel = chip->w662;

    chip->o_dac_r = dac_lut_rg[(chip->dac_sel >> 0) & 3];
    chip->o_dac_g = dac_lut_rg[(chip->dac_sel >> 2) & 3];
    chip->o_dac_b = dac_lut_b[(chip->dac_sel >> 4) & 3];

#if 0
    chip->o_dac_r /= 2;
    chip->o_dac_g /= 2;
    chip->o_dac_b /= 2;
    //chip->o_dac_b |= chip->w343[2] && (chip->w160 || chip->w159) ? 255 : 0;
    //chip->o_dac_b |= chip->w483 ? 255 : 0;

    if (chip->w83) // hack
        chip->o_dac_b = (chip->vram_address & 62) << 2;
    else
        chip->o_dac_b = 0;
    chip->o_dac_g |= !chip->w529 ? 255 : 0;
    chip->o_dac_r |= chip->w108 ? 255 : 0;
    if (chip->w108)
        chip->o_dac_r = chip->w126[1] << 3;
    else
        chip->o_dac_r = 0;
#endif

    chip->psg.input.i_clk = chip->zclk;
    chip->psg.input.i_reset = chip->input.reset;
    chip->psg.input.i_write = !(chip->cpu_wr || chip->cpu_iorq || chip->cpu_a7 || !chip->cpu_a6);
    chip->psg.input.i_data = chip->io_data;
    SMSVDP_ClockPSG(&chip->psg);

    if (chip->hclk2)
        chip->w751[0] = chip->w658;
    if (chip->hclk1)
        chip->w751[1] = chip->w751[0];

    if (chip->hclk1)
        chip->w752 = chip->reg_80_b0;

    if (chip->hclk2)
        chip->w753 = !(chip->w751[1] || chip->w752);

    chip->o_csync = chip->w753 ? 0 : state_z;

    if (chip->hclk2)
        chip->w754[0] = chip->w659;
    if (chip->hclk1)
        chip->w754[1] = chip->w754[0];

    if (chip->hclk2)
    {
        chip->w755[0] = chip->w754[1];
        chip->w755[2] = chip->w755[1];
        chip->w755[4] = chip->w755[3];
        chip->w755[6] = chip->w755[5];
    }
    if (chip->hclk1)
    {
        chip->w755[1] = chip->w754[0];
        chip->w755[3] = chip->w755[2];
        chip->w755[5] = chip->w755[4];
        chip->w755[7] = chip->w755[6];
    }

    if (chip->hclk2)
        chip->w756 = chip->w754[1];

    chip->o_cbt = !chip->w756;

    if (chip->hclk2)
        chip->w757 = chip->w755[7];

    chip->o_pcp = !chip->w757;

    if (!chip->input.reset)
    {
        chip->nmi_dff[0] = 0;
        chip->nmi_dff[1] = 0;
    }
    else
    {
        if (!chip->w160)
            chip->nmi_dff[0] = !chip->input.nmi;
        else
            chip->nmi_dff[1] = chip->nmi_dff[0];
    }
    
    chip->o_nmi = !chip->nmi_dff[1];

    chip->o_kbsel = !(!chip->input.iorq && chip->input.a6 && chip->input.a7);
    chip->o_csram = !(!chip->input.mreq && chip->input.a14 && chip->input.a15);
    chip->o_exm1 = !(!chip->input.mreq && !chip->input.a14 && chip->input.a15);
    chip->o_exm2 = !(!chip->input.mreq && !chip->input.a15);

    if (chip->hclk1)
        chip->w758[0] = chip->w656;
    if (chip->hclk2)
        chip->w758[1] = chip->w758[0];

    chip->o_ys = chip->w758[1];


    if (chip->w55[1])
        chip->w759 = 0;
    else if (chip->w263)
        chip->w759 = 1;

    chip->w760 = !(chip->w256 && (chip->w759 || !chip->reg_80_b4));

    chip->o_int = !chip->w760;

    chip->w761 = chip->w166 && chip->w164_;

    if (chip->w761)
    {
        chip->io_data = chip->input.data & 255;
        chip->o_data_z = 1;
    }
    else
    {
        chip->o_data = chip->io_data & 255;
        chip->o_data_z = 0;
    }

    VDPSMS_VRAMAddressCalc(chip);
}

static inline void vram_calc(int *update, int *value, int mask, int uvalue)
{
    *update |= mask;
    *value &= (uvalue & mask) | (~mask);
}

static void VDPSMS_VRAMAddressCalc(vdpsms_t *chip)
{
    int update = 0;
    int value = 0x3fff;
    if (chip->hclk2)
        vram_calc(&update, &value, 0x3fff, 0x3fff);
    if (chip->w42)
        vram_calc(&update, &value, 0x1fc0, (chip->w3 & 254) << 5);
    if (chip->w40)
        vram_calc(&update, &value, 0x20, (chip->w3 & 1) << 5);
    if (chip->w83)
        vram_calc(&update, &value, 0xfe, ((chip->w63 << 1) & 0x3e) | ((chip->w67 << 6) & 0xc0));
    if (chip->w97)
        vram_calc(&update, &value, 0x7c, (chip->w63 << 2) & 0x7c);
    if (chip->w88)
        vram_calc(&update, &value, 0x380, (chip->w63 << 2) & 0x380);
    if (chip->w105)
        vram_calc(&update, &value, 0x3, chip->w90[1] & 3);
    if (chip->w103)
        vram_calc(&update, &value, 0x3, 0x0);
    if (chip->w107)
        vram_calc(&update, &value, 0x1c, (chip->w117[0] & 7) << 2);
    if (chip->w125)
        vram_calc(&update, &value, 0x20, (chip->w117[0] & 8) << 2);
    if (chip->w140)
        vram_calc(&update, &value, 0x7c, (chip->w131[0] & 0x3e) << 1);
    if (chip->w137)
        vram_calc(&update, &value, 0x7e, (chip->w135[0] & 0x3f) << 1);
    if (chip->w237)
        vram_calc(&update, &value, 0x3ff, ((chip->w313 >> 3) & 0x1f) | (((chip->w145 >> 3) & 0x1f) << 5));
    if (chip->w243)
        vram_calc(&update, &value, 0x1800, ((chip->w145 >> 6) & 3) << 11);
    if (chip->w234)
        vram_calc(&update, &value, 0x1807, (((chip->w145 >> 6) & 3) << 11) | (chip->w145 & 7));
    if (chip->w249)
        vram_calc(&update, &value, 0x7, (chip->w145 >> 2) & 7);
    if (chip->w246)
        vram_calc(&update, &value, 0x7, chip->w145 & 7);
    if (chip->w226)
        vram_calc(&update, &value, 0x3c00, chip->reg_nt << 10);
    if (chip->w219)
        vram_calc(&update, &value, 0x3fc0, chip->reg_ct << 6);
    if (chip->w224)
        vram_calc(&update, &value, 0x3800, chip->reg_bg << 11);
    if (chip->w222)
        vram_calc(&update, &value, 0x3f80, chip->reg_sat << 7);
    if (chip->w229)
        vram_calc(&update, &value, 0x3800, chip->reg_spr << 11);
    if (chip->w231)
        vram_calc(&update, &value, 0x3fff, chip->reg_addr);
    if (chip->w395)
        vram_calc(&update, &value, 0x7fe, ((chip->w396 & 31) << 1) | (((chip->w402 >> 3) & 3) << 6) | ((chip->w411 & 7) << 8));
    if (chip->w409)
        vram_calc(&update, &value, 0x1e, ((chip->w406 << 1) | chip->w405[1]) << 1);
    if (chip->w434)
        vram_calc(&update, &value, 0x3fe0, chip->w430 << 5);
    if (chip->w458)
        vram_calc(&update, &value, 0x3f, (chip->w449 >> 3) & 31);
    if (chip->w452)
        vram_calc(&update, &value, 0x7e0, (chip->w449 << 3) & 0x7e0);
    if (chip->w455)
        vram_calc(&update, &value, 0x18, (chip->w449 << 3) & 0x18);
    if (chip->w525)
        vram_calc(&update, &value, 0x7, chip->w522[0] & 7);
    if (chip->w528)
        vram_calc(&update, &value, 0x18, (chip->w522[0] & 8) | (((chip->w313 & 2) ^ 2) << 3));
    if (chip->w540)
        vram_calc(&update, &value, 0x2, (chip->w537[1] & 2) ^ 2);

    chip->vram_address &= ~update;
    chip->vram_address |= value & update;
}

static void VDPSMS_ClockSprite1(vdpsms_t *chip, vdpsms_spriteunit1_t *spr)
{
    if (chip->hclk1)
        spr->w561 = spr->i1;
    spr->w562 = spr->w561 ? chip->hclk2 : 0;

    if (chip->hclk1)
        spr->w563 = spr->w567;
    spr->w564 = spr->w563 ? chip->hclk2 : 0;

    spr->w565 = spr->w568 == 0;

    spr->w566 = spr->w565 && !chip->reg_80_b2;

    spr->w567 = spr->i2 && !chip->reg_80_b2;

    if (spr->w562)
        spr->w568 = chip->vram_data & 15;
    else if (chip->hclk1)
        spr->w568 = spr->w568;

    if (spr->w562)
        spr->w569 = (chip->vram_data & 128) != 0;
    else if (chip->hclk1)
        spr->w569 = spr->w569;

    if (spr->i3)
        spr->w570 = 0;
    else if ((spr->w569 && chip->w297) || chip->w366[1])
        spr->w570 = 1;

    if (chip->hclk1)
        spr->w571 = spr->w570 && spr->w577[0] == 255;

    if (spr->w571)
        spr->w572 = 0;
    else if (spr->w573)
        spr->w572 = 1;

    if (chip->hclk1)
        spr->w573 = spr->i3;

    spr->w574 = !((chip->reg_81_b0 && spr->w578) || spr->w572);

    if (chip->hclk1)
        spr->w575 = spr->w570;

    spr->w576 = (spr->w577[1] + spr->w575) & 255;

    if (chip->hclk2)
        spr->w577[0] = spr->w573 ? (chip->vram_data ^ 255) : spr->w576;
    if (chip->hclk1)
        spr->w577[1] = spr->w577[0];

    if (chip->hclk1)
        spr->w578 = (spr->w577[0] & 1) == 0;

    spr->w579 = !spr->i4;

    if (chip->hclk1)
    {
        spr->w580[0] = spr->w579;
        spr->w580[2] = spr->w580[1];
    }
    if (chip->hclk2)
    {
        spr->w580[1] = spr->w580[0];
        spr->w580[3] = spr->w580[2];
    }

    if (chip->hclk1)
        spr->w581 = !spr->w580[3];

    spr->w582 = spr->w574;

    if (chip->hclk1)
        spr->w583 = !spr->w579;

    spr->w584 = !(spr->w581 || spr->w582);
    spr->w585 = !(spr->w581 || !spr->w582);
    spr->w586 = !(spr->w583 || spr->w582);
    spr->w587 = !(spr->w583 || !spr->w582);

    spr->w589 = !(chip->w588 || spr->w602);

    if (spr->w583)
        spr->w590 = chip->vram_data & 255;
    else if (spr->w587)
        spr->w590 = ((spr->w591[1] << 1) | spr->w589) & 511;
    else if (spr->w586)
        spr->w590 = spr->w591[1];

    if (chip->hclk2)
        spr->w591[0] = spr->w590;
    if (chip->hclk1)
        spr->w591[1] = spr->w591[0];

    spr->w594 = (spr->w591[0] & 256) == 0;

    if (spr->w581)
        spr->w592 = chip->vram_data & 255;
    else if (spr->w585)
        spr->w592 = (spr->w593[1] << 1) & 511;
    else if (spr->w584)
        spr->w592 = spr->w593[1];

    if (chip->hclk2)
        spr->w593[0] = spr->w592;
    if (chip->hclk1)
        spr->w593[1] = spr->w593[0];

    spr->w595 = (spr->w593[0] & 256) == 0;

    if (spr->w583)
        spr->w596 = (chip->vram_data2 >> 8) & 255;
    else if (spr->w587)
        spr->w596 = (spr->w597[1] << 1) & 511;
    else if (spr->w586)
        spr->w596 = spr->w597[1];

    if (chip->hclk2)
        spr->w597[0] = spr->w596;
    if (chip->hclk1)
        spr->w597[1] = spr->w597[0];

    spr->w600 = (spr->w597[0] & 256) == 0;

    if (spr->w581)
        spr->w598 = (chip->vram_data2 >> 8) & 255;
    else if (spr->w585)
        spr->w598 = (spr->w599[1] << 1) & 511;
    else if (spr->w584)
        spr->w598 = spr->w599[1];

    if (chip->hclk2)
        spr->w599[0] = spr->w598;
    if (chip->hclk1)
        spr->w599[1] = spr->w599[0];

    spr->w601 = (spr->w599[0] & 256) == 0;

    if (chip->hclk1)
        spr->w602 = (spr->w593[0] & 128) == 0;

    spr->w603 = chip->reg_80_b2 ? ((!spr->w594) + (!spr->w600) * 2 + (!spr->w595) * 4 + (!spr->w601) * 8)
        : !spr->w594;

    if (chip->hclk1)
    {
        spr->w639[0] = spr->w603;
        spr->w639[2] = spr->w639[1];
    }
    if (chip->hclk2)
        spr->w639[1] = spr->w639[0];

    spr->w604 = spr->w603 == 0;

    if (chip->hclk1)
        spr->w605 = !(!chip->reg_80_b2 || !spr->i2);
    spr->w606 = spr->w605 ? chip->hclk2 : 0;
}

static void VDPSMS_ClockSprite2(vdpsms_t *chip, vdpsms_spriteunit2_t *spr)
{
    if (spr->i1)
        spr->w607 = 0;
    else if (chip->w366[1])
        spr->w607 = 1;

    if (chip->hclk1)
        spr->w608 = !spr->w607;

    if (chip->hclk1)
        spr->w609 = spr->w607 && spr->w612[0] == 255;

    if (spr->w609)
        spr->w610 = 0;
    else if (spr->w611)
        spr->w610 = 1;

    if (chip->hclk1)
        spr->w611 = spr->i1;

    spr->w613 = (spr->w612[1] + !spr->w608) & 255;

    if (chip->hclk2)
        spr->w612[0] = spr->w611 ? (chip->vram_data ^ 255) : spr->w613;
    if (chip->hclk1)
        spr->w612[1] = spr->w612[0];

    spr->w614 = !spr->i2;

    if (chip->hclk1)
    {
        spr->w615[0] = spr->w614;
        spr->w615[2] = spr->w615[1];
    }
    if (chip->hclk2)
    {
        spr->w615[1] = spr->w615[0];
        spr->w615[3] = spr->w615[2];
    }

    if (chip->hclk1)
        spr->w616 = !spr->w614;

    if (chip->hclk1)
        spr->w617 = !spr->w615[3];

    spr->w618 = spr->w610;

    spr->w619 = !(!spr->w618 || spr->w616);
    spr->w620 = !(spr->w618 || spr->w616);
    spr->w621 = !(!spr->w618 || spr->w617);
    spr->w622 = !(spr->w618 || spr->w617);

    if (spr->w616)
        spr->w623 = chip->vram_data & 255;
    else if (spr->w620)
        spr->w623 = (spr->w624[1] << 1) & 511;
    else if (spr->w619)
        spr->w623 = spr->w624[1];

    if (chip->hclk2)
        spr->w624[0] = spr->w623;
    if (chip->hclk1)
        spr->w624[1] = spr->w624[0];

    spr->w625 = (spr->w624[0] & 256) == 0;

    if (spr->w617)
        spr->w626 = chip->vram_data & 255;
    else if (spr->w622)
        spr->w626 = (spr->w627[1] << 1) & 511;
    else if (spr->w621)
        spr->w626 = spr->w627[1];

    if (chip->hclk2)
        spr->w627[0] = spr->w626;
    if (chip->hclk1)
        spr->w627[1] = spr->w627[0];

    spr->w628 = (spr->w627[0] & 256) == 0;

    if (spr->w616)
        spr->w629 = (chip->vram_data2 >> 8) & 255;
    else if (spr->w620)
        spr->w629 = (spr->w630[1] << 1) & 511;
    else if (spr->w619)
        spr->w629 = spr->w630[1];

    if (chip->hclk2)
        spr->w630[0] = spr->w629;
    if (chip->hclk1)
        spr->w630[1] = spr->w630[0];

    spr->w631 = (spr->w630[0] & 256) == 0;

    if (spr->w617)
        spr->w632 = (chip->vram_data2 >> 8) & 255;
    else if (spr->w622)
        spr->w632 = (spr->w633[1] << 1) & 511;
    else if (spr->w621)
        spr->w632 = spr->w633[1];

    if (chip->hclk2)
        spr->w633[0] = spr->w632;
    if (chip->hclk1)
        spr->w633[1] = spr->w633[0];

    spr->w634 = (spr->w633[0] & 256) == 0;

    spr->w635 = (!spr->w625) + (!spr->w631) * 2 + (!spr->w628) * 4 + (!spr->w634) * 8;

    spr->w636 = spr->w635 == 0;

    if (chip->hclk1)
    {
        spr->w637[0] = spr->w635;
        spr->w637[2] = spr->w637[1];
    }
    if (chip->hclk2)
        spr->w637[1] = spr->w637[0];

    if (chip->hclk1)
        spr->w640 = spr->i3;
    spr->w638 = spr->w640 ? chip->hclk2 : 0;
}

const float ympsg_vol[16] = {
    1.f, 0.785f, 0.612f, 0.482f, 0.4f, 0.316f, 0.248f, 0.197f, 0.164f, 0.131f, 0.103f, 0.083f, 0.069f, 0.056f, 0.045f, 0.f
};

static void SMSVDP_ClockPSG(vdpsms_psg_t *chip)
{
    chip->clk1 = !chip->input.i_clk;
    chip->clk2 = chip->input.i_clk;

    if (chip->clk1)
        chip->w663[0] = chip->input.i_reset;
    if (chip->clk2)
        chip->w663[1] = !chip->w663[0];

    chip->w664 = !chip->w663[1];

    if (chip->clk1)
        chip->w665[0] = chip->w664;
    if (chip->clk2)
        chip->w665[1] = !chip->w665[0];

    chip->w666 = !(chip->w665[1] || chip->w664);

    if (chip->clk1)
        chip->w667[0] = !(chip->w666 || chip->w667[1]);
    if (chip->clk2)
        chip->w667[1] = chip->w667[0];

    if (chip->clk1)
        chip->w668[0] = !(chip->w666 ? 0 : (chip->w668[1] ^ chip->w667[1]));
    if (chip->clk2)
        chip->w668[1] = !chip->w668[0];

    if (chip->clk2)
        chip->w669 = !chip->w668[0];

    chip->hclk1 = chip->w668[0] && !chip->w669;
    chip->hclk2 = !chip->w668[0] && chip->w669;

    if (chip->input.i_write)
        chip->w670 = 0;
    else if (chip->w672[1])
        chip->w670 = 1;

    chip->w671 = !(chip->w670 || chip->input.i_write);

    if (chip->clk1)
        chip->w672[0] = chip->w671;
    if (chip->clk2)
        chip->w672[1] = chip->w672[0];

    if (chip->clk1)
        chip->w673[0] = chip->w672[1];
    if (chip->clk2)
        chip->w673[1] = chip->w673[0];

    if (chip->input.i_write)
    {
        //printf("PSG %x\n", chip->input.i_data & 255);
        chip->data_latch = chip->input.i_data & 255;
    }

    chip->w674 = chip->w672[1] && (chip->data_latch & 128) != 0;

    if (chip->w674)
        chip->w675 = (chip->data_latch >> 4) & 7;

    chip->w676 = chip->w673[1] && chip->w675 == 0 && (chip->data_latch & 128) != 0;
    chip->w677 = chip->w673[1] && chip->w675 == 2 && (chip->data_latch & 128) != 0;
    chip->w678 = chip->w673[1] && chip->w675 == 4 && (chip->data_latch & 128) != 0;
    chip->w679 = chip->w673[1] && chip->w675 == 4 && (chip->data_latch & 128) == 0;
    chip->w680 = chip->w673[1] && chip->w675 == 2 && (chip->data_latch & 128) == 0;
    chip->w681 = chip->w673[1] && chip->w675 == 0 && (chip->data_latch & 128) == 0;
    chip->w682 = chip->w673[1] && chip->w675 == 1;
    chip->w683 = chip->w673[1] && chip->w675 == 3;
    chip->w684 = chip->w673[1] && chip->w675 == 5;
    chip->w685 = chip->w673[1] && chip->w675 == 7;
    chip->w686 = chip->w673[1] && chip->w675 == 6;

    if (chip->w686)
        chip->w687 = chip->data_latch & 7;
    else if (chip->w663[1])
        chip->w687 = 0;

    if (chip->w663[1])
        chip->w688 = 0;
    else
    {
        if (chip->w676)
        {
            chip->w688 &= ~15;
            chip->w688 |= chip->data_latch & 15;
        }
        if (chip->w681)
        {
            chip->w688 &= ~1008;
            chip->w688 |= (chip->data_latch << 4) & 1008;
        }
    }

    if (chip->w663[1])
        chip->w689 = 0;
    else
    {
        if (chip->w677)
        {
            chip->w689 &= ~15;
            chip->w689 |= chip->data_latch & 15;
        }
        if (chip->w680)
        {
            chip->w689 &= ~1008;
            chip->w689 |= (chip->data_latch << 4) & 1008;
        }
    }

    if (chip->w663[1])
        chip->w690 = 0;
    else
    {
        if (chip->w678)
        {
            chip->w690 &= ~15;
            chip->w690 |= chip->data_latch & 15;
        }
        if (chip->w679)
        {
            chip->w690 &= ~1008;
            chip->w690 |= (chip->data_latch << 4) & 1008;
        }
    }

    chip->w691 = 0;
    if (chip->w700[1])
        chip->w691 |= chip->w688;
    if (chip->w701[1])
        chip->w691 |= chip->w689;
    if (chip->w702[1])
        chip->w691 |= chip->w690;
    if (chip->w703[1])
    {
        if ((chip->w687 & 3) == 0)
            chip->w691 |= 16;
        if ((chip->w687 & 3) == 1)
            chip->w691 |= 32;
        if ((chip->w687 & 3) == 2)
            chip->w691 |= 64;
    }

    if (chip->hclk1)
        chip->w692 = chip->w691;

    chip->w693 = chip->w692 <= chip->w698[0];
    
    if (chip->hclk1)
    {
        chip->w694[0] = chip->w709 ? 0 : chip->w698[1];
        chip->w695[0] = chip->w694[1];
        chip->w696[0] = chip->w695[1];
        chip->w698[0] = chip->w697;
    }
    if (chip->hclk2)
    {
        chip->w694[1] = chip->w694[0];
        chip->w695[1] = chip->w695[0];
        chip->w696[1] = chip->w696[0];
        chip->w698[1] = chip->w698[0];
    }

    chip->w697 = (chip->w696[1] + 1) & 1023;

    chip->w699 = !(chip->w663[1] || chip->w700[1] || chip->w701[1] || chip->w702[1]);

    if (chip->hclk1)
    {
        chip->w700[0] = chip->w699;
        chip->w701[0] = chip->w700[1];
        chip->w702[0] = chip->w701[1];
        chip->w703[0] = chip->w702[1];
    }
    if (chip->hclk2)
    {
        chip->w700[1] = chip->w700[0];
        chip->w701[1] = chip->w701[0];
        chip->w702[1] = chip->w702[0];
        chip->w703[1] = chip->w703[0];
    }

    if (chip->hclk2)
        chip->w704[0] = (chip->w704[1] << 1) | chip->w693;
    if (chip->hclk1)
        chip->w704[1] = chip->w704[0];

    if (chip->hclk1)
        chip->w705 = chip->w700[1];

    chip->w706 = chip->w705 ? (chip->w704[1] & 15) : 0;

    if (chip->hclk2)
        chip->w707[0] = (chip->w708[2] ? 0 : (chip->w707[1] ^ chip->w706)) ^ 15;
    if (chip->hclk1)
        chip->w707[1] = chip->w707[0] ^ 15;

    if (chip->hclk1)
    {
        chip->w708[0] = chip->w663[1];
        chip->w708[2] = chip->w708[1];
    }
    if (chip->hclk2)
        chip->w708[1] = chip->w708[0];

    if (chip->hclk2)
        chip->w709 = chip->w708[2] || chip->w693;

    if (chip->hclk1)
        chip->w710[0] = chip->w711;
    if (chip->hclk2)
        chip->w710[1] = chip->w710[0];

    if (chip->w712)
    {
        chip->noise_lfsr[0] = 0;
        chip->noise_lfsr[1] = 0;
    }
    else if (chip->w710[1])
        chip->noise_lfsr[0] = (chip->noise_lfsr[1] << 1) | chip->w713;
    else
        chip->noise_lfsr[1] = chip->noise_lfsr[0];

    chip->w711 = !((chip->w687 & 3) == 3 ? (chip->w707[0] & 2) == 0 : (chip->w707[0] & 1) == 0);

    chip->w712 = chip->w663[1] || chip->w686;

    chip->w714 = ((chip->noise_lfsr[1] >> 15) ^ (chip->noise_lfsr[1] >> 12)) & 1;

    chip->w713 = chip->w712 ? 0 : ((chip->noise_lfsr[1] & 0x7fff) == 0 ||
        ((chip->w687 & 4) != 0 && chip->w714));

    if (chip->w663[1])
    {
        chip->w715 = 15;
        chip->w716 = 15;
        chip->w717 = 15;
        chip->w718 = 15;
    }
    else
    {
        if (chip->w682)
            chip->w715 = chip->data_latch & 15;
        if (chip->w683)
            chip->w716 = chip->data_latch & 15;
        if (chip->w684)
            chip->w717 = chip->data_latch & 15;
        if (chip->w685)
            chip->w718 = chip->data_latch & 15;
    }

    chip->w719 = (chip->w707[0] & 8) != 0 ? 15 : chip->w715;
    chip->w720 = (chip->w707[0] & 4) != 0 ? 15 : chip->w716;
    chip->w721 = (chip->w707[0] & 2) != 0 ? 15 : chip->w717;
    chip->w722 = (chip->noise_lfsr[1] & 0x4000) != 0 ? chip->w718 : 15;

    chip->dac[0] = ympsg_vol[chip->w719];
    chip->dac[1] = ympsg_vol[chip->w720];
    chip->dac[2] = ympsg_vol[chip->w721];
    chip->dac[3] = ympsg_vol[chip->w722];

    chip->o_dac = chip->dac[0] + chip->dac[1] + chip->dac[2] + chip->dac[3];
}

void VDPSMS_Clock2(vdpsms_t *chip)
{
    if (!memcmp(&chip->input, &chip->o_input, sizeof(vdpsms_input_t)))
        return;

    chip->o_input = chip->input;

    VDPSMS_Clock(chip);
    VDPSMS_Clock(chip);
    VDPSMS_Clock(chip);
    //VDPSMS_Clock(chip);
    //VDPSMS_Clock(chip);
}
