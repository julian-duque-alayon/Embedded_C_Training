cmake_minimum_required(VERSION 3.22)

# 1. Toolchain Setup (Must be before project())
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/stm32_gcc.cmake)

project(Nucleo_F413_Template C ASM)

# 2. Compiler Definitions (Crucial for headers)
add_definitions(-DSTM32F413xx -DUSE_FULL_LL_DRIVER)

# 3. Include Directories
include_directories(
    App/inc
    Drivers/CMSIS/Include
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/STM32F4xx_HAL_Driver/Inc
)

# 4. Source Files Selection
# We only grab the LL files and the startup/system files.
file(GLOB_RECURSE SOURCES 
    "App/src/*.c"
    "Startup/*.s"
    "Drivers/STM32F4xx_HAL_Driver/Src/*_ll_*.c" # Only LL sources
)

# 5. Executable and Linker Script
add_executable(${PROJECT_NAME}.elf ${SOURCES})

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F413XX_FLASH.ld)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    -T${LINKER_SCRIPT}
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
)

# 6. Post-build: Create Hex and Print Size
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}hex
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
)