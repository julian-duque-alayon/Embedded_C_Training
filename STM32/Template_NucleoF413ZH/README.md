# 🏗️ Nucleo-F413ZH Master Template

![Project Header](./docs/img/header.png)

This is the **Gold Standard** starting point for STM32F413ZH development. It is a professional, lightweight blueprint that bypasses the weight of specialized IDEs, focusing on **Direct Hardware Control** and **CMake-driven** portability.

---

## 💎 Key Features
*   **Minimalist Core**: Strips away HAL overhead in favor of **Low-Layer (LL) Drivers**.
*   **System Integrity**: Includes `syscalls.c` to enable standard C library functions (I/O, memory).
*   **Professional Toolchain**: Custom CMake architecture for cross-compiling on ANY machine.
*   **IDE Ready**: Fully configured `.vscode` tasks for one-click Flash and Debug.

---

## 📂 The Blueprint
To understand **why** this project is organized this way and the **origin** of every single file (Drivers, Startup, App, etc.), see our central guide:

👉 **[Standard Project Structure Explainer](../../PROJECT_STRUCTURE.md)**

---

## 🛠️ The Workflow

### 1. Configure & Build
**Option A: VS Code (Status Bar)**
1.  Select Kit (`Ctrl + Shift + P` -> `CMake: Select a Kit`) -> `arm-none-eabi`.
2.  Click **Build** button in the bottom status bar.

**Option B: Terminal**
```bash
cmake -B build -G Ninja
cmake --build build
```

---

### 2. Flash & Test
**Option A: VS Code (Recommended)**
1.  Press `Ctrl + Shift + P`.
2.  Type `Tasks: Run Task`.
3.  Select **Flash device**.

**Option B: Terminal (OpenOCD)**
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---

## � Maintenance
*   **Modifying Pinout**: Open the `Template.ioc` in **STM32CubeMX**.
*   **Updating Drivers**: Replace the contents of the `Drivers/` folder from the latest ST Firmware Package.

---
[⬅️ Back to STM32 Modules](../README.md)

