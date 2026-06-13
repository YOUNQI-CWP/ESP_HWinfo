#ifndef HARDWARE_INFO_H
#define HARDWARE_INFO_H

#include <Arduino.h>
#include "cpu_info.h"
#include "flash_info.h"
#include "psram_info.h"
#include "heap_info.h"
#include "wifi_info.h"
#include "ble_info.h"
#include "system_info.h"

class HardwareInfo {
public:
    void init();
    void printAll();

    const char* getBoardName();
    CpuInfo getCpuInfo();
    FlashInfo getFlashInfo();
    PsramInfo getPsramInfo();
    HeapInfo getHeapInfo();
    WifiInfo getWifiInfo();
    BleInfo getBleInfo();
    SystemInfo getSystemInfo();

private:
    CpuInfo _cpu;
    FlashInfo _flash;
    PsramInfo _psram;
    HeapInfo _heap;
    WifiInfo _wifi;
    BleInfo _ble;
    SystemInfo _sys;
};

HardwareInfo& hwInfo();

#endif
