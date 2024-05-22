#include <SDL.h>
#include <stdbool.h>

void init_sdl(SDL_Window** window, SDL_Renderer** renderer, int width, int height);

void quit_sdl(SDL_Window* window, SDL_Renderer* renderer);

void clear_screen(SDL_Renderer* renderer, int r, int g, int b, int a);

void present_screen(SDL_Renderer* renderer);