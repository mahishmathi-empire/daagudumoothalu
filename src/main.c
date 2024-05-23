#include "daagudumoothalu/wumpus.h"
#include <time.h>

int main(int argc, char* argv[])
{
  srand(time(NULL));

  SDL_Window* window;
  SDL_Renderer* renderer;

  init_sdl(&window, &renderer, 1400, 1400);
  clear_screen(renderer, 69, 66, 65, 255);

  WumpusWorldTextures textures;
  load_textures(renderer, &textures);
  
  int grid_size = 4;
  int wumpus_grid[grid_size * grid_size];

  Player player = {0, 0, 1};

  WumpusWorld *wumpus_world = calloc(1, sizeof(WumpusWorld));
  wumpus_world->grid_size = grid_size;
  wumpus_world->wumpus_grid = wumpus_grid;
  wumpus_world->player = player;

  generate_wumpus_grid(grid_size, wumpus_world);
  display_wumpus_grid(renderer, &textures, wumpus_world);

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      // handle key stroke
      handle_player_movement(&event, wumpus_world);
    }

    clear_screen(renderer, 69, 66, 65, 255);
    display_wumpus_grid(renderer, &textures, wumpus_world);

    present_screen(renderer);
  }
  
  quit_sdl(window, renderer);

  return 0;
}
