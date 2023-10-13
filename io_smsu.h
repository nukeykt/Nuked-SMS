#pragma once

#define PORT_BUTTON_UP      1
#define PORT_BUTTON_DOWN    2
#define PORT_BUTTON_LEFT    4
#define PORT_BUTTON_RIGHT   8
#define PORT_BUTTON_TR      16
#define PORT_BUTTON_TL      32
#define PORT_BUTTON_TH      64

typedef struct {
    int data;
    int a0;
    int a6;
    int a7;
    int wr;
    int rd;
    int iorq;
    int mreq;
    int cont1;
    int cont2;
    int killga;
    int csram;
    int reset;
    int port_a;
    int port_b;
} io_smsu_input_t;

typedef struct {
    io_smsu_input_t input;
    io_smsu_input_t o_input;

    int reg_3e_2[2];
    int reg_3e_3[2];
    int reg_3e_4[2];
    int reg_3e_5[2];
    int reg_3e_6[2];
    int reg_3e_7[2];
    int reg_3f_0[2];
    int reg_3f_1[2];
    int reg_3f_2[2];
    int reg_3f_3[2];
    int reg_3f_4[2];
    int reg_3f_5[2];
    int reg_3f_6[2];
    int reg_3f_7[2];

    int o_data;
    int o_data_dir;
    int o_ce0;
    int o_ce1;
    int o_ce2;
    int o_ce3;
    int o_ce4;
    int o_port_a;
    int o_port_a_d;
    int o_port_b;
    int o_port_b_d;
    int o_hl;
} io_smsu_t;

void IO_SMSU_Clock2(io_smsu_t *chip);
