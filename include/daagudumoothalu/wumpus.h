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

#define VISIBLE 64

#include <stdlib.h>

#include "daagudumoothalu/sdl_stuff.h"

typedef struct
{
  SDL_Texture* player_front_texture;
  SDL_Texture* player_back_texture;
  SDL_Texture* player_left_texture;
  SDL_Texture* player_right_texture;
  SDL_Texture* wumpus_texture;
  SDL_Texture* pit_texture;
  SDL_Texture* gold_texture;
  SDL_Texture* cell_texture;
  SDL_Texture* breeze_texture;
  SDL_Texture* stench_texture;
  SDL_Texture* breeze_stench_texture;
  SDL_Texture* breeze_gold_texture;
  SDL_Texture* stench_gold_texture;
  SDL_Texture* wall_texture;
  SDL_Texture* arrow_texture;
} WumpusWorldTextures;

typedef struct
{
  int x, y;
  int facing;
} Player;

// game state
typedef struct
{
  int grid_size;
  int* wumpus_grid;
  Player player;

  int found_gold;
  int killed_wumpus;
  
  bool killed_by_wumpus;
  bool fell_in_pit;
  bool won;
} WumpusWorld;

/**
 * @brief generate wumpus grid
 * @assumption grid is always n x n
 * @param grid_size size of the grid
 * @param wumpus_grid grid to be generated
 */
void generate_wumpus_grid(int grid_size, WumpusWorld* wumpus_world);

/**
 * @brief display wumpus grid on the screen with sdl
 * @param grid_size size of the grid
 * @param wumpus_grid grid to be displayed
 * @param renderer sdl renderer
 */
void display_wumpus_grid(SDL_Renderer* renderer, WumpusWorldTextures* textures,
                         WumpusWorld* wumpus_world);

void make_adjacent_cells_visible(WumpusWorld* wumpus_world);

void handle_player_movement(SDL_Event* event, WumpusWorld* wumpus_world);

void handle_player_render_rect(SDL_Renderer* renderer, WumpusWorldTextures* textures,
                               WumpusWorld* wumpus_world, SDL_Rect* rect);

void load_textures(SDL_Renderer* renderer, WumpusWorldTextures* textures);

#endif  // DAAGUDUMOOTHALU_WUMPUS_H