// YM2602 core

#include "vdp_sms.h"

void VDPSMS_Clock(vdpsms_t *chip, int clk)
{
    if (chip->hclk2)
        chip->w1 = chip->input.ad_i;
    if (chip->hclk1)
    {
        chip->w2_h = (chip->w1 >> 8) & 255;
        chip->w2_l = (chip->w1 >> 0) & 255;
    }
    if (chip->w32)
        chip->vram_data = w2_h;
    if (chip->w34)
        chip->vram_data = w2_l;

    if (chip->w25)
        chip->w3 = (chip->input.ad_i >> 8) & 255;
    if (chip->w42)
    {
        chip->vram_address &= ~0x1fc0;
        chip->vram_address |= (w3 & 254) << 5;
    }
    if (chip->w40)
    {
        chip->vram_address &= ~0x20;
        chip->vram_address |= (w3 & 1) << 5;
    }

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
        chip->w16 = !chip->tm_w1;

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
        chip->w22[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w22[1] = chip->w22[0];

    chip->w23 = !(chip->tm_w1 || chip->w22[1]);

    if (chip->hclk1)
        chip->w24 = !chip->w23;

    chip->w25 = chip->w27[1] ? chip->hclk2 : 0;

    if (chip->hclk2)
        chip->w26[0] = chip->tm_w1;
    if (chip->hclk1)
        chip->w26[1] = chip->w26[0];
    if (chip->hclk2)
        chip->w27[0] = chip->w26[1];
    if (chip->hclk1)
        chip->w27[1] = chip->w27[0];

    if (chip->w30)
        chip->w28 = chip->vram_address & 1;

    if (chip->hclk1)
        chip->w29[0] = !chip->tm_w1;
    if (chip->hclk2)
        chip->w29[1] = chip->w29[0];

    chip->w30 = chip->w29[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w31 = !chip->w35[2] && chip->tm_w2;

    chip->w32 = chip->w31 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w33 = chip->w35[2] && chip->tm_w2;

    chip->w34 = chip->w33 ? chip->hclk2 : 0;

    if (chip->hclk2)
    {
        chip->w35[0] = !(chip->w28 && chip->w38[1]);
        chip->w35[2] = chip->w35[1];
    }
    if (chip->hclk1)
        chip->w35[1] = chip->w35[0];

    if (chip->hclk1)
        chip->w36 = !chip->tm_w1;

    chip->w37 = !(chip->w36 || !chip->tm_w1);

    if (chip->hclk2)
        chip->w38[0] = !chip->w37;
    if (chip->hclk1)
        chip->w38[1] = chip->w38[0];

    if (chip->hclk2)
        chip->w39 = chip->tm_w1 && !chip->tm_w2;
    chip->w40 = chip->w39 ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w41 = chip->tm_w1;
    chip->w42 = chip->w41 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w43[0] = chip->tm_w1;
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

    if (chip->tm_w1)
        chip->reg_hit = 0;
    else if (!chip->tm_w2)
        chip->reg_hit = (chip->reg_addr & 255) ^ 255;

    chip->w49 = (chip->w53 ? chip->reg_hit : chip->w51) ^ 255;

    if (chip->hclk1)
        chip->w50 = chip->w49;
    if (chip->hclk2)
        chip->w51 = ((chip->w50 ^ 255) + !chip->w54) & 255;

    chip->w52 = !(chip->tm_w1 || chip->tm_w2);

    chip->w53 = chip->w52 || chip->w55[1];

    if (chip->hclk1)
        chip->w54 = !chip->tm_w1;

    if (chip->hclk1)
        chip->w55[0] = chip->w56;
    if (chip->hclk2)
        chip->w55[1] = chip->w55[0];

    chip->w56 = !(chip->w52 || !chip->tm_w1 || chip->w49 != 0);

    if (chip->hclk1)
        chip->w57 = !chip->tm_w1;
    if (chip->hclk2)
        chip->w58 = chip->w57;

    chip->w59 = chip->w58 ? chip->hclk1 : 0;

    if (chip->w59)
        chip->w60 = chip->tm_w1 & 255;
    else if (chip->hclk2)
        chip->w60 = chip->w60;

    if (!chip->tm_w2)
    {
        chip->cpu_data = chip->tm_w1 ? chip->w60 : chip->tm_w3;
    }

    if (chip->hclk1)
        chip->w62 = (chip->tm_w3 || chip->tm_w4) ? 0 : ((chip->w63 + chip->tm_w1) & 255);
    if (chip->hclk2)
        chip->w63 = chip->w62 | (chip->w65 & chip->w66);

    if (chip->tm_w1)
        chip->w64 = chip->w63;

    if (chip->hclk1)
        chip->w65 = chip->w64;
    if (chip->hclk1)
        chip->w66 = chip->tm_w1 ? 255 : 0;

    if (chip->tm_w1)
    {
        chip->vram_address &= ~0x3e;
        chip->vram_address |= (chip->w63 << 1) & 0x3e;
    }
    if (chip->tm_w2)
    {
        chip->vram_address &= ~0x7c;
        chip->vram_address |= (chip->w63 << 2) & 0x7c;
    }
    if (chip->tm_w3)
    {
        chip->vram_address &= ~0x380;
        chip->vram_address |= (chip->w63 << 2) & 0x380;
    }
}
