cmake_minimum_required(VERSION 3.17)
include(pico_sdk_import.cmake)
project(pico-life C CXX ASM)
pico_sdk_init()

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
add_compile_options(-Wall -Wextra -Wpedantic)

################### Main binary ###################
add_executable(
  ${PROJECT_NAME}
  src/main.c
  src/display.c
  src/life.c
)

target_link_libraries(
  ${PROJECT_NAME}
  pico_stdlib
  pico_bootsel_via_double_reset
  )

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})
###################################################

############## Game of life test ##################
add_executable(
  life.test
  test/life.test.c
  src/life.c
  src/display.c
)
target_link_libraries(
  life.test
  pico_stdlib
  pico_bootsel_via_double_reset
)
target_link_libraries(
  life.test
  pico_stdlib
  pico_bootsel_via_double_reset
  )

pico_enable_stdio_usb(life.test 1)
pico_enable_stdio_uart(life.test 1)
pico_add_extra_outputs(life.test 1)
###################################################
