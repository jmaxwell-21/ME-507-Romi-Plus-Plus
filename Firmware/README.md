# Firmware

This folder contains the full STM32CubeIDE project for the STM32F411 microcontroller used in the Romi++ Differential Drive Robot.

## Contents

- `Core/` – Source code and header files for all robot software
- `Drivers/` – HAL drivers for peripherals
- `.ioc` file – STM32CubeMX configuration file
- `.project` and `.cproject` – Eclipse project files for STM32CubeIDE

- `Additional Code/` - Python script for controlling robot and STM32CubeIDE project for HC-05 Bluetooth Module configuration
- `Task Diagrams/` - Task diagrams for each FSM shown on the main page

## How to Open the Project

To open this project in STM32CubeIDE:

### Option 1: Import via `.ioc` File

1. Open STM32CubeIDE
2. Go to **File → Open Projects from File System**
3. Click **Directory…** and select the `firmware/` folder
4. STM32CubeIDE will automatically detect and import the project
5. Click **Finish**

### Option 2: Open `.project` Directly

1. Double-click the `.project` file in the `firmware/` folder
2. STM32CubeIDE will open it as a recognized workspace project

---

## Notes

- The `.ioc` file defines all clock settings, pin mappings, and peripheral configurations
- Any changes made in `.ioc` can regenerate code in `Core/` and `Drivers/`
