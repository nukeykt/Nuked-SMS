#include <stdio.h>
#include <string.h>
#include "fm_opll.h"

enum {
    fmopll_patch_1 = 0x00,
    fmopll_patch_2,
    fmopll_patch_3,
    fmopll_patch_4,
    fmopll_patch_5,
    fmopll_patch_6,
    fmopll_patch_7,
    fmopll_patch_8,
    fmopll_patch_9,
    fmopll_patch_10,
    fmopll_patch_11,
    fmopll_patch_12,
    fmopll_patch_13,
    fmopll_patch_14,
    fmopll_patch_15,
    fmopll_patch_drum_0,
    fmopll_patch_drum_1,
    fmopll_patch_drum_2,
    fmopll_patch_drum_3,
    fmopll_patch_drum_4,
    fmopll_patch_drum_5,
    fmopll_patch_max
};

#if 1
static const fmopll_patch_t fmopll_patch_ym2413[fmopll_patch_max] = {
    { 0x1e, 0x01, 0x00, 0x07,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x0d, 0x07 },{ 0x00, 0x08 },{ 0x00, 0x01 },{ 0x00, 0x07 } },
    { 0x1a, 0x00, 0x01, 0x05,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x03, 0x01 },{ 0x00, 0x00 },{ 0x0d, 0x0f },{ 0x08, 0x07 },{ 0x02, 0x01 },{ 0x03, 0x03 } },
    { 0x19, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x03, 0x01 },{ 0x02, 0x00 },{ 0x0f, 0x0c },{ 0x02, 0x04 },{ 0x01, 0x02 },{ 0x01, 0x03 } },
    { 0x0e, 0x00, 0x00, 0x07,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x06 },{ 0x08, 0x04 },{ 0x07, 0x02 },{ 0x00, 0x07 } },
    { 0x1e, 0x00, 0x00, 0x06,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x02, 0x01 },{ 0x00, 0x00 },{ 0x0e, 0x07 },{ 0x00, 0x06 },{ 0x00, 0x02 },{ 0x00, 0x08 } },
    { 0x16, 0x00, 0x00, 0x05,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x02 },{ 0x00, 0x00 },{ 0x0e, 0x07 },{ 0x00, 0x01 },{ 0x00, 0x01 },{ 0x00, 0x08 } },
    { 0x1d, 0x00, 0x00, 0x07,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x08, 0x08 },{ 0x02, 0x01 },{ 0x01, 0x00 },{ 0x00, 0x07 } },
    { 0x2d, 0x01, 0x00, 0x04,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x03, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x07 },{ 0x02, 0x02 },{ 0x00, 0x00 },{ 0x00, 0x07 } },
    { 0x1b, 0x00, 0x00, 0x06,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x06, 0x06 },{ 0x04, 0x05 },{ 0x01, 0x01 },{ 0x00, 0x07 } },
    { 0x0b, 0x01, 0x01, 0x00,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x08, 0x0f },{ 0x05, 0x07 },{ 0x07, 0x00 },{ 0x01, 0x07 } },
    { 0x03, 0x01, 0x00, 0x01,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x03, 0x01 },{ 0x02, 0x00 },{ 0x0f, 0x0e },{ 0x0a, 0x04 },{ 0x01, 0x00 },{ 0x00, 0x04 } },
    { 0x24, 0x00, 0x00, 0x07,{ 0x00, 0x01 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x07, 0x01 },{ 0x00, 0x00 },{ 0x0f, 0x0f },{ 0x08, 0x08 },{ 0x02, 0x01 },{ 0x02, 0x02 } },
    { 0x0c, 0x00, 0x00, 0x05,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x0c, 0x0f },{ 0x02, 0x05 },{ 0x02, 0x04 },{ 0x00, 0x02 } },
    { 0x15, 0x00, 0x00, 0x03,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x0c, 0x09 },{ 0x09, 0x05 },{ 0x00, 0x00 },{ 0x03, 0x02 } },
    { 0x09, 0x00, 0x00, 0x03,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x02, 0x00 },{ 0x0f, 0x0e },{ 0x01, 0x04 },{ 0x04, 0x01 },{ 0x00, 0x03 } },

    { 0x18, 0x00, 0x01, 0x07,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x0d, 0x00 },{ 0x0f, 0x00 },{ 0x06, 0x00 },{ 0x0a, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x0c, 0x00 },{ 0x08, 0x00 },{ 0x0a, 0x00 },{ 0x07, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x05, 0x00 },{ 0x00, 0x00 },{ 0x0f, 0x00 },{ 0x08, 0x00 },{ 0x05, 0x00 },{ 0x09, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0f },{ 0x00, 0x08 },{ 0x00, 0x06 },{ 0x00, 0x0d } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0d },{ 0x00, 0x08 },{ 0x00, 0x04 },{ 0x00, 0x08 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0a },{ 0x00, 0x0a },{ 0x00, 0x05 },{ 0x00, 0x05 } }
};
#else
static const fmopll_patch_t fmopll_patch_ym2413[fmopll_patch_max] = {
    { 0x05, 0x00, 0x00, 0x06,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x03, 0x01 },{ 0x00, 0x00 },{ 0x0e, 0x08 },{ 0x08, 0x01 },{ 0x04, 0x02 },{ 0x02, 0x07 } },
    { 0x14, 0x00, 0x01, 0x05,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x03, 0x01 },{ 0x00, 0x00 },{ 0x0d, 0x0f },{ 0x08, 0x06 },{ 0x02, 0x01 },{ 0x03, 0x02 } },
    { 0x08, 0x00, 0x01, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x0f, 0x0b },{ 0x0a, 0x02 },{ 0x02, 0x01 },{ 0x00, 0x02 } },
    { 0x0c, 0x00, 0x00, 0x07,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x06 },{ 0x08, 0x04 },{ 0x06, 0x02 },{ 0x01, 0x07 } },
    { 0x1e, 0x00, 0x00, 0x06,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x02, 0x01 },{ 0x00, 0x00 },{ 0x0e, 0x07 },{ 0x01, 0x06 },{ 0x00, 0x02 },{ 0x01, 0x08 } },
    { 0x06, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x02, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x0e },{ 0x03, 0x02 },{ 0x0f, 0x0f },{ 0x04, 0x04 } },
    { 0x1d, 0x00, 0x00, 0x07,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x08, 0x08 },{ 0x02, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x07 } },
    { 0x22, 0x01, 0x00, 0x07,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x03, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x07 },{ 0x02, 0x02 },{ 0x00, 0x01 },{ 0x01, 0x07 } },
    { 0x25, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x01, 0x01 },{ 0x05, 0x01 },{ 0x00, 0x00 },{ 0x04, 0x07 },{ 0x00, 0x03 },{ 0x07, 0x00 },{ 0x02, 0x01 } },
    { 0x0f, 0x00, 0x01, 0x07,{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x01, 0x00 },{ 0x05, 0x01 },{ 0x00, 0x00 },{ 0x0a, 0x0a },{ 0x08, 0x05 },{ 0x05, 0x00 },{ 0x01, 0x02 } },
    { 0x24, 0x00, 0x00, 0x07,{ 0x00, 0x01 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x07, 0x01 },{ 0x00, 0x00 },{ 0x0f, 0x0f },{ 0x08, 0x08 },{ 0x02, 0x01 },{ 0x02, 0x02 } },
    { 0x11, 0x00, 0x00, 0x06,{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x00 },{ 0x01, 0x03 },{ 0x00, 0x00 },{ 0x06, 0x07 },{ 0x05, 0x04 },{ 0x01, 0x01 },{ 0x08, 0x06 } },
    { 0x13, 0x00, 0x00, 0x05,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x02 },{ 0x03, 0x00 },{ 0x0c, 0x09 },{ 0x09, 0x05 },{ 0x00, 0x00 },{ 0x03, 0x02 } },
    { 0x0c, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x01, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x00 },{ 0x01, 0x03 },{ 0x00, 0x00 },{ 0x09, 0x0c },{ 0x04, 0x00 },{ 0x03, 0x0f },{ 0x03, 0x06 } },
    { 0x0d, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x01, 0x01 },{ 0x00, 0x01 },{ 0x01, 0x02 },{ 0x00, 0x00 },{ 0x0c, 0x0d },{ 0x01, 0x05 },{ 0x05, 0x00 },{ 0x06, 0x06 } },

    { 0x18, 0x00, 0x01, 0x07,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x0d, 0x00 },{ 0x0f, 0x00 },{ 0x06, 0x00 },{ 0x0a, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x01, 0x00 },{ 0x00, 0x00 },{ 0x0c, 0x00 },{ 0x08, 0x00 },{ 0x0a, 0x00 },{ 0x07, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x05, 0x00 },{ 0x00, 0x00 },{ 0x0f, 0x00 },{ 0x08, 0x00 },{ 0x05, 0x00 },{ 0x09, 0x00 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0f },{ 0x00, 0x08 },{ 0x00, 0x06 },{ 0x00, 0x0d } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0d },{ 0x00, 0x08 },{ 0x00, 0x04 },{ 0x00, 0x08 } },
    { 0x00, 0x00, 0x00, 0x00,{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x00 },{ 0x00, 0x01 },{ 0x00, 0x00 },{ 0x00, 0x0a },{ 0x00, 0x0a },{ 0x00, 0x05 },{ 0x00, 0x05 } }
};
#endif


