#include "heap_info.h"

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void heapInfoInit(HeapInfo& info) {
    info.totalBytes = ESP.getHeapSize();
    info.freeBytes = ESP.getFreeHeap();
    info.minFreeBytes = ESP.getMinFreeHeap();
    info.maxAllocBytes = ESP.getMaxAllocHeap();
}

void heapInfoPrint(const HeapInfo& info) {
    printSection("堆内存信息");
    uint32_t totalKB = info.totalBytes / 1024;
    uint32_t freeKB = info.freeBytes / 1024;
    Serial.printf("堆内存总量:   %d KB\n", totalKB);
    Serial.printf("堆内存可用:   %d KB\n", freeKB);
    Serial.printf("堆内存使用:   %d KB\n", totalKB - freeKB);
    Serial.printf("堆内存最低:   %d KB (历史最低水位)\n", info.minFreeBytes / 1024);
    Serial.printf("堆内存最大块: %d KB\n", info.maxAllocBytes / 1024);
}
