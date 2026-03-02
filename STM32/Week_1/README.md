# ⚡ Semana 1: El Despertar del Silicio
## (23/02 - 01/03)

![Semana 1 Header](./docs/img/header.png)

Esta es la planificación atómica de tu **Semana 1**. En este periodo, dejaremos de ver el código como algo abstracto y empezaremos a verlo como impulsos eléctricos manipulando celdas de memoria de 32 bits, bajo el rigor de la ingeniería de software profesional.

---

### 📝 Resumen General
*   **Qué se va a hacer:** Dominarás la **anatomía del dato** y el **mapa de memoria lineal** del STM32F413ZH [RM0430, 2.2]. Aprenderás a configurar hardware "bare-metal" sin librerías externas, usando solo punteros crudos y operaciones a nivel de bit.
*   **Qué se va a lograr:** Al finalizar, habrás construido una "Calculadora con Acarreo" física que detecta errores lógicos (overflow) y los señaliza mediante hardware, validando tu lógica con pruebas unitarias (TDD).
*   **Alineación con el Plan Maestro:** Esta es la piedra angular de la **Fase I (Ingeniería de Software y Silicio)**. Un arquitecto no puede diseñar sistemas robustos si no entiende cómo el compilador organiza los datos en la SRAM.

---

### 🏆 El Gran Objetivo: "The LED Carry Calculator"

Diseñarás un sistema que sume dos números de 8 bits (`uint8_t`). Los 8 LEDs externos actuarán como tu **Bus de Datos**, mostrando el resultado.
1.  **Visualización de Datos:** El resultado truncado se verá en los LEDs externos.
2.  **Visualización de Estado:** El **LED3 (Rojo - PB14)** de la Nucleo se encenderá si la lógica detecta un **Integer Overflow**, indicando un acarreo (Carry).
3.  **Rigor Bare-metal:** No usarás `HAL_GPIO_Write()`. Usarás punteros directos a los registros `RCC_AHB1ENR`, `GPIOx_MODER` y `GPIOx_ODR`.

---

### 📅 Cronograma de Actividades

| Fecha | Día | Actividad Granular | Objetivo Técnico |
| :--- | :--- | :--- | :--- |
| **23/02** | **Lunes** | **Estándares y Rigor** | Configurar `-Werror` e implementar `stdint.h`. |
| **24/02** | **Martes** | **Mapa de Memoria** | Localizar SRAM/Flash e identificar direcciones físicas [RM0430, 2.2]. |
| **25/02** | **Miércoles** | **Bitwise Ops** | Implementar macros para manipular bits individuales. |
| **26/02** | **Jueves** | **Punteros y Volatilidad** | Casting de direcciones y uso crítico de `volatile`. |
| **27/02** | **Viernes** | **Taller Físico** | Ejecución del proyecto en hardware real (Calculadora LED). |
| **28/02** | **Sábado** | **Unit Testing (TDD)** | Validar lógica con Ceedling/Unity en la PC. |
| **01/03** | **Domingo** | **Refactorización** | Limpiar el código y aplicar Shutsuke (Autodisciplina). |

---

### 🔬 Guía Atómica Día a Día

#### 🟢 Lunes: La Disciplina del Tipo de Dato
*   **Acción 1:** En tu `toolchain` o `CMakeLists.txt`, añade `-Wall -Wextra -Werror`. Si hay un warning, el build falla.
*   **Acción 2:** Crea `printTypeSizes()` validando `uint8_t`, `uint16_t`, `uint32_t` y `float`.
*   **Meta:** El programa debe compilar sin warnings.

#### 🔵 Martes: Cartografía del Silicio
*   **Acción 1:** Abre el manual **RM0430**. Localiza la **Tabla 1 (Memory Map)**. SRAM1 empieza en `0x2000 0000`.
*   **Acción 2:** Imprime direcciones de variables `static` (RAM) y locales (Stack) usando `%p`.
*   **Verificación:** Comprueba la distancia entre ambas direcciones en el mapa de memoria.

#### 🟡 Miércoles: Operaciones Quirúrgicas de Bits
*   **Acción 1:** Crea macros `SET_BIT`, `CLEAR_BIT` y `TOGGLE_BIT` usando desplazamientos (`<<`) y máscaras.
*   **Principio:** "Hacer una sola cosa": una función para el cálculo y otra para la visualización.

#### 🔴 Jueves: Hackeo de Memoria y Volatilidad
*   **Acción 1:** Localiza la dirección del registro `GPIOB_ODR` (`0x4002 0414`).
*   **Acción 2:** Declara el puntero: `volatile uint32_t *pODR = (uint32_t *)0x40020414;`.
*   **Importante:** El uso de `volatile` es obligatorio para evitar que el compilador optimice y elimine tus escrituras al LED.

#### 🔌 Viernes: Board Bring-Up (El Taller)
*   **Hardware:** Habilita el reloj del GPIOB en `RCC_AHB1ENR` (Bit 1). Configura los pines en `GPIOB_MODER`.
*   **Lógica:** Implementa la suma con detección de acarreo: `if (result < opA) { *pODR |= (1 << 14); }`.

#### 🧪 Sábado: Test-Driven Development (TDD)
*   **Acción:** Configura **Ceedling**. Escribe una prueba unitaria para tu función de suma.
*   **Rigor:** Ciclo Rojo-Verde-Refactor. Asegúrate de tener **un solo Assert por test**.

#### 🧹 Domingo: Shutsuke (Autodisciplina)
*   **Regla del Boy Scout:** Mejora los nombres de variables y funciones para que revelen su intención.
*   **Metáfora del Periódico:** El `main` arriba con la lógica de alto nivel; detalles de registros al final del archivo.

---

### 🚀 Criterio de Éxito
Si el domingo tu placa muestra una suma correcta y el LED rojo se activa solo cuando hay overflow, habrás ganado la semana con la honestidad técnica de un profesional.

---

### 🛠️ Guía Rápida de Compilación

#### 1. Build
```bash
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/stm32_gcc.cmake
cmake --build build
```

#### 2. Flash
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---
*Back to [STM32 Modules](../README.md)*