void FMOPLL_Prescaler(fm_opll_t *chip)
{
    if (!chip->mclk)
    {
        chip->ic_latch[0] = chip->ic;
        chip->prescaler_cnt[0] = (chip->prescaler_cnt[1] + 1) & 3;
        if (chip->ic && !chip->ic_latch[1])
        {
            chip->prescaler_cnt[0] = 0;
        }
        chip->clk1_latch[0] = (chip->prescaler_cnt[1] & 3) == 1;
        chip->clk2_latch[0] = (chip->prescaler_cnt[1] & 3) == 3;
        chip->clk1_latch[2] = chip->clk1_latch[1];
        chip->clk2_latch[2] = chip->clk2_latch[1];
        chip->clk_dac_latch = (chip->prescaler_cnt[1] & 3) == 3;
    }
    else
    {
        chip->ic_latch[1] = chip->ic_latch[0];
        chip->prescaler_cnt[1] = chip->prescaler_cnt[0];
        chip->clk1_latch[1] = chip->clk1_latch[0];
        chip->clk2_latch[1] = chip->clk2_latch[0];
        chip->clk_dac = !chip->clk_dac_latch;
    }
    chip->clk1 = chip->clk1_latch[2] || chip->clk1_latch[1];
    chip->clk2 = chip->clk2_latch[2] || chip->clk2_latch[1];
}

void FMOPLL_DoShiftRegisters(fm_opll_t *chip, int sel)
{
    int i, j;
    int to = sel;
    int from = sel ^ 1;
    int rot = sel == 0 ? 1 : 0;
#define CH_ROTATE(x) rot ? ((x << 1) | ((x >> 8) & 1)) : x
    // channel registers

    // fnum
    for (j = 0; j < 9; j++)
        chip->chan_fnum[j][to] = CH_ROTATE(chip->chan_fnum[j][from]);
    // block
    for (j = 0; j < 3; j++)
        chip->chan_block[j][to] = CH_ROTATE(chip->chan_block[j][from]);
    // kon
    chip->chan_kon[to] = CH_ROTATE(chip->chan_kon[from]);
    // son
    chip->chan_son[to] = CH_ROTATE(chip->chan_son[from]);
    // volume
    for (j = 0; j < 4; j++)
        chip->chan_volume[j][to] = CH_ROTATE(chip->chan_volume[j][from]);
    // inst
    for (j = 0; j < 4; j++)
        chip->chan_inst[j][to] = CH_ROTATE(chip->chan_inst[j][from]);
#undef CH_ROTATE
}

void FMOPLL_UpdateRegisters(fm_opll_t* chip)
{
    int i;
    int chan_update;
    int update10 = 0;
    int update20 = 0;
    int update30 = 0;
    if (chip->clk1)
    {
        if (chip->write0)
        {
            for (i = 0; i < 8; i++)
                chip->reg_write[i][0] = chip->data_latch == i;
            chip->reg_write_rhy[0] = chip->data_latch == 0x0e;
            chip->reg_write_test[0] = chip->data_latch == 0x0f;
        }
        else
        {
            for (i = 0; i < 8; i++)
                chip->reg_write[i][0] = chip->reg_write[i][1];
            chip->reg_write_rhy[0] = chip->reg_write_rhy[1];
            chip->reg_write_test[0] = chip->reg_write_test[1];
        }
    }
    if (chip->clk2)
    {
        for (i = 0; i < 8; i++)
            chip->reg_write[i][1] = chip->reg_write[i][0];
        chip->reg_write_rhy[1] = chip->reg_write_rhy[0];
        chip->reg_write_test[1] = chip->reg_write_test[0];
    }
    if (chip->write1 && chip->reg_write[0][1])
    {
        chip->patch.multi[0] = chip->data_latch & 0x0f;
        chip->patch.ksr[0] = (chip->data_latch >> 4) & 0x01;
        chip->patch.et[0] = (chip->data_latch >> 5) & 0x01;
        chip->patch.vib[0] = (chip->data_latch >> 6) & 0x01;
        chip->patch.am[0] = (chip->data_latch >> 7) & 0x01;
    }
    else if (chip->ic)
    {
        chip->patch.multi[0] = 0;
        chip->patch.ksr[0] = 0;
        chip->patch.et[0] = 0;
        chip->patch.vib[0] = 0;
        chip->patch.am[0] = 0;
    }
    if (chip->write1 && chip->reg_write[1][1])
    {
        chip->patch.multi[1] = chip->data_latch & 0x0f;
        chip->patch.ksr[1] = (chip->data_latch >> 4) & 0x01;
        chip->patch.et[1] = (chip->data_latch >> 5) & 0x01;
        chip->patch.vib[1] = (chip->data_latch >> 6) & 0x01;
        chip->patch.am[1] = (chip->data_latch >> 7) & 0x01;
    }
    else if (chip->ic)
    {
        chip->patch.multi[1] = 0;
        chip->patch.ksr[1] = 0;
        chip->patch.et[1] = 0;
        chip->patch.vib[1] = 0;
        chip->patch.am[1] = 0;
    }
    if (chip->write1 && chip->reg_write[2][1])
    {
        chip->patch.ksl[0] = (chip->data_latch >> 6) & 0x03;
        chip->patch.tl = chip->data_latch & 0x3f;
    }
    else if (chip->ic)
    {
        chip->patch.ksl[0] = 0;
        chip->patch.tl = 0;
    }
    if (chip->write1 && chip->reg_write[3][1])
    {
        chip->patch.ksl[1] = (chip->data_latch >> 6) & 0x03;
        chip->patch.dc = (chip->data_latch >> 4) & 0x01;
        chip->patch.dm = (chip->data_latch >> 3) & 0x01;
        chip->patch.fb = chip->data_latch & 0x07;
    }
    else if (chip->ic)
    {
        chip->patch.ksl[1] = 0;
        chip->patch.dc = 0;
        chip->patch.dm = 0;
        chip->patch.fb = 0;
    }
    if (chip->write1 && chip->reg_write[4][1])
    {
        chip->patch.dr[0] = chip->data_latch & 0x0f;
        chip->patch.ar[0] = (chip->data_latch >> 4) & 0x0f;
    }
    else if (chip->ic)
    {
        chip->patch.dr[0] = 0;
        chip->patch.ar[0] = 0;
    }
    if (chip->write1 && chip->reg_write[5][1])
    {
        chip->patch.dr[1] = chip->data_latch & 0x0f;
        chip->patch.ar[1] = (chip->data_latch >> 4) & 0x0f;
    }
    else if (chip->ic)
    {
        chip->patch.dr[1] = 0;
        chip->patch.ar[1] = 0;
    }
    if (chip->write1 && chip->reg_write[6][1])
    {
        chip->patch.rr[0] = chip->data_latch & 0x0f;
        chip->patch.sl[0] = (chip->data_latch >> 4) & 0x0f;
    }
    else if (chip->ic)
    {
        chip->patch.rr[0] = 0;
        chip->patch.sl[0] = 0;
    }
    if (chip->write1 && chip->reg_write[7][1])
    {
        chip->patch.rr[1] = chip->data_latch & 0x0f;
        chip->patch.sl[1] = (chip->data_latch >> 4) & 0x0f;
    }
    else if (chip->ic)
    {
        chip->patch.rr[1] = 0;
        chip->patch.sl[1] = 0;
    }
    if (chip->write1 && chip->reg_write_rhy[1])
    {
        chip->rhythm = (chip->data_latch >> 5) & 0x01;
        chip->rhythm_kon = chip->data_latch & 0x1f;
    }
    else if (chip->ic)
    {
        chip->rhythm = 0;
        chip->rhythm_kon = 0;
    }
    if (chip->write1 && chip->reg_write_test[1])
    {
        chip->testmode = chip->data_latch & 0x0f;
    }
    else if (chip->ic)
    {
        chip->testmode = 0;
    }

    if (chip->write0)
        chip->update_chan_regs = (chip->data_latch & 0xc0) == 0;
    if (chip->write0 && (chip->data_latch & 0xc0) == 0)
        chip->chan_reg_addr = chip->data_latch & 0x3f;
    if (chip->write1 && chip->update_chan_regs)
        chip->chan_data = chip->data_latch;
    else if (chip->ic)
        chip->chan_data = 0;

    if (chip->clk2)
    {
        chip->update_chan_latch[1] = chip->update_chan_latch[0];
        chip->chan_cnt[1] = chip->chan_cnt[0];
    }

    chan_update = chip->update_chan_latch[1] && !chip->ic && !chip->write0;
    if (chip->clk1)
    {
        chip->update_chan_latch[0] = chan_update || (chip->write1 && chip->update_chan_regs);
        if (chip->fsm_out[10])
            chip->chan_cnt[0] = 0;
        else
            chip->chan_cnt[0] = (chip->chan_cnt[1] + 1) & 0x1f;
    }

    if (chip->chan_cnt[1] == (chip->chan_reg_addr & 0x0f) && chan_update)
    {
        update10 = (chip->chan_reg_addr & 0x30) == 0x10;
        update20 = (chip->chan_reg_addr & 0x30) == 0x20;
        update30 = (chip->chan_reg_addr & 0x30) == 0x30;
    }
    if (chip->ic)
    {
        update10 = 1;
        update20 = 1;
        update30 = 1;
    }
    if (chip->clk1)
    {
        FMOPLL_DoShiftRegisters(chip, 0);
        if (update10)
        {
            for (i = 0; i < 8; i++)
            {
                chip->chan_fnum[i][0] &= ~1;
                chip->chan_fnum[i][0] |= (chip->chan_data >> i) & 1;
            }
        }
        if (update20)
        {
            chip->chan_fnum[8][0] &= ~1;
            chip->chan_fnum[8][0] |= chip->chan_data & 1;
            for (i = 0; i < 3; i++)
            {
                chip->chan_block[i][0] &= ~1;
                chip->chan_block[i][0] |= (chip->chan_data >> (i + 1)) & 1;
            }
            chip->chan_kon[0] &= ~1;
            chip->chan_kon[0] |= (chip->chan_data >> 4) & 1;
            //if ((chip->chan_reg_addr & 15) != 4)
            //    chip->chan_kon[0] &= ~1;
            chip->chan_son[0] &= ~1;
            chip->chan_son[0] |= (chip->chan_data >> 5) & 1;
        }
        if (update30)
        {
            for (i = 0; i < 4; i++)
            {
                chip->chan_volume[i][0] &= ~1;
                chip->chan_volume[i][0] |= (chip->chan_data >> i) & 1;
            }
            for (i = 0; i < 4; i++)
            {
                chip->chan_inst[i][0] &= ~1;
                chip->chan_inst[i][0] |= (chip->chan_data >> (i + 4)) & 1;
            }
        }
    }
    if (chip->clk2)
    {
        FMOPLL_DoShiftRegisters(chip, 1);
    }
    chip->fnum = 0;
    chip->block = 0;
    chip->kon = 0;
    chip->son = 0;
    chip->inst = 0;
    chip->volume = 0;
    if (chip->fsm_out[8])
    {
        for (i = 0; i < 9; i++)
        {
            chip->fnum |= ((chip->chan_fnum[i][1] >> 1) & 1) << i;
        }
        for (i = 0; i < 3; i++)
        {
            chip->block |= ((chip->chan_block[i][1] >> 1) & 1) << i;
        }
        chip->kon = (chip->chan_kon[1] >> 1) & 1;
        chip->son = (chip->chan_son[1] >> 1) & 1;
        for (i = 0; i < 4; i++)
        {
            chip->inst |= ((chip->chan_inst[i][1] >> 1) & 1) << i;
        }
        for (i = 0; i < 4; i++)
        {
            chip->volume |= ((chip->chan_volume[i][1] >> 1) & 1) << i;
        }
    }
    if (chip->fsm_out[7])
    {
        for (i = 0; i < 9; i++)
        {
            chip->fnum |= ((chip->chan_fnum[i][1] >> 4) & 1) << i;
        }
        for (i = 0; i < 3; i++)
        {
            chip->block |= ((chip->chan_block[i][1] >> 4) & 1) << i;
        }
        chip->kon = (chip->chan_kon[1] >> 4) & 1;
        chip->son = (chip->chan_son[1] >> 4) & 1;
        for (i = 0; i < 4; i++)
        {
            chip->inst |= ((chip->chan_inst[i][1] >> 4) & 1) << i;
        }
        for (i = 0; i < 4; i++)
        {
            chip->volume |= ((chip->chan_volume[i][1] >> 4) & 1) << i;
        }
    }
    if (chip->fsm_out[12])
    {
        for (i = 0; i < 9; i++)
        {
            chip->fnum |= ((chip->chan_fnum[i][1] >> 7) & 1) << i;
        }
        for (i = 0; i < 3; i++)
        {
            chip->block |= ((chip->chan_block[i][1] >> 7) & 1) << i;
        }
        chip->kon = (chip->chan_kon[1] >> 7) & 1;
        chip->son = (chip->chan_son[1] >> 7) & 1;
        for (i = 0; i < 4; i++)
        {
            chip->inst |= ((chip->chan_inst[i][1] >> 7) & 1) << i;
        }
        for (i = 0; i < 4; i++)
        {
            chip->volume |= ((chip->chan_volume[i][1] >> 7) & 1) << i;
        }
    }
    if (chip->clk1)
    {
        chip->volume_latch1 = chip->volume;
        chip->volume_latch2 = chip->inst;
    }
}

