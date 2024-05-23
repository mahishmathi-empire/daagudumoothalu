#include "daagudumoothalu/wumpus.h"

void generate_wumpus_grid(int grid_size, WumpusWorld* wumpus_world)
{
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      // make all cells empty and invisible
      wumpus_world->wumpus_grid[i * grid_size + j] = EMPTY & ~VISIBLE;
    }
  }

  // place player at (0, 0)
  wumpus_world->wumpus_grid[wumpus_world->player.x * grid_size + wumpus_world->player.y] =
      PLAYER | VISIBLE;

  // make the cells around the player visible
  if (wumpus_world->player.x > 0)
    wumpus_world->wumpus_grid[(wumpus_world->player.x - 1) * grid_size +
                              wumpus_world->player.y] |= VISIBLE;
  if (wumpus_world->player.x < grid_size - 1)
    wumpus_world->wumpus_grid[(wumpus_world->player.x + 1) * grid_size +
                              wumpus_world->player.y] |= VISIBLE;
  if (wumpus_world->player.y > 0)
    wumpus_world->wumpus_grid[wumpus_world->player.x * grid_size +
                              (wumpus_world->player.y - 1)] |= VISIBLE;
  if (wumpus_world->player.y < grid_size - 1)
    wumpus_world->wumpus_grid[wumpus_world->player.x * grid_size +
                              (wumpus_world->player.y + 1)] |= VISIBLE;

  int wumpus_x, wumpus_y;
  int gold_x, gold_y;
  int pit_x, pit_y;

  // place wumpus
  do
  {
    wumpus_x = rand() % grid_size;
    wumpus_y = rand() % grid_size;
  } while (wumpus_world->wumpus_grid[wumpus_x * grid_size + wumpus_y] != EMPTY);
  wumpus_world->wumpus_grid[wumpus_x * grid_size + wumpus_y] = WUMPUS;

  // place gold
  do
  {
    gold_x = rand() % grid_size;
    gold_y = rand() % grid_size;

  } while (wumpus_world->wumpus_grid[gold_x * grid_size + gold_y] != EMPTY);
  wumpus_world->wumpus_grid[gold_x * grid_size + gold_y] = GOLD;

  // place pits
  int num_pits = grid_size / 2;
  for (int i = 0; i < num_pits; i++)
  {
    do
    {
      pit_x = rand() % grid_size;
      pit_y = rand() % grid_size;

    } while (wumpus_world->wumpus_grid[pit_x * grid_size + pit_y] != EMPTY &&
             wumpus_world->wumpus_grid[gold_x * grid_size + gold_y] != (EMPTY | VISIBLE));
    wumpus_world->wumpus_grid[pit_x * grid_size + pit_y] = PIT;
  }

  // place stench next to wumpus and breeze next to pits
  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      if (wumpus_world->wumpus_grid[i * grid_size + j] == WUMPUS)
      {
        // Place stenches around the Wumpus
        if (i > 0 && !(wumpus_world->wumpus_grid[(i - 1) * grid_size + j] &
                       (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[(i - 1) * grid_size + j] |= STENCH;
        if (i < grid_size - 1 && !(wumpus_world->wumpus_grid[(i + 1) * grid_size + j] &
                                   (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[(i + 1) * grid_size + j] |= STENCH;
        if (j > 0 && !(wumpus_world->wumpus_grid[i * grid_size + (j - 1)] &
                       (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[i * grid_size + (j - 1)] |= STENCH;
        if (j < grid_size - 1 && !(wumpus_world->wumpus_grid[i * grid_size + (j + 1)] &
                                   (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[i * grid_size + (j + 1)] |= STENCH;
      }
      else if (wumpus_world->wumpus_grid[i * grid_size + j] == PIT)
      {
        // Place breezes around pits
        if (i > 0 && !(wumpus_world->wumpus_grid[(i - 1) * grid_size + j] &
                       (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[(i - 1) * grid_size + j] |= BREEZE;
        if (i < grid_size - 1 && !(wumpus_world->wumpus_grid[(i + 1) * grid_size + j] &
                                   (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[(i + 1) * grid_size + j] |= BREEZE;
        if (j > 0 && !(wumpus_world->wumpus_grid[i * grid_size + (j - 1)] &
                       (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[i * grid_size + (j - 1)] |= BREEZE;
        if (j < grid_size - 1 && !(wumpus_world->wumpus_grid[i * grid_size + (j + 1)] &
                                   (WUMPUS | PIT | PLAYER)))
          wumpus_world->wumpus_grid[i * grid_size + (j + 1)] |= BREEZE;
      }
    }
  }
}

void display_wumpus_grid(SDL_Renderer* renderer, WumpusWorldTextures* textures,
                         WumpusWorld* wumpus_world)
{
  // Compute cell width and height based on the renderer size and grid size
  int renderWidth, renderHeight;
  SDL_GetRendererOutputSize(renderer, &renderWidth, &renderHeight);

  // if not dead or won, display the grid
  if (wumpus_world->won)
  {
    // display won message
    SDL_Rect rect = {renderWidth / 4, renderHeight / 4, renderWidth / 2, renderHeight / 2};
    SDL_RenderCopy(renderer, textures->gold_texture, NULL, &rect);
    return;
  }
  if (wumpus_world->killed_by_wumpus)
  {
    // display wumpus killed message
    SDL_Rect rect = {renderWidth / 4, renderHeight / 4, renderWidth / 2, renderHeight / 2};
    SDL_RenderCopy(renderer, textures->wumpus_texture, NULL, &rect);
    return;
  }
  if (wumpus_world->fell_in_pit)
  {
    // display pit killed message
    SDL_Rect rect = {renderWidth / 4, renderHeight / 4, renderWidth / 2, renderHeight / 2};
    SDL_RenderCopy(renderer, textures->pit_texture, NULL, &rect);
    return;
  }

  int grid_size = wumpus_world->grid_size;

  int cellWidth = renderWidth / grid_size;
  int cellHeight = renderHeight / grid_size;

  for (int i = 0; i < grid_size; i++)
  {
    for (int j = 0; j < grid_size; j++)
    {
      int cell = wumpus_world->wumpus_grid[i * grid_size + j];
      SDL_Rect rect = {j * cellWidth, i * cellHeight, cellWidth, cellHeight};

      // if cell is not visible, display a wall
      if (!(cell & VISIBLE))
      {
        SDL_RenderCopy(renderer, textures->wall_texture, NULL, &rect);
        // add border to the cell
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);
        continue;
      }

      // display cell
      SDL_RenderCopy(renderer, textures->cell_texture, NULL, &rect);

      switch (cell & 0x3F)
      {
        case PLAYER:
          handle_player_render_rect(renderer, textures, wumpus_world, &rect);
          break;
        case WUMPUS:
          SDL_RenderCopy(renderer, textures->wumpus_texture, NULL, &rect);
          break;
        case PIT:
          SDL_RenderCopy(renderer, textures->pit_texture, NULL, &rect);
          break;
        case GOLD:
          SDL_RenderCopy(renderer, textures->gold_texture, NULL, &rect);
          break;
        case BREEZE:
          SDL_SetTextureAlphaMod(textures->breeze_texture, 255);
          SDL_RenderCopy(renderer, textures->breeze_texture, NULL, &rect);
          break;
        case STENCH:
          SDL_SetTextureAlphaMod(textures->stench_texture, 255);
          SDL_RenderCopy(renderer, textures->stench_texture, NULL, &rect);
          break;
        case BREEZE_STENCH:
          SDL_SetTextureAlphaMod(textures->breeze_stench_texture, 255);
          SDL_RenderCopy(renderer, textures->breeze_stench_texture, NULL, &rect);
          break;
        case BREEZE_GOLD:
          SDL_RenderCopy(renderer, textures->breeze_gold_texture, NULL, &rect);
          break;
        case STENCH_GOLD:
          SDL_RenderCopy(renderer, textures->stench_gold_texture, NULL, &rect);
          break;
        case (PLAYER | BREEZE):
          handle_player_render_rect(renderer, textures, wumpus_world, &rect);
          SDL_SetTextureAlphaMod(textures->breeze_texture, 128);
          SDL_RenderCopy(renderer, textures->breeze_texture, NULL, &rect);
          break;
        case (PLAYER | STENCH):
          handle_player_render_rect(renderer, textures, wumpus_world, &rect);
          SDL_SetTextureAlphaMod(textures->stench_texture, 128);
          SDL_RenderCopy(renderer, textures->stench_texture, NULL, &rect);
          break;
        case (PLAYER | BREEZE | STENCH):
          handle_player_render_rect(renderer, textures, wumpus_world, &rect);
          SDL_SetTextureAlphaMod(textures->breeze_stench_texture, 128);
          SDL_RenderCopy(renderer, textures->breeze_stench_texture, NULL, &rect);
          break;
      }
      // add border to the cell with thickness of 2
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_RenderDrawRect(renderer, &rect);
    }
  }
}

void handle_player_render_rect(SDL_Renderer* renderer, WumpusWorldTextures* textures,
                               WumpusWorld* wumpus_world, SDL_Rect* rect)
{
  switch (wumpus_world->player.facing)
  {
    case 0:
      SDL_RenderCopy(renderer, textures->player_front_texture, NULL, rect);
      break;
    case 1:
      SDL_RenderCopy(renderer, textures->player_right_texture, NULL, rect);
      break;
    case 2:
      SDL_RenderCopy(renderer, textures->player_back_texture, NULL, rect);
      break;
    case 3:
      SDL_RenderCopy(renderer, textures->player_left_texture, NULL, rect);
      break;
  }
}

void handle_player_movement(SDL_Event* event, WumpusWorld* wumpus_world)
{
  // handle key down event only
  if (event->type != SDL_KEYDOWN)
    return;

  int old_x = wumpus_world->player.x;
  int old_y = wumpus_world->player.y;

  // handle player facing direction and movement based on arrow keys
  // 0 - up, 1 - right, 2 - down, 3 - left
  // if player is not facing the direction, change the direction
  // if player is facing the direction, then only move
  switch (event->key.keysym.sym)
  {
    case SDLK_UP:
      if (wumpus_world->player.facing == 0)
      {
        if (wumpus_world->player.x > 0)
          wumpus_world->player.x--;
      }
      else
        wumpus_world->player.facing = 0;
      break;
    case SDLK_DOWN:
      if (wumpus_world->player.facing == 2)
      {
        if (wumpus_world->player.x < wumpus_world->grid_size - 1)
          wumpus_world->player.x++;
      }
      else
        wumpus_world->player.facing = 2;
      break;
    case SDLK_LEFT:
      if (wumpus_world->player.facing == 3)
      {
        if (wumpus_world->player.y > 0)
          wumpus_world->player.y--;
      }
      else
        wumpus_world->player.facing = 3;
      break;
    case SDLK_RIGHT:
      if (wumpus_world->player.facing == 1)
      {
        if (wumpus_world->player.y < wumpus_world->grid_size - 1)
          wumpus_world->player.y++;
      }
      else
        wumpus_world->player.facing = 1;
      break;
  }

  // remove the player from the current cell
  wumpus_world->wumpus_grid[old_x * wumpus_world->grid_size + old_y] &= ~PLAYER;

  // place the player in the new cell
  wumpus_world->wumpus_grid[wumpus_world->player.x * wumpus_world->grid_size +
                            wumpus_world->player.y] |= PLAYER | VISIBLE;

  // check if player has found gold or killed by wumpus or fell in pit
  int cell = wumpus_world->wumpus_grid[wumpus_world->player.x * wumpus_world->grid_size +
                                       wumpus_world->player.y];
  if (cell & GOLD)
  {
    wumpus_world->found_gold = 1;
    wumpus_world->won = 1;
  }
  if (cell & WUMPUS)
  {
    wumpus_world->killed_wumpus = 1;
    wumpus_world->killed_by_wumpus = 1;
  }
  if (cell & PIT)
  {
    wumpus_world->fell_in_pit = 1;
  }
}

void load_textures(SDL_Renderer* renderer, WumpusWorldTextures* textures)
{
  int r =
      load_texture(renderer, "../assets/player_front.png", &textures->player_front_texture);
  r = load_texture(renderer, "../assets/player_back.png", &textures->player_back_texture);
  r = load_texture(renderer, "../assets/player_left.png", &textures->player_left_texture);
  r = load_texture(renderer, "../assets/player_right.png", &textures->player_right_texture);

  r = load_texture(renderer, "../assets/wumpus.png", &textures->wumpus_texture);
  r = load_texture(renderer, "../assets/temp_pit.png", &textures->pit_texture);
  r = load_texture(renderer, "../assets/treasure.png", &textures->gold_texture);
  r = load_texture(renderer, "../assets/common_bg.png", &textures->cell_texture);
  r = load_texture(renderer, "../assets/breeze.png", &textures->breeze_texture);
  r = load_texture(renderer, "../assets/stench.png", &textures->stench_texture);
  r = load_texture(renderer, "../assets/breeze_stench.png",
                   &textures->breeze_stench_texture);
  r = load_texture(renderer, "../assets/treasure_breeze.png",
                   &textures->breeze_gold_texture);
  r = load_texture(renderer, "../assets/treasure_stench.png",
                   &textures->stench_gold_texture);
  r = load_texture(renderer, "../assets/wall.png", &textures->wall_texture);
  r = load_texture(renderer, "../assets/arrow.png", &textures->arrow_texture);
}