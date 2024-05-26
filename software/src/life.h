#ifndef INCL_LIFE
#define INCL_LIFE

#include "hardware/gpio.h"
#include "lfsr.h"
#include <stdint.h>

// Included for testing
#define SET_XY(life, x, y)                                                     \
  do {                                                                         \
    life.current_board[(y << 3) + x] = 1;                                      \
  } while (0)

// Included for testing
#define CLEAR_XY(life, x, y)                                                   \
  do {                                                                         \
    life.current_board[(y << 3) + x] = 0;                                      \
  } while (0)

#define BOARD_SIZE 64
#define WIDTH 8
#define HEIGHT 8

struct life {
  int8_t board_0[BOARD_SIZE];
  int8_t board_1[BOARD_SIZE];
  int8_t *current_board;
  struct lfsr lfsr;
};

// Creates a new instance of the life struct
struct life life_new(void);

// Zeroes out board
void life_reset(struct life *life);
// Fills board with random data
void life_init(struct life *life);
// Advances the game by one step
void life_step(struct life *life);
// Returns 1 if the contents of board_0 and board_1 are different, 0 otherwise
uint8_t life_changed(struct life *life);
// Displays the state of the game on the led matrix
void life_display(struct life *life, uint frame_time_ms);
#endif
