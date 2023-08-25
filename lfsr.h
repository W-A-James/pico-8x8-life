#ifndef INCL_LFSR
#define INCL_LFSR
#include "stdint.h"

void lfsr_init(uint16_t seed);
uint16_t lfsr_fib_step(void);

#endif
