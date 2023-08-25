#include "stdint.h"
// Implementation adapted from https://en.wikipedia.org/wiki/Linear-feedback_shift_register

static uint16_t LFSR_STATE;

void lfsr_init(uint16_t seed) { LFSR_STATE = seed; }

unsigned lfsr_fib_step(void) {
  uint16_t bit; /* Must be 16-bit to allow bit<<15 later in the code */

  /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
  bit = ((LFSR_STATE >> 0) ^ (LFSR_STATE >> 2) ^ (LFSR_STATE >> 3) ^
         (LFSR_STATE >> 5)) &
        1u;
  LFSR_STATE = (LFSR_STATE >> 1) | (bit << 15);

  return bit;
}
