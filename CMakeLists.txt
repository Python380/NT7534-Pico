cmake_minimum_required(VERSION 3.20)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)
pico_sdk_init()

project(UI)

add_executable(UI
    ./src/main.cpp
    ./lib/NT7534.cpp
    ./lib/parallelInterface.cpp
)

# pull in common dependencies
target_link_libraries(UI
    pico_stdlib
)

pico_enable_stdio_usb(UI 1)
pico_enable_stdio_uart(UI 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(UI)