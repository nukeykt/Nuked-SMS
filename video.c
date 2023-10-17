/*
 * Copyright (C) 2023 nukeykt
 *
 * This file is part of Nuked-MD.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *  SDL/Video routines
 *
 */

#include <stdio.h>
#include <string.h>
#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "video.h"
#include "vdp_sms.h"

extern vdpsms_t vdp;
extern int pal;
extern uint64_t mcycles;

SDL_Window* vid_window;
SDL_Renderer* vid_renderer;
SDL_Texture* vid_texture;

uint32_t vid_counter;
uint32_t vid_counter_write;
uint64_t vid_mcycles;

FILE* vid_dump_file;

uint32_t vid_workbuffer[VID_HEIGHT][VID_WIDTH];
uint32_t vid_currentbuffer[VID_HEIGHT][VID_WIDTH];
uint8_t vid_filebuffer[VID_HEIGHT][VID_WIDTH][3];
SDL_mutex* vid_mutex;

uint64_t frame_mcycles;

void Video_Init(char* videoout_filename)
{
    vid_counter = vid_counter_write = 0;

    vid_window = SDL_CreateWindow("Nuked SMS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        VID_WIDTH, VID_HEIGHT * 2, SDL_WINDOW_SHOWN);
    if (!vid_window)
        return;

    vid_renderer = SDL_CreateRenderer(vid_window, -1, 0);
    if (!vid_renderer)
        return;

    vid_texture = SDL_CreateTexture(vid_renderer, SDL_PIXELFORMAT_BGR888, SDL_TEXTUREACCESS_STREAMING,
        VID_WIDTH, VID_HEIGHT);

    if (!vid_texture)
        return;

    //vid_dump_file = fopen(videoout_filename, "wb");

    vid_mutex = SDL_CreateMutex();
}

void Video_Shutdown(void)
{
    if (vid_dump_file) {
        fclose(vid_dump_file);
        vid_dump_file = NULL;
    }
}

void Video_Blit(void)
{
    SDL_LockMutex(vid_mutex);
    SDL_UpdateTexture(vid_texture, NULL, vid_currentbuffer, VID_WIDTH * 4);

    if (vid_dump_file)
    {
        if (vid_counter_write < vid_counter)
        {
            int x, y;
            for (y = 0; y < VID_HEIGHT; y++)
            {
                for (x = 0; x < VID_WIDTH; x++)
                {
                    uint32_t abgr = vid_currentbuffer[y][x];
                    vid_filebuffer[y][x][0] = (abgr >> 0) & 255;
                    vid_filebuffer[y][x][1] = (abgr >> 8) & 255;
                    vid_filebuffer[y][x][2] = (abgr >> 16) & 255;
                }
            }
            memcpy(vid_filebuffer, &vid_mcycles, sizeof(vid_mcycles));
            fwrite(vid_filebuffer, 1, sizeof(vid_filebuffer), vid_dump_file);
            fflush(vid_dump_file);
            vid_counter_write = vid_counter;
        }
    }

    SDL_UnlockMutex(vid_mutex);
    SDL_RenderCopy(vid_renderer, vid_texture, NULL, NULL);
    SDL_RenderPresent(vid_renderer);
}

void Video_PlotVDP(void)
{
    static int ocsync;
    static int plot_x;
    static int plot_y;
    static int csync_cnt;

    if (!ocsync && vdp.o_csync)
    {
        if (csync_cnt >= 100)
        {
            // vsync
            plot_y = 0;
            if (pal)
                plot_y = -22;
            SDL_LockMutex(vid_mutex);
            memcpy(vid_currentbuffer, vid_workbuffer, sizeof(vid_workbuffer));
            vid_mcycles = frame_mcycles;
            vid_counter++;
            SDL_UnlockMutex(vid_mutex);
            memset(vid_workbuffer, 0, sizeof(vid_workbuffer));
            frame_mcycles = mcycles;

            Video_Blit();
        }
        else
        {
            // hsync
            plot_x = 0;
            plot_y++;
        }
        csync_cnt = 0;
    }
    else if (!vdp.o_csync)
    {
        csync_cnt++;
    }

    if (plot_x >= 0 && plot_x < VID_WIDTH && plot_y >= 0 && plot_y < VID_HEIGHT/* && vdp.o_csync*/)
    {
        uint32_t abgr = 0;

        abgr |= vdp.o_dac_r << 0;
        abgr |= vdp.o_dac_g << 8;
        abgr |= vdp.o_dac_b << 16;

        vid_workbuffer[plot_y][plot_x] = abgr;
    }

    plot_x++;

    ocsync = vdp.o_csync != 0;
}

void Video_UpdateTitle(uint64_t ms)
{
    char buffer[100];
    int _ms = ms % 1000;
    int _s = (int)(ms / 1000);
    int mn = _s / 60;
    _s %= 60;
    SDL_snprintf(buffer, sizeof(buffer), "Nuked SMS v" VERSION " [%i:%02i:%03i]", mn, _s, _ms);
    buffer[99] = 0;

    if (!vid_window)
        return;

    SDL_SetWindowTitle(vid_window, buffer);
}
