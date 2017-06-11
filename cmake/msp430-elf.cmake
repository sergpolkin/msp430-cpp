# TOOLCHAIN FILE for MSP430

find_program(MSP430_CC      msp430-elf-gcc)
find_program(MSP430_CXX     msp430-elf-g++)
find_program(MSP430_OBJCOPY msp430-elf-objcopy)
find_program(MSP430_SIZE    msp430-elf-size)
find_program(MSP430_OBJDUMP msp430-elf-objdump)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR msp430)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER ${MSP430_CC})
set(CMAKE_CXX_COMPILER ${MSP430_CXX})

if(NOT MCU)
	message(STATUS "Setting default MCU type 'msp430g2553'")
	set(MCU "msp430g2553" CACHE STRING "MSP430 MCU TYPE")
else()
	message(STATUS "MCU defined as '${MCU}'")
endif()

set(CMAKE_C_FLAGS "-mmcu=${MCU} -minrt -Os -g \
-Wall -Wextra -Wunused -ffunction-sections -fdata-sections" CACHE STRING "C Flags")
set(CMAKE_C_LINK_FLAGS "-Wl,-gc-sections,-Map=main.map" CACHE STRING "Linker Flags")

set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -std=c++11 -Os -g \
 -Wall -Wextra -Wunused -fpermissive -ffunction-sections -fdata-sections" CACHE STRING "C++ Flags")
set(CMAKE_CXX_LINK_FLAGS "-Wl,-gc-sections,-Map=main-cxx.map" CACHE STRING "Linker Flags")