void FMOPLL_UpdateIO(fm_opll_t *chip)
{
    if (!chip->cs && !chip->we && !chip->ic)
    {
        chip->data_latch = chip->in_data & 255;
        if (!chip->a0 && !chip->write0)
            chip->write_sr0 = 1;
        if (chip->write0)
            chip->write_sr0 = 0;
        if (chip->a0 && !chip->write1)
            chip->write_sr1 = 1;
        if (chip->write1)
            chip->write_sr1 = 0;

        if (chip->write0 || chip->write1)
        {
            FMOPLL_UpdateRegisters(chip);
        }
    }
}

void FMOPLL_UpdateIO2(fm_opll_t *chip)
{
    if (chip->write0)
        chip->write_sr0 = 0;
    if (chip->write1)
        chip->write_sr1 = 0;
    if (!chip->mclk)
    {
        chip->write0_latch[0] = chip->write0_latch[0];
        chip->write0_latch[1] = chip->write0_latch[0];

        chip->write1_latch[0] = chip->write1_latch[0];
        chip->write1_latch[1] = chip->write1_latch[0];
    }
    else
    {
        chip->write0_latch[0] = chip->write_sr0;
        chip->write0_latch[2] = chip->write0_latch[1];

        chip->write1_latch[0] = chip->write_sr1;
        chip->write1_latch[2] = chip->write1_latch[1];
    }
    if (chip->clk1)
    {
        chip->write0_latch[3] = chip->write0_latch[3];
        chip->write0_latch[4] = chip->write0_latch[3];

        chip->write1_latch[3] = chip->write1_latch[3];
        chip->write1_latch[4] = chip->write1_latch[3];
    }
    if (chip->clk2)
    {
        chip->write0_latch[3] = chip->write0_latch[2];
        chip->write0 = chip->write0_latch[4];

        chip->write1_latch[3] = chip->write1_latch[2];
        chip->write1 = chip->write1_latch[4];
    }
}

void FMOPLL_FSMTable(fm_opll_t *chip)
{
    int rclk;
    int cnt_comb = (chip->fsm_cnt2[1] << 3) | chip->fsm_cnt1[1];
    chip->fsm_out[3] = !((cnt_comb & 5) == 4 || (cnt_comb & 6) == 2);
    chip->fsm_out[0] = chip->fsm_out[3] && !(chip->rhythm && (chip->fsm_cnt_latch1[1] & 2) != 0);
    chip->fsm_out[1] = chip->fsm_out[3] && !(chip->rhythm && (cnt_comb & 30) == 16);
    chip->fsm_out[2] = !chip->fsm_out[3] && !(chip->rhythm && cnt_comb == 20) && !(chip->rhythm && cnt_comb == 19);
    chip->fsm_out[4] = cnt_comb == 20;
    chip->fsm_out[5] = cnt_comb == 17;
    chip->fsm_out[6] = cnt_comb == 12;
    chip->fsm_out[7] = (chip->fsm_cnt_latch2[1] & 2) != 0;
    chip->fsm_out[12] = (chip->fsm_cnt_latch1[1] & 2) != 0;
    chip->fsm_out[8] = !chip->fsm_out[7] && !chip->fsm_out[12];
    chip->fsm_out[9] = (chip->fsm_cnt_latch2[1] & 4) == 0 && (cnt_comb & 16) == 0;
    // guesswork
    chip->fsm_out[13] = chip->rhythm && (
        (cnt_comb & 28) == 0 ||
        cnt_comb == 4 ||
        (cnt_comb & 30) == 10 ||
        cnt_comb == 19 ||
        (cnt_comb & 30) == 20
        );
    rclk = !chip->rhythm || chip->fsm_out[13];

    chip->rclk1 = rclk && chip->clk1;
    chip->rclk2 = chip->rclk_latch && chip->clk2;

    if (chip->clk1)
    {
        chip->fsm_cnt_latch3[0] = chip->fsm_cnt_latch3[1] << 1;
        chip->fsm_cnt_latch3[0] |= chip->fsm_out[4];
        chip->rclk_latch = rclk;
    }
    if (chip->clk2)
    {
        chip->fsm_cnt_latch3[1] = chip->fsm_cnt_latch3[0];
    }
    chip->fsm_out[10] = (chip->fsm_cnt_latch3[1] & 1) != 0;
    chip->fsm_out[11] = (chip->fsm_cnt_latch3[1] & 2) != 0;
}

void FMOPLL_FSM(fm_opll_t *chip)
{
    int reset;
    int inc = 0;
    if (chip->clk1)
    {
        chip->ic_latch2[0] = chip->ic_latch2[1] << 1;
        chip->ic_latch2[0] |= chip->ic;
        reset = chip->ic && !(chip->ic_latch2[1] & 2);
        inc = (chip->fsm_cnt1[1] & 5) == 5;
        if (inc || reset)
            chip->fsm_cnt1[0] = 0;
        else
            chip->fsm_cnt1[0] = (chip->fsm_cnt1[1] + 1) & 7;
        if ((inc && (chip->fsm_cnt2[0] & 2) == 2) || reset)
            chip->fsm_cnt2[0] = 0;
        else
            chip->fsm_cnt2[0] = (chip->fsm_cnt2[1] + inc) & 3;
        chip->fsm_cnt_latch1[0] = chip->fsm_cnt_latch1[1] << 1;
        chip->fsm_cnt_latch1[0] |= (chip->fsm_cnt2[1] >> 1) & 1;
        chip->fsm_cnt_latch2[0] = chip->fsm_cnt_latch2[1] << 1;
        chip->fsm_cnt_latch2[0] |= chip->fsm_cnt2[1] & 1;
    }
    if (chip->clk2)
    {
        chip->ic_latch2[1] = chip->ic_latch2[0];
        chip->fsm_cnt1[1] = chip->fsm_cnt1[0];
        chip->fsm_cnt2[1] = chip->fsm_cnt2[0];
        chip->fsm_cnt_latch1[1] = chip->fsm_cnt_latch1[0];
        chip->fsm_cnt_latch2[1] = chip->fsm_cnt_latch2[0];
    }
}

void FMOPLL_RhythmCtrl(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        chip->rhythm_sel[0] = chip->rhythm_sel[1] << 1;
        if (!chip->rhythm)
            chip->rhythm_sel[0] &= ~2;
        chip->rhythm_sel[0] |= chip->fsm_out[6];
    }
    if (chip->clk2)
    {
        chip->rhythm_sel[1] = chip->rhythm_sel[0];
    }
}

