#include "display.h"
#include "hardware/gpio.h"
#include "pico/time.h"

void display_init() {
  for (int i = 0; i < 8; i++) {
    gpio_init(ROW_PINS[i]);
    gpio_init(COL_PINS[i]);
    gpio_set_dir(ROW_PINS[i], GPIO_OUT);
    gpio_set_dir(COL_PINS[i], GPIO_IN);
    gpio_put(ROW_PINS[i], 0);
  }
}

void display_clear() {
  for (int i = 0; i < 8; i++) {
    // Set col pins to high impedance
    gpio_set_dir(COL_PINS[i], GPIO_IN);
    // Clear all rows
    gpio_put(ROW_PINS[i], 0);
  }
}

void display_activate_led(const uint led) {
  const uint row = led / 8u;
  const uint col = led % 8u;

  // Clear all other pins
  display_clear();

  // Set col_pin to output and pull it low
  gpio_set_dir(COL_PINS[col], GPIO_OUT);
  gpio_put(COL_PINS[col], 0);

  // Set row_pin high
  gpio_put(ROW_PINS[row], 1);
}

void display_set_row(const uint row_num, uint8_t row_bitmask) {
  // Clear all other pins
  display_clear();

  for (int i = 0; i < 8; i++) {
    int pin = COL_PINS[i];
    if ((row_bitmask & 0x80u) != 0) {
      gpio_set_dir(pin, GPIO_OUT);
      gpio_put(pin, 0);
    }
    row_bitmask <<= 1u;
  }
  gpio_put(ROW_PINS[row_num], 1);
}

void display_show_bitmap(uint8_t bmp[8], uint frame_time_ms) {
  absolute_time_t start = get_absolute_time();
  int64_t frame_time_us = ((int64_t)frame_time_ms * 1000u);
  int frame_time_elapsed = 0;
  while (!frame_time_elapsed) {
    for (uint8_t i = 0; i < 8u; i++) {
      display_set_row(i, bmp[i]);
      sleep_us(2000);
    }
    absolute_time_t now = get_absolute_time();
    frame_time_elapsed = (absolute_time_diff_us(start, now) > frame_time_us);
  }
}
