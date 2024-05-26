#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include "../src/display.h"
#include "../src/life.h"

int main() {
  // set up display
  display_init();
  // Initialize life sim
  struct life life = life_new();
  while (1) {
    // block still life
    SET_XY(life, 4, 4);
    SET_XY(life, 5, 4);
    SET_XY(life, 4, 5);
    SET_XY(life, 5, 5);

    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_reset(&life);

    // blinker
    SET_XY(life, 4, 4);
    SET_XY(life, 5, 4);
    SET_XY(life, 6, 4);

    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_step(&life);
    life_display(&life, 1000);
    life_reset(&life);

    sleep_ms(1000);
  }
}
