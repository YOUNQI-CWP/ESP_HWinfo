#include "psram_info.h"
#include "config/hardware_config.h"

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void psramInfoInit(PsramInfo& info) {
#if HAS_PSRAM
    info.found = psramFound();
    if (info.found) {
        info.totalBytes = ESP.getPsramSize();
        info.freeBytes = ESP.getFreePsram();
        info.minFreeBytes = ESP.getMinFreePsram();
        info.maxAllocBytes = ESP.getMaxAllocPsram();
    } else {
        info.totalBytes = 0;
        info.freeBytes = 0;
        info.minFreeBytes = 0;
        info.maxAllocBytes = 0;
    }
#else
    info.found = false;
    info.totalBytes = 0;
    info.freeBytes = 0;
    info.minFreeBytes = 0;
    info.maxAllocBytes = 0;
#endif
}

void psramInfoPrint(const PsramInfo& info) {
    printSection("PSRAM 信息");
#if HAS_PSRAM
    if (info.found) {
        uint32_t totalKB = info.totalBytes / 1024;
        uint32_t freeKB = info.freeBytes / 1024;
        Serial.printf("PSRAM 大小:   %d KB (%d MB)\n", totalKB, info.totalBytes / (1024 * 1024));
        Serial.printf("PSRAM 可用:   %d KB\n", freeKB);
        Serial.printf("PSRAM 使用:   %d KB\n", totalKB - freeKB);
        Serial.printf("PSRAM 最低:   %d KB (历史最低水位)\n", info.minFreeBytes / 1024);
        Serial.printf("PSRAM 最大块: %d KB\n", info.maxAllocBytes / 1024);
        Serial.printf("PSRAM 接口:   QSPI / OPI\n");
    } else {
        Serial.println("PSRAM:        未检测到");
    }
#else
    Serial.println("PSRAM:        不支持");
#endif
}
