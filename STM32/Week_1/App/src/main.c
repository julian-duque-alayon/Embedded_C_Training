/**
 * @file    main.c
 * @brief   Week 1 - Action 2: Type Size Validation
 *
 * Goal: Verify that fixed-width integer types and float have the
 *       expected sizes on this platform (STM32 ARM Cortex-M).
 */

/* ── Includes ──────────────────────────────────────────────────────────── */
#include <stdint.h>   /* uint8_t, uint16_t, uint32_t                       */
#include <stdio.h>    /* printf()                                           */
#include <assert.h>   /* static_assert() — compile-time checks             */

/* ── Global Variables ──────────────────────────────────────────────────── */
/* 
 * uwTick is required by stm32f4xx_it.c for the SysTick_Handler. 
 * Since we are in a bare-metal state, we define it here.
 */
volatile uint32_t uwTick = 0;

/* ── Compile-Time Validation (runs BEFORE the program even starts) ──────
 *
 *  static_assert(condition, "message if false");
 *
 *  If the condition is false, the compiler STOPS and shows the message.
 *  This is the BEST kind of check for embedded: zero runtime cost.
 */
static_assert(sizeof(uint8_t)  == 1, "uint8_t must be 1 byte");
static_assert(sizeof(uint16_t) == 2, "uint16_t must be 2 bytes");
static_assert(sizeof(uint32_t) == 4, "uint32_t must be 4 bytes");
static_assert(sizeof(float)    == 4, "float must be 4 bytes");

/* ── Function Prototype ─────────────────────────────────────────────────── */
void printTypeSizes(void);

/* ── printTypeSizes ─────────────────────────────────────────────────────
 *
 *  Runtime validation: prints the actual size and confirms expectation.
 *  Uses printf() — on bare-metal STM32 this requires semihosting or
 *  a UART redirect. On a hosted environment (Linux/PC) it prints normally.
 */
void printTypeSizes(void)
{
    printf("=== Type Size Validation ===\n");

    /* sizeof() returns size_t; we cast to int for simple printf format    */
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

/* ── main ───────────────────────────────────────────────────────────────── */
int main(void)
{
    printTypeSizes();

    return 0;
}
