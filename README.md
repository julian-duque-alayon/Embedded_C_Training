# 🛰️ Mission Control: Embedded C Training

Welcome to the **Embedded C Training Laboratory**. This is a comprehensive repository designed for mastering firmware development on **STM32 (ARM Cortex-M)** and **ESP32 (Xtensa/RISC-V)** architectures. We move from foundational "Blinky" projects to professional-grade modular firmware engineering.

---

## 🗺️ The Exploration Map

This repository is organized by architecture. Each folder contains its own self-contained environment:

| Target | Description | Shortcut |
| :--- | :--- | :--- |
| **STM32** | ARM Cortex-M4 (Nucleo-F413ZH). Low-Layer (LL) Drivers & CMake. | [Go to STM32](./STM32) |
| **ESP32** | IoT Powerhouse. ESP-IDF & Arduino framework support. | [Go to ESP32](./ESP32) |
| **Standard** | Documentation on our professional project structure. | [Read Structure](./PROJECT_STRUCTURE.md) |

---

## 🚀 Environment Setup (The Heavy Lifting)

To compile and flash code to silicon, you need a specific toolchain. Choose your operating system/method below:

---

### 🐧 Option A: Native Linux

### 📦 1. Core Toolchain Dependencies

You will need the ARM GCC compiler, flashing tools (ST-Link/OpenOCD), and build systems.

#### **Arch Linux / Manjaro**
```bash
sudo pacman -S --needed \
    base-devel git cmake ninja \
    arm-none-eabi-gcc arm-none-eabi-newlib arm-none-eabi-binutils \
    arm-none-eabi-gdb stlink openocd \
    python python-pip usbutils
```

#### **Ubuntu / Debian / Linux Mint**
```bash
sudo apt update && sudo apt install -y \
    build-essential git cmake ninja-build \
    gcc-arm-none-eabi libnewlib-arm-none-eabi binutils-arm-none-eabi \
    gdb-multiarch stlink-tools openocd \
    python3 python3-pip usbutils
```

#### **Fedora**
```bash
sudo dnf install \
    gcc gcc-c++ make git cmake ninja-build \
    arm-none-eabi-gcc-cs arm-none-eabi-newlib arm-none-eabi-binutils-cs \
    arm-none-eabi-gdb-cs stlink openocd \
    python3 python3-pip usbutils
```

---

### 🔑 2. Hardware Permissions (udev Rules)

Linux protects USB devices by default. You need permission to talk to the ST-LINK without using `sudo`.

1.  **Add your user to groups:**
    *   **Arch/Manjaro**: `sudo usermod -aG uucp $USER`
    *   **Ubuntu/Others**: `sudo usermod -aG dialout,plugdev $USER`
2.  **Install udev rules (via stlink package):**
    The `stlink` package usually handles this, but if your device isn't recognized, you might need to reload:
    ```bash
    sudo udevadm control --reload-rules
    sudo udevadm trigger
    ```

> [!IMPORTANT]
> **Reboot or Log out & Log in** after adding yourself to groups for changes to take effect.

---

### 🔌 3. The "Truth Check" (Verifying Hardware)

Once everything is installed, plug in your Nucleo board and run these commands to verify the connection:

1.  **USB Check**:
    ```bash
    lsusb | grep -i "STMicroelectronics"
    ```
    *Should show: `ID 0483:374b STMicroelectronics ST-LINK/V2.1`*

2.  **Serial Port Check**:
    ```bash
    ls /dev/ttyACM*
    ```
    *Should show: `/dev/ttyACM0` (or similar).*

3.  **ST-LINK Tool Check**:
    ```bash
    st-info --probe
    ```
    *If you get `command not found`, ensure `stlink` (Arch) or `stlink-tools` (Ubuntu) is installed correctly and `/usr/bin` is in your `$PATH`.*

---

### 🪟 Option B: Windows (WSL2)

Developing from Windows is highly recommended using **WSL2** (Windows Subsystem for Linux). This allows you to use the same professional toolchains as in Linux while staying on Windows.

#### **1. Core Concept**
WSL2 runs a real Linux kernel. This means that once you are inside WSL, **the installation and dependencies are identical to Native Linux**. The only difference is how the hardware is connected.

#### **2. Install Dependencies**
Choose your distro (usually Ubuntu) and follow the **[Native Linux](#-option-a-native-linux)** instructions *inside* your WSL terminal.

#### **3. Hardware Bridging (The Bridge)**
By default, WSL2 cannot access USB ports. You must "pass" the ST-Link from Windows to Linux:

1.  **On Windows Host**: Install [usbipd-win](https://github.com/dorssel/usbipd-win/releases).
2.  **On Windows Terminal (Admin)**:
    ```powershell
    usbipd list                         # Identify the ST-Link Bus ID
    usbipd bind --busid <BUSID>          # Do this only the first time
    usbipd attach --wsl --busid <BUSID>  # Run this every time you connect the board
    ```
3.  **On WSL Terminal**: Run `lsusb` to verify that the board is visible.

#### **4. VS Code Integration**
You MUST use the **WSL Extension**. 
- Open VS Code, click the green icon (bottom-left) -> **Connect to WSL**.
- **Important**: Your extensions (C/C++, CMake, Cortex-Debug) must be installed **"in WSL"** (VS Code will show a button to install them in the remote context).

---

## 💻 The Toolbox (VS Code Setup)

For the best experience, install these extensions:
1.  **C/C++ Extension Pack** (`ms-vscode.cpptools-extension-pack`)
2.  **CMake Tools** (`ms-vscode.cmake-tools`)
3.  **Cortex-Debug** (`marus25.cortex-debug`) - *Vital for STM32 debugging.*

---

## ⚙️ Development Workflow

### 💡 The Golden Rule: Use "Folder Context"
**Do NOT open the root `Embedded_C_Training` folder in VS Code.**
Instead, open the specific project folder (e.g., `STM32/Template_NucleoF413ZH`). This ensures the `.vscode` settings for that specific architecture are loaded correctly.

### 🛫 Building & Flashing
1.  **Configure**: Press `Ctrl + Shift + P` and search for `CMake: Configure`.
2.  **Select Kit**: Choose `GCC [version] arm-none-eabi`.
3.  **Build**: Click **Build** in the status bar or press `F7`.
4.  **Flash & Debug**: Press **F5**. This will automatically compile, upload the code via OpenOCD/ST-LINK, and start the debugger.

---

## ⚡ ESP32 Specifics

ESP32 development uses the **ESP-IDF**.
1. Open an ESP32 project folder.
2. The first time, it will prompt you to install the ESP-IDF Toolchain (select "Express Install").
3. Use the icons in the bottom bar to Build, Flash, and Monitor.

---

<p align="center">
  <i>Maintained with focus by <a href="https://github.com/julian-duque-alayon">Julian Duque</a></i><br>
  <b>Happy Hacking! 🚀</b>
</p>