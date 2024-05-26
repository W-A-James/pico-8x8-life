#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include "../src/display.h"
#include "../src/life.h"

int main() {
  // set up display
  display_init();
  // Initialize life sim
  life_init();
  life_reset();

  uint8_t row = 0;
  while (1) {
    // block still life
    SET_XY(4, 4);
    SET_XY(5, 4);
    SET_XY(4, 5);
    SET_XY(5, 5);

    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_reset();

    // blinker
    SET_XY(4, 4);
    SET_XY(5, 4);
    SET_XY(6, 4);

    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_step();
    life_display_board(1000);
    life_reset();

    sleep_ms(1000);
  }
}
