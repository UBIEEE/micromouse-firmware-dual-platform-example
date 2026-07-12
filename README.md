# Example Dual-Platform MicroMouse Firmware Project

## Overview

This is an example MicroMouse software project that can be built for both an STM32F405RGT6 target and a desktop target (for simulation).

This project is structured like so:

- `firmware/include` and `firmware/lib` contain the main 'logic' code for the MicroMouse. This is where all maze solving algorithms and other logic should be implemented. This code is platform agnostic and can be built for both targets. To control hardware, this code will declare function prototypes for hardware control functions (e.g. `MotorsSetPercentOutputs()`) which will be implemented in the platform-specific code.
    - `firmware/tests` contains unit tests for this logic code which can be run on the desktop target.
- `firmware/platform/desktop` contains the platform-specific code for the desktop target. Implement this how you like. You may want to interface with a simulator or just print out diagnostic information to the console to verify that your logic code is working correctly without needing to run on the actual hardware.
- `firmware/platform/robot` contains the platform-specific code for the STM32F405RGT6 target. This is where you implement the hardware control functions declared in the logic code. Most of the STM32 code can be auto-generated using [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) from the project located at `firmware/platform/robot/micromouse.ioc`.

## Building

Only Linux and macOS are supported for building this project. If you are using Windows please use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install).

### Prerequisites

Linux (Ubuntu):
```bash
sudo apt install build-essential cmake gcc-arm-none-eabi
```

macOS:
```bash
brew install cmake
```
```bash
brew install --cask gcc-arm-embedded
```

### Configure

Navigate to the `firmware` directory and use CMake to configure the project for either the desktop or robot target like so:

Robot:
```bash
cmake -S . -B build_robot -DBUILD_FOR_HARDWARE=ON
```

Desktop:
```bash
cmake -S . -B build_desktop -DBUILD_FOR_DESKTOP=ON -DBUILD_TESTS=ON
```

Now build the project:

Robot:
```bash
cmake --build build_robot
```

Desktop:
```bash
cmake --build build_desktop
```

The resulting executable will be located at `build_robot/micromouse-firmware.elf` for the robot target and `build_desktop/micromouse-firmware` for the desktop target.

For desktop, the unit test executable can be found at `build_desktop/tests/micromouse-firmware-tests`

## Flashing the Robot and Debugging

### Prerequisites

Install [OpenOCD](https://github.com/openocd-org/openocd):

Linux (Ubuntu):
```bash
sudo apt install openocd
```

macOS:
```bash
brew install open-ocd
```

### Flashing

Connect the ST-Link programmer to the robot and your computer. Then, start OpenOCD:

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

In another terminal, start GDB:

```bash
arm-none-eabi-gdb ./build_robot/micromouse-firmware.elf
```

```
(gdb) target remote localhost:3333
(gdb) load
(gdb) continue
```

And off you go!
