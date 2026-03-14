# 🛰️ Mission Control: Embedded C Training

Welcome to the **Embedded C Training Laboratory**. This is where code meets copper, and logic controls electricity. We're focusing on the **STM32** and **ESP32** ecosystems, moving from "Hello World" (blinking LEDs) to professional modular firmware engineering.

> [!IMPORTANT]
> **Safety First:** No microcontrollers were harmed in the making of this repository. Let's keep it that way! 🧨 (until now)

---

## 🗺️ The Exploration Map

Navigate through the different architectures and templates available:

| Target | Description | Shortcut |
| :--- | :--- | :--- |
| **STM32** | Hardcore ARM Cortex-M4 (NUCLEO-F413ZH). LL Drivers & CMake. | [Go to STM32](./STM32) |
| **ESP32** | IoT Powerhouse (Wi-Fi/Bluetooth). ESP-IDF & Arduino. | [Go to ESP32](./ESP32) |
| **Standard** | Learn how we organize things here (Standard Structure). | [Read Structure](./PROJECT_STRUCTURE.md) |

---

## 🚀 Ignition: Linux Environment Setup

Before we flash any silicon, we need to sharpen our tools. Choose your distribution and run the magic commands:

### 🛠️ Step 1: Install the Arsenal

<details>
<summary><b>Arch / Manjaro (The User's Choice) 🐧</b></summary>

```bash
sudo pacman -S --needed \
    arm-none-eabi-gcc arm-none-eabi-newlib \
    arm-none-eabi-binutils arm-none-eabi-gdb \
    cmake ninja openocd stlink
```
</details>

<details>
<summary><b>Ubuntu / Debian 🐧</b></summary>

```bash
sudo apt update && sudo apt install -y \
    gcc-arm-none-eabi binutils-arm-none-eabi \
    libnewlib-arm-none-eabi gdb-multiarch \
    cmake ninja-build openocd stlink-tools
```
</details>

<details>
<summary><b>Fedora 🐧</b></summary>

```bash
sudo dnf install \
    arm-none-eabi-gcc-cs arm-none-eabi-binutils-cs \
    arm-none-eabi-newlib arm-none-eabi-gdb \
    cmake ninja-build openocd stlink
```
</details>

### 🔑 Step 2: Gaining "Superpowers" (Permissions)

To talk to your hardware without being `root`, you need to join the inner circle:

*   **Arch/Manjaro**: `sudo usermod -aG uucp $USER`
*   **Others**: `sudo usermod -aG dialout,plugdev $USER`

> [!CAUTION]
> **Logout/Restart!** Your terminal won't know you're famous (part of the group) until you log back in.

### 🔌 Step 3: The Secret Handshake (Is it connected?)

Run these to ensure your Linux kernel is talking to your Nucleo board:
1.  **USB Peek**: `lsusb` → Look for `STMicroelectronics ST-LINK/V2.1`.
2.  **Port Scan**: `ls /dev/ttyACM*` → Should see `/dev/ttyACM0`.
3.  **The Probe**: `st-info --probe` → The ultimate truth. If it returns a Serial ID, you're golden!

---

## 💻 The Toolbox (VS Code Extensions)

To make your life 100x easier, install these **Mandatory** extensions:
1. 🛡️ **C/C++** (`ms-vscode.cpptools`)
2. 🔨 **CMake Tools** (`ms-vscode.cmake-tools`)
3. 🐞 **Cortex-Debug** (`marus25.cortex-debug`)

---

## ⚙️ The Flight Manual: Development Workflow

We use a **Professional Modular Setup**. No messy root folders, just clean projects.

### 💡 The Golden Rule: Focus!
**Do NOT open the root `Embedded_C_Training` folder in VS Code.**
Instead, open the *specific project* folder (e.g., `STM32/Template_NucleoF413ZH`). This triggers the local config and makes everything "just work".

---

### 🛫 Pre-Flight Checklist (The "Big Three")

The first time you enter a project, perform these incantations (`Ctrl + Shift + P`):
1.  **Select Kit**: Choose `GCC for arm-none-eabi`.
2.  **Select Variant**: Choose `Debug` (unless you like guessing why your code crashed).
3.  **Configure**: Run `CMake: Configure` to generate the build files.

---

### 🚢 Building & Launching

*   **Build**: Click the **Build** button in the status bar or run `cmake --build build`.
*   **The "Magic" Button (F5)**: Pressing **F5** will **Compile**, **Flash**, and start a **Debug** session automatically. 
*   **Quick Flash**: Press `Ctrl + Shift + B` -> Select `Flash Nucleo`. Fast and effective.

---

## 📟 Terminal Fu (For the Hardcore)

If the IDE is acting up, use the raw power of the terminal:

**A. Manual Build:**
```bash
cmake -B build -G Ninja && cmake --build build
```

**B. Manual Flash (OpenOCD):**
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---

## ⚡ The ESP32 Realm

ESP32 projects are different beasts. They don't use the ARM tools.
1. Open the ESP32 folder directly.
2. Use the **ESP-IDF extension** icons.
3. Terminal commands: `idf.py build`, `idf.py flash`, `idf.py monitor`.

---

<p align="center">
  <i>Developed with ❤️ by <a href="https://github.com/julian-duque-alayon">Julian Duque</a></i>
</p>