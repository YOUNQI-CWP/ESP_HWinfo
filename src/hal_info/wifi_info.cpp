#include "wifi_info.h"
#include "config/hardware_config.h"

#if HAS_WIFI
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_netif.h"
#endif
#endif

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void wifiInfoInit(WifiInfo& info) {
#if HAS_WIFI
    static String s_mac, s_ssid, s_bssid, s_apMac, s_apIP, s_apSsid;

    info.mode = WiFi.getMode();

    s_mac = WiFi.macAddress();
    info.mac = s_mac.c_str();

    info.hostname = WiFi.getHostname();

    if (info.mode != WIFI_MODE_NULL) {
#if defined(ESP8266)
        info.txPower = 0;
        info.channel = WiFi.channel();
        info.secondChan = 0;
        info.protocol = 0;
        memset(info.countryCode, 0, 4);
        info.inactiveTime = 0;
#else
        info.txPower = WiFi.getTxPower();

        uint8_t primary;
        wifi_second_chan_t second;
        if (esp_wifi_get_channel(&primary, &second) == ESP_OK) {
            info.channel = primary;
            info.secondChan = second;
        } else {
            info.channel = 0;
            info.secondChan = WIFI_SECOND_CHAN_NONE;
        }

        uint8_t protocol;
        if (esp_wifi_get_protocol(WIFI_IF_STA, &protocol) == ESP_OK) {
            info.protocol = protocol;
        } else {
            info.protocol = 0;
        }

        char countryCode[4] = {0};
        if (esp_wifi_get_country_code(countryCode) == ESP_OK) {
            memcpy(info.countryCode, countryCode, 4);
        } else {
            memset(info.countryCode, 0, 4);
        }

        uint16_t inactiveTime;
        if (esp_wifi_get_inactive_time(WIFI_IF_STA, &inactiveTime) == ESP_OK) {
            info.inactiveTime = inactiveTime;
        } else {
            info.inactiveTime = 0;
        }
#endif

        if (WiFi.status() == WL_CONNECTED) {
            info.connected = true;

            s_ssid = WiFi.SSID();
            info.ssid = s_ssid.c_str();

            s_bssid = WiFi.BSSIDstr();
            info.bssid = s_bssid.c_str();

            info.rssi = WiFi.RSSI();
            info.authMode = "UNKNOWN";
            info.apChannel = 0;
            info.apRssi = 0;
#if !defined(ESP8266)
            wifi_ap_record_t ap_info;
            if (esp_wifi_sta_get_ap_info(&ap_info) == ESP_OK) {
                switch (ap_info.authmode) {
                    case WIFI_AUTH_OPEN:            info.authMode = "OPEN";         break;
                    case WIFI_AUTH_WEP:             info.authMode = "WEP";          break;
                    case WIFI_AUTH_WPA_PSK:         info.authMode = "WPA_PSK";      break;
                    case WIFI_AUTH_WPA2_PSK:        info.authMode = "WPA2_PSK";     break;
                    case WIFI_AUTH_WPA_WPA2_PSK:    info.authMode = "WPA_WPA2_PSK"; break;
                    case WIFI_AUTH_WPA3_PSK:        info.authMode = "WPA3_PSK";     break;
                    default:                        info.authMode = "UNKNOWN";       break;
                }
                info.apChannel = ap_info.primary;
                info.apRssi = ap_info.rssi;
            }
#endif
        } else {
            info.connected = false;
            info.ssid = "";
            info.bssid = "";
            info.rssi = 0;
            info.authMode = "UNKNOWN";
            info.apChannel = 0;
            info.apRssi = 0;
        }
    } else {
        info.txPower = 0;
        info.channel = 0;
        info.secondChan = 0;
        info.protocol = 0;
        memset(info.countryCode, 0, 4);
        info.inactiveTime = 0;
        info.connected = false;
        info.ssid = "";
        info.bssid = "";
        info.rssi = 0;
        info.authMode = "UNKNOWN";
        info.apChannel = 0;
        info.apRssi = 0;
    }

    if (info.mode == WIFI_MODE_AP || info.mode == WIFI_MODE_APSTA) {
        s_apMac = WiFi.softAPmacAddress();
        info.apMac = s_apMac.c_str();

        s_apIP = WiFi.softAPIP().toString();
        info.apIP = s_apIP.c_str();

        s_apSsid = WiFi.softAPSSID();
        info.apSsid = s_apSsid.c_str();

        info.apClients = WiFi.softAPgetStationNum();
    } else {
        info.apMac = "";
        info.apIP = "";
        info.apSsid = "";
        info.apClients = 0;
    }
#else
    memset(&info, 0, sizeof(info));
#endif
}

void wifiInfoPrint(const WifiInfo& info) {
    printSection("WiFi 信息");
#if HAS_WIFI
    const char* modeStr;
    switch (info.mode) {
        case WIFI_MODE_NULL:  modeStr = "OFF";      break;
        case WIFI_MODE_STA:   modeStr = "STA";      break;
        case WIFI_MODE_AP:    modeStr = "AP";       break;
        case WIFI_MODE_APSTA: modeStr = "STA+AP";   break;
        default:              modeStr = "UNKNOWN";   break;
    }
    Serial.printf("WiFi 模式:    %s\n", modeStr);
    Serial.printf("WiFi MAC:     %s\n", info.mac);
    Serial.printf("主机名:       %s\n", info.hostname);

    if (info.mode != WIFI_MODE_NULL) {
#if !defined(ESP8266)
        Serial.printf("TX 功率:      %d dBm\n", info.txPower);
        Serial.printf("可选带宽:     HT20 HT40\n");

        const char* secStr;
        switch (info.secondChan) {
            case WIFI_SECOND_CHAN_NONE:  secStr = "无";     break;
            case WIFI_SECOND_CHAN_ABOVE: secStr = " above"; break;
            case WIFI_SECOND_CHAN_BELOW: secStr = " below"; break;
            default:                     secStr = "未知";   break;
        }
        Serial.printf("主信道:       %d (副信道: %s)\n", info.channel, secStr);

        Serial.printf("协议:         %s%s%s\n",
            (info.protocol & WIFI_PROTOCOL_11B) ? "11b " : "",
            (info.protocol & WIFI_PROTOCOL_11G) ? "11g " : "",
            (info.protocol & WIFI_PROTOCOL_11N) ? "11n " : "");

        Serial.printf("国家码:       %s\n", info.countryCode);
        Serial.printf("不活跃超时:   %d 秒\n", info.inactiveTime);
#else
        Serial.printf("信道:         %d\n", info.channel);
#endif

        if (info.connected) {
            Serial.printf("连接状态:    已连接\n");
            Serial.printf("SSID:        %s\n", info.ssid);
            Serial.printf("BSSID:       %s\n", info.bssid);
            Serial.printf("信号强度:    %d dBm\n", info.rssi);
            Serial.printf("加密类型:    %s\n", info.authMode);
            Serial.printf("AP 信道:     %d\n", info.apChannel);
            Serial.printf("AP RSSI:     %d dBm\n", info.apRssi);
        } else {
            Serial.printf("连接状态:    未连接\n");
        }
    }

    if (info.mode == WIFI_MODE_AP || info.mode == WIFI_MODE_APSTA) {
        Serial.printf("AP MAC:       %s\n", info.apMac);
        Serial.printf("AP IP:        %s\n", info.apIP);
        Serial.printf("AP SSID:      %s\n", info.apSsid);
        Serial.printf("已连接客户端: %d\n", info.apClients);
    }
#else
    Serial.println("WiFi:         不支持");
#endif
}
