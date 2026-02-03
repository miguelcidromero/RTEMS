# ABSURD Benchmarks Suite on RTEMS 7 (STM32F4 Discovery)

This repository contains the full integration of the **ABSURD Benchmark Suite** running on the **RTEMS 7** real-time operating system for the **STM32F4 Discovery** board.

> **⚠️ Note:** This project runs without a Serial Console. Visual feedback is provided entirely through the board's **LEDs**.

---

## 🚀 Quick Start (Build & Run)

Follow these commands to build the binary from source.

### 1. Build the Executable
Assuming you have the RTEMS 7 toolchain installed and `waf` configured:

```bash
# 1. Clean and configure the build environment
./waf clean
./waf configure

# 2. Compile the project
./waf
```
### 3. Generate the Binary
```bash
arm-rtems7-objcopy -O binary build/arm/stm32f4/testsuites/benchmarks/absurd.exe absurd.bin
```

### 4. Flash to Hardware
Connect your STM32F4 Discovery board via USB.
Locate the mass storage drive (e.g., DIS_F4) on your computer.
Drag and drop the absurd.bin file into that drive.
The board will flash and reboot automatically.
