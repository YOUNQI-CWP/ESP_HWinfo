#ifndef BLE_INFO_H
#define BLE_INFO_H

#include <Arduino.h>

struct BleInfo {
    uint8_t controllerStatus;
    bool initialized;
    const char* address;
    uint16_t mtu;
    int8_t txPower;
    int bondedCount;
    uint16_t whitelistSize;
};

void bleInfoInit(BleInfo& info);
void bleInfoPrint(const BleInfo& info);

#endif
