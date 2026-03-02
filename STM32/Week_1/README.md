# ⚡ Week 1: Awakening the Silicon
## (02/03 - 08/03)

![Week 1 Header](./docs/img/header.png)

This is the atomic planning for your **Week 1**. During this period, we will stop seeing code as something abstract and begin to see it as electrical impulses manipulating 32-bit memory cells, under the rigor of professional software engineering.

---

### 📝 General Overview
*   **What will be done:** You will master **data anatomy** and the **linear memory map** of the STM32F413ZH [RM0430, 2.2]. You will learn to configure "bare-metal" hardware without external libraries, using only raw pointers and bit-level operations.
*   **What will be achieved:** By the end, you will have built a physical "Carry Calculator" that detects logical errors (overflow) and signals them via hardware, validating your logic with Unit Testing (TDD).
*   **Master Plan Alignment:** This is the cornerstone of **Phase I (Software and Silicon Engineering)**. An architect cannot design robust systems without understanding how the compiler organizes data in SRAM.
*   **Detailed Blueprint:** For a file-by-file breakdown of why everything exists, see [PROJECT_STRUCTURE.md](../../PROJECT_STRUCTURE.md).

---

### 🏆 The Big Goal: "The LED Carry Calculator"

You will design a system that adds two 8-bit numbers (`uint8_t`). The 8 external LEDs will act as your **Data Bus**, displaying the result.
1.  **Data Visualization:** The truncated result will be shown on the external LEDs.
2.  **Status Visualization:** The **LED3 (Red - PB14)** on the Nucleo will turn on if the logic detects an **Integer Overflow**, indicating a Carry.
3.  **Bare-metal Rigor:** You will not use `HAL_GPIO_Write()`. You will use direct pointers to the `RCC_AHB1ENR`, `GPIOx_MODER`, and `GPIOx_ODR` registers.

---

### 📅 Activity Schedule

| Date | Day | Granular Activity | Technical Objective |
| :--- | :--- | :--- | :--- |
| **02/03** | **Monday** | **Standards and Rigor** | Configure `-Werror` and implement `stdint.h`. |
| **03/03** | **Tuesday** | **Memory Mapping** | Locate SRAM/Flash and identify physical addresses [RM0430, 2.2]. |
| **04/03** | **Wednesday** | **Bitwise Ops** | Implement macros to manipulate individual bits. |
| **05/03** | **Thursday** | **Pointers and Volatility** | Address casting and critical use of `volatile`. |
| **06/03** | **Friday** | **Physical Workshop** | Real hardware execution (LED Calculator). |
| **07/03** | **Saturday** | **Unit Testing (TDD)** | Validate logic with Ceedling/Unity on PC. |
| **08/03** | **Sunday** | **Refactoring** | Clean code and apply Shutsuke (Self-discipline). |

---

### 🔬 Daily Atomic Guide

#### 🟢 Monday: The Discipline of Data Types
*   **Action 1:** In your `toolchain` or `CMakeLists.txt`, add `-Wall -Wextra -Werror`. If there is a warning, the build must fail.
*   **Action 2:** Create `printTypeSizes()` validating `uint8_t`, `uint16_t`, `uint32_t`, and `float`.
*   **Goal:** The program must compile without warnings.

#### 🔵 Tuesday: Silicon Cartography
*   **Action 1:** Open the **RM0430** manual. Locate **Table 1 (Memory Map)**. SRAM1 starts at `0x2000 0000`.
*   **Action 2:** Print memory addresses of `static` variables (RAM) and local variables (Stack) using `%p`.
*   **Verification:** Check the distance between both addresses in the memory map.

#### 🟡 Wednesday: Surgical Bit Operations
*   **Action 1:** Create `SET_BIT`, `CLEAR_BIT`, and `TOGGLE_BIT` macros using bit shifts (`<<`) and masks.
*   **Principle:** "Do one thing": one function for calculation and another for visualization.

#### 🔴 Thursday: Memory Hacking and Volatility
*   **Action 1:** Locate the address for the `GPIOB_ODR` register (`0x4002 0414`).
*   **Action 2:** Declare the pointer: `volatile uint32_t *pODR = (uint32_t *)0x40020414;`.
*   **Important:** Using `volatile` is mandatory to prevent the compiler from optimizing and removing your LED writes.

#### 🔌 Friday: Board Bring-Up (The Workshop)
*   **Hardware:** Enable the GPIOB clock in `RCC_AHB1ENR` (Bit 1). Configure pins in `GPIOB_MODER`.
*   **Logic:** Implement the sum with carry detection: `if (result < opA) { *pODR |= (1 << 14); }`.

#### 🧪 Saturday: Test-Driven Development (TDD)
*   **Action:** Set up **Ceedling**. Write a unit test for your addition function.
*   **Rigor:** Red-Green-Refactor cycle. Ensure you have **only one Assert per test**.

#### 🧹 Sunday: Shutsuke (Self-discipline)
*   **Boy Scout Rule:** Improve variable and function names to reveal their intent.
*   **Newspaper Metaphor:** `main` at the top with high-level logic; register details at the bottom of the file.

---

### 🚀 Success Criteria
If by Sunday your board shows a correct sum and the red LED activates only when there is an overflow, you will have won the week with the technical honesty of a professional.

---

### 📓 Daily Notes

Detailed code explanations and concept breakdowns for each day live here:

| Day | Topic | File |
| :--- | :--- | :--- |
| Monday 02/03 | Fixed-width types, `sizeof`, `static_assert` | [day1_type_sizes.md](./docs/day1_type_sizes.md) |

---

### 🛠️ Quick Build Guide

#### 1. Build
**Option A: VS Code (Recommended)**
*   Click the **Build** button in the bottom status bar.

**Option B: Terminal**
```bash
cmake --build build
```

#### 2. Flash
**Option A: VS Code (Recommended)**
1.  Press `Ctrl + Shift + P`.
2.  Type `Tasks: Run Task`.
3.  Select **Flash device**.

**Option B: Terminal**
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---
*Back to [STM32 Modules](../README.md)*
