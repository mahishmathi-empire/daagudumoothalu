#include "daagudumoothalu/wumpus.h"
#include <time.h>

int main(int argc, char* argv[])
{
  srand(time(NULL));

  SDL_Window* window;
  SDL_Renderer* renderer;

  init_sdl(&window, &renderer, 1400, 1400);
  clear_screen(renderer, 69, 66, 65, 255);

  int grid_size = 4;
  int wumpus_grid[grid_size * grid_size];

  generate_wumpus_grid(grid_size, wumpus_grid);
  display_wumpus_grid(grid_size, wumpus_grid, renderer);

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
    }

    clear_screen(renderer, 69, 66, 65, 255);
    display_wumpus_grid(grid_size, wumpus_grid, renderer);

    present_screen(renderer);
  }
  
  quit_sdl(window, renderer);

  return 0;
}
