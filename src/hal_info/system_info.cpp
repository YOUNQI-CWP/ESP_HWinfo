#include "system_info.h"
#include "config/project_config.h"
#include "config/hardware_config.h"

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void systemInfoInit(SystemInfo& info) {
    static String s_md5;

    info.sdkVersion = ESP.getSdkVersion();
    info.buildDate = BUILD_DATE;
    info.buildTime = BUILD_TIME;
    info.sketchSize = ESP.getSketchSize();
    info.freeSketchSpace = ESP.getFreeSketchSpace();

    s_md5 = ESP.getSketchMD5();
    info.sketchMd5 = s_md5.c_str();
}

void systemInfoPrint(const SystemInfo& info) {
    printSection("固件信息");
    Serial.printf("项目名称:     %s\n", PROJECT_NAME);
    Serial.printf("项目版本:     %s\n", PROJECT_VERSION);
    Serial.printf("固件大小:     %d KB\n", info.sketchSize / 1024);
    Serial.printf("OTA 剩余:     %d KB\n", info.freeSketchSpace / 1024);
    Serial.printf("固件 MD5:     %s\n", info.sketchMd5);
    Serial.printf("SDK 版本:     %s\n", info.sdkVersion);
    Serial.printf("编译时间:     %s %s\n", info.buildDate, info.buildTime);
#if HAS_VCC
    Serial.printf("供电电压:     %d mV\n", ESP.getVcc());
#endif
}
