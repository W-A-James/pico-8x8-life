cmake_minimum_required(VERSION 3.17)
include(pico_sdk_import.cmake)
project(display C CXX ASM)
pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(
  ${PROJECT_NAME}
  main.c
  display.c
  life.c
  lfsr.c
)

add_executable(
  test 
  test.c
  display.c
  life.c
  lfsr.c
)

target_link_libraries(
  ${PROJECT_NAME}
  pico_stdlib
  pico_printf
  hardware_adc 
  hardware_uart
  hardware_gpio
  pico_bootsel_via_double_reset
  )
target_link_libraries(
  test
  pico_stdlib
  pico_printf
  hardware_adc 
  hardware_uart
  hardware_gpio
  pico_bootsel_via_double_reset
  )

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

pico_add_extra_outputs(test)
