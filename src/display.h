#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY
#include "hardware/gpio.h"
#include <stdint.h>

static const uint ROW_PINS[8] = {15, 14, 13, 12, 11, 10, 9, 8};
static const uint COL_PINS[8] = {26, 22, 21, 20, 19, 18, 17, 16};

void display_init();
void display_clear();
void display_activate_led(const uint led);
void display_set_row(const uint row_num, uint8_t row_bitmask);
void display_show_bitmap(uint8_t bmp[8], uint frame_time_ms);
#endif