void FMOPLL_InstrumentCopyPatch(int index, fmopll_patch_cur_t* dest, int modcar)
{
    dest->tl = fmopll_patch_ym2413[index].tl;
    dest->dc = fmopll_patch_ym2413[index].dc;
    dest->dm = fmopll_patch_ym2413[index].dm;
    dest->fb = fmopll_patch_ym2413[index].fb;
    dest->am = fmopll_patch_ym2413[index].am[modcar];
    dest->vib = fmopll_patch_ym2413[index].vib[modcar];
    dest->et = fmopll_patch_ym2413[index].et[modcar];
    dest->ksr = fmopll_patch_ym2413[index].ksr[modcar];
    dest->multi = fmopll_patch_ym2413[index].multi[modcar];
    dest->ksl = fmopll_patch_ym2413[index].ksl[modcar];
    dest->ar = fmopll_patch_ym2413[index].ar[modcar];
    dest->dr = fmopll_patch_ym2413[index].dr[modcar];
    dest->sl = fmopll_patch_ym2413[index].sl[modcar];
    dest->rr = fmopll_patch_ym2413[index].rr[modcar];
}

void FMOPLL_InstrumentCtrl(fm_opll_t *chip)
{
    int is_rhythm = 0;
    int bd0;
    int hh;
    int tom;
    int bd1;
    int sd;
    int tc;
    bd0 = chip->rhythm && (chip->rhythm_sel[1] & 1) != 0;
    hh = (chip->rhythm_sel[1] & 2) != 0;
    tom = (chip->rhythm_sel[1] & 4) != 0;
    bd1 = (chip->rhythm_sel[1] & 8) != 0;
    sd = (chip->rhythm_sel[1] & 16) != 0;
    tc = (chip->rhythm_sel[1] & 32) != 0;
    is_rhythm = bd0 || hh || tom || bd1 || sd || tc;
    if (chip->clk1)
    {
        chip->inst0_sel = !is_rhythm && chip->inst == 0;
        chip->modcar_sel_latch = chip->fsm_out[3];
        chip->kon_latch = chip->kon_comb;
        chip->hh_tom_latch = hh || tom;
        chip->force_zerorate = !chip->hh_tom_latch && !chip->kon_latch && chip->modcar_sel_latch;
    }
    if (chip->clk2)
    {
        memset(&chip->patch_latch[0], 0, sizeof(fmopll_patch_cur_t));
    }
    else
    {
        if (is_rhythm)
        {
            if (bd0)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_0, &chip->patch_latch[0], !chip->fsm_out[3]);
            else if (hh)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_1, &chip->patch_latch[0], !chip->fsm_out[3]);
            else if (tom)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_2, &chip->patch_latch[0], !chip->fsm_out[3]);
            else if (bd1)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_3, &chip->patch_latch[0], !chip->fsm_out[3]);
            else if (sd)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_4, &chip->patch_latch[0], !chip->fsm_out[3]);
            else if (tc)
                FMOPLL_InstrumentCopyPatch(fmopll_patch_drum_5, &chip->patch_latch[0], !chip->fsm_out[3]);
        }
        else if (chip->inst != 0)
            FMOPLL_InstrumentCopyPatch(chip->inst - 1, &chip->patch_latch[0], !chip->fsm_out[3]);
    }

    if (chip->clk1)
        chip->patch_latch[1] = chip->patch_latch[0];

    if (chip->hh_tom_latch)
        chip->patch_cur.tl = chip->volume_latch2 << 2;
    if (!chip->modcar_sel_latch)
        chip->patch_cur.tl = chip->volume_latch1 << 2;
    if (chip->inst0_sel && chip->modcar_sel_latch)
    {
        if (chip->ic && chip->write1 && chip->reg_write[0][1])
        {
            chip->patch_cur.multi &= chip->patch.multi[0];
            chip->patch_cur.vib &= chip->patch.vib[0];
            chip->patch_cur.et &= chip->patch.et[0];
            chip->patch_cur.am &= chip->patch.am[0];
            chip->patch_cur.ksr &= chip->patch.ksr[0];
        }
        else
        {
            chip->patch_cur.multi = chip->patch.multi[0];
            chip->patch_cur.vib = chip->patch.vib[0];
            chip->patch_cur.et = chip->patch.et[0];
            chip->patch_cur.am = chip->patch.am[0];
            chip->patch_cur.ksr = chip->patch.ksr[0];
        }
        if (chip->ic && chip->write1 && chip->reg_write[2][1])
        {
            chip->patch_cur.ksl &= chip->patch.ksl[0];
            chip->patch_cur.tl &= chip->patch.tl;
        }
        else
        {
            chip->patch_cur.ksl = chip->patch.ksl[0];
            chip->patch_cur.tl = chip->patch.tl;
        }
        if (chip->ic && chip->write1 && chip->reg_write[4][1])
        {
            chip->patch_cur.ar &= chip->patch.ar[0];
            chip->patch_cur.dr &= chip->patch.dr[0];
        }
        else
        {
            chip->patch_cur.ar = chip->patch.ar[0];
            chip->patch_cur.dr = chip->patch.dr[0];
        }
        if (chip->ic && chip->write1 && chip->reg_write[6][1])
        {
            chip->patch_cur.sl &= chip->patch.sl[0];
            chip->patch_cur.dr &= chip->patch.dr[0];
        }
        else
        {
            chip->patch_cur.sl = chip->patch.sl[0];
            chip->patch_cur.rr = chip->patch.rr[0];
        }
    }
    if (chip->inst0_sel && !chip->modcar_sel_latch)
    {
        if (chip->ic && chip->write1 && chip->reg_write[1][1])
        {
            chip->patch_cur.multi &= chip->patch.multi[1];
            chip->patch_cur.vib &= chip->patch.vib[1];
            chip->patch_cur.et &= chip->patch.et[1];
            chip->patch_cur.am &= chip->patch.am[1];
            chip->patch_cur.ksr &= chip->patch.ksr[1];
        }
        else
        {
            chip->patch_cur.multi = chip->patch.multi[1];
            chip->patch_cur.vib = chip->patch.vib[1];
            chip->patch_cur.et = chip->patch.et[1];
            chip->patch_cur.am = chip->patch.am[1];
            chip->patch_cur.ksr = chip->patch.ksr[1];
        }
        if (chip->ic && chip->write1 && chip->reg_write[3][1])
        {
            chip->patch_cur.ksl &= chip->patch.ksl[1];
        }
        else
        {
            chip->patch_cur.ksl = chip->patch.ksl[1];
            chip->patch_cur.dc = chip->patch.dc;
            chip->patch_cur.dm = chip->patch.dm;
        }
        if (chip->ic && chip->write1 && chip->reg_write[5][1])
        {
            chip->patch_cur.ar &= chip->patch.ar[1];
            chip->patch_cur.dr &= chip->patch.dr[1];
        }
        else
        {
            chip->patch_cur.ar = chip->patch.ar[1];
            chip->patch_cur.dr = chip->patch.dr[1];
        }
        if (chip->ic && chip->write1 && chip->reg_write[7][1])
        {
            chip->patch_cur.sl &= chip->patch.sl[1];
            chip->patch_cur.dr &= chip->patch.dr[1];
        }
        else
        {
            chip->patch_cur.sl = chip->patch.sl[1];
            chip->patch_cur.rr = chip->patch.rr[1];
        }
    }
    if (chip->inst0_sel)
    {
        if (chip->ic && chip->write1 && chip->reg_write[3][1])
        {
            chip->patch_cur.dc &= chip->patch.dc;
            chip->patch_cur.dm &= chip->patch.dm;
            chip->patch_cur.fb &= chip->patch.fb;
        }
        else
        {
            chip->patch_cur.dc = chip->patch.dc;
            chip->patch_cur.dm = chip->patch.dm;
            chip->patch_cur.fb = chip->patch.fb;
        }
    }
    if (!chip->inst0_sel)
    {
        chip->patch_cur.dc = chip->patch_latch[1].dc;
        chip->patch_cur.dm = chip->patch_latch[1].dm;
        chip->patch_cur.fb = chip->patch_latch[1].fb;
        chip->patch_cur.am = chip->patch_latch[1].am;
        chip->patch_cur.vib = chip->patch_latch[1].vib;
        chip->patch_cur.et = chip->patch_latch[1].et;
        chip->patch_cur.ksr = chip->patch_latch[1].ksr;
        chip->patch_cur.multi = chip->patch_latch[1].multi;
        chip->patch_cur.ksl = chip->patch_latch[1].ksl;
        chip->patch_cur.ar =  chip->patch_latch[1].ar;
        chip->patch_cur.dr =  chip->patch_latch[1].dr;
        chip->patch_cur.sl =  chip->patch_latch[1].sl;
        chip->patch_cur.rr =  chip->patch_latch[1].rr;
    }
    if (!(chip->inst0_sel && chip->modcar_sel_latch) && chip->modcar_sel_latch && !chip->hh_tom_latch)
    {
        chip->patch_cur.tl = chip->patch_latch[1].tl;
    }
}

void FMOPLL_RegistersExtraLatch(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        chip->dc_latch[0] = chip->dc_latch[1];
        chip->dm_latch[0] = chip->dm_latch[1];
    }
    if (chip->clk2)
    {
        chip->multi_latch = chip->patch_cur.multi;
        chip->sl_latch = chip->patch_cur.sl;
        chip->fb_latch = chip->patch_cur.fb;
        chip->tremolo_latch = chip->patch_cur.am;
        chip->vibrato_latch = chip->patch_cur.vib;
        chip->dc_latch[1] = (chip->dc_latch[0] << 1) | chip->patch_cur.dc;
        chip->dm_latch[1] = (chip->dm_latch[0] << 1) | chip->patch_cur.dm;
    }
}

