// 315-5216 core

#include "io_smsu.h"

static void IO_SMSU_UpdateDFFS(int *reg, int set, int value, int clk)
{
    if (!set)
    {
        reg[0] = reg[1] = 1;
    }
    else
    {
        if (!clk)
            reg[0] = value;
        else
            reg[1] = reg[0];
    }
}

static void IO_SMSU_UpdateDFFR(int *reg, int reset, int value, int clk)
{
    if (!reset)
    {
        reg[0] = reg[1] = 0;
    }
    else
    {
        if (!clk)
            reg[0] = value;
        else
            reg[1] = reg[0];
    }
}

// 1 - input, 0 - output

void IO_SMSU_Clock(io_smsu_t *chip)
{
    int iorq = chip->input.killga || chip->input.iorq;

    int sel0 = iorq || !(chip->input.a6 && chip->input.a7);
    int sel1 = iorq || !(!chip->input.a6 && !chip->input.a7);
    int port_read = !(sel0 || chip->input.rd);
    int write0 = !(sel1 || chip->input.wr || chip->input.a0);
    int write1 = !(sel1 || chip->input.wr || !chip->input.a0);

    int reset = chip->input.reset; // FIXME

    chip->o_data_dir = !(port_read && !chip->reg_3e_2[1]);

    int data = chip->o_data_dir ? chip->input.data : chip->o_data;

    IO_SMSU_UpdateDFFR(chip->reg_3e_2, reset, (data & 4) != 0, write0);
    IO_SMSU_UpdateDFFR(chip->reg_3e_3, reset, (data & 8) != 0, write0);
    IO_SMSU_UpdateDFFR(chip->reg_3e_4, reset, (data & 16) != 0, write0);
    IO_SMSU_UpdateDFFS(chip->reg_3e_5, reset, (data & 32) != 0, write0);
    IO_SMSU_UpdateDFFS(chip->reg_3e_6, reset, (data & 64) != 0, write0);
    IO_SMSU_UpdateDFFS(chip->reg_3e_7, reset, (data & 128) != 0, write0);

    IO_SMSU_UpdateDFFS(chip->reg_3f_0, reset, (data & 1) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_1, reset, (data & 2) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_2, reset, (data & 4) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_3, reset, (data & 8) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_4, reset, (data & 16) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_5, reset, (data & 32) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_6, reset, (data & 64) != 0, write1);
    IO_SMSU_UpdateDFFS(chip->reg_3f_7, reset, (data & 128) != 0, write1);

    chip->o_port_a_d = (PORT_BUTTON_TR | PORT_BUTTON_TH) ^ 0x7f;
    chip->o_port_b_d = (PORT_BUTTON_TR | PORT_BUTTON_TH) ^ 0x7f;
    if (chip->reg_3f_0[1])
        chip->o_port_a_d |= PORT_BUTTON_TR;
    if (chip->reg_3f_1[1])
        chip->o_port_a_d |= PORT_BUTTON_TH;
    if (chip->reg_3f_2[1])
        chip->o_port_b_d |= PORT_BUTTON_TR;
    if (chip->reg_3f_3[1])
        chip->o_port_b_d |= PORT_BUTTON_TH;

    chip->o_port_a = 0;
    chip->o_port_b = 0;
    if (chip->reg_3f_0[1] ? (chip->input.port_a & PORT_BUTTON_TR) != 0 : chip->reg_3f_4[1])
        chip->o_port_a |= PORT_BUTTON_TR;
    if (chip->reg_3f_1[1] ? (chip->input.port_a & PORT_BUTTON_TH) != 0 : chip->reg_3f_5[1])
        chip->o_port_a |= PORT_BUTTON_TH;
    if (chip->reg_3f_2[1] ? (chip->input.port_b & PORT_BUTTON_TR) != 0 : chip->reg_3f_6[1])
        chip->o_port_b |= PORT_BUTTON_TR;
    if (chip->reg_3f_3[1] ? (chip->input.port_b & PORT_BUTTON_TH) != 0 : chip->reg_3f_7[1])
        chip->o_port_b |= PORT_BUTTON_TH;

    chip->o_data = 0;

    if (!chip->input.a0)
    {
        if (chip->input.port_b & PORT_BUTTON_LEFT)
            chip->o_data |= 1;
        if (chip->input.port_b & PORT_BUTTON_RIGHT)
            chip->o_data |= 2;
        if (chip->input.port_b & PORT_BUTTON_TL)
            chip->o_data |= 4;
        if (chip->o_port_b & PORT_BUTTON_TR)
            chip->o_data |= 8;
        if (chip->input.cont2)
            chip->o_data |= 16;
        if (chip->input.cont1)
            chip->o_data |= 32;
        if (chip->o_port_a & PORT_BUTTON_TH)
            chip->o_data |= 64;
        if (chip->o_port_b & PORT_BUTTON_TH)
            chip->o_data |= 128;
    }
    else
    {
        if (chip->input.port_a & PORT_BUTTON_UP)
            chip->o_data |= 1;
        if (chip->input.port_a & PORT_BUTTON_DOWN)
            chip->o_data |= 2;
        if (chip->input.port_a & PORT_BUTTON_LEFT)
            chip->o_data |= 4;
        if (chip->input.port_a & PORT_BUTTON_RIGHT)
            chip->o_data |= 8;
        if (chip->input.port_a & PORT_BUTTON_TL)
            chip->o_data |= 16;
        if (chip->o_port_a & PORT_BUTTON_TR)
            chip->o_data |= 32;
        if (chip->input.port_b & PORT_BUTTON_UP)
            chip->o_data |= 64;
        if (chip->input.port_b & PORT_BUTTON_DOWN)
            chip->o_data |= 128;
    }

    int port_a_irq = !(chip->o_port_a & PORT_BUTTON_TH) && chip->reg_3f_1[1];
    int port_b_irq = !(chip->o_port_b & PORT_BUTTON_TH) && chip->reg_3f_3[1];

    chip->o_hl = !(port_a_irq || port_b_irq);

    chip->o_ce0 = chip->input.mreq || chip->reg_3e_3[1];
    chip->o_ce1 = chip->input.csram || chip->reg_3e_4[1];
    chip->o_ce2 = chip->input.mreq || chip->reg_3e_5[1];
    chip->o_ce3 = chip->input.mreq || chip->reg_3e_6[1];
    chip->o_ce4 = chip->input.mreq || chip->reg_3e_7[1];
}
