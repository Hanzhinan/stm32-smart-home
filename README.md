# STM32 智能家居控制系统

基于 STM32F103C8T6 的智能家居控制系统，使用 FreeRTOS 实现多任务管理，支持语音控制、环境监测、自动控制等功能。

## 📋 项目概述

本项目是一个基于 STM32F103C8T6 的智能家居控制系统，具备以下功能：

- **环境监测**：实时采集温湿度（DHT11）和光照强度（光敏传感器）
- **语音控制**：通过串口接收语音命令，控制灯光和电机
- **自动控制**：根据环境条件自动开关灯光和电机
- **OLED 显示**：实时显示传感器数据和设备状态
- **电机调速**：支持 PWM 调速，四档转速控制

## 🔧 硬件配置

### 主控芯片
| 项目 | 规格 |
|------|------|
| MCU | STM32F103C8T6 |
| 主频 | 72MHz |
| 内存 | 64KB Flash / 20KB RAM |

### 外设连接

| 外设 | 接口 | 引脚 |
|------|------|------|
| **DHT11** | GPIO | PA1 |
| **OLED** | I2C | PB6(SCL), PB7(SDA) |
| **LED** | GPIO | PA0 |
| **电机** | PWM(TIM3_CH3) | PB0 |
| **光敏传感器** | ADC | PA2 |
| **语音串口** | USART1 | PA9(TX), PA10(RX) |
| **日志串口** | USART3 | PB10(TX), PB11(RX) |

### 电路示意图

```
STM32F103C8T6
├── PA0  ──────── LED指示灯
├── PA1  ──────── DHT11数据引脚
├── PA2  ──────── 光敏传感器(ADC)
├── PA9  ──────── USART1_TX(语音命令输出)
├── PA10 ──────── USART1_RX(语音命令输入)
├── PB0  ──────── TIM3_CH3(电机PWM)
├── PB6  ──────── I2C1_SCL(OLED)
├── PB7  ──────── I2C1_SDA(OLED)
├── PB10 ──────── USART3_TX(日志输出)
└── PB11 ──────── USART3_RX(日志输入)
```

## 📁 项目结构

```
My_Project/
├── Core/                          # STM32 核心代码
│   ├── Inc/                       # 头文件
│   │   ├── FreeRTOSConfig.h       # FreeRTOS 配置
│   │   ├── main.h                 # 主头文件
│   │   ├── gpio.h                 # GPIO 配置
│   │   ├── tim.h                  # 定时器配置
│   │   └── usart.h                # 串口配置
│   └── Src/                       # 源文件
│       ├── main.c                 # 主函数
│       ├── freertos.c             # FreeRTOS 任务配置
│       ├── gpio.c                 # GPIO 驱动
│       ├── tim.c                  # 定时器驱动(PWM)
│       ├── usart.c                # 串口驱动
│       └── stm32f1xx_it.c         # 中断服务函数
├── DHT11/                         # DHT11 驱动
│   ├── bsp_dht11.c                # DHT11 底层驱动
│   ├── bsp_dht11.h                # DHT11 头文件
│   └── sensor_data.h              # 传感器数据结构定义
├── Hardware/                      # 外设驱动
│   ├── OLED.c                     # OLED 驱动
│   ├── OLED.h                     # OLED 头文件
│   ├── OLED_Data.c                # OLED 字库数据
│   └── OLED_Data.h                # OLED 字库头文件
├── Middlewares/                   # 中间件
│   └── Third_Party/FreeRTOS/      # FreeRTOS 源码
├── Drivers/                       # STM32 HAL 库
│   ├── CMSIS/                     # CMSIS 核心
│   └── STM32F1xx_HAL_Driver/      # STM32 HAL 驱动
├── MDK-ARM/                       # Keil 工程文件
│   ├── My_Project.uvprojx         # Keil 工程文件
│   └── My_Project.uvoptx          # Keil 配置文件
├── My_Project.ioc                 # STM32CubeMX 配置文件
└── .gitignore                     # Git 忽略规则
```

## ⚙️ 软件架构

### 任务列表（FreeRTOS）