void FMOPLL_Vibrato(fm_opll_t *chip)
{
    int vib_step;
    int vib_val;
    int vib_add;
    int b10;
    chip->trem_step = ((chip->lfo_cnt[1] & 63) + chip->fsm_out[10]) >> 6;
    vib_step = ((chip->lfo_cnt[1] & 1023) + chip->fsm_out[10]) >> 10;
    if (chip->clk1)
    {
        chip->lfo_cnt[0] = chip->lfo_cnt[1] + chip->fsm_out[10];
        if (chip->testmode & 2)
            chip->lfo_cnt[0] = 0;

        chip->vib_cnt[0] = chip->vib_cnt[1];
        if (vib_step || ((chip->testmode & 8) != 0 && chip->fsm_out[10]))
            chip->vib_cnt[0]++;
        if (chip->testmode & 2)
            chip->vib_cnt[0] = 0;
    }
    if (chip->clk2)
    {
        chip->lfo_cnt[1] = chip->lfo_cnt[0];
        chip->vib_cnt[1] = chip->vib_cnt[0];
    }
    
    if (chip->clk1)
    {
        chip->fnum_vib = chip->fnum_latch[1] << 1;
        vib_val = 0;
        vib_add = 0;
        if (chip->vibrato_latch)
        {
            if ((chip->vib_cnt[1] & 3) == 2)
                vib_val = (chip->fnum >> 6) & 7;
            if ((chip->vib_cnt[1] & 1) == 1)
                vib_val = (chip->fnum >> 7) & 3;
            if (chip->vib_cnt[1] & 4)
            {
                vib_val = (vib_val ^ 7) | 0b1111111000;
                vib_add = 1;
            }
        }
        chip->fnum_vib = (chip->fnum_vib & 1023) + (vib_val & 1023) + vib_add;
        if (vib_add)
            chip->fnum_vib &= 1023;
    }
}

void FMOPLL_LFSR(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        int bit;
        bit = ((chip->lfsr[1] >> 22) ^ (chip->lfsr[1] >> 8)) & 1;

        if ((chip->lfsr[1] & 0x7fffff) == 0 || (chip->testmode & 2) != 0)
            bit = 1;
        chip->lfsr[0] = (chip->lfsr[1] << 1) | bit;

        chip->noise_bit = (chip->lfsr[1] >> 22) & 1;
    }

    if (chip->clk2)
    {
        chip->lfsr[1] = chip->lfsr[0];
    }
}

void FMOPLL_PhaseRhythm(fm_opll_t *chip, int phase)
{
    int sd = chip->fsm_out[4] && chip->rhythm;
    int hh = chip->fsm_out[5] && chip->rhythm;
    int tc = chip->fsm_out[10] && chip->rhythm;
    if (chip->clk1)
        chip->hh_load = chip->fsm_out[5];
    if (!chip->hh_load && chip->fsm_out[5])
    {
        chip->hh_bit2 = (phase >> 2) & 1;
        chip->hh_bit3 = (phase >> 3) & 1;
        chip->hh_bit7 = (phase >> 7) & 1;
        chip->hh_bit8 = (phase >> 8) & 1;
    }
    if (chip->clk1)
        chip->tc_load = tc;
    if (!chip->tc_load && tc)
    {
        chip->tc_bit3 = (phase >> 3) & 1;
        chip->tc_bit5 = (phase >> 5) & 1;
    }
    if (chip->clk1)
    {
        int rm_bit;

        rm_bit = (chip->hh_bit2 ^ chip->hh_bit7)
            | (chip->tc_bit5 ^ chip->hh_bit3)
            | (chip->tc_bit5 ^ chip->tc_bit3);

        chip->pg_out = 0;
        if (!sd && !hh && !tc)
            chip->pg_out = phase;
        if (sd)
            chip->pg_out |= (chip->hh_bit8 << 9) | ((chip->noise_bit ^ chip->hh_bit8) << 8);
        if (tc)
            chip->pg_out |= 0x100;
        if (hh)
        {
            if (chip->noise_bit ^ rm_bit)
                chip->pg_out |= 0xd0;
            else
                chip->pg_out |= 0x34;
        }

        if (tc || hh)
            chip->pg_out |= rm_bit << 9;
    }
}

void FMOPLL_PhaseGen(fm_opll_t *chip)
{
    static const int pg_multi[16] = {
        1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 20, 24, 24, 30, 30
    };
    int fnum_block;
    int phase;
    int phase_sum;
    int i;
    int reset;
    if (chip->clk1)
    {
        chip->fnum_latch[0] = chip->fnum;
        chip->block_latch[0] = chip->block;
    }
    if (chip->clk2)
    {
        chip->fnum_latch[1] = chip->fnum_latch[0];
        chip->block_latch[1] = chip->block_latch[0];
    }

    FMOPLL_Vibrato(chip);

    FMOPLL_LFSR(chip);

    phase = 0;
    for (i = 0; i < 19; i++)
    {
        phase |= ((chip->pg_phase[i][1] >> 16) & 1) << i;
    }

    if (chip->clk1)
    {
        fnum_block = (chip->fnum_vib << chip->block_latch[1]) >> 1;
        chip->freq_multi[0] = (fnum_block * pg_multi[chip->multi_latch]) >> 1;
        if (chip->mc_latch[1])
            reset = (chip->eg_dokon[1] & 32768) != 0;
        else
            reset = (chip->eg_dokon[1] & 1) != 0;
        reset |= (chip->testmode & 4) != 0;
        if (reset)
            chip->pg_phase_latch[0] = 0;
        else
            chip->pg_phase_latch[0] = phase;

        phase_sum = chip->freq_multi[1] + chip->pg_phase_latch[1];
        for (i = 0; i < 19; i++)
        {
            chip->pg_phase[i][0] = chip->pg_phase[i][1] << 1;
            chip->pg_phase[i][0] |= (phase_sum >> i) & 1;
        }

        chip->debug_out[0][0] = chip->debug_out[0][1] << 1;

        if (chip->fsm_out[11])
        {
            for (i = 0; i < 9; i++)
            {
                chip->debug_out[0][0] |= ((phase >> i) & 1) << (i + 7);
            }
        }
    }
    if (chip->clk2)
    {
        chip->freq_multi[1] = chip->freq_multi[0];
        chip->pg_phase_latch[1] = chip->pg_phase_latch[0];
        for (i = 0; i < 19; i++)
            chip->pg_phase[i][1] = chip->pg_phase[i][0];
        chip->debug_out[0][1] = chip->debug_out[0][0];
    }

    FMOPLL_PhaseRhythm(chip, phase >> 9);
}

void FMOPLL_Keyon(fm_opll_t *chip)
{
    int bd0;
    int hh;
    int tom;
    int bd1;
    int sd;
    int tc;
    if (chip->clk1)
    {
        bd0 = chip->rhythm && (chip->rhythm_sel[1] & 1) != 0;
        hh = (chip->rhythm_sel[1] & 2) != 0;
        tom = (chip->rhythm_sel[1] & 4) != 0;
        bd1 = (chip->rhythm_sel[1] & 8) != 0;
        sd = (chip->rhythm_sel[1] & 16) != 0;
        tc = (chip->rhythm_sel[1] & 32) != 0;
        chip->kon_comb = chip->kon;
        if ((bd0 || bd1) && (chip->rhythm_kon & 16) != 0)
            chip->kon_comb |= 1;
        if (sd && (chip->rhythm_kon & 8) != 0)
            chip->kon_comb |= 1;
        if (tom && (chip->rhythm_kon & 4) != 0)
            chip->kon_comb |= 1;
        if (tc && (chip->rhythm_kon & 2) != 0)
            chip->kon_comb |= 1;
        if (hh && (chip->rhythm_kon & 1) != 0)
            chip->kon_comb |= 1;
    }
}

void FMOPLL_Tremolo(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        chip->trem_load1 = chip->fsm_out[10];
        chip->trem_load2 = chip->fsm_out[11];
    }
    if (!chip->trem_load1 && chip->fsm_out[10])
    {
        chip->trem_step_latch = chip->trem_step;
        if (chip->trem_step)
            chip->trem_step = 1;
    }

    if (chip->clk1)
    {
        int trem_of = 0;
        int bit, add, carry;
        chip->trem_dir[0] = chip->trem_dir[1];
        trem_of |= chip->trem_dir[1] == 0
            && (chip->trem_sr[1] & 105) == 105
            && chip->fsm_out[11];
        trem_of |= chip->trem_dir[1] == 1
            && (chip->trem_sr[1] & 127) == 0
            && chip->fsm_out[11];
        if (chip->trem_step_latch && trem_of)
            chip->trem_dir[0] ^= 1;
        if (chip->ic || (chip->testmode & 2) != 0)
            chip->trem_dir[0] = 0;

        bit = chip->trem_sr[1] & 1;
        add = ((chip->trem_step_latch || (chip->testmode & 8) != 0) && (chip->fsm_out[11] || chip->trem_dir[1]))
            && chip->fsm_out[9];
        carry = chip->fsm_out[9] && chip->trem_cb[1];

        bit += add + carry;

        chip->trem_cb[0] = (bit >> 1) & 1;

        chip->trem_sr[0] = chip->trem_sr[1] >> 1;
        
        bit &= 1;
        if (chip->ic || (chip->testmode & 2) != 0)
            bit = 0;
        chip->trem_sr[0] |= bit << 8;

    }
    else
    {
        chip->trem_sr[1] = chip->trem_sr[0];
        chip->trem_dir[1] = chip->trem_dir[0];
        chip->trem_cb[1] = chip->trem_cb[0];
    }
    if (!chip->trem_load2 && chip->fsm_out[11])
        chip->trem_out = (chip->trem_sr[1] >> 3) & 15;
}

