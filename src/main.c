#include <SDL.h>
#include <stdbool.h>

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  // Get the current display mode of the default display
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int screenWidth = DM.w;
  int screenHeight = DM.h;

  // get center of the screen
  int centerX = screenWidth / 2;
  int centerY = screenHeight / 2;

  // Create a window centered in the screen
  SDL_Window* window =
      SDL_CreateWindow("Daagudumoothalu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       screenWidth, screenHeight, SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  int renderWidth, renderHeight;
  SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight);

  bool running = true;
  bool fullscreen = false;
  SDL_Event event;

  // Initial position and size of the square
  float squarePosX = renderWidth / 2.0f - 50.0f;
  float squarePosY = renderHeight / 2.0f - 50.0f;
  const int squareWidth = 100, squareHeight = 100;
  int squareSpeed = 200;  // Speed of the square movement (pixels per second)

  // Key state
  bool up = false, down = false, left = false, right = false;

  // Timing
  Uint32 lastTime = SDL_GetTicks();

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      else if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
            up = true;
            break;
          case SDLK_DOWN:
            down = true;
            break;
          case SDLK_LEFT:
            left = true;
            break;
          case SDLK_RIGHT:
            right = true;
            break;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        switch (event.key.keysym.sym)
        {
          case SDLK_UP:
            up = false;
            break;
          case SDLK_DOWN:
            down = false;
            break;
          case SDLK_LEFT:
            left = false;
            break;
          case SDLK_RIGHT:
            right = false;
            break;
        }
      }
    }

    // Calculate delta time
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Move the square based on the arrow key state and delta time
    if (up)
      squarePosY -= squareSpeed * deltaTime;
    if (down)
      squarePosY += squareSpeed * deltaTime;
    if (left)
      squarePosX -= squareSpeed * deltaTime;
    if (right)
      squarePosX += squareSpeed * deltaTime;

    // Set background color to dark gray
    SDL_SetRenderDrawColor(renderer, 69, 66, 65, 255);  // Dark gray color
    SDL_RenderClear(renderer);

    // Draw the moving square
    SDL_Rect square = {(int)squarePosX, (int)squarePosY, squareWidth, squareHeight};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Light beige color
    SDL_RenderFillRect(renderer, &square);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
