#include "lfsr.h"
#include "stdint.h"
// Implementation adapted from
// https://en.wikipedia.org/wiki/Linear-feedback_shift_register

struct lfsr lfsr_init(uint16_t seed) {
  struct lfsr lfsr = {.state = seed};
  return lfsr;
}

uint16_t lfsr_fib_step(struct lfsr *lfsr) {
  uint16_t state = lfsr->state;
  uint16_t bit; /* Must be 16-bit to allow bit<<15 later in the code */

  /* taps: 16 14 13 11; feedback polynomial: x^16 + x^14 + x^13 + x^11 + 1 */
  bit = ((state >> 0) ^ (state >> 2) ^ (state >> 3) ^ (state >> 5)) & 1u;
  lfsr->state = (state >> 1) | (bit << 15);

  return bit;
}
