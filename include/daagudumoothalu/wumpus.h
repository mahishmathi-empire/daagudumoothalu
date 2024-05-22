#ifndef DAAGUDUMOOTHALU_WUMPUS_H
#define DAAGUDUMOOTHALU_WUMPUS_H

#define EMPTY 0
#define WUMPUS 1
#define PLAYER 2
#define PIT 4
#define GOLD 8
#define BREEZE 16
#define STENCH 32

#define BREEZE_STENCH (BREEZE | STENCH)
#define BREEZE_GOLD (BREEZE | GOLD)
#define STENCH_GOLD (STENCH | GOLD)

#include <stdlib.h>

#include "daagudumoothalu/sdl_stuff.h"

/**
 * @brief generate wumpus grid
 * @assumption grid is always n x n
 * @param grid_size size of the grid
 * @param wumpus_grid grid to be generated
 */
void generate_wumpus_grid(int grid_size, int* wumpus_grid);

/**
 * @brief display wumpus grid on the screen with sdl
 * @param grid_size size of the grid
 * @param wumpus_grid grid to be displayed
 * @param renderer sdl renderer
 */
void display_wumpus_grid(int grid_size, int* wumpus_grid, SDL_Renderer* renderer);

#endif // DAAGUDUMOOTHALU_WUMPUS_H