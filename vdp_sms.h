#pragma once

typedef struct {
    int ad_i;
    int reset;
    int xin;
    int hl;
    int pal;
    int rd;
    int wr;
    int iorq;
    int a0;
    int a6;
    int a7;
    int a14;
    int a15;
    int csync;
    int nmi;
    int mreq;
    int data;
} vdpsms_input_t;

typedef struct {

    int i1;
    int i2;
    int i3;
    int i4;

    int w561;
    int w562;
    int w563;
    int w564;
    int w565;
    int w566;
    int w567;
    int w568;
    int w569;
    int w570;
    int w571;
    int w572;
    int w573;
    int w574;
    int w575;
    int w576;
    int w577[2];
    int w578;
    int w579;
    int w580[4];
    int w581;
    int w582;
    int w583;
    int w584;
    int w585;
    int w586;
    int w587;
    int w589;
    int w590;
    int w591[2];
    int w592;
    int w593[2];
    int w594;
    int w595;
    int w596;
    int w597[2];
    int w598;
    int w599[2];
    int w600;
    int w601;
    int w602;
    int w603;
    int w604;
    int w605;
    int w606;
    int w639[3];
} vdpsms_spriteunit1_t; // mode 4 & tms sprite

typedef struct {
    int i_clk;
    int i_reset;
    int i_write;
    int i_data;

} vdpsms_psg_input_t;

typedef struct {
    vdpsms_psg_input_t input;

    int clk1;
    int clk2;
    int hclk1;
    int hclk2;
    int w663[2];
    int w664;
    int w665[2];
    int w666;
    int w667[2];
    int w668[2];
    int w669;
    int w670;
    int w671;
    int w672[2];
    int w673[2];
    int data_latch;
    int w674;
    int w675;
    int w676;
    int w677;
    int w678;
    int w679;
    int w680;
    int w681;
    int w682;
    int w683;
    int w684;
    int w685;
    int w686;
    int w687;
    int w688;
    int w689;
    int w690;
    int w691;
    int w692;
    int w693;
    int w694[2];
    int w695[2];
    int w696[2];
    int w697;
    int w698[2];
    int w699;
    int w700[2];
    int w701[2];
    int w702[2];
    int w703[2];
    int w704[2];
    int w705;
    int w706;
    int w707[2];
    int w708[3];
    int w709;
    int noise_lfsr[2];
    int w710[2];
    int w711;
    int w712;
    int w713;
    int w714;
    int w715;
    int w716;
    int w717;
    int w718;
    int w719;
    int w720;
    int w721;
    int w722;
    float dac[4];
    float o_dac;
} vdpsms_psg_t;

typedef struct {

    int i1;
    int i2;
    int i3;

    int w607;
    int w608;
    int w609;
    int w610;
    int w611;
    int w612[2];
    int w613;
    int w614;
    int w615[4];
    int w616;
    int w617;
    int w618;
    int w619;
    int w620;
    int w621;
    int w622;
    int w623;
    int w624[2];
    int w625;
    int w626;
    int w627[2];
    int w628;
    int w629;
    int w630[2];
    int w631;
    int w632;
    int w633[2];
    int w634;
    int w635;
    int w636;
    int w637[3];
    int w638;
    int w640;
} vdpsms_spriteunit2_t; // mode 4 sprite

