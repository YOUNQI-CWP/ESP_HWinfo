# ESP32/ESP8266 通用硬件信息检测

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![PlatformIO](https://img.shields.io/badge/PlatformIO-Library-orange)](https://platformio.org/)

ESP32/ESP8266 系列芯片通用硬件信息检测项目。自动识别芯片型号，显示全面的硬件详情。

## 功能特性

- **CPU 信息**: 芯片型号、版本、核心数、频率、时钟源、XTAL/APB 频率
- **Flash 信息**: 大小、速度、模式 (QIO/QOUT/DIO/DOUT)、可选配置
- **PSRAM 信息**: 大小、可用/已用内存、最低/最大水位线（仅支持的芯片）
- **堆内存信息**: 总量、可用、已用、最低水位线、最大可分配块
- **WiFi 信息**: 模式、MAC 地址、TX 功率、协议、国家码、连接状态
- **BLE 信息**: 控制器状态、BLE 地址、MTU、TX 功率、BLE 5.0 支持
- **固件信息**: SDK 版本、固件大小、OTA 剩余空间、MD5、编译时间戳

## 支持芯片

| 芯片 | WiFi | BLE | PSRAM | 状态 |
|------|------|-----|-------|------|
| ESP8266 | WiFi 4 | 无 | 无 | 支持 |
| ESP32 | WiFi 4 | BLE 4.2 | 可选 | 支持 |
| ESP32-S2 | WiFi 4 | 无 | 可选 | 支持 |
| ESP32-S3 | WiFi 4 | BLE 5.0 | 可选 | 支持 |
| ESP32-C3 | WiFi 4 | BLE 5.0 | 无 | 支持 |
| ESP32-C6 | WiFi 6 | BLE 5.0 | 无 | 需升级 SDK |
| ESP32-H2 | 无 | BLE 5.0 | 无 | 需升级 SDK |

## 软件要求

- [PlatformIO](https://platformio.org/) 搭配 `espressif32` 平台
- Arduino 框架
- ESP-IDF v4.4.x (PlatformIO 内置)

## 快速开始

### 1. 克隆仓库

```bash
git clone https://github.com/YOUNQI-CWP/ESP_HWinfo.git
cd ESP_HWinfo
```

### 2. 安装 PlatformIO

```bash
pip install platformio
```

### 3. 编译和上传

```bash
# ESP32 系列
pio run                                    # 编译默认目标 (ESP32-S3)
pio run -e esp32-s3-n16r8                 # ESP32-S3
pio run -e esp32                           # ESP32
pio run -e esp32-s2-devkitm-1             # ESP32-S2
pio run -e esp32-c3-devkitc-02            # ESP32-C3
pio run -e esp32-s3-n16r8 --target upload # 上传到设备

# ESP8266 系列（需要单独的配置文件）
pio run -c platformio_esp8266.ini                          # 编译默认目标 (NodeMCU V2)
pio run -c platformio_esp8266.ini -e nodemcuv2            # NodeMCU V2
pio run -c platformio_esp8266.ini -e esp01s               # ESP-01S
pio run -c platformio_esp8266.ini -e wemos_d1_mini        # WeMos D1 Mini
pio run -c platformio_esp8266.ini -e nodemcuv2 --target upload

# 监控串口输出
pio device monitor
```

### 4. 清理编译 (可选)

```bash
./platformiokill.sh
```

## 项目结构

```
ESP_HWinfo/
├── src/
│   ├── main.cpp                  # 入口点（条件编译外设初始化）
│   └── hal_info/
│       ├── hardware_info.cpp     # 主协调器（仅调度，无芯片逻辑）
│       ├── cpu_info.cpp          # CPU 信息（全芯片通用）
│       ├── flash_info.cpp        # Flash 信息（全芯片通用）
│       ├── psram_info.cpp        # PSRAM 信息（HAS_PSRAM 守护）
│       ├── heap_info.cpp         # 堆内存信息（全芯片通用）
│       ├── wifi_info.cpp         # WiFi 信息（HAS_WIFI 守护）
│       ├── ble_info.cpp          # BLE 信息（HAS_BLE 守护）
│       └── system_info.cpp       # 固件/系统信息（全芯片通用）
├── include/
│   ├── config/
│   │   ├── project_config.h      # 项目版本信息
│   │   └── hardware_config.h     # 芯片能力宏定义（核心）
│   └── hal_info/
│       ├── hardware_info.h       # 主头文件（类定义 + 模块 include）
│       ├── cpu_info.h            # 各模块头文件（结构体 + 函数声明）
│       ├── flash_info.h
│       ├── psram_info.h
│       ├── heap_info.h
│       ├── wifi_info.h
│       ├── ble_info.h
│       └── system_info.h
├── platformio.ini                # ESP32 多板配置
├── platformio_esp8266.ini        # ESP8266 配置
├── platformiokill.sh             # 编译清理脚本
├── LICENSE                       # MIT 许可证
├── CONTRIBUTING.md               # 贡献指南
└── README.md                     # 本文件
```

## 架构设计

### 芯片能力检测

项目通过 `hardware_config.h` 中的能力宏自动适配不同芯片：

```cpp
// ESP8266 系列
#if defined(ESP8266)
    #define HAS_WIFI    1
    #define HAS_BLE     0   // 无蓝牙硬件
    #define HAS_PSRAM   0   // 无 PSRAM
    #define HAS_VCC     1   // 支持读取供电电压

// ESP32 系列
#elif CONFIG_IDF_TARGET_ESP32 || ...
    #define HAS_WIFI    1
    #define HAS_BLE     1   // ESP32-S2 除外
    #define HAS_PSRAM   1   // 仅部分型号
    #define HAS_VCC     0
#endif
```

### 模块化设计

- **通用模块**: `cpu_info`、`flash_info`、`heap_info`、`system_info` — 全芯片通用，无需守护
- **条件模块**: `wifi_info`、`ble_info`、`psram_info` — 内部用 `#if HAS_xxx` 守护
- **主协调器**: `src/hal_info/hardware_info.cpp` — 仅调度，不含任何芯片判断逻辑
- **头文件安全**: 结构体字段始终存在，未实现的芯片填入默认值

### 添加新芯片

1. 在 `hardware_config.h` 的能力宏定义处添加新芯片的 `#elif`
2. 验证该芯片的 ESP-IDF API 兼容性
3. 编译测试

## 输出示例

```
========================================
  ESP32-S3 设备详细信息
========================================
----------------------------------------
[CPU 信息]
芯片型号:     ESP32-S3
芯片版本:     0
CPU 核心数:   2
CPU 频率:     240 MHz
XTAL 频率:    40 MHz
APB 频率:     80000000 Hz
时钟源:       PLL (480 MHz / 2 = 240 MHz)
当前核心 ID:  1
eFuse MAC:    00000C4E0F90A994
----------------------------------------
[Flash 信息]
Flash 大小:   16 MB
Flash 频率:   80 MHz
可选频率:     40 MHz 80 MHz 120 MHz
Flash 模式:   QIO (Quad I/O)
可选模式:     QIO QOUT DIO DOUT FAST_READ SLOW_READ
...
```

## 贡献指南

欢迎贡献！请阅读 [CONTRIBUTING.md](CONTRIBUTING.md) 了解提交 Pull Request 的流程。

## 许可证

本项目基于 MIT 许可证 - 详见 [LICENSE](LICENSE) 文件。

## 致谢

- [乐鑫科技](https://www.espressif.com/) 提供 ESP32 系列芯片和 ESP-IDF
- [PlatformIO](https://platformio.org/) 提供开发框架
- [Arduino](https://www.arduino.cc/) 提供 Arduino 框架
