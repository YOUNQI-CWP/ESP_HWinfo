#ifndef CPU_INFO_H
#define CPU_INFO_H

#include <Arduino.h>

struct CpuInfo {
    const char* model;
    uint8_t revision;
    uint8_t cores;
    uint32_t freqMhz;
    uint32_t xtalMhz;
    uint32_t apbHz;
    uint8_t coreId;
    uint64_t efuseMac;
    const char* clockSource;
    uint32_t clkSourceFreqMhz;
    uint32_t clkDiv;
};

void cpuInfoInit(CpuInfo& info);
void cpuInfoPrint(const CpuInfo& info);

#endif
