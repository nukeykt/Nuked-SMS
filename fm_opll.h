#pragma once

typedef struct {
    int mclk;
    int cs;
    int we;
    int a0;
    int ic;
    int in_data;
} fmopll_input_t;

typedef struct {
    int tl;
    int dc;
    int dm;
    int fb;
    int am[2];
    int vib[2];
    int et[2];
    int ksr[2];
    int multi[2];
    int ksl[2];
    int ar[2];
    int dr[2];
    int sl[2];
    int rr[2];
} fmopll_patch_t;

typedef struct {
    int tl;
    int dc;
    int dm;
    int fb;
    int am;
    int vib;
    int et;
    int ksr;
    int multi;
    int ksl;
    int ar;
    int dr;
    int sl;
    int rr;
} fmopll_patch_cur_t;

typedef struct {
    // input
    fmopll_input_t input, o_input;

    int ic_latch[2];
    int ic_latch2[2];
    int prescaler_cnt[2];
    int clk1_latch[3];
    int clk1;
    int clk2_latch[3];
    int clk2;
    int clk_dac_latch;
    int clk_dac;
    int data_latch;
    int write_sr0;
    int write_sr1;
    int write0_latch[5];
    int write1_latch[5];

    int write0;
    int write1;

    int fsm_cnt1[2];
    int fsm_cnt2[2];

    int fsm_cnt_latch1[2];
    int fsm_cnt_latch2[2];
    int fsm_cnt_latch3[2];

    int fsm_out[14];

    int rclk_latch;
    int rclk1;
    int rclk2;

    int reg_write[8][2];
    int reg_write_rhy[2];
    int reg_write_test[2];

    fmopll_patch_t patch;

    int rhythm;
    int rhythm_kon;
    int testmode;

    int update_chan_regs;
    int chan_reg_addr;
    int chan_data;
    int update_chan_latch[2];
    int chan_cnt[2];
    int chan_fnum[9][2];
    int chan_block[3][2];
    int chan_kon[2];
    int chan_son[2];
    int chan_volume[4][2];
    int chan_inst[4][2];

    int fnum;
    int block;
    int kon;
    int son;
    int inst;
    int volume;
    int volume_latch1;
    int volume_latch2;
    int force_zerorate;
    int rhythm_sel[2];
    int inst0_sel;
    int modcar_sel_latch;
    int kon_latch;
    int hh_tom_latch;

    fmopll_patch_cur_t patch_latch[2];
    fmopll_patch_cur_t patch_cur;

    int fnum_latch[2];
    int block_latch[2];
    int multi_latch;
    int sl_latch;
    int fb_latch;
    int tremolo_latch;
    int vibrato_latch;
    int dc_latch[2];
    int dm_latch[2];
    int lfo_cnt[2];
    int trem_step;
    int trem_step_latch;
    int vib_cnt[2];
    int fnum_vib;
    int freq_multi[2];
    int pg_phase_latch[2];
    int pg_phase[19][2];
    int pg_reset_latch[2];
    int mc_latch[2];
    int eg_dokon[2];
    int debug_out[2][2];
    int pg_out;
    int lfsr[2];
    int noise_bit;
    int hh_load;
    int tc_load;
    int hh_bit2;
    int hh_bit3;
    int hh_bit7;
    int hh_bit8;
    int tc_bit3;
    int tc_bit5;
    int kon_comb;
    int trem_load1;
    int trem_load2;
    int trem_dir[2];
    int trem_sr[2];
    int trem_cb[2];
    int trem_out;
    int eg_timer_sr[2];
    int eg_timer_sr_masked[2];
    int eg_timer_bit_latch[2];
    int eg_timer_mask[2];
    int eg_ic_latch[2];
    int eg_sync_latch[2];
    int eg_timer_prescaler[2];
    int eg_subcnt1_latch[2];
    int eg_subcnt2_latch;
    int eg_timer_load;
    int eg_timer_carry[2];
    int eg_timer_low;
    int eg_shift;
    int eg_state[2][2];
    int eg_level[7][2];
    int eg_off;
    int eg_kon_latch[2];
    int eg_off_latch[2];
    int eg_ratesel;
    int eg_isrelease;
    int eg_resetlevel;
    int eg_instantattack;
    int eg_slreach;
    int eg_zeroreach;
    int eg_expstep;
    int eg_linstep;
    int eg_sllatch[2];
    int eg_ksr_freq;
    int eg_ksr_low[3];
    int eg_ksr_high;
    int eg_rate_latch;
    int eg_son_latch;
    int eg_rate1;
    int eg_kon_latch2;
    int eg_isrelease_notoff;
    int eg_son_latch2;
    int eg_zerorate[3];
    int eg_rate_latch2;
    int eg_rate_latch3;
    int eg_rate_high;
    int eg_rate_12;
    int eg_rate_13;
    int eg_rate_14;
    int eg_rate_15;
    int eg_shift_latch;
    int eg_subcnt1_latch2;
    int eg_subcnt2_latch2;
    int eg_step_hi;
    int eg_step1;
    int eg_step2;
    int eg_step3;
    int eg_step4;
    int eg_ksllatch;
    int eg_ksltl;
    int eg_ksltltrem;
    int eg_level_latch;
    int eg_out;
    int eg_silent[2];
    int op_logsin_add_delta;
    int op_logsin_base;
    int op_logsin_delta;
    int op_logsin;
    int op_shift[2];
    int op_pow_add_delta;
    int op_pow_base;
    int op_pow_delta;
    int op_pow;
    int op_sign[2];
    int op_fb[2][12][2];
    int op_mod[2];
    int op_fbmod[2];
    int op_modenable[2];
    int op_out;

    int ch_out[2];
    int ch_rhysr[9][2];
    int ch_m_en[2];
    int ch_r_en[2];
    int ch_debug[2];

    int out_m;
    int out_r;

    int oclk1;
    int oclk2;
} fm_opll_t;

void FMOPLL_Clock2(fm_opll_t *chip);