void FMOPLL_EnvTimer(fm_opll_t *chip)
{
    int timer_load = !(chip->eg_sync_latch[1] && chip->eg_subcnt1_latch[1]);
    if (chip->clk1)
    {
        int bit;
        int carry;
        int mask_reset;
        chip->eg_timer_sr[0] = chip->eg_timer_sr[1];
        chip->eg_timer_sr_masked[0] = chip->eg_timer_sr_masked[1];
        if (chip->testmode & 8)
            bit = (chip->data_latch >> 2) & 1;
        else
            bit = chip->eg_timer_bit_latch[1];
        chip->eg_timer_sr[0] |= bit << 17;
        chip->eg_timer_sr_masked[0] |= (bit & chip->eg_timer_mask[1]) << 17;
        chip->eg_ic_latch[0] = chip->ic;
        chip->eg_sync_latch[0] = chip->fsm_out[10];
        mask_reset = chip->eg_ic_latch[1] || chip->eg_sync_latch[1];
        chip->eg_timer_mask[0] = mask_reset || (chip->eg_timer_mask[1] && !bit);
        chip->eg_timer_prescaler[0] = chip->eg_timer_prescaler[1];
        chip->eg_timer_prescaler[0] += chip->fsm_out[10];
        if (chip->ic)
            chip->eg_timer_prescaler[0] = 0;
        chip->eg_subcnt2_latch = (chip->eg_timer_prescaler[1] & 3) != 3;
        chip->eg_subcnt1_latch[0] = (chip->eg_timer_prescaler[1] & 1) != 1;
        chip->eg_timer_load = timer_load;

        bit = chip->eg_timer_sr[1] & 1;

        carry = (chip->eg_timer_carry[1] || chip->eg_sync_latch[1]) &&
            (chip->eg_timer_prescaler[1] & 3) == 3;
        bit += carry;
        chip->eg_timer_carry[0] = (bit >> 1) & 1;
        chip->eg_timer_bit_latch[0] = bit & 1;

    }
    if (chip->clk2)
    {
        chip->eg_timer_sr[1] = chip->eg_timer_sr[0] >> 1;
        chip->eg_timer_sr_masked[1] = chip->eg_timer_sr_masked[0] >> 1;
        chip->eg_timer_mask[1] = chip->eg_timer_mask[0];
        chip->eg_ic_latch[1] = chip->eg_ic_latch[0];
        chip->eg_sync_latch[1] = chip->eg_sync_latch[0];
        chip->eg_timer_prescaler[1] = chip->eg_timer_prescaler[0];
        chip->eg_subcnt1_latch[1] = !chip->eg_subcnt1_latch[0];
        chip->eg_timer_bit_latch[1] = chip->eg_timer_bit_latch[0] && !chip->eg_ic_latch[0];
        chip->eg_timer_carry[1] = chip->eg_timer_carry[0];
    }
    if (!chip->eg_timer_load && !timer_load)
    {
        chip->eg_timer_low = chip->eg_timer_sr[0] & 3;
        chip->eg_shift = 0;
        if (chip->eg_timer_sr_masked[0] & 0x1555)
            chip->eg_shift |= 1;
        if (chip->eg_timer_sr_masked[0] & 0x666)
            chip->eg_shift |= 2;
        if (chip->eg_timer_sr_masked[0] & 0x1878)
            chip->eg_shift |= 4;
        if (chip->eg_timer_sr_masked[0] & 0x1f80)
            chip->eg_shift |= 8;

        int temp = chip->eg_timer_sr[0];
        int temp2 = 1 << chip->eg_shift;
    }
}

enum {
    eg_state_attack = 0,
    eg_state_decay,
    eg_state_sustain,
    eg_state_release
};

void FMOPLL_EnvState(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        int b0;
        int b1;
        int state;
        int nextstate;
        chip->eg_state[0][0] = chip->eg_state[0][1] >> 1;
        chip->eg_state[1][0] = chip->eg_state[1][1] >> 1;

        b0 = (chip->eg_state[0][1] >> 2) & 1;
        b1 = (chip->eg_state[1][1] >> 2) & 1;
        state = b1 * 2 + b0;
        chip->eg_dokon[0] = chip->eg_dokon[1] << 1;
        chip->eg_isrelease = state == eg_state_release;
        chip->eg_ratesel = state;
        if (state == eg_state_release && chip->kon_comb && chip->eg_off)
        {
            chip->eg_dokon[0] |= 1;
            chip->eg_ratesel = eg_state_attack;
        }
        chip->eg_kon_latch[0] = (chip->eg_kon_latch[1] << 1) | chip->kon_comb;
        chip->eg_off_latch[0] = (chip->eg_off_latch[1] << 1) | chip->eg_off;

        b0 = chip->eg_state[0][1] & 1;
        b1 = chip->eg_state[1][1] & 1;
        state = b1 * 2 + b0;

        chip->eg_resetlevel = chip->ic ||
            ((chip->eg_off_latch[1] & 2) && state != eg_state_attack && !(chip->eg_dokon[1] & 2));
        chip->eg_instantattack = (chip->eg_dokon[1] & 2) != 0 && chip->eg_rate_15;

        nextstate = eg_state_attack;

        if (!(chip->eg_dokon[1] & 2))
        {
            if (!(chip->eg_kon_latch[1] & 2))
            {
                nextstate |= eg_state_release;
            }
            if (state == eg_state_release)
            {
                nextstate |= eg_state_release;
            }
            if (state == eg_state_sustain)
            {
                nextstate |= eg_state_sustain;
            }
            if (state == eg_state_decay && chip->eg_slreach)
            {
                nextstate |= eg_state_sustain;
            }
            if (state == eg_state_decay && !chip->eg_slreach)
            {
                nextstate |= eg_state_decay;
            }
            if (state == eg_state_attack && chip->eg_zeroreach)
            {
                nextstate |= eg_state_decay;
            }
        }

        if (chip->ic)
            nextstate = eg_state_release;

        b0 = nextstate & 1;
        b1 = (nextstate >> 1) & 1;

        chip->eg_state[0][0] |= b0 << 17;
        chip->eg_state[1][0] |= b1 << 17;

        chip->eg_expstep = state == eg_state_attack && !chip->eg_rate_15 && (chip->eg_kon_latch[1] & 2) != 0
            && !chip->eg_zeroreach;

        chip->eg_linstep = !(chip->eg_dokon[1] & 2) && state == eg_state_decay && !chip->eg_slreach && !(chip->eg_off_latch[1] & 2);
        chip->eg_linstep |= !(chip->eg_dokon[1] & 2) && (state & 2) == 2 && !(chip->eg_off_latch[1] & 2);

    }
    if (chip->clk2)
    {
        chip->eg_dokon[1] = chip->eg_dokon[0];
        chip->eg_state[0][1] = chip->eg_state[0][0];
        chip->eg_state[1][1] = chip->eg_state[1][0];
        chip->eg_kon_latch[1] = chip->eg_kon_latch[0];
        chip->eg_off_latch[1] = chip->eg_off_latch[0];
    }
}

void FMOPLL_EnvRate(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        chip->eg_son_latch = chip->son;
    }
    if (chip->clk2)
    {
        int rate = 0;
        if (chip->eg_ratesel == eg_state_attack)
            rate |= chip->patch_cur.ar;
        if (chip->eg_ratesel == eg_state_decay)
            rate |= chip->patch_cur.dr;
        if (chip->eg_ratesel == eg_state_release && chip->eg_son_latch)
            rate |= 5;
        if (chip->eg_ratesel == eg_state_release && !chip->eg_son_latch)
            rate |= chip->patch_cur.rr;
        if (chip->eg_ratesel == eg_state_sustain && !chip->patch_cur.et)
            rate |= chip->patch_cur.rr;
        if (chip->force_zerorate)
            rate = 0;
        chip->eg_rate1 = rate;
    }
}

void FMOPLL_EnvStep(fm_opll_t *chip)
{
    static const int eg_stephi[4][4] = {
        { 0, 0, 0, 0 },
        { 1, 0, 0, 0 },
        { 1, 0, 1, 0 },
        { 1, 1, 1, 0 }
    };
    if (chip->clk1)
    {
        int sum;
        int inc;
        chip->eg_ksr_freq = (chip->block << 1) | (chip->fnum >> 8);
        chip->eg_kon_latch2 = chip->kon_comb;
        chip->eg_isrelease_notoff = chip->eg_isrelease && !chip->eg_off;
        chip->eg_son_latch2 = chip->son;

        chip->eg_ksr_low[1] = chip->eg_ksr_low[0];
        chip->eg_zerorate[1] = chip->eg_zerorate[0];

        chip->eg_rate_latch2 = chip->eg_rate_latch + chip->eg_ksr_high;

        sum = (chip->eg_shift_latch + chip->eg_rate_latch3) & 15;

        inc = 0;
        if (!chip->eg_zerorate[2] && !chip->eg_rate_high)
        {
            if (sum == 12)
                inc = 1;
            if (sum == 13)
                inc |= (chip->eg_ksr_low[2] >> 1) & 1;
            if (sum == 14)
                inc |= chip->eg_ksr_low[2] & 1;
        }

        chip->eg_step1 = (!chip->eg_step_hi && chip->eg_rate_12) || inc;
        chip->eg_step2 = (!chip->eg_step_hi && chip->eg_rate_13) || (chip->eg_step_hi && chip->eg_rate_12);
        chip->eg_step3 = (inc && !chip->eg_subcnt2_latch2 && chip->eg_linstep)
            || (chip->eg_rate_12 && !chip->eg_subcnt2_latch2 && chip->eg_linstep && !chip->eg_step_hi)
            || (chip->eg_rate_12 && !chip->eg_subcnt1_latch2 && chip->eg_linstep && chip->eg_step_hi)
            || (chip->eg_rate_13 && !chip->eg_subcnt1_latch2 && chip->eg_linstep && !chip->eg_step_hi)
            || (chip->eg_rate_13 && chip->eg_step_hi)
            || (chip->eg_rate_14 && !chip->eg_step_hi);
        chip->eg_step4 = (chip->eg_rate_14 && chip->eg_step_hi) || chip->eg_rate_15;

    }
    if (chip->clk2)
    {
        int ksr;
        int rate = 0;

        ksr = chip->eg_ksr_freq;
        if (!chip->patch_cur.ksr)
            ksr >>= 2;

        chip->eg_ksr_low[0] = ksr & 3;
        chip->eg_ksr_low[2] = chip->eg_ksr_low[1];
        chip->eg_ksr_high = ksr >> 2;

        if (chip->eg_kon_latch2 && chip->eg_isrelease_notoff)
            rate = 12;
        else if (!chip->eg_kon_latch2 && !chip->eg_son_latch2 && !chip->patch_cur.et && !chip->modcar_sel_latch)
            rate = 7;
        else
            rate = chip->eg_rate1;

        chip->eg_rate_latch = rate;
        chip->eg_zerorate[0] = rate == 0;
        chip->eg_zerorate[2] = chip->eg_zerorate[1];

        rate = chip->eg_rate_latch2;
        if (rate & 16)
            rate = 15;
        chip->eg_rate_latch3 = rate;

        chip->eg_rate_high = (rate & 12) == 12;

        chip->eg_rate_12 = rate == 12;
        chip->eg_rate_13 = rate == 13;
        chip->eg_rate_14 = rate == 14;
        chip->eg_rate_15 = rate == 15;

        chip->eg_shift_latch = chip->eg_shift;

        chip->eg_subcnt1_latch2 = chip->eg_subcnt1_latch[0];
        chip->eg_subcnt2_latch2 = chip->eg_subcnt2_latch;

        chip->eg_step_hi = eg_stephi[chip->eg_ksr_low[1]][chip->eg_timer_low];
    }
}

