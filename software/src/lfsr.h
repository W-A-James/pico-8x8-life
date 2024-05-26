#ifndef INCL_LFSR
#define INCL_LFSR
#include "stdint.h"

struct lfsr {
  uint16_t state;
};

struct lfsr lfsr_init(uint16_t seed);

uint16_t lfsr_fib_step(struct lfsr *lfsr);
#endif
