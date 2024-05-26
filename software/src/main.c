#include "hardware/gpio.h"
#include "pico/stdlib.h"

#include "display.h"
#include "life.h"

#define DEAD_BOARD_THRESH 10

// Blank screen
uint8_t blank[8] = {0, 0, 0, 0, 0, 0, 0, 0};
// Full screen
uint8_t full[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

inline void flash_display() {
  display_show_bitmap(blank, 200);
  display_show_bitmap(full, 200);
  display_show_bitmap(blank, 200);
  display_show_bitmap(full, 200);
  display_show_bitmap(blank, 200);
  display_show_bitmap(full, 200);
  display_show_bitmap(blank, 200);
}

int main() {
  // set up display
  display_init();

  // Initialize life sim
  struct life life = life_new();

  // reset after DEAD_BOARD_THRESH steps without any board changes
  int steps_without_change = 0;
  while (1) {
    life_display(&life, 200);
    life_step(&life);

    if (!life_changed(&life))
      steps_without_change++;
    else {
      steps_without_change = 0;
    }

    if (steps_without_change >= DEAD_BOARD_THRESH) {
      flash_display();

      life_init(&life);
      steps_without_change = 0;
    }
  }
}
