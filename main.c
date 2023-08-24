#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

#include "display.h"
#include "life.h"

#define S_AS_US * 1000000
#define RESET_TIME_US 10 S_AS_US

uint8_t blank[8] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t full[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
int main() {
  // set up display
  display_init();

  // set up adc
  adc_init();
  adc_select_input(2);

  // Initialize life sim
  life_init();

  // reset every 10 seconds
  absolute_time_t start = get_absolute_time();
  absolute_time_t now;

  uint8_t row = 0;
  while (1) {
    life_display_board(200);
    life_step();

    now = get_absolute_time();
    if (absolute_time_diff_us(start, now) > RESET_TIME_US) {
      display_show_bitmap(blank, 200);
      display_show_bitmap(full, 200);
      display_show_bitmap(blank, 200);
      display_show_bitmap(full, 200);
      display_show_bitmap(blank, 200);
      display_show_bitmap(full, 200);
      display_show_bitmap(blank, 200);

      life_init();
      start = get_absolute_time();
    }
  }
}
