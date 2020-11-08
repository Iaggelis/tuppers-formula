#ifndef TUPPER_VISUAL_H_
#define TUPPER_VISUAL_H_

#include "./tupper_field.h"

#define SCREEN_WIDTH 1060
#define SCREEN_HEIGHT 170

#define CELL_WIDTH 10.0
#define CELL_HEIGHT 10.0

// Style
#define BACKGROUND_COLOR 0x353535FF
#define GRID_COLOR 0x748CABFF
#define WALL_COLOR (GRID_COLOR)

int scc(int code);
void *scp(void *ptr);

#define HEX_COLOR(hex)                                                         \
  ((hex) >> (3 * 8)) & 0xFF, ((hex) >> (2 * 8)) & 0xFF,                        \
      ((hex) >> (1 * 8)) & 0xFF, ((hex) >> (0 * 8)) & 0xFF

void render_field_grid(SDL_Renderer *renderer);
void render_field(SDL_Renderer *renderer, const Field *field);

#endif // TUPPER_VISUAL_H_
