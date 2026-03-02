# 📁 Project Structure: Week 1

This document provides a detailed breakdown of the file structure for the **Week 1** project. Understanding these files is essential for mastering how Code is translated into Silicon behavior.

---

## 📂 Root Directory

| File/Folder | Purpose | Description |
| :--- | :--- | :--- |
| `App/` | **Application Source** | Contains the logic you write. This is where your surgical bit manipulation happens. |
| `Drivers/` | **Hardware Extraction** | Standard header/source files from ST (CMSIS and Low-Layer). These define register addresses and base functions. |
| `Startup/` | **The First Breath** | Contains the Assembly code that the processor runs immediately after reset (Vector Table setup). |
| `CMakeLists.txt` | **Build Architect** | The master script for CMake. It tells the compiler which files to include, what flags to use, and how to link the final `.elf` file. |
| `STM32F413XX_FLASH.ld` | **Memory Map / Linker Script** | Crucial file. It defines the exact physical address where code (Flash) and data (SRAM) reside. |
| `Template.ioc` | **Configuration File** | The STM32CubeMX project file. Used to graphically configure pins, clocks, and peripherals. |
| `build/` | **The Workshop** | Temporary folder where the compiler puts object files and the final executable. **Do not edit files here.** |

---

## 📂 App/ (Your Application)

This is your primary workspace.

### 📍 `App/inc/` (Headers)
*   **`main.h`**: The global configuration header. Used to include all LL drivers needed by `main.c` and define global constants.
*   **`stm32f4xx_it.h`**: Header for interrupt handlers. Defines the prototypes for functions called when an event (like a timer or button) interrupts the CPU.
*   **`stm32f4xx_hal_conf.h`**: Even though we use LL, this file is required by the vendor to toggle which peripherals are active in the project.

### 📍 `App/src/` (Source Logic)
*   **`main.c`**: The entry point. It contains `SystemClock_Config()` (initializing the heart of the chip) and your main control loop.
*   **`stm32f4xx_it.c`**: The "Traffic Controller". This file contains the C-code for interrupt handlers (like `SysTick_Handler`), which we use for precise timing.
*   **`syscalls.c`**: The "Bridge". Provides minimal implementations for standard C functions (like `printf` or `malloc`) so the compiler knows how to handle them in a bare-metal environment.
*   **`system_stm32f4xx.c`**: Vendor code that performs the very first low-level clock setup before `main()` is even reached.

---

## 📂 Startup/

*   **`startup_stm32f413xx.s`**: An Assembly (`.s`) file. It defines the **Vector Table** (the list of memory addresses for every possible interrupt) and calls the `_reset` handler that eventually jumps to your `main()`.

---

## 📂 Drivers/

*   **`CMSIS/`**: The "Standard". Definitions that are common across all ARM Cortex-M4 processors, regardless of the manufacturer.
*   **`STM32F4xx_HAL_Driver/`**: The "Translator". We are using the **LL (Low-Layer)** part of this library, which provides thin wrappers over the raw hardware registers (e.g., `LL_GPIO_SetPinMode`).

---

## 📂 .vscode/ (Environment)

*   **`tasks.json`**: Automates your workflow. Contains the "Flash device" command.
*   **`launch.json`**: Debugging configuration. Tells VS Code how to use OpenOCD to connect to your physical board for step-by-step debugging.
*   **`c_cpp_properties.json`**: Tells the VS Code "IntelliSense" where the header files are so you don't see red squiggles under your `#include` lines.
