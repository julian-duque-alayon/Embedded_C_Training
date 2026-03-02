# 🛰️ Embedded C Training

Embedded systems training laboratory for **STM32** and **ESP32** microcontrollers.

---

## 📂 Repository Structure

### [STM32](./STM32)
Projects for the STM32 family, specifically focused on the **NUCLEO-F413ZH** board.
- **[Template_NucleoF413ZH](./STM32/Template_NucleoF413ZH)**: Base project with CMake and Low-Layer (LL) Drivers.
- **[Standard Project Structure](./PROJECT_STRUCTURE.md)**: Detailed explanation of the directory and file population for STM32 projects.

### [ESP32](./ESP32)
Projects for **ESP32** (Wi-Fi/Bluetooth IoT systems).
- **[Template](./ESP32/Template)**: Base structure for ESP-IDF / Arduino projects.

---

## 🛠️ Development Workflow (Professional Modular Setup)

To avoid conflicts between different microcontrollers (STM32 vs ESP32) and different project versions, this repository uses a **Modular Project Model**.

### 💡 The Core Rule: Open the Subfolder, Not the Root
Do **not** open the entire `Embedded_C_Training` folder in VS Code. Instead:
1.  Go to **File > Open Folder...**
2.  Navigate into the specific project you want to work on (e.g., `STM32/Week_1` or `STM32/Template_NucleoF413ZH`).
3.  VS Code will now use the local `.vscode` configuration specifically tuned for that project.

---

### 1. Initial Setup (The "Big Three" Commands)
The first time you open a project folder, or if you change the compiler, you must configure the environment:
1.  **Select Kit**: Press `Ctrl + Shift + P` -> **`CMake: Select a Kit`**. Choose your ARM compiler (e.g., `GCC for arm-none-eabi`).
2.  **Select Variant**: Press `Ctrl + Shift + P` -> **`CMake: Select Variant`**. Choose **`Debug`** (enables breakpoints and variable inspection).
3.  **Configure**: Press `Ctrl + Shift + P` -> **`CMake: Configure`**. This scans the source files and generates the build system (Ninja).

---

### 2. Building & Compiling
Once configured, you have two ways to compile:
*   **IDE (Status Bar)**: Click the **Build** button (or the gear icon) at the very bottom of the VS Code window.
*   **Terminal**: 
    ```bash
    cmake --build build
    ```

---

### 3. Flashing & Debugging (The "Play" Button)
We use **OpenOCD** and the **Cortex-Debug** extension to talk to the Nucleo board.
*   **To Debug**: Press **F5** (or go to the "Run and Debug" side tab and click the green arrow).
    *   This will automatically **Compile**, **Flash**, and **Launch** the debugger.
    *   The code will pause at the start of `main()`, allowing you to step through line-by-line.
*   **To Quick-Flash (No Debug)**: Press **`Ctrl + Shift + B`** and select **`Flash Nucleo`**. This is a fast way to just update the code on the board without starting a full debug session.

---

### 4. Direct Terminal Control (Troubleshooting)
If the IDE buttons fail or you are on a system without the extension:
#### **A. Manual Build**
```bash
cmake -B build -G Ninja
cmake --build build
```
#### **B. Manual Flash (via OpenOCD)**
From the project root:
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/Nucleo_F413_Template.elf verify reset exit"
```

---

### 5. ESP32 Projects
ESP32 projects (like the one in `ESP32/Template_ESP32`) do not use the standard ARM CMake tools. They use the **ESP-IDF** framework. 
1. Open the ESP32 folder directly.
2. Use the **ESP-IDF icon** in the sidebar.
3. Use `idf.py build`, `idf.py flash`, and `idf.py monitor` in the terminal.

---
*Developed by [Julian Duque](https://github.com/julian-duque-alayon)*