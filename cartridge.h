#pragma once

#define ROM_SIZE (2 * 1024 * 1024)

int cart_load_game_rom(char *filename);
void cart_handle(void);