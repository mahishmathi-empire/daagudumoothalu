#include "daagudumoothalu/wumpus.h"

void generate_wumpus_grid(int grid_size, int* wumpus_grid)
{
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      wumpus_grid[i * grid_size + j] = EMPTY;
    }
  }

  // place player at (0, 0)
  wumpus_grid[0] = PLAYER;

  int wumpus_x, wumpus_y;
  int gold_x, gold_y;
  int pit_x, pit_y;

  // place wumpus
  do
  {
    wumpus_x = rand() % grid_size;
    wumpus_y = rand() % grid_size;
  } while (wumpus_grid[wumpus_x * grid_size + wumpus_y] != EMPTY);
  wumpus_grid[wumpus_x * grid_size + wumpus_y] = WUMPUS;

  // place gold
  do
  {
    gold_x = rand() % grid_size;
    gold_y = rand() % grid_size;

  } while (wumpus_grid[gold_x * grid_size + gold_y] != EMPTY);
  wumpus_grid[gold_x * grid_size + gold_y] = GOLD;

  // place pits
  int num_pits = grid_size / 2;
  for (int i = 0; i < num_pits; i++)
  {
    do
    {
      pit_x = rand() % grid_size;
      pit_y = rand() % grid_size;

    } while (wumpus_grid[pit_x * grid_size + pit_y] != EMPTY);
    wumpus_grid[pit_x * grid_size + pit_y] = PIT;
  }

  // place stench next to wumpus and breeze next to pits
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (wumpus_grid[i * grid_size + j] == WUMPUS)
      {
        // Place stenches around the Wumpus
        if (i > 0 && !(wumpus_grid[(i - 1) * grid_size + j] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[(i - 1) * grid_size + j] |= STENCH;
        if (i < grid_size - 1 &&
            !(wumpus_grid[(i + 1) * grid_size + j] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[(i + 1) * grid_size + j] |= STENCH;
        if (j > 0 && !(wumpus_grid[i * grid_size + (j - 1)] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[i * grid_size + (j - 1)] |= STENCH;
        if (j < grid_size - 1 &&
            !(wumpus_grid[i * grid_size + (j + 1)] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[i * grid_size + (j + 1)] |= STENCH;
      }
      else if (wumpus_grid[i * grid_size + j] == PIT)
      {
        // Place breezes around pits
        if (i > 0 && !(wumpus_grid[(i - 1) * grid_size + j] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[(i - 1) * grid_size + j] |= BREEZE;
        if (i < grid_size - 1 &&
            !(wumpus_grid[(i + 1) * grid_size + j] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[(i + 1) * grid_size + j] |= BREEZE;
        if (j > 0 && !(wumpus_grid[i * grid_size + (j - 1)] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[i * grid_size + (j - 1)] |= BREEZE;
        if (j < grid_size - 1 &&
            !(wumpus_grid[i * grid_size + (j + 1)] & (WUMPUS | PIT | PLAYER)))
          wumpus_grid[i * grid_size + (j + 1)] |= BREEZE;
      }
    }
  }
}

void display_wumpus_grid(int grid_size, int* wumpus_grid, SDL_Renderer* renderer)
{
  // Compute cell width and height based on the renderer size and grid size
  int renderWidth, renderHeight;
  SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight);

  int cellWidth = renderWidth / grid_size;
  int cellHeight = renderHeight / grid_size;

  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      int cell = wumpus_grid[i * grid_size + j];
      SDL_Rect rect = {j * cellWidth, i * cellHeight, cellWidth, cellHeight};
      switch (cell)
      {
        case EMPTY:
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
          break;
        case WUMPUS:
          SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red color
          break;
        case PLAYER:
          SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green color
          break;
        case PIT:
          SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);  // Blue color
          break;
        case GOLD:
          SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Yellow color
          break;
        case BREEZE:
          SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);  // Cyan color
          break;
        case STENCH:
          SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);  // Magenta color
          break;
        case BREEZE | STENCH:
          SDL_SetRenderDrawColor(renderer, 128, 128, 128,
                                 255);  // Gray color for BREEZE_STENCH
          break;
        case BREEZE | GOLD:
          SDL_SetRenderDrawColor(renderer, 0, 128, 128,
                                 255);  // Teal color for BREEZE_GOLD
          break;
        case STENCH | GOLD:
          SDL_SetRenderDrawColor(renderer, 128, 0, 128,
                                 255);  // Purple color for STENCH_GOLD
          break;
        default:
          SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Default to black if unknown
          break;
      }

      SDL_RenderFillRect(renderer, &rect);
    }
  }
}
