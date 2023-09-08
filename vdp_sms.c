// YM2602 core

#include "vdp_sms.h"

void VDPSMS_Clock(vdpsms_t *chip, int clk)
{
    if (chip->clk2)
        chip->w1 = chip->input.ad_i;
    if (chip->clk1)
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

    if (chip->clk2)
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
        chip->ad_o_z = 1;
    }
    else
    {
        chip->ad_o_z = 0;
        chip->ad_o = chip->w7;
    }
}
