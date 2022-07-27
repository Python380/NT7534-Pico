﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out

# Utility rule file for cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.

# Include any custom commands dependencies for this target.
include pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\compiler_depend.make

# Include the progress variables for this target.
include pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\progress.make

pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h: pico-sdk\src\rp2_common\cyw43_driver\cyw43_bus_pio_spi.pio.h
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\pico-sdk\src\rp2_common\cyw43_driver
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out

pico-sdk\src\rp2_common\cyw43_driver\cyw43_bus_pio_spi.pio.h: C:\Users\henrik.pedersen\pico\pico-sdk\src\rp2_common\cyw43_driver\cyw43_bus_pio_spi.pio
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating cyw43_bus_pio_spi.pio.h"
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\pico-sdk\src\rp2_common\cyw43_driver
	..\..\..\..\pioasm\pioasm.exe -o c-sdk C:/Users/henrik.pedersen/pico/pico-sdk/src/rp2_common/cyw43_driver/cyw43_bus_pio_spi.pio C:/Users/henrik.pedersen/pico/rotbot/RotBot_UI/out/pico-sdk/src/rp2_common/cyw43_driver/cyw43_bus_pio_spi.pio.h
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out

cyw43_driver_picow_cyw43_bus_pio_spi_pio_h: pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h
cyw43_driver_picow_cyw43_bus_pio_spi_pio_h: pico-sdk\src\rp2_common\cyw43_driver\cyw43_bus_pio_spi.pio.h
cyw43_driver_picow_cyw43_bus_pio_spi_pio_h: pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\build.make
.PHONY : cyw43_driver_picow_cyw43_bus_pio_spi_pio_h

# Rule to build all files generated by this target.
pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\build: cyw43_driver_picow_cyw43_bus_pio_spi_pio_h
.PHONY : pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\build

pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\clean:
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\pico-sdk\src\rp2_common\cyw43_driver
	$(CMAKE_COMMAND) -P CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\cmake_clean.cmake
	cd C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out
.PHONY : pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\clean

pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI C:\Users\henrik.pedersen\pico\pico-sdk\src\rp2_common\cyw43_driver C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\pico-sdk\src\rp2_common\cyw43_driver C:\Users\henrik.pedersen\pico\rotbot\RotBot_UI\out\pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : pico-sdk\src\rp2_common\cyw43_driver\CMakeFiles\cyw43_driver_picow_cyw43_bus_pio_spi_pio_h.dir\depend

