#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#include <Arduino.h>

struct SystemInfo {
    const char* sdkVersion;
    const char* buildDate;
    const char* buildTime;
    uint32_t sketchSize;
    uint32_t freeSketchSpace;
    const char* sketchMd5;
};

void systemInfoInit(SystemInfo& info);
void systemInfoPrint(const SystemInfo& info);

#endif
