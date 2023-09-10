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
        chip->w62 = (chip->w74 || chip->w80) ? 0 : ((chip->w63 + chip->w76) & 255);
    if (chip->hclk2)
        chip->w63 = chip->w62 | (chip->w65 & chip->w66);

    if (chip->w81)
        chip->w64 = chip->w63;

    if (chip->hclk1)
        chip->w65 = chip->w64;
    if (chip->hclk1)
        chip->w66 = chip->tm_w1 ? 255 : 0;

    chip->w67 = chip->w85[1] ? ((chip->w63 >> 5) & 3) : 0;

    if (chip->w83)
    {
        chip->vram_address &= ~0xfe;
        chip->vram_address |= (chip->w63 << 1) & 0x3e;
        chip->vram_address |= (chip->w67 << 6) & 0xc0;
    }
    if (chip->w97)
    {
        chip->vram_address &= ~0x7c;
        chip->vram_address |= (chip->w63 << 2) & 0x7c;
    }
    if (chip->w88)
    {
        chip->vram_address &= ~0x380;
        chip->vram_address |= (chip->w63 << 2) & 0x380;
    }

    if (chip->hclk1)
        chip->w68 = !chip->tm_w1;
    if (chip->hclk2)
        chip->w69 = !chip->w68;
    if (chip->hclk1)
        chip->w70 = chip->w69;
    if (chip->hclk2)
        chip->w71 = !(chip->w70 || chip->w68);

    chip->w72 = !(chip->w71 || chip->tm_w1 || (chip->tm_w2 && chip->tm_w3));

    if (chip->hclk1)
        chip->w73 = chip->w72;
    if (chip->hclk2)
        chip->w74 = !chip->w73;

    chip->w75 = !(chip->w77 ? chip->w78 : chip->w79);

    if (chip->hclk2)
        chip->w76 = !chip->w75;

    if (chip->hclk2)
        chip->vram_address = 0x3fff;

    if (chip->hclk1)
        chip->w77 = chip->tm_w1;
    if (chip->hclk1)
        chip->w78 = chip->tm_w1;
    if (chip->hclk1)
        chip->w79 = chip->w94;

    chip->w80 = !(chip->tm_w1 || !chip->tm_w2);

    chip->w81 = chip->tm_w1;

    if (chip->hclk2)
        chip->w82 = chip->tm_w1;
    chip->w83 = chip->w82 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w84 = !(!chip->tm_w1 || chip->tm_w2);

    if (chip->hclk1)
        chip->w85[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w85[1] = chip->w85[0];

    chip->w86 = !(chip->tm_w1 || !chip->tm_w2);

    if (chip->hclk1)
        chip->w87[0] = w86;
    if (chip->hclk2)
        chip->w87[1] = chip->w87[0];

    chip->w88 = chip->w87[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w89[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w89[1] = chip->w89[0];

    if (chip->hclk1)
        chip->w90[0] = chip->w74 ? 0 : ((chip->w90[1] + chip->w89[1]) & 3);
    if (chip->hclk2)
        chip->w90[1] = chip->w90[0];

    if (chip->w105)
    {
        chip->vram_address &= ~3;
        chip->vram_address |= chip->w90[1] & 3;
    }

    chip->w91 = !((chip->w90[1] & 1) != 0 || (chip->w90[1] & 2) == 0 || !chip->w89[1]);
    chip->w92 = !((chip->w90[1] & 1) == 0 || (chip->w90[1] & 2) == 0 || !chip->w89[1]);

    chip->w93 = chip->w91;
    chip->w94 = chip->w93;

    chip->w95 = !(chip->w98 || chip->tm_w2);

    if (chip->hclk1)
        chip->w96[0] = chip->w95;
    if (chip->hclk2)
        chip->w96[1] = chip->w96[0];

    chip->w97 = chip->w96[1] ? chip->hclk1 : 0;

    chip->w98 = !chip->tm_w1;

    chip->w99 = !(chip->w98 || chip->tm_w1 || chip->tm_w2);

    chip->w100 = !chip->tm_w1;

    chip->w101 = !(chip->w100 || chip->tm_w1);

    if (chip->hclk1)
        chip->w102[0] = w99;
    if (chip->hclk2)
        chip->w102[1] = chip->w102[0];

    chip->w103 = chip->w102[1] ? chip->hclk1 : 0;

    if (chip->w103)
        chip->vram_address &= ~3;

    if (chip->hclk1)
        chip->w104[0] = w101;
    if (chip->hclk2)
        chip->w104[1] = chip->w104[0];

    chip->w105 = chip->w104[1] ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w106 = chip->tm_w1;
    chip->w107 = chip->w106 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w108 = !chip->tm_w1;

    if (chip->hclk1)
        chip->w109 = (chip->tm_w1 & 15) ^ 15;

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

    if (chip->w107)
    {
        chip->vram_address &= ~0x1c;
        chip->vram_address |= (chip->w117[0] & 7) << 2;
    }
    if (chip->w125)
    {
        chip->vram_address &= ~0x20;
        chip->vram_address |= (chip->w117[0] & 8) << 2;
    }

    if (chip->hclk1)
        chip->w118 = !chip->tm_w1;

    if (chip->hclk2)
        chip->w119[0] = chip->w108 ? (((chip->w119[1] << 1) | chip->w118) & 255) : chip->w119[1];
    if (chip->hclk1)
        chip->w119[1] = chip->w119[0];

    chip->w120 = (chip->w119[0] >> 7) & 1;

    chip->w121 = !((chip->w119[0] & 8) == 0 || chip->tm_w1);

    chip->w122 = !((chip->w119[0] & 16) == 0 || chip->tm_w1);

    chip->w123 = !(chip->w121 || (chip->tm_w1 && chip->w120));

    if (chip->hclk2)
        chip->w124 = chip->tm_w1 && chip->tm_w2;
    chip->w125 = chip->w124 ? chip->hclk1 : 0;

    if (chip->hclk2)
        chip->w126[0] = chip->tm_w1 & 31;
    if (chip->hclk1)
        chip->w126[1] = chip->w126[0];

    if (chip->hclk1)
        chip->w127 = !chip->tm_w1;

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

    if (chip->w140)
    {
        chip->vram_address &= ~0x7c;
        chip->vram_address |= (chip->w131[0] & 0x3e) << 1;
    }

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

    if (chip->w137)
    {
        chip->vram_address &= ~0x7e;
        chip->vram_address |= (chip->w135[0] & 0x3f) << 1;
    }

    if (chip->hclk2)
        chip->w136 = chip->tm_w1;
    chip->w137 = chip->w136 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w138 = chip->tm_w1 && !chip->tm_w2;
    if (chip->hclk2)
        chip->w139 = chip->w138;
    chip->w140 = chip->w139 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w141 = chip->tm_w1;

    if (chip->hclk2)
    {
        chip->w142 = chip->tm_w1 ? 0 : ((chip->w143 + chip->w141) & 511);
        chip->w144 = chip->tm_w1;
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

    chip->cpu_pal = chip->tm_w1;
}
