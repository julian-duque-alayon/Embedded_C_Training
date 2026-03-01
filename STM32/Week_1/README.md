# 🚀 Semana 1: Anatomía del Dato y Mapa de Memoria

¡Claro que sí! No solo tenemos un plan, sino que el objetivo de esta primera semana es transformar la teoría que estás leyendo en el manual en conocimiento **"machacado en tus dedos"**. Como indica la bibliografía, no puedes llamarte profesional si no aplicas la disciplina del código limpio y la práctica constante desde el inicio.

> [!IMPORTANT]
> **Ley de LeBlanc:** *"Más tarde es igual a nunca"*.  
> No dejes para mañana lo que puedes programar hoy.

---

## 🏆 El Gran Objetivo de la Semana: "The LED Carry Calculator"
Para el domingo, debes haber programado un sistema que:
1. **Operación Crítica:** Realice una operación aritmética (como una suma) que cause un desbordamiento de bits (**Integer Overflow**).
2. **Visualización:** Configure los registros físicos del **STM32F413ZH** para mostrar el resultado en binario usando los LEDs de la placa (**PB0, PB7, PB14**).
3. **Bajo Nivel:** Maneje el hardware mediante **punteros directos a memoria** y el calificador `volatile`, sin usar ninguna librería externa de ST.

---

## 📅 Plan de Programación Diario (Nivel Atómico)

| Día | Objetivo de Programación (Hacer) | Resultado Esperado |
| :--- | :--- | :--- |
| **Lunes** | Crear la función `printStandardTypeSizes` usando exclusivamente `<stdint.h>`. | Ver en consola el tamaño exacto de `uint8_t`, `uint32_t` y `float`. |
| **Martes** | Imprimir las direcciones de memoria de una variable global y una local usando `%p`. | Confirmar que la global empieza en `0x20...` (SRAM) y la local en el Stack. |
| **Miércoles** | Implementar macros de operaciones bitwise (`SET_BIT`, `CLEAR_BIT`) y probarlas. | Dominar la manipulación quirúrgica de bits antes de tocar el hardware. |
| **Jueves** | Escribir código que lea el registro `RCC_AHB1ENR` (dirección `0x40023830`). | Validar acceso a direcciones físicas usando casting de punteros. |
| **Viernes** | **Taller Físico:** Configurar pines de LEDs como salida y realizar suma con overflow. | Ver el resultado de tu lógica de C reflejado en los voltajes de la placa. |

---

## 🧐 ¿Por qué debes programar hoy mismo?
La pereza es el primer obstáculo para un arquitecto. El libro *Clean Code* explica que aprender a escribir código limpio requiere sudar sobre él y practicar tú mismo. Leer el manual es necesario, pero si no programas, solo estarás acumulando **"conocimiento de avión"** que olvidarás al aterrizar.

### 🏁 Tu meta técnica para hoy:
**No termines el día sin que tu Makefile/CMake compile un `main.c` que use `sizeof()` para validar que estás en una arquitectura de 32 bits.** Esa pequeña victoria dopaminérgica es la que eliminará la pereza para mañana.

---

## 🛠️ Guía Rápida de Uso

### 1. Construir el Proyecto
```bash
# Configurar el sistema de construcción
cmake -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=cmake/stm32_gcc.cmake

# Compilar
cmake --build build
```

### 2. Flashear la Placa
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---
*Volver a [Módulos STM32](../README.md)*

