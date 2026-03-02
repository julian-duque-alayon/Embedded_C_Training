# 📅 Day 1 — Monday: The Discipline of Data Types

**Date:** 02/03 | **Week:** 1 | **Theme:** Standards and Rigor

---

## 🎯 Objectives

- **Standardize:** Transition from ambiguous C types (`int`, `char`) to deterministic fixed-width types (`uint8_t`, `uint32_t`).
- **Validate:** Use `sizeof()` to bridge the gap between abstract code and physical memory consumption.
- **Enforce:** Implement compile-time guards using `static_assert()` to prevent invalid binaries.
- **Inspect:** Create a diagnostic tool (`printTypeSizes()`) to verify the platform's data anatomy.

---

## 🏗️ Hardware Context (ARM Cortex-M4)

The **STM32F413ZH** is a 32-bit microcontroller based on the **ARM Cortex-M4** architecture. This means:
- The native **Word Size** is 32 bits (4 bytes).
- Standard CPU registers (R0-R15) are 32 bits wide.
- Memory addresses are 32 bits, allowing for a 4GB addressable space.

In this environment, an `int` is typically 32 bits, but the C standard only guarantees that it is *at least* 16 bits. This ambiguity is why we use `<stdint.h>`.

---

## 🧠 Core Concepts in Detail

### 1. The Anatomy of Fixed-Width Types
In embedded systems, memory is a physical resource, not an abstraction. Using the wrong type can lead to:
- **Memory Waste:** Using a 32-bit `int` for a flag only needing 1 bit.
- **Silent Overflows:** A 16-bit variable rolling over at 65,535 when you expected more.
- **Bus Misalignment:** 32-bit CPUs often access memory faster when data is aligned to 4-byte boundaries.

| Type | Bytes | Bits | Range (Unsigned) | Typical Embedded Use Case |
| :--- | :---: | :---: | :--- | :--- |
| `uint8_t` | 1 | 8 | 0 to 255 | Register bitmasks, byte buffers, ASCII characters. |
| `uint16_t` | 2 | 16 | 0 to 65,535 | ADC samples, PWM duty cycles, 16-bit timers. |
| `uint32_t` | 4 | 32 | 0 to ~4.29 Billion | Memory addresses, system ticks, 32-bit registers. |
| `float` | 4 | 32 | ±3.4e38 | Sensor scaling (uses the FPU - Floating Point Unit). |

---

### 2. `sizeof()` — The Compiler's Ruler
Most beginners think `sizeof()` is a function call. It is **not**. It is a **unary operator** evaluated by the compiler.

```c
uint32_t myVar;
size_t s = sizeof(myVar); // The compiler replaces this with "4" at build time.
```

**Why it matters:** Because it happens at compile-time, it adds **0% CPU overhead**. You can use it inside performance-critical loops without penalty.

---

### 3. The Power of `static_assert()`
Modern C (C11 and beyond) introduced `static_assert`. This is the most powerful "Technical Honesty" tool for an embedded engineer.

- **Standard `assert()`:** Happens at runtime. If it fails, the code crashes while the device is in the field.
- **`static_assert()`:** Happens during compilation. If it fails, the **compiler generates an error** and refuses to produce a `.bin` or `.hex` file.

**Scenario:** If you accidentally compile code designed for a 32-bit STM32 on an 8-bit Arduino where types differ, `static_assert` will stop you before you even flash the board.

---

## 🔍 The `uwTick` Linker Mystery

When we moved to a bare-metal `main.c`, the build failed with:
`undefined reference to 'uwTick'` inside `stm32f4xx_it.c`.

### What happened?
The file `stm32f4xx_it.c` contains the **System Tick Handler** (an interrupt that fires every 1ms). This handler tries to increment a global variable named `uwTick`.

1. In a standard project, the **HAL** (Hardware Abstraction Layer) defines this variable.
2. Because we deleted the standard `main.c` (which usually includes the HAL init), the variable vanished.
3. The **Linker** couldn't find the memory address for `uwTick`, so it failed.

### The Fix: Manual Definition
We added `volatile uint32_t uwTick = 0;` to our `main.c`.
- **`volatile`:** This is crucial. It tells the compiler "This variable can change at any time (via an interrupt), so don't optimize it away."
- This satisfies the linker while keeping our code independent of the bulky HAL libraries.

---

## 💻 Implementation: `App/src/main.c`

```c
#include <stdint.h>   /* Fixed-width types */
#include <stdio.h>    /* printf and console I/O */
#include <assert.h>   /* static_assert */

/* 
 * ── Global Variables ──
 * Required to satisfy the stm32f4xx_it.c dependency.
 * Volatile ensures the compiler doesn't assume the value stays constant. 
 */
volatile uint32_t uwTick = 0;

/* 
 * ── Compile-Time Enforcers ──
 * These check our assumptions before the code even reaches the board.
 */
static_assert(sizeof(uint8_t)  == 1, "Platform Error: uint8_t is not 1 byte");
static_assert(sizeof(uint16_t) == 2, "Platform Error: uint16_t is not 2 bytes");
static_assert(sizeof(uint32_t) == 4, "Platform Error: uint32_t is not 4 bytes");
static_assert(sizeof(float)    == 4, "Platform Error: float is not 4 bytes");

void printTypeSizes(void)
{
    printf("\n--- STM32 Data Anatomy Check ---\n");
    
    /* Format: Type | Size | Status */
    printf("uint8_t  : %d Byte  [%s]\n", (int)sizeof(uint8_t),  sizeof(uint8_t)  == 1 ? "PASS" : "FAIL");
    printf("uint16_t : %d Bytes [%s]\n", (int)sizeof(uint16_t), sizeof(uint16_t) == 2 ? "PASS" : "FAIL");
    printf("uint32_t : %d Bytes [%s]\n", (int)sizeof(uint32_t), sizeof(uint32_t) == 4 ? "PASS" : "FAIL");
    printf("float    : %d Bytes [%s]\n", (int)sizeof(float),    sizeof(float)    == 4 ? "PASS" : "FAIL");
    
    printf("---------------------------------\n");
}

int main(void)
{
    printTypeSizes();
    
    /* Infinite loop to prevent CPU from running into garbage memory */
    while(1) { }
    
    return 0;
}
```

---

## 📤 Verified Output (Nucleo-F413ZH)
```text
--- STM32 Data Anatomy Check ---
uint8_t  : 1 Byte  [PASS]
uint16_t : 2 Bytes [PASS]
uint32_t : 4 Bytes [PASS]
float    : 4 Bytes [PASS]
---------------------------------
```

---

## 🔑 Key Takeaways for Today

1. **Determinism:** Embedded C is about control. `uint32_t` is a contract; `int` is a suggestion.
2. **Zero-Cost Abstraction:** `sizeof()` and `static_assert()` provide safety with **zero** impact on code size or speed.
3. **Linker Logic:** Every symbol (`uwTick`, `functions`) must have a home. If you remove the home (HAL), you must provide a new one.
4. **Volatile is Mandatory:** For variables shared between `main` and Interrupts, `volatile` is your only protection against compiler over-optimization.

---

## 🔗 References
- **C11 Standard (ISO/IEC 9899:2011):** Section 6.7.10 (Static assertions).
- **ARM Cortex-M4 Generic User Guide:** Section 2.2 (Data types).
- **STM32F413ZH Datasheet:** Section 3.12 (Floating point unit).
