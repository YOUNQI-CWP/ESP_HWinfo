#ifndef PSRAM_INFO_H
#define PSRAM_INFO_H

#include <Arduino.h>

struct PsramInfo {
    bool found;
    uint32_t totalBytes;
    uint32_t freeBytes;
    uint32_t minFreeBytes;
    uint32_t maxAllocBytes;
};

void psramInfoInit(PsramInfo& info);
void psramInfoPrint(const PsramInfo& info);

#endif
