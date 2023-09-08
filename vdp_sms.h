#pragma once

typedef struct {
    int ad_i;

} vdpsms_input_t;

typedef struct {
    vdpsms_input_t input;

    int o_ad;
    int o_ad_z;
    int o_oe;
    int o_we0;
    int o_we1;
    int o_ce;

    int w1;
    int w2_h;
    int w2_l;
    int w3;
    int w4;
    int w5;
    int w6;
    int w7;
    int w8;
    int w9;
    int w10;
    int w11;
    int w12;
    int w13;
    int w14;
    int w15;
    int w16;
    int w17;
    int w18;
    int w19;
    int w20;
    int w21;
    int w22[2];
    int w23;
    int w24;

    int vram_data;
    int vram_address;

    int clk1;
    int clk2;

    int hclk1;
    int hclk2;

    int tm_w1;
    int tm_w2;
    int tm_w3;
    int tm_w4;
    int tm_w5;
    int tm_w6;
    int tm_w7;
    int tm_w8;
    int tm_w9;
} vdpsms_t;
