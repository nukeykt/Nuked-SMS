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
    if (chip->tm_w1)
        chip->vram_data = w2_h;
    if (chip->tm_w2)
        chip->vram_data = w2_l;

    if (chip->tm_w1)
        chip->w3 = (chip->input.ad_i >> 8) & 255;
    if (chip->tm_w2)
    {
        chip->vram_address &= ~0x1fc0;
        chip->vram_address |= (w3 & 254) << 5;
    }
    if (chip->tm_w3)
    {
        chip->vram_address &= ~0x20;
        chip->vram_address |= (w3 & 1) << 5;
    }

    if (chip->hclk2)
        chip->w4 = (chip->vram_data & 255) | ((chip->vram_data & 255) << 8);
    if (chip->tm_w1)
        chip->w5 = chip->w4;

    if (chip->tm_w1)
        chip->w6 = (chip->vram_address >> 1) & 0x1fff;

    if (chip->tm_w1)
        chip->w7 = chip->w5;
    if (chip->tm_w2)
        chip->w7 = chip->w6;

    if (chip->tm_w1)
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
        chip->w12 = chip->tm_w1;

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
}
