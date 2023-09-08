#pragma once

typedef struct {
    int ad_i;

} vdpsms_input_t;

typedef struct {
    vdpsms_input_t input;

    int ad_o;
    int ad_o_z;

    int w1;
    int w2_h;
    int w2_l;
    int w3;
    int w4;
    int w5;
    int w6;
    int w7;

    int vram_data;
    int vram_address;

    int clk1;
    int clk2;

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
