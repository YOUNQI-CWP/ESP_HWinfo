#include "cpu_info.h"
#include "config/hardware_config.h"

#if defined(ESP8266)
    // ESP8266 无 esp32-hal-cpu.h 和 soc/rtc.h
#else
    #include "esp32-hal-cpu.h"
    #include "soc/rtc.h"
#endif

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void cpuInfoInit(CpuInfo& info) {
#if defined(ESP8266)
    info.model = "ESP8266";
    info.revision = 0;
    info.cores = 1;
    info.freqMhz = ESP.getCpuFreqMHz();
    info.xtalMhz = 0;
    info.apbHz = 0;
    info.coreId = 0;
    info.efuseMac = ESP.getChipId();
    info.clockSource = "XTAL";
    info.clkSourceFreqMhz = ESP.getCpuFreqMHz();
    info.clkDiv = 1;
#else
    info.model = ESP.getChipModel();
    info.revision = ESP.getChipRevision();
    info.cores = ESP.getChipCores();
    info.freqMhz = ESP.getCpuFreqMHz();
    info.xtalMhz = getXtalFrequencyMhz();
    info.apbHz = getApbFrequency();
    info.coreId = xPortGetCoreID();
    info.efuseMac = ESP.getEfuseMac();

    rtc_cpu_freq_config_t clkConfig;
    rtc_clk_cpu_freq_get_config(&clkConfig);
    info.clkSourceFreqMhz = clkConfig.source_freq_mhz;
    info.clkDiv = clkConfig.div;

    switch (clkConfig.source) {
        case RTC_CPU_FREQ_SRC_XTAL:  info.clockSource = "XTAL";  break;
        case RTC_CPU_FREQ_SRC_PLL:   info.clockSource = "PLL";   break;
        case RTC_CPU_FREQ_SRC_8M:    info.clockSource = "RC 8M";  break;
        case RTC_CPU_FREQ_SRC_APLL:  info.clockSource = "APLL";  break;
        default:                     info.clockSource = "未知";   break;
    }
#endif
}

void cpuInfoPrint(const CpuInfo& info) {
    printSection("CPU 信息");
    Serial.printf("芯片型号:     %s\n", info.model);
    Serial.printf("芯片版本:     %d\n", info.revision);
    Serial.printf("CPU 核心数:   %d\n", info.cores);
    Serial.printf("CPU 频率:     %d MHz\n", info.freqMhz);
#if !defined(ESP8266)
    Serial.printf("XTAL 频率:    %d MHz\n", info.xtalMhz);
    Serial.printf("APB 频率:     %d Hz\n", info.apbHz);
    Serial.printf("时钟源:       %s (%d MHz / %d = %d MHz)\n",
        info.clockSource, info.clkSourceFreqMhz, info.clkDiv, info.freqMhz);
    Serial.printf("当前核心 ID: %d\n", info.coreId);
    Serial.printf("eFuse MAC:    %016llX\n", info.efuseMac);
#else
    Serial.printf("Chip ID:      %08X\n", (uint32_t)info.efuseMac);
#endif
}
