#include "daagudumoothalu/sdl_stuff.h"

void init_sdl(SDL_Window** window, SDL_Renderer** renderer, int width, int height)
{
  SDL_Init(SDL_INIT_VIDEO);

  *window =
      SDL_CreateWindow("Daagudumoothalu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_ALLOW_HIGHDPI);
  *renderer = SDL_CreateRenderer(*window, -1, 0);
}

void quit_sdl(SDL_Window* window, SDL_Renderer* renderer)
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void clear_screen(SDL_Renderer* renderer, int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderClear(renderer);
}

void present_screen(SDL_Renderer* renderer)
{
  SDL_RenderPresent(renderer);
}