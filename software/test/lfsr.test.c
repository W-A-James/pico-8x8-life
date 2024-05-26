#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/lfsr.h"

#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  stdio_flush();

  while (1) {
    printf("Reseeding lfsr");
    struct lfsr lfsr = lfsr_init(0xabcd);

    int ones = 0;
    int zeros = 0;

    for (int i = 0; i < 1000; i++) {
      if (lfsr_fib_step(&lfsr))
        ones++;
      else
        zeros++;
    }

    printf("Got %d ones and %d zeros\n", ones, zeros);
    sleep_ms(5000);
  }
}
