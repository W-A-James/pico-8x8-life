#ifndef INCL_LIFE
#define INCL_LIFE
#include "hardware/gpio.h"
#include <stdint.h>

#define SET_XY(x, y)                                                           \
  do {                                                                         \
    current_board[(y << 3) + x] = 1;                                           \
  } while (0)

#define CLEAR_XY(x, y)                                                         \
  do {                                                                         \
    current_board[(y << 3) + x] = 0;                                           \
  } while (0)


#define BOARD_SIZE 64
#define WIDTH 8
#define HEIGHT 8
static int8_t board_0[BOARD_SIZE];
static int8_t board_1[BOARD_SIZE];
static int8_t *current_board;

void life_init();
void life_reset();
void life_step();
void life_display_board(uint frame_time_ms);
#endif
