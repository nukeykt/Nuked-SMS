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
        chip->w84 = !(!chip->tm_w1 || chip->w163);

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
        chip->w142 = chip->w162 ? 0 : ((chip->w143 + chip->w141) & 511);
        chip->w144 = chip->w162;
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

    if (chip->hclk2)
    {
        chip->w146 = chip->v_pla[0];
        chip->w147 = chip->v_pla[1];
        chip->w148 = chip->v_pla[2];
        chip->w149 = chip->v_pla[3];
        chip->w150 = chip->v_pla[4];
        chip->w152 = chip->v_pla[5];
        chip->w153 = chip->v_pla[6];
        chip->w154 = chip->v_pla[7];
        chip->w155 = chip->v_pla[8];
        chip->w157 = chip->v_pla[9];
        chip->w158 = chip->v_pla[10];
        chip->w160 = chip->v_pla[11];
        chip->w161 = chip->v_pla[12] || chip->v_pla[13];
    }

    if (chip->tm_w1 || chip->w150 || chip->w149)
        chip->w151 = 1;
    else if (chip->w148 || chip->w147)
        chip->w151 = 0;

    if (chip->tm_w1 || chip->w155 || chip->w154)
        chip->w156 = 1;
    else if (chip->w153 || chip->w152)
        chip->w156 = 0;

    if (chip->w158)
        chip->w159 = 1;
    else if (chip->tm_w1 || chip->w157)
        chip->w159 = 0;


    if (chip->hclk1)
        chip->w162 = chip->tm_w1 || (chip->w161 && chip->tm_w2);

    if (chip->w237)
    {
        chip->vram_address &= ~0x3ff;
        chip->vram_address |= chip->tm_w1 & 0x1f;
        chip->vram_address |= ((chip->w145 >> 3) & 0x1f) << 5;
    }
    if (chip->w243)
    {
        chip->vram_address &= ~0x1800;
        chip->vram_address |= ((chip->w145 >> 6) & 3) << 11;
    }
    if (chip->w234)
    {
        chip->vram_address &= ~0x1807;
        chip->vram_address |= ((chip->w145 >> 6) & 3) << 11;
        chip->vram_address |= chip->w145 & 7;
    }
    if (chip->w249)
    {
        chip->vram_address &= ~7;
        chip->vram_address |= (chip->w145 >> 2) & 7;
    }
    if (chip->w246)
    {
        chip->vram_address &= ~7;
        chip->vram_address |= chip->w145 & 7;
    }

    chip->w163 = !chip->tm_w1;

    chip->w164 = chip->tm_w1 || chip->w160;

    chip->cpu_rd = chip->tm_w1;
    chip->cpu_wr = chip->tm_w1;
    chip->cpu_iorq = chip->tm_w1;
    chip->cpu_a0 = chip->tm_w1;
    chip->cpu_a6 = chip->tm_w1;
    chip->cpu_a7 = chip->tm_w1;


    chip->w164 = !chip->cpu_a6 || chip->cpu_iorq || chip->cpu_a7 || chip->cpu_rd;

    chip->w165 = !(chip->cpu_rd || chip->cpu_iorq || chip->cpu_a6 || !chip->cpu_a7);
    chip->w166 = !chip->w165;

    chip->w167 = !(chip->cpu_wr || chip->cpu_iorq || chip->cpu_a6 || !chip->cpu_a7);
    chip->w168 = !chip->w167;

    chip->w169 = chip->w165 || chip->w167;

    if (chip->w166)
        chip->w170 = chip->cpu_a0;

    chip->w171 = !(chip->w166 || chip->w170);

    if (chip->w168)
        chip->w172 = !chip->cpu_a0;

    chip->w173 = !(chip->w166 || !chip->cpu_a0);
    chip->w174 = !(chip->w166 || chip->cpu_a0);

    chip->w175 = !(chip->w168 || !chip->w172);
    chip->w176 = !(chip->w168 || chip->w172 || chip->w186);
    chip->w177 = !(chip->w168 || chip->w172 || chip->w186n);

    chip->w178 = chip->w173;
    chip->w179 = chip->w174;
    chip->w180 = chip->w175;

    chip->w181 = !(chip->w178 || chip->w179 || chip->w180 || chip->w177);

    chip->w182 = !chip->w177;

    chip->w183 = !chip->w176;

    if (chip->w177)
        chip->w184 = 0;
    else if (chip->tm_w1 || chip->w194[1])
        chip->w184 = 1;

    if (chip->tm_w1 || chip->w188)
        chip->w185 = 0;
    else if (chip->w176)
        chip->w185 = 1;
    if (chip->w176)
        chip->w185n = 0;
    else if (chip->tm_w1 || chip->w188)
        chip->w185n = 1;

    if (chip->tm_w1 || (chip->tm_w2 && chip->w185n))
        chip->w186 = 0;
    else if (chip->tm_w2 && chip->w185)
        chip->w186 = 1;
    if (chip->w194[1] && chip->w185)
        chip->w186n = 0;
    else if (chip->tm_w1 || (chip->w194[1] && chip->w185n))
        chip->w186n = 1;

    if (chip->w169)
        chip->w187 = 0;
    else if (chip->tm_w1 || chip->tm_w2)
        chip->w187 = 1;

    chip->w188 = !chip->w181;

    if (chip->hclk1)
        chip->w189 = chip->w187;
    if (chip->hclk2)
        chip->w190 = !chip->w189;

    if (chip->hclk1)
        chip->w191[0] = !chip->w190;
    if (chip->hclk2)
        chip->w191[1] = chip->w191[0];

    chip->w192 = !(chip->tm_w1 || chip->w190 || chip->w191[1]);

    if (chip->hclk1)
        chip->w193[0] = chip->w192;
    if (chip->hclk2)
        chip->w193[1] = chip->w193[0];

    if (chip->hclk1)
        chip->w194[0] = chip->w193[1];
    if (chip->hclk2)
        chip->w194[1] = chip->w194[0];

    chip->w195 = chip->w192 && chip->reg_code == 0 && !chip->w184;

    if (chip->w195 || chip->w180 || chip->w171)
        chip->w196 = 0;
    else if (chip->w201[1] || chip->tm_w2)
        chip->w196 = 1;

    if (chip->hclk2)
        chip->w197 = !chip->w194[0];

    chip->w198 = !(chip->w196 || chip->w197);

    if (chip->w198)
        chip->w199 = 0;
    else if (chip->w201[1] || chip->tm_w2)
        chip->w199 = 1;

    chip->w200 = !(chip->w199 || chip->tm_w1);

    chip->w201 = !chip->w200;

    if (chip->hclk1)
        chip->w201[0] = chip->w200;
    if (chip->hclk2)
        chip->w201[1] = chip->w201[0];

    if (chip->hclk1)
        chip->w202[0] = chip->w201[1];
    if (chip->hclk2)
        chip->w202[1] = chip->w202[0];

    chip->w203 = !chip->w202[1];

    if (chip->hclk1)
        chip->w204[0] = chip->w202[1];
    if (chip->hclk2)
        chip->w204[1] = chip->w204[0];

    if (chip->hclk1)
        chip->w205[0] = chip->w204[1];
    if (chip->hclk2)
        chip->w205[1] = chip->w205[0];

    if (chip->w180)
        chip->w206 = 0;
    else if (chip->tm_w1 || chip->w205[1])
        chip->w206 = 1;
    if (chip->tm_w1 || chip->w205[1])
        chip->w206n = 0;
    else if (chip->w180)
        chip->w206n = 1;

    chip->w207 = chip->w206 && chip->w204[1];

    chip->w208 = chip->w206n && chip->w212 && chip->w201[1];
    chip->w209 = chip->w206n && !chip->w212 && chip->w201[1];

    chip->w210 = !(chip->w194[1] || chip->w193[1]);

    chip->w211 = chip->reg_code == 2 && !chip->w184 && !chip->w210;

    chip->w212 = chip->reg_code != 3;

    if (!chip->w183)
    {
        chip->w214 = chip->w213 = chip->io_data & 255;
    }
    else
    {
        int i;
        int bit = chip->w215[1];
        for (i = 0; i < 8; i++)
        {
            int shift = 1 << i;
            if (bit)
            {
                chip->w213 &= ~shift;
                chip->w213 |= (chip->w214 & shift) ^ shift;
            }
            else
            {
                chip->w214 &= ~shift;
                chip->w214 |= chip->w213 & shift;
            }
            bit = (chip->w214 >> i) & 1;
        }
    }

    if (chip->hclk1)
        chip->w215[0] = chip->w203;
    if (chip->hclk2)
        chip->w215[1] = chip->w215[0];

    if (!chip->w182)
    {
        chip->w217 = chip->w216 = chip->io_data & 63;
        chip->reg_code = (chip->io_data >> 6) & 3;
    }
    else
    {
        int i;
        int bit = (chip->w214 >> 7) & 1;
        for (i = 0; i < 6; i++)
        {
            int shift = 1 << i;
            if (bit)
            {
                chip->w216 &= ~shift;
                chip->w216 |= (chip->w217 & shift) ^ shift;
            }
            else
            {
                chip->w217 &= ~shift;
                chip->w217 |= chip->w216 & shift;
            }
            bit = (chip->w217 >> i) & 1;
        }
    }

    chip->reg_addr = (chip->w217 << 8) | chip->w214;

    chip->reg_sel[0] = (chip->reg_addr & 0xf00) == 0x000 && chip->w211;
    chip->reg_sel[1] = (chip->reg_addr & 0xf00) == 0x100 && chip->w211;
    chip->reg_sel[2] = (chip->reg_addr & 0xf00) == 0x200 && chip->w211;
    chip->reg_sel[3] = (chip->reg_addr & 0xf00) == 0x300 && chip->w211;
    chip->reg_sel[4] = (chip->reg_addr & 0xf00) == 0x400 && chip->w211;
    chip->reg_sel[5] = (chip->reg_addr & 0xf00) == 0x500 && chip->w211;
    chip->reg_sel[6] = (chip->reg_addr & 0xf00) == 0x600 && chip->w211;
    chip->reg_sel[7] = (chip->reg_addr & 0xf00) == 0x700 && chip->w211;
    chip->reg_sel[8] = (chip->reg_addr & 0xf00) == 0x800 && chip->w211;
    chip->reg_sel[9] = (chip->reg_addr & 0xf00) == 0x900 && chip->w211;
    chip->reg_sel[10] = (chip->reg_addr & 0xf00) == 0xa00 && chip->w211;

    chip->reset1 = chip->tm_w1;

    if (chip->reg_sel[0])
    {
        chip->reg_80_b0 = (chip->reg_addr >> 0) & 1;
        chip->reg_80_b1 = (chip->reg_addr >> 1) & 1;
        chip->reg_80_b2 = (chip->reg_addr >> 2) & 1;
        chip->reg_80_b3 = (chip->reg_addr >> 3) & 1;
        chip->reg_80_b4 = (chip->reg_addr >> 4) & 1;
        chip->reg_80_b5 = (chip->reg_addr >> 5) & 1;
        chip->reg_80_b6 = (chip->reg_addr >> 6) & 1;
        chip->reg_80_b7 = (chip->reg_addr >> 7) & 1;
    }
    else if (chip->reset1)
    {
        chip->reg_80_b0 = 0;
        chip->reg_80_b1 = 0;
        chip->reg_80_b2 = 0;
        chip->reg_80_b3 = 0;
        chip->reg_80_b4 = 0;
        chip->reg_80_b5 = 0;
        chip->reg_80_b6 = 0;
        chip->reg_80_b7 = 0;
    }

    if (chip->reg_sel[1])
    {
        chip->reg_81_b0 = (chip->reg_addr >> 0) & 1;
        chip->reg_81_b1 = (chip->reg_addr >> 1) & 1;
        chip->reg_81_b2 = (chip->reg_addr >> 2) & 1;
        chip->reg_81_b3 = (chip->reg_addr >> 3) & 1;
        chip->reg_81_b4 = (chip->reg_addr >> 4) & 1;
        chip->reg_81_b5 = (chip->reg_addr >> 5) & 1;
        chip->reg_81_b6 = (chip->reg_addr >> 6) & 1;
    }
    else if (chip->reset1)
    {
        chip->reg_81_b0 = 0;
        chip->reg_81_b1 = 0;
        chip->reg_81_b2 = 0;
        chip->reg_81_b3 = 0;
        chip->reg_81_b4 = 0;
        chip->reg_81_b5 = 0;
        chip->reg_81_b6 = 0;
    }

    if (chip->reg_sel[2])
    {
        chip->reg_nt = (chip->reg_addr >> 0) & 15;
    }

    if (chip->w226)
    {
        chip->vram_address &= ~0x3c00;
        chip->vram_address |= chip->reg_nt << 10;
    }

    if (chip->reg_sel[3])
    {
        chip->reg_ct = (chip->reg_addr >> 0) & 255;
    }

    if (chip->w219)
    {
        chip->vram_address &= ~0x3fc0;
        chip->vram_address |= chip->reg_ct << 6;
    }

    if (chip->reg_sel[4])
    {
        chip->reg_bg = (chip->reg_addr >> 0) & 7;
    }

    if (chip->w224)
    {
        chip->vram_address &= ~0x3800;
        chip->vram_address |= chip->reg_bg << 11;
    }

    if (chip->reg_sel[5])
    {
        chip->reg_sat = (chip->reg_addr >> 0) & 127;
    }

    if (chip->w222)
    {
        chip->vram_address &= ~0x3f80;
        chip->vram_address |= chip->reg_sat << 7;
    }

    if (chip->reg_sel[6])
    {
        chip->reg_spr = (chip->reg_addr >> 0) & 7;
    }

    if (chip->w229)
    {
        chip->vram_address &= ~0x3800;
        chip->vram_address |= chip->reg_spr << 11;
    }

    if (chip->hclk1)
        chip->w218[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w218[1] = chip->w218[0];
    chip->w219 = chip->w218[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w220 = chip->tm_w1;
    if (chip->hclk2)
        chip->w221 = (chip->w220 && chip->tm_w1) || (chip->tm_w2 && chip->tm_w3);
    chip->w222 = chip->w221 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w223[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w223[1] = chip->w223[0];

    chip->w224 = chip->w223[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w225[0] = chip->tm_w1;
    if (chip->hclk2)
        chip->w225[1] = chip->w225[0];

    chip->w226 = chip->w225[1] ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w227 = chip->tm_w1;
    if (chip->hclk2)
        chip->w228 = (chip->w227 && chip->tm_w1) || (chip->tm_w2 && chip->tm_w3);
    chip->w229 = chip->w228 ? chip->hclk1 : 0;

    if (chip->hclk1)
        chip->w230[0] = !chip->w201;
    if (chip->hclk2)
        chip->w230[1] = chip->w230[0];
    chip->w231 = chip->w230[1] ? chip->hclk1 : 0;

    if (chip->w231)
    {
        chip->vram_address = chip->reg_addr & 0x3fff;
    }

    chip->w232 = !(chip->w240 || chip->tm_w2 || !chip->tm_w3);

    if (chip->hclk1)
        chip->w233[0] = chip->w232;
    if (chip->hclk2)
        chip->w233[1] = chip->w233[0];

    chip->w234 = chip->w233[1] ? chip->hclk1 : 0;

    chip->w235 = !(!chip->tm_w1 || chip->tm_w2);

    if (chip->hclk1)
        chip->w236[0] = chip->w235;
    if (chip->hclk2)
        chip->w236[1] = chip->w236[0];

    chip->w237 = chip->w236[1] ? chip->hclk1 : 0;

    chip->w238 = !chip->tm_w1;

    chip->w239 = !chip->tm_w1;

    chip->w240 = !chip->tm_w1;

    chip->w241 = !(chip->w239 || chip->tm_w1 || chip->w240);

    if (chip->hclk1)
        chip->w242[0] = chip->w241;
    if (chip->hclk2)
        chip->w242[1] = chip->w242[0];

    chip->w243 = chip->w242[1] ? chip->hclk1 : 0;

    chip->w244 = !(chip->tm_w1 || chip->tm_w2 || chip->w239);

    if (chip->hclk1)
        chip->w245[0] = chip->w244;
    if (chip->hclk2)
        chip->w245[1] = chip->w245[0];

    chip->w246 = chip->w245[1] ? chip->hclk1 : 0;

    chip->w247 = !(chip->w238 || chip->w239 || chip->tm_w1);

    if (chip->hclk1)
        chip->w248[0] = chip->w247;
    if (chip->hclk2)
        chip->w248[1] = chip->w248[0];

    chip->w249 = chip->w248[1] ? chip->hclk1 : 0;

    if (chip->tm_w1)
        chip->w250 = 1;
    else if (chip->w263)
        chip->w250 = 0;

    if (chip->w258)
        chip->w251 = 1;
    else if (chip->w263)
        chip->w251 = 0;

    if (chip->w255)
        chip->w252 = 1;
    else if (chip->w263)
        chip->w252 = 0;

    if (!chip->tm_w1)
    {
        chip->io_data &= ~0xe0;
        chip->io_data |= chip->w250 << 5;
        chip->io_data |= chip->w251 << 6;
        chip->io_data |= chip->w252 << 7;
    }

    chip->w253 = chip->w251;

    chip->w254 = !chip->w178;

    chip->w255 = chip->tm_w1 && chip->tm_w2;

    chip->w257 = !chip->w252;

    chip->w256 = chip->w257 || !chip->tm_w1;

    chip->w258 = !(!chip->w257 || !chip->tm_w1);

    if (chip->w178 || chip->reset1)
        chip->w259 = 0;
    else if (!chip->w261[1])
        chip->w259 = 1;

    if (chip->hclk1)
        chip->w260[0] = !chip->w259;
    if (chip->hclk2)
        chip->w260[1] = chip->w260[0];

    if (chip->hclk1)
        chip->w261[0] = !chip->w260[1];
    if (chip->hclk2)
        chip->w261[1] = chip->w261[0];

    chip->w262 = !(chip->reset1 || chip->w261[1] || chip->w260[1]);

    if (chip->hclk1)
        chip->w263 = chip->w262;

    if (chip->hclk1)
        chip->w264 = !chip->tm_w1;

    chip->w265 = chip->w264 ? chip->hclk2 : 0;

    if (chip->hclk1)
        chip->w266 = chip->tm_w1;
    chip->w267 = chip->w266 ? chip->hclk2 : 0;

    chip->w268 = !(chip->w267 || chip->w180);

    chip->w269 = !chip->w179;

    if (chip->w180)
        chip->w270 = chip->io_data & 255;
    else if (chip->w267)
        chip->w270 = chip->vram_data & 255;
    else if (chip->w268)
        chip->w270 = chip->w270;

    if (chip->w265)
        chip->vram_data = chip->w270;
    if (!chip->w269)
        chip->io_data = chip->w270;

    chip->w271 = !(chip->tm_w1 || chip->tm_w2);

    if (chip->hclk1)
        chip->w272 = chip->tm_w1;

    chip->w273 = chip->w272 ? chip->hclk1 : 0;

    chip->w274 = !(chip->w273 || chip->w271);

    if (chip->w273)
        chip->w275 = chip->tm_w1;
    else if (chip->w271)
        chip->w275 = chip->tm_w2;
    else if (chip->w274)
        chip->w275 = chip->w275;

    if (!chip->w254)
    {
        chip->io_data &= ~31;
        chip->io_data |= chip->w275 & 31;
    }

    chip->w276 = !chip->tm_w1;

    if (chip->hclk1)
        chip->w277 = (chip->w276 && chip->tm_w1 && chip->tm_w2) || (chip->w276 && !chip->tm_w1 && chip->tm_w3);

    chip->w278 = chip->w277 ? chip->hclk2 : 0;

    if (chip->w278)
        chip->w279 = chip->vram_data;
    else if (chip->hclk1)
        chip->w279 = chip->w279;

    chip->w280 = (chip->w279 & 15) == 0;
    chip->w281 = (chip->w279 & 240) == 0;
}
