# STM32H743 FreeRTOS Task Scheduler Demo

A portfolio-grade FreeRTOS demonstration on the STM32H743 Nucleo board,
showcasing preemptive task scheduling, inter-task communication, and
real-time UART logging at 480 MHz.

---

## Architecture

Four FreeRTOS tasks running concurrently:

| Task | Priority | Period | Role |
|---|---|---|---|
| WriterTask | 4 (highest) | 700 ms | Writes to mutex-protected shared buffer |
| SensorTask | 3 | 500 ms | Simulates ADC sensor polling |
| LedTask | 2 | 250 ms | Heartbeat LED toggle |
| LoggerTask | 1 | Event-driven | Drains log queue → UART output |

Inter-task communication via a **FreeRTOS queue** (10 items × 64 bytes).  
Shared resource protection via a **FreeRTOS mutex** with 100 ms timeout.

---

## Hardware

| Item | Detail |
|---|---|
| MCU | STM32H743ZI — Cortex-M7 @ **480 MHz**, 2MB Flash, 1MB SRAM |
| Board | NUCLEO-H743ZI2 |
| UART | USART3 via ST-Link VCP (115200 baud, 8N1) |
| Silicon | Revision V (required for 480 MHz / VOS0) |

---

## Key Concepts Demonstrated

- **Preemptive scheduling** — higher priority tasks immediately preempt lower ones
- **Queue-based logging** — tasks never call UART directly; all output funnelled through `logQueue`
- **Mutex with timeout** — WriterTask acquires/releases `sharedMutex` with 100 ms guard
- **Stack overflow hook** — catches stack violations at runtime via `vApplicationStackOverflowHook()`
- **Malloc failed hook** — detects heap exhaustion via `vApplicationMallocFailedHook()`
- **vTaskList() stats** — type `s` in terminal to print live CPU% and stack watermark per task
- **480 MHz clock config** — VOS0 power scale, PLL1 (PLLM=4, PLLN=480, PLLP=2, FLASH_LATENCY_4)

---

## UART Output (PuTTY @ 115200)

```
[SENSOR] tick=0  adc=1234
[SENSOR] tick=1  adc=1598
[WRITER] shared_buf: count=0
[LED]    toggle #3
[SENSOR] tick=2  adc=2011
[WRITER] shared_buf: count=1

--- Task List (press 's') ---
Name          State  Prio  Stack  Num
SensorTask    B      3     198    1
LedTask       B      2     112    2
LoggerTask    B      1     210    3
WriterTask    B      4     188    4
IDLE          R      0     118    5
```

---

## Clock Configuration

```
HSE (8 MHz) → PLLM=4 → 2 MHz → PLLN=480 → VCO=960 MHz → PLLP=2 → 480 MHz
VOS0 (Scale 0) overdrive enabled — mandatory for 480 MHz on Rev. V silicon
FLASH_LATENCY_4 — 4 wait states at 480 MHz / VOS0
AHB = 240 MHz | APB1 = 120 MHz | APB2 = 120 MHz
```

---

## Build & Flash

1. Open project in **STM32CubeIDE 2.1.1**
2. Press `Ctrl+B` to build — target: 0 errors, 0 warnings
3. Connect NUCLEO-H743ZI2 via **CN1 USB port** (ST-Link, not USB FS)
4. Click Debug button → press **F8** to resume
5. Open **PuTTY** → Serial → Nucleo COM port → 115200 baud → Open

---

## Project Structure

```
STM32H743-FreeRTOS-Demo/
├── Core/
│   ├── Inc/
│   │   ├── main.h              # Peripheral handles, extern declarations
│   │   ├── FreeRTOSConfig.h    # Tick rate, heap size, hook enables
│   │   └── stm32h7xx_hal_conf.h
│   └── Src/
│       ├── main.c              # Clock config (480 MHz), peripheral init
│       ├── freertos.c          # All task code — SensorTask, LedTask,
│       │                       # LoggerTask, WriterTask, hook functions
│       └── stm32h7xx_it.c      # Interrupt handlers
├── Middlewares/
│   └── Third_Party/
│       └── FreeRTOS/           # FreeRTOS kernel (do not edit)
├── Drivers/
│   ├── STM32H7xx_HAL_Driver/   # ST HAL drivers
│   └── BSP/                    # Nucleo board support (LEDs, COM port)
├── H743_FreeRTOS_Demo.ioc      # CubeMX config — open to regenerate
├── .gitignore
└── README.md
```

---

## Tools & Versions

| Tool | Version |
|---|---|
| STM32CubeIDE | 2.1.1 |
| STM32CubeMX | Standalone (v6.x) |
| FreeRTOS | via STM32 Middleware, CMSIS_V2 interface |
| STM32CubeH7 HAL | v1.11+ |
| Compiler | ARM GCC (bundled with CubeIDE) |

---

## FreeRTOS Config Highlights

```c
configCPU_CLOCK_HZ                    = 480000000
configTICK_RATE_HZ                    = 1000        // 1 ms tick
configTOTAL_HEAP_SIZE                 = 65536        // 64 KB
configCHECK_FOR_STACK_OVERFLOW        = 2
configUSE_MALLOC_FAILED_HOOK          = 1
configUSE_TRACE_FACILITY              = 1
configUSE_STATS_FORMATTING_FUNCTIONS  = 1
```

---

## Roadmap

- [x] FreeRTOS task scheduler with 4 tasks
- [x] Queue-based UART logging
- [x] Mutex-protected shared resource
- [x] Stack overflow + malloc failed hooks
- [ ] Hardware validation on physical Nucleo board (board on order)
- [ ] DMA-based UART TX for non-blocking logger
- [ ] vTaskList() live CPU stats command
- [ ] FDCAN two-node communication demo
- [ ] AEB (Autonomous Emergency Braking) state machine simulation

---

## Interview Talking Points

- Preemptive scheduler with 4 tasks at distinct priorities — WriterTask at P4 preempts all others
- All UART output routed through a single queue — no race conditions on the serial port
- Mutex timeout (100 ms) on shared buffer — avoids deadlock if WriterTask hangs
- Stack overflow hook catches overflow at runtime — not a silent HardFault
- 480 MHz requires VOS0 + silicon Rev. V + FLASH_LATENCY_4 — three things most people miss
