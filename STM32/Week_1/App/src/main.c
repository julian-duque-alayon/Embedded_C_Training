#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"

/* Global tick variable for LL_mDelay */
__IO uint32_t uwTick = 0;

void SystemClock_Config(void);

int main(void) {
    // 1. Setup the system clock (Essential)
    SystemClock_Config();

    // 2. Enable GPIO Clock (Nucleo-144 Blue LED is usually PB7)
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);

    // 3. Configure Pin PB7 as Output
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_14, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);

    while (1) {
        LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_14);
        LL_mDelay(500); // Only works if SysTick is configured
        LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_7);
        LL_mDelay(500); // Only works if SysTick is configured
    }
}

void SystemClock_Config(void) {
    // Basic internal clock config (HSI)
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
    LL_RCC_HSI_Enable();
    while(LL_RCC_HSI_IsReady() != 1);
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);
    while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI);
    LL_Init1msTick(16000000); // 16MHz
    LL_SetSystemCoreClock(16000000);
}