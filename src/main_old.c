#include <SDL.h>
#include <stdbool.h>

typedef struct
{
  bool up;
  bool down;
  bool left;
  bool right;
} KeyState;

typedef struct
{
  float x;
  float y;

  const int width;
  const int height;
} Player;

void handle_key_stroke(SDL_Event* event, KeyState* key_state)
{
  if (event->type == SDL_KEYDOWN)
  {
    switch (event->key.keysym.sym)
    {
      case SDLK_UP:
        key_state->up = true;
        break;
      case SDLK_DOWN:
        key_state->down = true;
        break;
      case SDLK_LEFT:
        key_state->left = true;
        break;
      case SDLK_RIGHT:
        key_state->right = true;
        break;
    }
  }
  else if (event->type == SDL_KEYUP)
  {
    switch (event->key.keysym.sym)
    {
      case SDLK_UP:
        key_state->up = false;
        break;
      case SDLK_DOWN:
        key_state->down = false;
        break;
      case SDLK_LEFT:
        key_state->left = false;
        break;
      case SDLK_RIGHT:
        key_state->right = false;
        break;
    }
  }
}

void handle_player_movement(Player* player, KeyState* key_state, float playerSpeed,
                            float deltaTime)
{
  if (key_state->up)
    player->y -= playerSpeed * deltaTime;
  if (key_state->down)
    player->y += playerSpeed * deltaTime;
  if (key_state->left)
    player->x -= playerSpeed * deltaTime;
  if (key_state->right)
    player->x += playerSpeed * deltaTime;
}

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  // Get the current display mode of the default display
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int screenWidth = DM.w;
  int screenHeight = DM.h;

  // Create a window centered in the screen
  SDL_Window* window =
      SDL_CreateWindow("Daagudumoothalu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       screenWidth, screenHeight, SDL_WINDOW_ALLOW_HIGHDPI);

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

  SDL_SetRenderDrawColor(renderer, 69, 66, 65, 255);  // Dark gray color
  SDL_RenderClear(renderer);

  int renderWidth, renderHeight;
  SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight);

  bool running = true;
  bool fullscreen = false;
  SDL_Event event;

  // Initial position and size of the square
  int playerSpeed = 200;  // Speed of the square movement (pixels per second)

  // Timing
  Uint32 lastTime = SDL_GetTicks();

  KeyState *ks = calloc(1, sizeof(KeyState));

  KeyState key_state = {false, false, false, false};
  Player player = {0, 0, 100, 100};
  player.x = renderWidth / 2.0f - 50.0f;
  player.y = renderHeight / 2.0f - 50.0f;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = false;
      else
      {
        handle_key_stroke(&event, &key_state);
      }
    }

    // Calculate delta time
    Uint32 currentTime = SDL_GetTicks();
    float deltaTime = (currentTime - lastTime) / 1000.0f;
    lastTime = currentTime;

    // Move the square based on the arrow key state and delta time
    handle_player_movement(&player, &key_state, playerSpeed, deltaTime);

    SDL_SetRenderDrawColor(renderer, 69, 66, 65, 255);  // Dark gray color
    SDL_RenderClear(renderer);

    // Draw the moving square
    SDL_Rect square = {(int)player.x, (int)player.y, player.width, player.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // Light beige color
    SDL_RenderFillRect(renderer, &square);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
