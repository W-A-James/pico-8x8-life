#ifndef INCLUDED_DISPLAY
#define INCLUDED_DISPLAY
#include "hardware/gpio.h"
#include <stdint.h>

static const uint ROW_PINS[8] = {15, 14, 13, 12, 11, 10, 9, 8};
static const uint COL_PINS[8] = {26, 22, 21, 20, 19, 18, 17, 16};

// Initializes gpio pins to correct state to drive display
void display_init();
// Deactivates all LEDs
void display_clear();
// Activates single LED at specified index
// Counts from top row, scanning left to right
void display_activate_led(const uint led);
// Sets row specified by row_num to display the 8 bit number provided as a
// bitmask. Disables all other rows.
// Row numbers are counted from 0 and go from top to bottom Leds
// correponding to high bits will be on while those corresponding to low bits
// will be off.
//
// Note that only one row can be set at a time*
//
// ```C
// display_set_row(0, 0x80); // Will set left-most led of top row
// display_set_row(1, 0x07); // Will set the last 3 leds of second row from the top
// ```
void display_set_row(const uint row_num, uint8_t row_bitmask);

// Displays the bitmapped image provided on the LED matrix for the time specified
// Uses persistence of vision to give illusion that the entire image is being displayed at once
void display_show_bitmap(uint8_t bmp[8], uint frame_time_ms);
#endif
