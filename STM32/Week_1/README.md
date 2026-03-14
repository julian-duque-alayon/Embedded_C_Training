# ⚡ Week 1: Awakening the Silicon
## 📅 Period: xx/xx — xx/xx

![Week 1 Header](./docs/img/header.png)

> "In the world of bare-metal, there are no abstractions—only you, the datasheet, and the electrons."

Welcome to **Week 1**. This isn't just a coding week; it's a deep dive into the physical reality of computing. We're moving beyond "running code" to **manipulating 32-bit memory cells** with surgical precision. 

---

### 🎯 The Mission Briefing
This week is the foundation of **Phase I (Software & Silicon Engineering)**. If you don't know how the compiler organizes SRAM, you're just guessing. We stop guessing now.

*   **The Challenge:** Master **data anatomy** and the **linear memory map** of the STM32F413ZH [RM0430, 2.2].
*   **The Weaponry:** Zero external libraries. Just raw pointers, bit-level operations, and pure hardware control.
*   **The Artifact:** By Sunday, you'll have built a **Physical Carry Calculator**—a system that detects logical overflows and signals them via hardware LEDs, all validated by a professional TDD workflow.

---

### 🏆 The Grand Goal: "The LED Carry Calculator"
Forget `printf`. Your hardware is your interface.
1.  **Data Bus:** Use 8 external LEDs to display truncated results.
2.  **Alert System:** **LED3 (Red - PB14)** triggers on **Integer Overflow**.
3.  **The Bare-Metal Oath:** No `HAL_GPIO_Write()`. You will strike the registers directly via `RCC_AHB1ENR`, `GPIOx_MODER`, and `GPIOx_ODR` using raw memory addresses.

---

### 🗺️ Mission Roadmap

| Phase | Milestone | Objective |
| :--- | :--- | :--- |
| **Mon** | **The Iron Rule** | Zero warnings tolerated (`-Werror`) & `stdint.h` mastery. |
| **Tue** | **Silicon Cartography** | Map the SRAM/Flash wilderness [RM0430, 2.2]. |
| **Wed** | **Bitwise Surgery** | Craft the macros that manipulate the machine. |
| **Thu** | **Memory Hacking** | Master `volatile` to keep the compiler in check. |
| **Fri** | **The Awakening** | First flight on real hardware (LED Calculator). |
| **Sat** | **Logic Forge (TDD)** | Prove your code works with Ceedling/Unity. |
| **Sun** | **The Clean Slate** | Shutsuke: Refactor for absolute clarity. |

---

### 🔬 Daily Manual: Step-by-Step

#### 🟢 Monday: The Discipline of Types
*   **The Standard:** Update your `CMakeLists.txt` with `-Wall -Wextra -Werror`. If it warns, it fails.
*   **Action:** Build `printTypeSizes()` to audit `uint8_t`, `uint16_t`, `uint32_t`, and `float`. 
*   **Goal:** 100% clean compilation. No excuses.

#### 🔵 Tuesday: Cartography of the STM32
*   **The Recon:** Open the **RM0430** manual. Find **Table 1**.
*   **Action:** Locate SRAM1 (`0x2000 0000`) and print addresses of `static` (RAM) vs local (Stack) variables.
*   **Insight:** See the distance between your data and your stack.

#### 🟡 Wednesday: Surgical Bit Operations
*   **The Kit:** Build your own `SET_BIT`, `CLEAR_BIT`, and `TOGGLE_BIT`.
*   **Philosophy:** "Do one thing well": Separate math from visualization.

#### 🔴 Thursday: The `volatile` Guardian
*   **The Target:** `GPIOB_ODR` register at `0x4002 0414`.
*   **The Code:** `volatile uint32_t *pODR = (uint32_t *)0x40020414;`.
*   **Why?** Without `volatile`, the compiler thinks your LED writes are "useless" and deletes them. Don't let it.

#### 🔌 Friday: Hardware Bring-Up
*   **Power On:** Enable the GPIOB clock in `RCC_AHB1ENR`. 
*   **The Logic:** `if (result < opA) { *pODR |= (1 << 14); }` — Real-world overflow detection.

#### 🧪 Saturday: The TDD Gauntlet
*   **Process:** Red-Green-Refactor. 
*   **Rigor:** One Assert per test. If it's worth writing, it's worth testing.

#### 🧹 Sunday: Shutsuke (Self-Discipline)
*   **The Scout Rule:** Leave the code cleaner than you found it. 
*   **The Newspaper Layout:** High-level logic at the top, register-level details at the bottom.

---

### 📂 Knowledge Base
*Need a deep dive? Check the daily field notes:*

| Day | Topic | Deep Dive |
| :--- | :--- | :--- |
| **Day 1** | Types & Assertions | [day1_type_sizes.md](./docs/day1_type_sizes.md) |

---

### 🛠️ Quick Start Commands

#### 1. The Forge (Build)
*   **Standard:** Hit **Build** in VS Code status bar.
*   **Terminal:** `cmake --build build`

#### 2. The Deployment (Flash)
*   **Standard:** `Ctrl + Shift + P` ⮕ `Tasks: Run Task` ⮕ **Flash device**.
*   **Terminal:** 
    ```bash
    openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
    ```

---

### 🎙️ Debugging: The Semihosting Magic
By default, an STM32 doesn't have a screen or a terminal. When you call `printf()`, the poor microcontroler has no idea where to send that text. To solve this without adding extra hardware (like UART cables), we use **Semihosting**.

#### ⚡ What is Semihosting?
It's a mechanism that lets the STM32 "borrow" the keyboard and screen of your PC. When the code hits a `printf`:
1. The STM32 pauses for a microsecond.
2. It sends the data through the **ST-LINK** debugger cable.
3. **OpenOCD** (on your PC) catches that data and prints it in your VS Code **Debug Console**.

#### 🛠️ How we implemented it:
To make this work, we had to perform a "triple surgery" on the project:

1.  **Linker Alchemy (`cmake/stm32_gcc.cmake`)**: 
    - We swapped `nosys.specs` (which "mutes" system calls) for `rdimon.specs`.
    - We linked `librdimon`, which contains the ARM technical wizardry to talk back to the debugger.
    - We added a `-DSEMIHOSTING` flag so our code knows when this mode is active.

2.  **The Peacekeeper (`CMakeLists.txt` & `syscalls.c`)**: 
    - Since `librdimon` and our default `syscalls.c` both try to define how `printf` works, they would normally fight (Multiple Definition Error). 
    - We modified CMake to **exclude** `syscalls.c` whenever Semihosting is active, letting the professional library take the lead.

3.  **The "Wake Up" Call (`main.c`)**:
    - We added `initialise_monitor_handles()`. Think of this as turning on the "intercom" between the STM32 and your PC before anyone starts talking.

4.  **The Ear on the PC (`launch.json`)**:
    - We told VS Code to send the command `monitor arm semihosting enable` to the debugger automatically. Without this, the PC would ignore the STM32's shouts.

> [!TIP]
> **Where are my prints?** They won't appear in the standard Terminal. Look for the **DEBUG CONSOLE** tab next to it while the debugger is running!

---
*Back to [STM32 Modules](../README.md)*
