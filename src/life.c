#include "pico/stdlib.h"

#include <stdlib.h> // For rand()

#include "display.h"
#include "lfsr.h"
#include "life.h"

void life_init() {
  if (!lfsr_initialized)
    lfsr_init((uint16_t)rand());

  for (int i = 0; i < BOARD_SIZE; i++) {
    board_0[i] = lfsr_fib_step() == 0;
    board_1[i] = 0;
  }

  current_board = board_0;
}

void life_reset() {
  for (int i = 0; i < BOARD_SIZE; i++) {
    board_0[i] = 0;
    board_1[i] = 0;
  }

  current_board = board_0;
}

void life_step() {
  int8_t *new_board = current_board == board_0 ? board_1 : board_0;
  int8_t *tmp_board;

  int8_t current = 0, left = 0, right = 0, top_right = 0, top_left = 0, top = 0,
         bottom_right = 0, bottom_left = 0, bottom = 0;

  for (int i = 0; i < BOARD_SIZE; i++) {
    int left_col = 0, right_col = 0, current_col = 0, top_row = 0,
        bottom_row = 0, current_row = 0;
    int8_t num_neighbours = 0;

    current = current_board[i];
    current_row = i / 8;
    current_col = i % 8;

    top_row = current_row == 0 ? (HEIGHT - 1) : current_row - 1;
    bottom_row = current_row == (HEIGHT - 1) ? 0 : current_row + 1;

    left_col = current_col == 0 ? (WIDTH - 1) : current_col - 1;
    right_col = current_col == (WIDTH - 1) ? 0 : current_col + 1;

    // left
    num_neighbours += current_board[(current_row << 3) + left_col];
    // top left
    num_neighbours += current_board[(top_row << 3) + left_col];
    // bottom left
    num_neighbours += current_board[(bottom_row << 3) + left_col];

    // right
    num_neighbours += current_board[(current_row << 3) + right_col];
    // top right
    num_neighbours += current_board[(top_row << 3) + right_col];
    // bottom right
    num_neighbours += current_board[(bottom_row << 3) + right_col];

    // top
    num_neighbours += current_board[(top_row << 3) + current_col];
    // bottom
    num_neighbours += current_board[(bottom_row << 3) + current_col];

    if (current == 1) {
      new_board[i] = num_neighbours == 2 || num_neighbours == 3;
    } else {
      new_board[i] = num_neighbours == 3;
    }
  }

  tmp_board = current_board;
  current_board = new_board;
  new_board = tmp_board;
}

void life_display_board(uint frame_time_ms) {
  uint8_t bmp[8] = {0, 0, 0, 0, 0, 0, 0, 0};
  for (int row = 0; row < HEIGHT; row++) {
    for (int col = 0; col < WIDTH; col++) {
      bmp[row] |= (uint8_t)(current_board[(row << 3) + col] << (7 - col));
    }
  }

  display_show_bitmap(bmp, frame_time_ms);
}
