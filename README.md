# 🛰️ Mission Control: Embedded C Training

Welcome to the **Embedded C Training Laboratory**. This is a comprehensive repository designed for mastering firmware development on **STM32 (ARM Cortex-M)** and **ESP32 (Xtensa/RISC-V)** architectures. We move from foundational "Blinky" projects to professional-grade modular firmware engineering.

> [!TIP]
> **How to read these READMEs beautifully in your IDE:**
> 
> **The native command (No extensions needed)**
> VS Code (and its forks like Antigravity) already include a basic but functional rendering engine.
> 
> - **Shortcut:** `Ctrl + Shift + V` (Opens the preview in a new tab).
> - **Side-by-side view:** `Ctrl + K` then `V` (Opens the preview next to your code).

---

## 🗺️ The Exploration Map

This repository is organized by architecture. Each folder contains its own self-contained environment. **For hardware details, flashing/debugging tools, and specific dependencies, please go directly to the directory you wish to use.**

| Target       | Description                                                    | Shortcut                                 |
| :----------- | :------------------------------------------------------------- | :--------------------------------------- |
| **STM32**    | ARM Cortex-M4 (Nucleo-F413ZH). Low-Layer (LL) Drivers & CMake. | [Go to STM32](./STM32)                   |
| **ESP32**    | IoT Powerhouse. ESP-IDF & Arduino framework support.           | [Go to ESP32](./ESP32)                   |
| **Standard** | Documentation on our professional project structure.           | [Read Structure](./PROJECT_STRUCTURE.md) |

---

## 🚀 Core Compilation Environment

To compile the code, you need a basic toolchain and build system. For hardware-specific tools (like ST-LINK detection, flashing, and debugging), please check the README inside the target directory (e.g., `STM32/README.md`).

---

### 🐧 Option A: Native Linux

#### **Arch Linux / Manjaro**
```bash
sudo pacman -S --needed base-devel git cmake ninja python python-pip
```

#### **Ubuntu / Debian / Linux Mint**
```bash
sudo apt update && sudo apt install -y build-essential git cmake ninja-build python3 python3-pip
```

#### **Fedora**
```bash
sudo dnf install gcc gcc-c++ make git cmake ninja-build python3 python3-pip
```

---

### 🪟 Option B: Windows (WSL2)

Developing from Windows is highly recommended using **WSL2** (Windows Subsystem for Linux). 

1. **Install Dependencies**: Choose your distro (usually Ubuntu) and follow the **[Native Linux](#-option-a-native-linux)** instructions *inside* your WSL terminal.
2. **VS Code Integration**: You MUST use the **WSL Extension**. Connect to WSL and ensure your extensions are installed in the WSL environment.

*(Note: For connecting USB hardware like ST-LINK to WSL, see the specific target directory's README).*

---

## 💻 VS Code Setup

To enable full compilation capabilities within VS Code, you need these essential extensions:

### C/C++ Extension Pack (Microsoft)
This is the core engine for C development:
*   **C/C++**: Provides IntelliSense, code navigation, and syntax highlighting.
*   **CMake Tools**: **Critical.** It manages the project via your `CMakeLists.txt`. It allows you to select your target "kit" and build with one click in the bottom status bar.

*(Note: For Debugging and Serial Monitoring extensions, refer to the target-specific README).*

---

## ⚙️ Development Workflow

### 💡 The Golden Rule: Use "Folder Context"
**Do NOT open the root `Embedded_C_Training` folder in VS Code.**
Instead, open the specific project folder (e.g., `STM32/Template_NucleoF413ZH`). This ensures the `.vscode` settings for that specific architecture are loaded correctly.

### 🛫 Building
1.  **Configure**: Press `Ctrl + Shift + P` and search for `CMake: Configure`.
2.  **Select Kit**: Choose the compiler toolchain specific to your target architecture.
3.  **Build**: Click **Build** in the status bar or press `F7`.

*(For Flashing and Debugging instructions, refer to the target-specific README).*

---

## ⚡ ESP32 Specifics

> [!WARNING]
> 🚧 **Work in Progress (WIP)** 🚧
> The ESP32 section is currently under development. Detailed guides, toolchain setup, and projects are *coming soon*!

ESP32 development uses the **ESP-IDF**.
1. Open an ESP32 project folder.
2. The first time, it will prompt you to install the ESP-IDF Toolchain (select "Express Install").
3. Use the icons in the bottom bar to Build, Flash, and Monitor.

---

<p align="center">
  <i>Maintained with focus by <a href="https://github.com/julian-duque-alayon">Julian Duque</a></i><br>
  <b>Happy Hacking! 🚀</b>
</p>