typedef struct {
    vdpsms_input_t input;
    vdpsms_input_t o_input;

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
    int w62;
    int w63;
    int w64;
    int w65;
    int w66;
    int w67;
    int w68;
    int w69;
    int w70;
    int w71;
    int w72;
    int w73;
    int w74;
    int w75;
    int w76;
    int w77;
    int w78;
    int w79;
    int w80;
    int w81;
    int w82;
    int w83;
    int w84;
    int w85[2];
    int w86;
    int w87[2];
    int w88;
    int w89[2];
    int w90[2];
    int w91;
    int w92;
    int w93;
    int w94;
    int w95;
    int w96[2];
    int w97;
    int w98;
    int w99;
    int w100;
    int w101;
    int w102[2];
    int w103;
    int w104[2];
    int w105;
    int w106;
    int w107;
    int w108;
    int w109;
    int w110[2];
    int w111[2];
    int w112[2];
    int w113[2];
    int w114[2];
    int w115[2];
    int w116[2];
    int w117[2];
    int w118;
    int w119[2];
    int w120;
    int w121;
    int w122;
    int w123;
    int w124;
    int w125;
    int w126[2];
    int w127;
    int w128[2];
    int w129[2];
    int w130[2];
    int w131[2];
    int w132[2];
    int w133[2];
    int w134[2];
    int w135[2];
    int w136;
    int w137;
    int w138;
    int w139;
    int w140;
    int w141;
    int w142;
    int w143;
    int w144;
    int w145; // v counter
    int v_pla[14];
    int w146;
    int w147;
    int w148;
    int w149;
    int w150;
    int w151;
    int w152;
    int w153;
    int w154;
    int w155;
    int w156;
    int w157;
    int w158;
    int w159;
    int w160;
    int w161;
    int w162;
    int w163;
    int w164;
    int w164_;
    int w165;
    int w166;
    int w167;
    int w168;
    int w169;
    int w170;
    int w171;
    int w172;
    int w173;
    int w174;
    int w175;
    int w176;
    int w177;
    int w178;
    int w179;
    int w180;
    int w181;
    int w182;
    int w183;
    int w184;
    int w185;
    int w185n;
    int w186;
    int w186n;
    int w187;
    int w188; // sync trigger
    int w189; // sync trigger
    int w190;
    int w191[2];
    int w192;
    int w193[2];
    int w194[2];
    int w195;
    int w196;
    int w197;
    int w198;
    int w199;
    int w200;
    int w201;
    int w201_[2];
    int w202[2];
    int w203;
    int w204[2];
    int w205[2];
    int w206;
    int w206n;
    int w207;
    int w208;
    int w209;
    int w210;
    int w211;
    int w212;
    int w213;
    int w214;
    int w215[2];
    int w216;
    int w217;
    int reg_sel[11];
    int w218[2];
    int w219;
    int w220;
    int w221;
    int w222;
    int w223[2];
    int w224;
    int w225[2];
    int w226;
    int w227;
    int w228;
    int w229;
    int w230[2];
    int w231;
    int w232;
    int w233[2];
    int w234;
    int w235;
    int w236[2];
    int w237;
    int w238;
    int w239;
    int w240;
    int w241;
    int w242[2];
    int w243;
    int w244;
    int w245[2];
    int w246;
    int w247;
    int w248[2];
    int w249;
    int w250;
    int w251;
    int w252;
    int w253;
    int w254;
    int w255;
    int w256;
    int w257;
    int w258;
    int w259;
    int w260[2];
    int w261[2];
    int w262;
    int w263;
    int w264;
    int w265;
    int w266;
    int w267;
    int w268;
    int w269;
    int w270;
    int w271;
    int w272;
    int w273;
    int w274;
    int w275;
    int w276;
    int w277;
    int w278;
    int w279;
    int w280;
    int w281;
    int w282;
    int w283;
    int w284;
    int w285;
    int w286;
    int w287;
    int w288;
    int w289;
    int w290[4];
    int w291;
    int w292;
    int w293;
    int w294;
    int w295;
    int w296;
    int w297;
    int w298;
    int w299;
    int w300;
    int w301[9];
    int w302;
    int w303[2];
    int w304;
    int w305;
    int w306[2];
    int w307;
    int w308;
    int w309;
    int w310[2];
    int w311;
    int w312;
    int w313;
    int w314[2];
    int w315[2];
    int w316;
    int w317;
    int w318;
    int w319;
    int w320;
    int w321;
    int w322[2];
    int w323;
    int w324[2];
    int w325;
    int w326;
    int w327;
    int w328[2];
    int w329;
    int w330[2];
    int w331;
    int w332;
    int w333;
    int w334;
    int w335[2];
    int w336;
    int w337;
    int w338[2];
    int w339;

    int hpla[57];

    int w340[22];
    int w341[21];
    int w342[13];
    int w343[13];
    int w344[2];
    int w345[2];
    int w346[2];
    int w347[2];
    int w348[2];
    int w349[2];
    int w350[2];
    int w351[2];
    int w352[2];
    int w353[2];
    int w354[2];
    int w355[2];
    int w356[2];
    int w357[2];
    int w358[2];
    int w359[2];
    int w360;
    int w361;
    int w362;
    int w363;
    int w364;
    int w365;
    int w366[2];
    int w367[2];
    int w368[2];
    int w369[2];
    int w370[2];
    int w371[2];
    int w372[2];
    int w373[2];
    int w374[2];
    int w375[2];
    int w376[2];
    int w377[2];
    int w378[2];
    int w379[2];
    int w380[2];
    int w381[2];
    int w382[2];
    int w383;
    int w384;
    int w385;
    int w386;
    int w387;
    int w388;
    int w389;
    int w390;
    int w391;
    int w392;
    int w393;
    int w394;
    int w395;
    int w396;
    int w397;
    int w398;
    int w399;
    int w400[2];
    int w401;
    int w402;
    int w403;
    int w404;
    int w405[2];
    int w406;
    int w407;
    int w408[2];
    int w409;
    int w410;
    int w411;
    int w412;
    int w413;
    int w414;
    int w415;
    int w416;
    int w417;
    int w418[4];
    int w419;
    int w420;
    int w421;
    int w422;
    int w423;
    int w424;
    int w425;
    int w426;
    int w427[2];
    int w428;
    int w429;
    int w430;
    int w431;
    int w432;
    int w433;
    int w434;
    int w435[2];
    int w436;
    int w437;
    int w438;
    int w438_[4];
    int w439;
    int w440;
    int w441;
    int w442[4];
    int w443;
    int w444;
    int w445;
    int w446;
    int w447;
    int w448;
    int w449;
    int w450;
    int w451;
    int w452;
    int w453;
    int w454;
    int w455;
    int w456;
    int w457;
    int w458;
    int reg_bc;
    int reg_fc;
    int w459;
    int w460;
    int w461;
    int w462;
    int w463;
    int w464;
    int w465;
    int w466;
    int w467;
    int w468;
    int w469;
    int w470;
    int w471;
    int w472;
    int w473;
    int w474;
    int w475;
    int w476;
    int w477;
    int w478;
    int w479;
    int w480;
    int w481;
    int w482;
    int w483;
    int w484;
    int w485;
    int w486[4];
    int w487;
    int w488;
    int w489;
    int w490;
    int w491;
    int w492;
    int w493;
    int w494;
    int w495;
    int w496;
    int w497;
    int w498;
    int w499;
    int w500[2];
    int w501[6];
    int w502;
    int w503;
    int w504[2];
    int w505;
    int w506;
    int w507;
    int w508;
    int w509;
    int w510;
    int w511;
    int w512[2];
    int w513;
    int w514;
    int w515[2];
    int w516;
    int w517;
    int w518;
    int w519;
    int w520[2];
    int w521[4];
    int w522[2];
    int w523;
    int w524[2];
    int w525;
    int w526;
    int w527[2];
    int w528;
    int w529;
    int w530[2];
    int w531[2];
    int w532;
    int w533;
    int w534;
    int w535;
    int w536;
    int w537[2];
    int w538;
    int w539;
    int w540;
    int w541;
    int w542;
    int w543;
    int w544;
    int w545[5];
    int w546[2];
    int w547[4];
    int w548;
    int w549[2];
    int w550[8];
    int w551[8][2];
    int w552[4];
    int w553[8][4];
    int w554[4];
    int w555[4];
    int w556;
    int w557[2];
    int w558;
    int w559;
    int w560[5][2];
    int w588;
    int w641;
    int w642;
    int w643;
    int w644;
    int w645;
    int color_ram_index;
    int w646[2];
    //int w647;
    //int w648;
    int color_ram_write;
    int w649;
    int color_ram[32];
    int color_ram_bus;
    int w650;
    int w651;
    int w652[2];
    int w653;
    int w654;
    int w655;
    int w656;
    int w657[2];
    int w658;
    int w659;
    int w660;
    int w661;
    int w662;
    int dac_sel;

    int w723[2];
    int w724[2];
    int w725;
    int w726;
    int w727;
    int w728[2];
    int w729[2];
    int w730[2];
    int w731;
    int zclk;
    int w732;
    int w733;
    int w734[2];
    int w735[2];
    int w736;
    int w737;
    int w738;
    int w739;
    int w740;
    int w741;
    int w742[2];
    int w743;
    int w744[2];
    int w745[2];
    int w746;
    int w747;
    int w748[2];
    int w749;
    int w750;
    int w751[2];
    int w752;
    int w753;
    int w754[2];
    int w755[8];
    int w756;
    int w757;
    int w758[2];
    int nmi_dff[2];
    int w759;
    int w760;
    int w761;

    vdpsms_psg_t psg;


    int cpu_pal;
    int cpu_rd;
    int cpu_wr;
    int cpu_iorq;
    int cpu_a0;
    int cpu_a6;
    int cpu_a7;

    int io_data;

    int reg_addr;
    int reg_code;

    int vram_data;
    int vram_data2;
    int vram_address;

    int color_index;
    int color_palette;

    int clk1;
    int clk2;

    int hclk1;
    int hclk2;

    int reset1;

    int reg_80_b0;
    int reg_80_b1;
    int reg_80_b2;
    int reg_80_b3;
    int reg_80_b4;
    int reg_80_b5;
    int reg_80_b6;
    int reg_80_b7;

    int reg_81_b0;
    int reg_81_b1;
    int reg_81_b2;
    int reg_81_b3;
    int reg_81_b4;
    int reg_81_b5;
    int reg_81_b6;

    int reg_nt;
    int reg_ct;
    int reg_bg;
    int reg_sat;
    int reg_spr;

    vdpsms_spriteunit1_t sprite1[4];
    vdpsms_spriteunit2_t sprite2[4];

    int o_dac_r;
    int o_dac_g;
    int o_dac_b;

    int o_zclk;

    int o_csync;

    int o_pcp;
    int o_cbt;

    int o_nmi;

    int o_kbsel;
    int o_csram;
    int o_exm1;
    int o_exm2;

    int o_ys;

    int o_ad;
    int o_ad_z;
    int o_oe;
    int o_we0;
    int o_we1;
    int o_ce;
    int o_int;

    int o_data;
    int o_data_z;


    int dbg_address;
} vdpsms_t;

void VDPSMS_Clock2(vdpsms_t *chip);
