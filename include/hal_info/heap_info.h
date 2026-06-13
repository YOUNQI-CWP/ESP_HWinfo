#ifndef HEAP_INFO_H
#define HEAP_INFO_H

#include <Arduino.h>

struct HeapInfo {
    uint32_t totalBytes;
    uint32_t freeBytes;
    uint32_t minFreeBytes;
    uint32_t maxAllocBytes;
};

void heapInfoInit(HeapInfo& info);
void heapInfoPrint(const HeapInfo& info);

#endif
