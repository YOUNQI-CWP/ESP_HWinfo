#include "flash_info.h"

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void flashInfoInit(FlashInfo& info) {
    info.sizeBytes = ESP.getFlashChipSize();
    info.speedHz = ESP.getFlashChipSpeed();
    info.mode = ESP.getFlashChipMode();

    switch (info.mode) {
        case FM_QIO:       info.modeStr = "QIO (Quad I/O)";       break;
        case FM_QOUT:      info.modeStr = "QOUT (Quad Output)";   break;
        case FM_DIO:       info.modeStr = "DIO (Dual I/O)";       break;
        case FM_DOUT:      info.modeStr = "DOUT (Dual Output)";   break;
        case FM_FAST_READ: info.modeStr = "FAST_READ (Single)";    break;
        case FM_SLOW_READ: info.modeStr = "SLOW_READ (Single)";    break;
        default:           info.modeStr = "UNKNOWN";               break;
    }
}

void flashInfoPrint(const FlashInfo& info) {
    printSection("Flash 信息");
    Serial.printf("Flash 大小:   %d MB\n", info.sizeBytes / (1024 * 1024));
    Serial.printf("Flash 频率:   %d MHz\n", info.speedHz / 1000000);
    Serial.printf("可选频率:     40 MHz 80 MHz 120 MHz\n");
    Serial.printf("Flash 模式:   %s\n", info.modeStr);
    Serial.printf("可选模式:     QIO QOUT DIO DOUT FAST_READ SLOW_READ\n");
}
