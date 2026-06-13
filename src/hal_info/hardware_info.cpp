#include "hardware_info.h"

static HardwareInfo s_hwInfo;

HardwareInfo& hwInfo() { return s_hwInfo; }

const char* HardwareInfo::getBoardName() { return _cpu.model; }
CpuInfo HardwareInfo::getCpuInfo() { return _cpu; }
FlashInfo HardwareInfo::getFlashInfo() { return _flash; }
PsramInfo HardwareInfo::getPsramInfo() { return _psram; }
HeapInfo HardwareInfo::getHeapInfo() { return _heap; }
WifiInfo HardwareInfo::getWifiInfo() { return _wifi; }
BleInfo HardwareInfo::getBleInfo() { return _ble; }
SystemInfo HardwareInfo::getSystemInfo() { return _sys; }

void HardwareInfo::init() {
    cpuInfoInit(_cpu);
    flashInfoInit(_flash);
    psramInfoInit(_psram);
    heapInfoInit(_heap);
    systemInfoInit(_sys);
    wifiInfoInit(_wifi);
    bleInfoInit(_ble);
}

void HardwareInfo::printAll() {
    Serial.println();
    Serial.println("========================================");
    Serial.printf("  %s 设备详细信息\n", _cpu.model);
    Serial.println("========================================");

    cpuInfoPrint(_cpu);
    flashInfoPrint(_flash);
    psramInfoPrint(_psram);
    heapInfoPrint(_heap);
    systemInfoPrint(_sys);
    wifiInfoPrint(_wifi);
    bleInfoPrint(_ble);

    Serial.println("========================================");
    Serial.println();
}
