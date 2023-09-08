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
    int w25;
    int w26[2];
    int w27[2];
    int w28;
    int w29[2];
    int w30;
    int w31;
    int w32;
    int w33;
    int w34;
    int w35[3];
    int w36;
    int w37;
    int w38[2];
    int w39;
    int w40;
    int w41;
    int w42;
    int w43[2];
    int w44[2];
    int w45;
    int w46;
    int w47;
    int w48;
    int reg_hit;
    int w49;
    int w50;
    int w51;
    int w52;
    int w53;
    int w54;
    int w55[2];
    int w56;
    int w57;
    int w58;
    int w59;
    int w60;
    int w61;
    int w62;
    int w63;
    int w64;
    int w65;
    int w66;

    int reg_addr;

    int vram_data;
    int vram_address;

    int cpu_data;

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