void FMOPLL_EnvKSLTL(fm_opll_t *chip)
{
    static const int eg_ksltable[16] = {
        0, 32, 40, 45, 48, 51, 53, 55, 56, 58, 59, 60, 61, 62, 63, 64
    };

    if (chip->clk1)
    {
        int ksl;
        int ksl_sum;
        int ksl_of;
        int sum;
        ksl = eg_ksltable[chip->fnum >> 5] ^ 127;

        ksl += ((chip->block ^ 7) + 1) << 3;
        if (ksl & 128)
            ksl = 0;
        else
            ksl = (ksl ^ 63) & 63;

        chip->eg_ksllatch = ksl;

        sum = chip->eg_ksltl & 127;

        if (chip->tremolo_latch)
            sum += chip->trem_out;

        chip->eg_ksltltrem = sum & 127;

        if ((sum & 128) || (chip->eg_ksltl & 128))
            chip->eg_ksltltrem |= 128;

    }
    if (chip->clk2)
    {
        int ksltl;
        if (!chip->patch_cur.ksl)
            ksltl = 0;
        else
            ksltl = (chip->eg_ksllatch << 1) >> (3 - chip->patch_cur.ksl);

        ksltl += chip->patch_cur.tl << 1;
        chip->eg_ksltl = ksltl;
    }
}

void FMOPLL_EnvGen(fm_opll_t *chip)
{
    if (chip->clk1)
    {
        int bit;
        int i;
        int level;
        bit = 1;
        for (i = 2; i < 7; i++)
        {
            bit &= (chip->eg_level[i][1] >> 2) & 1;
        }
        chip->eg_off = bit;
        level = 0;
        for (i = 0; i < 7; i++)
        {
            level |= (chip->eg_level[i][1] & 1) << i;
        }
        chip->eg_zeroreach = level == 0;
        chip->eg_slreach = (level >> 3) == chip->eg_sllatch[1];

        chip->eg_sllatch[0] = chip->sl_latch;
    }
    if (chip->clk2)
    {
        chip->eg_sllatch[1] = chip->eg_sllatch[0];
    }
    FMOPLL_Tremolo(chip);
    FMOPLL_EnvTimer(chip);
    FMOPLL_EnvState(chip);
    FMOPLL_EnvRate(chip);
    FMOPLL_EnvStep(chip);
    FMOPLL_EnvKSLTL(chip);
    if (chip->clk1)
    {
        int i;
        int level;
        int nextlevel;
        int step;
        level = 0;
        for (i = 0; i < 7; i++)
        {
            level |= (chip->eg_level[i][1] & 1) << i;
        }

        if (chip->eg_instantattack)
            nextlevel = 0;
        else if (chip->eg_resetlevel)
            nextlevel = 127;
        else
            nextlevel = level;

        step = 0;
        if (chip->eg_linstep)
            step |= chip->eg_step3 + chip->eg_step4 * 2;
        if (chip->eg_expstep)
        {
            if (chip->eg_step1)
                step |= (~level) >> 4;
            if (chip->eg_step2)
                step |= (~level) >> 3;
            if (chip->eg_step3)
            {
                int temp = (~level) >> 2;
                if (chip->eg_linstep)
                    temp &= ~1;
                step |= temp;
            }
            if (chip->eg_step4)
            {
                int temp = (~level) >> 1;
                if (chip->eg_linstep)
                    temp &= ~2;
                step |= temp;
            }
        }
        nextlevel += step;

        for (i = 0; i < 7; i++)
        {
            chip->eg_level[i][0] = chip->eg_level[i][1] >> 1;
            chip->eg_level[i][0] |= ((nextlevel >> i) & 1) << 17;
        }

        chip->eg_silent[0] = level == 127;

        level = 0;

        for (i = 0; i < 7; i++)
        {
            level |= ((chip->eg_level[i][1] >> 1) & 1) << i;
        }
        chip->eg_level_latch = level;

        if (chip->fsm_out[11])
        {
            for (i = 0; i < 9; i++)
            {
                chip->debug_out[0][0] |= ((chip->eg_out >> i) & 1) << i;
            }
        }
    }
    if (chip->clk2)
    {
        int sum;
        int i;
        for (i = 0; i < 7; i++)
        {
            chip->eg_level[i][1] = chip->eg_level[i][0];
        }
        sum = chip->eg_level_latch;
        sum += chip->eg_ksltltrem & 127;
        if ((sum & 128) || (chip->eg_ksltltrem & 128))
            sum = 127;

        if (chip->testmode & 1)
            sum = 0;

        chip->eg_out = sum;
        chip->eg_silent[1] = chip->eg_silent[0];
    }
}