| 任务名称 | 优先级 | 栈大小 | 功能描述 |
|----------|--------|--------|----------|
| **VoiceTask** | 最高 | 2048 | 语音命令接收与解析 |
| **SensorCollectTa** | 中高 | 1536 | 传感器数据采集 |
| **AutoLogicTask** | 中 | 1024 | 自动控制逻辑 |
| **DeviceCtrlTask** | 中低 | 1024 | 设备控制执行 |
| **OledDisplayTask** | 最低 | 2048 | OLED 显示刷新 |

### 数据结构

```c
// 传感器数据
typedef struct {
    uint8_t temp;           // 温度 (℃)
    uint8_t humi;           // 湿度 (%)
    uint8_t light_status;   // 光照状态 (0=亮, 1=暗)
    uint8_t dht11_valid;    // DHT11 数据有效标志
} SensorData_t;

// 控制状态
typedef struct {
    uint8_t motor_level;    // 电机档位 (0-3)
    uint8_t motor_running;  // 电机运行状态
    uint8_t led_on;         // LED 状态
    uint8_t voice_cmd;      // 最新语音命令
} ControlState_t;

// 显示缓冲区
typedef struct {
    char line1[32];         // OLED 第1行
    char line2[32];         // OLED 第2行
    char line3[32];         // OLED 第3行
    char line4[32];         // OLED 第4行
} DisplayBuf_t;
```

### 语音命令协议

通过 USART1（波特率 9600）接收语音命令，命令格式为单字节：

| 命令码 | 功能 |
|--------|------|
| `0x01` | 开灯 |
| `0x02` | 关灯 |
| `0x03` | 电机开（低速） |
| `0x04` | 机关关 |
| `0x05` | 电机加速 |
| `0x06` | 电机减速 |
| `0x10` | 查询温湿度 |
| `0x20` | 自动模式开启 |
| `0x21` | 自动模式关闭 |

### 自动控制逻辑

- **灯光自动控制**：当光照强度低于阈值（环境变暗）时自动开灯
- **电机自动控制**：当温度高于阈值（30℃）时自动开启电机散热

## 🛠️ 编译与运行

### 开发环境

| 工具 | 版本 |
|------|------|
| Keil MDK | v5.28+ |
| STM32CubeMX | v6.0+ |
| ARM Compiler | v5.06 update 5 |

### 编译步骤

1. **打开工程**：使用 Keil MDK 打开 `MDK-ARM/My_Project.uvprojx`
2. **配置路径**：确保 `Output` 和 `Listing` 路径不含中文
3. **编译**：点击 `Build` 或 `Rebuild` 按钮
4. **下载**：连接 ST-Link，点击 `Load` 下载到开发板

### 串口配置

| 串口 | 波特率 | 数据位 | 停止位 | 校验位 |
|------|--------|--------|--------|--------|
| USART1（语音） | 9600 | 8 | 1 | 无 |
| USART3（日志） | 9600 | 8 | 1 | 无 |

## 📊 功能演示

### OLED 显示界面

```
┌─────────────────────────┐
│ Temp: 25C  Humi: 60%    │  第1行：温湿度
│ Light: Normal           │  第2行：光照状态
│ Motor: Level 1          │  第3行：电机状态
│ LED: ON  Mode: Manual   │  第4行：LED状态与模式
└─────────────────────────┘
```

### 日志输出（USART3）

```
[INFO] System started
[INFO] Voice cmd: Light ON
[INFO] Sensor: Temp=25C, Humi=60%
[INFO] Auto: Light ON (dark detected)
[INFO] Auto: Motor ON (temp > 30C)
```

## 📝 注意事项

1. **编译环境**：Windows 用户名为中文时可能导致编译失败，需修改系统临时目录
2. **电源供应**：电机驱动需要外部电源，建议使用 12V 电源
3. **串口接线**：USART1 用于语音命令，USART3 用于调试日志
4. **DHT11**：通信引脚需上拉电阻（4.7KΩ）

## 📄 许可证

本项目基于 STM32 HAL 库和 FreeRTOS，遵循各自的开源协议。

## 👤 作者

Hanzhinan

---

*如有问题或建议，欢迎提交 Issue 或 PR！*
