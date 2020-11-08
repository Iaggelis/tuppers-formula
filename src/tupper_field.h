#ifndef TUPPER_FIELD_H_
#define TUPPER_FIELD_H_

#define BOARD_WIDTH 106
#define BOARD_HEIGHT 17

typedef struct {
  int x, y;
} Coord;

typedef struct {
  Coord pos;
} Wall;

typedef struct {
  Wall walls[BOARD_HEIGHT][BOARD_WIDTH];
} Field;

#endif // TUPPER_FIELD_H_
