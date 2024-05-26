#ifndef INCL_LFSR
#define INCL_LFSR
#include "stdint.h"

static int lfsr_initialized = 0;

void lfsr_init(uint16_t seed);
uint16_t lfsr_fib_step(void);

#endif
