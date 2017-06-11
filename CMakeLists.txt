set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/msp430-elf.cmake)

cmake_minimum_required(VERSION 3.0)

project(demo C CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Configuration
set(CONF_FREQUENCY_IN_HZ "12000000UL" CACHE STRING "CPU frequency used")
add_definitions("-DF_CPU=${CONF_FREQUENCY_IN_HZ}")

include_directories("${CMAKE_SOURCE_DIR}/lib")
add_executable(${CMAKE_PROJECT_NAME}.elf src/main.cpp)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
	COMMAND ${MSP430_OBJCOPY} ARGS -Obinary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
	COMMAND ${MSP430_OBJDUMP} ARGS -dS ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.lst
	COMMAND ${MSP430_SIZE} ARGS -d ${CMAKE_PROJECT_NAME}.elf)
add_custom_target(flash
	COMMAND mspdebug rf2500 "prog ${CMAKE_PROJECT_NAME}.elf"
	DEPENDS ${CMAKE_PROJECT_NAME}.elf
)
