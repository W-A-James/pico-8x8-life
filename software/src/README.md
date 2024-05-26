# Software

All code here is written in C making use of the [Raspberry Pi Pico C/C++ SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html).

## Components

|Component|Description|Files|
|---------|-----------|-----|
|`display`|The driver of the LED matrix.|`src/display.c`, `src/display.h`|
|`lfsr`|Linear Feedback Shift Register providing pseudorandom bits|`src/lfsr.c`, `src/lfsr.h`, `test/lfsr.test.c`| 
|`life`|Implementation of Conway's game of life|`src/life.c`, `src/life.h`, `test/life.test.c`|
