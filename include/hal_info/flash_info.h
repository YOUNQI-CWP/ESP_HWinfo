#ifndef FLASH_INFO_H
#define FLASH_INFO_H

#include <Arduino.h>

struct FlashInfo {
    uint32_t sizeBytes;
    uint32_t speedHz;
    uint8_t mode;
    const char* modeStr;
};

void flashInfoInit(FlashInfo& info);
void flashInfoPrint(const FlashInfo& info);

#endif
