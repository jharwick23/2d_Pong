# Pong Project Setup Guide

This guide provides instructions for setting up and running the Pong project on **Windows** and **Linux**. Since the project includes `tasks.json` and `launch.json`, you do not need to manually build it if you're using **VS Code**.

---

## Prerequisites

Ensure you have the following installed on your system:

### **Windows**
1. **SFML 2.5.1**
   - Download SFML from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
   - Extract and place SFML in a known directory (e.g., `C:\SFML-2.5.1`)
2. **MinGW (if using GCC)**
   - Install `mingw-w64` from [https://www.mingw-w64.org/](https://www.mingw-w64.org/)
   - Ensure `g++` is available in your system path
3. **Visual Studio Code (Recommended)**
   - Install [VS Code](https://code.visualstudio.com/)
   - Install the C++ extension from the Extensions Marketplace

### **Linux**
1. Install **SFML** using your package manager:
   ```sh
   sudo apt update && sudo apt install libsfml-dev
   ```
   _For Arch Linux:_
   ```sh
   sudo pacman -S sfml
   ```
2. Install **GCC** (if not installed):
   ```sh
   sudo apt install g++
   ```
3. Install **Visual Studio Code (Optional but Recommended)**:
   - Follow the instructions at [https://code.visualstudio.com/Download](https://code.visualstudio.com/Download)

---

## Setting Up the Project

### **Using VS Code (Recommended Method)**
1. Open the project folder in **VS Code**.
2. Make sure SFML is correctly installed on your system.
3. The project contains **tasks.json** and **launch.json**, which allow you to:
   - **Build** automatically when pressing `Ctrl+Shift+B`.
   - **Run and Debug** using `F5`.
4. If needed, update `tasks.json` to point to your SFML installation path.

---

## **Running the Project Manually** (If Not Using VS Code)

### **Windows (MinGW) Manual Build**
If not using VS Code, compile manually using:
```sh
g++ -g pong.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
Then, run the executable:
```sh
./pong.exe
```

### **Linux Manual Build**
```sh
g++ -g pong.cpp -o pong -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
./pong
```

---

## Troubleshooting
- **SFML Not Found?** Ensure SFML is correctly installed and available in your compiler's library path.
- **Missing Dependencies?** Run `ldd pong` (Linux) or check MinGW installation (Windows).
- **Audio Issues?** Confirm that `paddle.wav` and `win.wav` are in the project folder and use `.wav` files (not `.mp3`).

---

## GitHub Repository
Find the latest version of this project on GitHub:
[https://github.com/jharwick23/2d_Pong](https://github.com/jharwick23/2d_Pong)

---

## Contributors
- **jharwick23** - Original Developer

This setup should allow you to develop, build, and run the Pong project smoothly. 

