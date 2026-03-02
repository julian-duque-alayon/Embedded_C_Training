# 📅 Day 1 — Monday: The Discipline of Data Types

**Date:** 02/03 | **Week:** 1 | **Theme:** Standards and Rigor

---

## 🎯 Objectives

- Understand why **fixed-width integer types** exist and matter in embedded systems.
- Use `sizeof()` to inspect how many bytes each type occupies.
- Distinguish between **compile-time** and **runtime** validation.
- Implement `printTypeSizes()` to verify platform data type guarantees.

---

## 🧠 Core Concepts

### 1. Why Not Just Use `int`?

In standard C, the size of `int` is **not guaranteed**. It can be 2 bytes on an 8-bit AVR or 4 bytes on a 32-bit ARM. This ambiguity is dangerous in embedded C:

```c
int counter = 256;  // Fine on ARM, OVERFLOWS on 8-bit AVR (max 255 for 8-bit int)
```

**Solution → Fixed-width types from `<stdint.h>`:**

| Type | Guaranteed Size | Range |
|---|---|---|
| `uint8_t` | 1 byte (8 bits) | 0 – 255 |
| `uint16_t` | 2 bytes (16 bits) | 0 – 65,535 |
| `uint32_t` | 4 bytes (32 bits) | 0 – 4,294,967,295 |
| `float` | 4 bytes (IEEE 754) | ±3.4 × 10³⁸ |

> **Rule of thumb:** In embedded C, always use `uint8_t`, `uint16_t`, `uint32_t`
> instead of `char`, `short`, `int`. Your intent is explicit and portable.

---

### 2. `sizeof()` — The Size Operator

`sizeof()` is a **compile-time operator** that returns the number of bytes a
type or variable occupies in memory. It returns a `size_t` value.

```c
sizeof(uint8_t)   // → 1
sizeof(uint16_t)  // → 2
sizeof(uint32_t)  // → 4
sizeof(float)     // → 4
```

> ⚠️ `sizeof()` is NOT a function — it is evaluated entirely by the compiler.
> There is **zero runtime cost**.

---

### 3. Two Kinds of Validation

#### ✅ Compile-Time: `static_assert()` ← *Preferred in embedded*

```c
#include <assert.h>

static_assert(sizeof(uint8_t) == 1, "uint8_t must be 1 byte");
```

- If the condition is **false**, the compiler **refuses to build** and prints the message.
- The binary is **never created** if types don't match expectations.
- Available in **C11** and later (`_Static_assert` keyword, or `static_assert` via `<assert.h>`).
- **Zero runtime cost** — the check literally does not exist in the final .elf.

#### 🖨️ Runtime: `printf()` + manual comparison

```c
printf("uint8_t : %d byte(s) - %s\n",
       (int)sizeof(uint8_t),
       sizeof(uint8_t) == 1 ? "OK" : "FAIL");
```

- Prints the actual value when the program **executes**.
- Useful for debugging and logging.
- On bare-metal STM32, requires **semihosting** or **UART redirect** to see output.

---

## 💻 Implementation

### File: `App/src/main.c`

```c
#include <stdint.h>   /* uint8_t, uint16_t, uint32_t                       */
#include <stdio.h>    /* printf()                                           */
#include <assert.h>   /* static_assert()                                   */

/* ── Compile-Time Validation ──────────────────────────────────────────── */
static_assert(sizeof(uint8_t)  == 1, "uint8_t must be 1 byte");
static_assert(sizeof(uint16_t) == 2, "uint16_t must be 2 bytes");
static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
static_assert(sizeof(float)    == 4, "float must be 4 bytes");

/* ── Function Prototype ──────────────────────────────────────────────── */
void printTypeSizes(void);

/* ── printTypeSizes() ────────────────────────────────────────────────── */
void printTypeSizes(void)
{
    printf("=== Type Size Validation ===\n");

    printf("uint8_t  : %d byte(s)  - expected 1  - %s\n",
           (int)sizeof(uint8_t),
           sizeof(uint8_t) == 1 ? "OK" : "FAIL");

    printf("uint16_t : %d byte(s)  - expected 2  - %s\n",
           (int)sizeof(uint16_t),
           sizeof(uint16_t) == 2 ? "OK" : "FAIL");

    printf("uint32_t : %d byte(s)  - expected 4  - %s\n",
           (int)sizeof(uint32_t),
           sizeof(uint32_t) == 4 ? "OK" : "FAIL");

    printf("float    : %d byte(s)  - expected 4  - %s\n",
           (int)sizeof(float),
           sizeof(float) == 4 ? "OK" : "FAIL");

    printf("============================\n");
}

/* ── main() ──────────────────────────────────────────────────────────── */
int main(void)
{
    printTypeSizes();
    return 0;
}
```

---

## 📤 Expected Output

```
=== Type Size Validation ===
uint8_t  : 1 byte(s)  - expected 1  - OK
uint16_t : 2 byte(s)  - expected 2  - OK
uint32_t : 4 byte(s)  - expected 4  - OK
float    : 4 byte(s)  - expected 4  - OK
============================
```

> On the STM32F413ZH (ARM Cortex-M4, 32-bit), all types above match
> their expected sizes. The `static_assert` calls will pass silently at
> compile time — which is exactly what we want.

---

## 🔑 Key Takeaways

1. **Always use `uint8_t`, `uint16_t`, `uint32_t`** instead of `char`, `short`, `int` in embedded C.
2. **`sizeof()` is free** — it is resolved at compile time with zero runtime overhead.
3. **`static_assert()` is your safety net** — it catches wrong assumptions about your platform before the MCU ever runs your code.
4. Cast `sizeof()` to `int` when using with `printf`: `(int)sizeof(uint8_t)`.

---

## 🔗 References

- `<stdint.h>` — C99 Standard §7.18
- `_Static_assert` — C11 Standard §6.7.10
- STM32F413ZH Reference Manual: **RM0430** — Section 2.2 (Memory Map)
- [Back to Week 1 README](../README.md)
