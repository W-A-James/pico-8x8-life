#include "pico/stdlib.h"

#include <stdlib.h> // For rand()

#include "display.h"
#include "life.h"

struct life life_new(void) {
  struct life life;
  life_reset(&life);

  return life;
}

void life_init(struct life *life) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    life->board_0[i] = rand() % 2;
    life->board_1[i] = 0;
  }

  life->current_board = life->board_0;
}

void life_reset(struct life *life) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    life->board_0[i] = 0;
    life->board_1[i] = 0;
  }

  life->current_board = life->board_0;
}

void life_step(struct life *life) {
  int8_t *new_board_pointer =
      life->current_board == life->board_0 ? life->board_1 : life->board_0;

  int8_t current = 0;

  for (int i = 0; i < BOARD_SIZE; i++) {
    int left_col = 0, right_col = 0, current_col = 0, top_row = 0,
        bottom_row = 0, current_row = 0;
    int8_t num_neighbours = 0;

    current = life->current_board[i];
    current_row = i / 8;
    current_col = i % 8;

    top_row = current_row == 0 ? (HEIGHT - 1) : current_row - 1;
    bottom_row = current_row == (HEIGHT - 1) ? 0 : current_row + 1;

    left_col = current_col == 0 ? (WIDTH - 1) : current_col - 1;
    right_col = current_col == (WIDTH - 1) ? 0 : current_col + 1;

    // left
    num_neighbours += life->current_board[(current_row << 3) + left_col];
    // top left
    num_neighbours += life->current_board[(top_row << 3) + left_col];
    // bottom left
    num_neighbours += life->current_board[(bottom_row << 3) + left_col];

    // right
    num_neighbours += life->current_board[(current_row << 3) + right_col];
    // top right
    num_neighbours += life->current_board[(top_row << 3) + right_col];
    // bottom right
    num_neighbours += life->current_board[(bottom_row << 3) + right_col];

    // top
    num_neighbours += life->current_board[(top_row << 3) + current_col];
    // bottom
    num_neighbours += life->current_board[(bottom_row << 3) + current_col];

    if (current == 1) {
      new_board_pointer[i] = num_neighbours == 2 || num_neighbours == 3;
    } else {
      new_board_pointer[i] = num_neighbours == 3;
    }
  }

  // set life->current_board to new_board_pointer
  life->current_board = new_board_pointer;
}

void life_display(struct life *life, uint frame_time_ms) {
  uint8_t bmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      bmp[row] |= (uint8_t)(life->current_board[(row << 3) + col] << (7 - col));
    }
  }

  display_show_bitmap(bmp, frame_time_ms);
}

uint8_t life_changed(struct life *life) {
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (life->board_0[i] != life->board_1[i])
      return 1;
  }

  return 0;
}