void FMOPLL_Operator(fm_opll_t *chip)
{
    static const int logsin[128] = {
        0x6c3, 0x58b, 0x4e4, 0x471, 0x41a, 0x3d3, 0x398, 0x365, 0x339, 0x311, 0x2ed, 0x2cd, 0x2af, 0x293, 0x279, 0x261,
        0x24b, 0x236, 0x222, 0x20f, 0x1fd, 0x1ec, 0x1dc, 0x1cd, 0x1be, 0x1b0, 0x1a2, 0x195, 0x188, 0x17c, 0x171, 0x166,
        0x15b, 0x150, 0x146, 0x13c, 0x133, 0x129, 0x121, 0x118, 0x10f, 0x107, 0x0ff, 0x0f8, 0x0f0, 0x0e9, 0x0e2, 0x0db,
        0x0d4, 0x0cd, 0x0c7, 0x0c1, 0x0bb, 0x0b5, 0x0af, 0x0a9, 0x0a4, 0x09f, 0x099, 0x094, 0x08f, 0x08a, 0x086, 0x081,
        0x07d, 0x078, 0x074, 0x070, 0x06c, 0x068, 0x064, 0x060, 0x05c, 0x059, 0x055, 0x052, 0x04e, 0x04b, 0x048, 0x045,
        0x042, 0x03f, 0x03c, 0x039, 0x037, 0x034, 0x031, 0x02f, 0x02d, 0x02a, 0x028, 0x026, 0x024, 0x022, 0x020, 0x01e,
        0x01c, 0x01a, 0x018, 0x017, 0x015, 0x014, 0x012, 0x011, 0x00f, 0x00e, 0x00d, 0x00c, 0x00a, 0x009, 0x008, 0x007,
        0x007, 0x006, 0x005, 0x004, 0x004, 0x003, 0x002, 0x002, 0x001, 0x001, 0x001, 0x001, 0x000, 0x000, 0x000, 0x000
    };
    static const int logsin_d[128] = {
        0x196, 0x07c, 0x04a, 0x035, 0x029, 0x022, 0x01d, 0x019, 0x015, 0x013, 0x012, 0x00f, 0x00e, 0x00d, 0x00d, 0x00c,
        0x00b, 0x00a, 0x00a, 0x009, 0x009, 0x009, 0x008, 0x007, 0x007, 0x007, 0x007, 0x006, 0x007, 0x006, 0x006, 0x005,
        0x005, 0x005, 0x005, 0x005, 0x004, 0x005, 0x004, 0x004, 0x005, 0x004, 0x004, 0x003, 0x004, 0x003, 0x003, 0x003,
        0x003, 0x004, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x002, 0x003, 0x003, 0x003, 0x003, 0x002, 0x002,
        0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x002, 0x001, 0x002, 0x002, 0x002, 0x001,
        0x001, 0x001, 0x002, 0x002, 0x001, 0x001, 0x002, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001, 0x001,
        0x001, 0x001, 0x001, 0x000, 0x001, 0x000, 0x001, 0x000, 0x001, 0x001, 0x000, 0x000, 0x001, 0x001, 0x001, 0x001,
        0x000, 0x000, 0x000, 0x001, 0x000, 0x000, 0x001, 0x000, 0x001, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000
    };
    static const int pow[128] = {
        0x3f5, 0x3ea, 0x3df, 0x3d4, 0x3c9, 0x3bf, 0x3b4, 0x3a9, 0x39f, 0x394, 0x38a, 0x37f, 0x375, 0x36a, 0x360, 0x356,
        0x34c, 0x342, 0x338, 0x32e, 0x324, 0x31a, 0x310, 0x306, 0x2fd, 0x2f3, 0x2e9, 0x2e0, 0x2d6, 0x2cd, 0x2c4, 0x2ba,
        0x2b1, 0x2a8, 0x29e, 0x295, 0x28c, 0x283, 0x27a, 0x271, 0x268, 0x25f, 0x257, 0x24e, 0x245, 0x23c, 0x234, 0x22b,
        0x223, 0x21a, 0x212, 0x209, 0x201, 0x1f9, 0x1f0, 0x1e8, 0x1e0, 0x1d8, 0x1d0, 0x1c8, 0x1c0, 0x1b8, 0x1b0, 0x1a8,
        0x1a0, 0x199, 0x191, 0x189, 0x181, 0x17a, 0x172, 0x16b, 0x163, 0x15c, 0x154, 0x14d, 0x146, 0x13e, 0x137, 0x130,
        0x129, 0x122, 0x11b, 0x114, 0x10c, 0x106, 0x0ff, 0x0f8, 0x0f1, 0x0ea, 0x0e3, 0x0dc, 0x0d6, 0x0cf, 0x0c8, 0x0c2,
        0x0bb, 0x0b5, 0x0ae, 0x0a8, 0x0a1, 0x09b, 0x094, 0x08e, 0x088, 0x082, 0x07b, 0x075, 0x06f, 0x069, 0x063, 0x05d,
        0x057, 0x051, 0x04b, 0x045, 0x03f, 0x039, 0x033, 0x02d, 0x028, 0x022, 0x01c, 0x016, 0x011, 0x00b, 0x006, 0x000,
    };
    static const int pow_d[128] = {
        0x005, 0x005, 0x005, 0x006, 0x006, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x006, 0x005, 0x005,
        0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x004, 0x005,
        0x004, 0x004, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x005, 0x004, 0x004, 0x004, 0x005, 0x004, 0x005,
        0x004, 0x004, 0x004, 0x005, 0x004, 0x004, 0x005, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004,
        0x004, 0x003, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x004, 0x003, 0x004, 0x004, 0x004,
        0x003, 0x003, 0x003, 0x003, 0x004, 0x003, 0x003, 0x003, 0x003, 0x003, 0x004, 0x004, 0x003, 0x003, 0x004, 0x003,
        0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x004, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003,
        0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x003, 0x002, 0x003, 0x003, 0x003, 0x003, 0x003, 0x002, 0x003,
    };
    if (chip->clk1)
    {
        int phase;
        int quarter;
        int mod = 0;
        int atten;
        int index;
        int out;
        int shift;
        int mute;
        int i;
        int bit;
        int fb1;
        int fb2;

        if (chip->op_modenable[1])
            mod |= chip->op_mod[1] << 1;
        if (chip->fb_latch && chip->mc_latch[1])
        {
            int fbmod = chip->op_fbmod[1];
            if (fbmod & 2048)
                fbmod |= ~2047;

            mod |= fbmod >> (7 - chip->fb_latch);
        }

        phase = chip->pg_out + mod;

        quarter = phase & 255;
        if (phase & 256)
            quarter ^= 255;

        chip->op_logsin_add_delta = (quarter & 1) == 0;

        chip->op_logsin_base = logsin[quarter >> 1];
        chip->op_logsin_delta = logsin_d[quarter >> 1];

        chip->op_sign[0] = chip->op_sign[1] << 1;
        if (phase & 512)
            chip->op_sign[0] |= 1;

        atten = chip->op_logsin + (chip->eg_out << 4);
        if (atten & 4096)
            atten = 4095;

        chip->op_shift[0] = atten >> 8;

        index = atten & 255;

        chip->op_pow_add_delta = (index & 1) == 0;

        chip->op_pow_base = pow[index >> 1];
        chip->op_pow_delta = pow_d[index >> 1];

        mute = chip->eg_silent[1];

        if (chip->op_sign[1] & 2)
        {
            if (chip->fsm_out[2])
                mute |= (chip->dm_latch[1] & 4) != 0;
            else
                mute |= (chip->dc_latch[1] & 4) != 0;
        }

        shift = chip->op_shift[1];
        if (mute)
            shift |= 12;

        out = chip->op_pow;
        out >>= shift;

        if ((chip->op_sign[1] & 2) && !chip->eg_silent[1])
            out ^= 4095;

        for (i = 0; i < 12; i++)
        {
            chip->op_fb[0][i][0] = chip->op_fb[0][i][1] << 1;
            if (chip->fsm_out[2])
                bit = (out >> i) & 1;
            else
                bit = (chip->op_fb[0][i][1] >> 8) & 1;
            chip->op_fb[0][i][0] |= bit;
            chip->op_fb[1][i][0] = chip->op_fb[1][i][1] << 1;
            if (chip->fsm_out[2])
                bit = (chip->op_fb[0][i][1] >> 8) & 1;
            else
                bit = (chip->op_fb[1][i][1] >> 8) & 1;
            chip->op_fb[1][i][0] |= bit;
        }

        chip->op_mod[0] = out & 511;

        fb1 = 0;
        fb2 = 0;
        for (i = 0; i < 13; i++)
        {
            int j = i;
            if (i == 12)
                j = 11;
            fb1 |= ((chip->op_fb[0][j][1] >> 5) & 1) << i;
            fb2 |= ((chip->op_fb[1][j][1] >> 5) & 1) << i;
        }
        chip->op_fbmod[0] = ((fb1 + fb2) >> 1) & 4095;

        chip->op_modenable[0] = chip->fsm_out[2];

        chip->op_out = out >> 3;
    }

    if (chip->clk2)
    {
        int i;
        chip->op_logsin = chip->op_logsin_base;
        if (chip->op_logsin_add_delta)
            chip->op_logsin += chip->op_logsin_delta;
        chip->op_shift[1] = chip->op_shift[0];

        chip->op_pow = chip->op_pow_base;
        if (chip->op_pow_add_delta)
            chip->op_pow += chip->op_pow_delta;

        chip->op_pow |= 0x400;

        chip->op_sign[1] = chip->op_sign[0];

        for (i = 0; i < 12; i++)
        {
            chip->op_fb[0][i][1] = chip->op_fb[0][i][0];
            chip->op_fb[1][i][1] = chip->op_fb[1][i][0];
        }

        chip->op_mod[1] = chip->op_mod[0];
        chip->op_fbmod[1] = chip->op_fbmod[0];
        chip->op_modenable[1] = chip->op_modenable[0];
    }
}

void FMOPLL_Output(fm_opll_t *chip)
{
    int en_m;
    int en_r;
    int val1, val2;
    if (chip->clk1)
    {
        int value;
        int i;
        if (!chip->fsm_out[2])
            value = chip->op_out;
        else
        {
            value = 0;
            // guesswork
            if (chip->rhythm)
            {
                for (i = 0; i < 9; i++)
                {
                    value |= ((chip->ch_rhysr[i][1] >> 4) & 1) << i;
                }
            }
        }

        // guesswork
        if (chip->rclk1)
        {
            for (i = 0; i < 9; i++)
            {
                chip->ch_rhysr[i][0] = chip->ch_rhysr[i][1] << 1;
                chip->ch_rhysr[i][0] |= (value >> i) & 1;
            }
        }

        if (value & 256)
            value ^= 255;
        chip->ch_out[0] = value;

        chip->ch_m_en[0] = chip->fsm_out[0];
        chip->ch_r_en[0] = chip->fsm_out[13];

        chip->debug_out[1][0] = chip->debug_out[1][1] << 1;
        if (chip->fsm_out[11])
            chip->debug_out[1][0] |= chip->ch_out[1];

    }
    if (chip->clk2)
    {
        int i;
        chip->ch_out[1] = chip->ch_out[0];

        chip->ch_m_en[1] = chip->ch_m_en[0];
        chip->ch_r_en[1] = chip->ch_r_en[0];
        // guesswork
        if (chip->rclk2)
        {
            for (i = 0; i < 9; i++)
            {
                chip->ch_rhysr[i][1] = chip->ch_rhysr[i][0];
            }
        }

        chip->debug_out[1][1] = chip->debug_out[1][0];
    }
    en_m = chip->ch_m_en[1] && chip->clk_dac;
    en_r = chip->ch_r_en[1] && chip->clk_dac;
    val1 = chip->ch_out[1];
    if (val1 & 256)
    {
        val1 = -1 - (val1 & 255);
        val2 = -1;
    }
    else
    {
        val1 = 1 + (val1 & 255);
        val2 = 1;
    }
    if (en_m)
        chip->out_m = val1;
    else
        chip->out_m = val2;
    if (en_r)
        chip->out_r = val1;
    else
        chip->out_r = val2;
}

void FMOPLL_Clock(fm_opll_t *chip, int mclk)
{
    chip->mclk = mclk;
    FMOPLL_Prescaler(chip);
    FMOPLL_UpdateIO2(chip);

    if (chip->oclk1 != chip->clk1 || chip->oclk2 != chip->clk2)
    {
        FMOPLL_FSM(chip);
        FMOPLL_FSMTable(chip);
        if (chip->clk1)
        {
            chip->mc_latch[0] = chip->fsm_out[1];
        }
        if (chip->clk2)
        {
            chip->mc_latch[1] = chip->mc_latch[0];
        }
        FMOPLL_UpdateRegisters(chip);
        FMOPLL_RhythmCtrl(chip);
        FMOPLL_Keyon(chip);
        FMOPLL_InstrumentCtrl(chip);
        FMOPLL_RegistersExtraLatch(chip);
        FMOPLL_PhaseGen(chip);
        FMOPLL_EnvGen(chip);
        FMOPLL_Operator(chip);
    }
    FMOPLL_Output(chip);
    chip->oclk1 = chip->clk1;
    chip->oclk2 = chip->clk2;
}


void FMOPLL_SetCS(fm_opll_t *chip, int cs)
{
    chip->cs = !cs;
    FMOPLL_UpdateIO(chip);
}

void FMOPLL_SetWrite(fm_opll_t* chip, int we)
{
    chip->we = !we;
    FMOPLL_UpdateIO(chip);
}

void FMOPLL_SetAddress(fm_opll_t* chip, int a)
{
    chip->a0 = a & 1;
    FMOPLL_UpdateIO(chip);
}

void FMOPLL_SetData(fm_opll_t* chip, int data)
{
    chip->in_data = data & 255;
    FMOPLL_UpdateIO(chip);
}

void FMOPLL_SetIC(fm_opll_t* chip, int ic)
{
    chip->ic = ic;
}
