#include "./tupper_visual.h"

int scc(int code) {
  if (code < 0) {
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    exit(1);
  }

  return code;
}

void *scp(void *ptr) {
  if (ptr == NULL) {
    fprintf(stderr, "SDL error: %s\n", SDL_GetError());
    exit(1);
  }

  return ptr;
}

void render_field_grid(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, HEX_COLOR(GRID_COLOR));

  for (int x = 1; x < BOARD_WIDTH; ++x) {
    scc(SDL_RenderDrawLine(renderer, x * CELL_WIDTH, 0, x * CELL_WIDTH,
                           SCREEN_HEIGHT));
  }

  for (int y = 1; y < BOARD_HEIGHT; ++y) {
    scc(SDL_RenderDrawLine(renderer, 0, y * CELL_HEIGHT, SCREEN_WIDTH,
                           y * CELL_HEIGHT));
  }
}

void render_field(SDL_Renderer *renderer, const Field *field) {

  for (size_t i = 0; i < BOARD_HEIGHT; ++i) {
    for (size_t j = 0; j < BOARD_WIDTH; ++j) {
      SDL_Rect rect = {
          (int)floorf(field->walls[i][j].pos.x * CELL_WIDTH),
          (int)floorf(field->walls[i][j].pos.y * CELL_HEIGHT),
          (int)floorf(CELL_WIDTH),
          (int)floorf(CELL_HEIGHT),
      };

      SDL_SetRenderDrawColor(renderer, HEX_COLOR(WALL_COLOR));

      SDL_RenderFillRect(renderer, &rect);
    }
  }
}
