#include "ble_info.h"
#include "config/hardware_config.h"

#if HAS_BLE
#include <BLEDevice.h>
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#endif

static void printSection(const char* title) {
    Serial.println("----------------------------------------");
    Serial.printf("[%s]\n", title);
}

void bleInfoInit(BleInfo& info) {
#if HAS_BLE
    esp_bt_controller_status_t ctrlStatus = esp_bt_controller_get_status();
    switch (ctrlStatus) {
        case ESP_BT_CONTROLLER_STATUS_IDLE:    info.controllerStatus = 0; break;
        case ESP_BT_CONTROLLER_STATUS_INITED:  info.controllerStatus = 1; break;
        case ESP_BT_CONTROLLER_STATUS_ENABLED: info.controllerStatus = 2; break;
        default:                               info.controllerStatus = 3; break;
    }

    if (BLEDevice::getInitialized()) {
        info.initialized = true;

        static String s_addr;
        s_addr = BLEDevice::getAddress().toString().c_str();
        info.address = s_addr.c_str();

        info.mtu = BLEDevice::getMTU();

        esp_power_level_t txPower = esp_ble_tx_power_get(ESP_BLE_PWR_TYPE_DEFAULT);
        info.txPower = txPower;

        int bondedNum = esp_ble_get_bond_device_num();
        info.bondedCount = (bondedNum >= 0) ? bondedNum : 0;

        uint16_t whitelistSize;
        if (esp_ble_gap_get_whitelist_size(&whitelistSize) == ESP_OK) {
            info.whitelistSize = whitelistSize;
        } else {
            info.whitelistSize = 0;
        }
    } else {
        info.initialized = false;
        info.address = "";
        info.mtu = 0;
        info.txPower = 0;
        info.bondedCount = 0;
        info.whitelistSize = 0;
    }
#else
    info.controllerStatus = 3;
    info.initialized = false;
    info.deviceName = "";
    info.address = "";
    info.mtu = 0;
    info.txPower = 0;
    info.bondedCount = 0;
    info.whitelistSize = 0;
#endif
}

void bleInfoPrint(const BleInfo& info) {
    printSection("蓝牙信息");
#if HAS_BLE
    const char* ctrlStatusStr;
    switch (info.controllerStatus) {
        case 0:  ctrlStatusStr = "空闲";     break;
        case 1:  ctrlStatusStr = "已初始化";  break;
        case 2:  ctrlStatusStr = "已启用";    break;
        default: ctrlStatusStr = "未知";      break;
    }
    Serial.printf("控制器状态:   %s\n", ctrlStatusStr);

    if (info.initialized) {
        Serial.printf("BLE 地址:     %s\n", info.address);
        Serial.printf("MTU:          %d\n", info.mtu);
        Serial.printf("TX 功率:      %d dBm\n", info.txPower);
        Serial.printf("已配对设备:   %d\n", info.bondedCount);
        Serial.printf("白名单大小:   %d\n", info.whitelistSize);

#ifdef CONFIG_BT_BLE_50_FEATURES_SUPPORTED
        Serial.printf("BLE 5.0:      支持\n");
        Serial.printf("PHY 模式:     1M 2M CODED\n");
#else
        Serial.printf("BLE 5.0:      不支持\n");
        Serial.printf("PHY 模式:     1M\n");
#endif
    } else {
        Serial.println("BLE 未初始化");
    }
#else
    Serial.println("蓝牙:         不支持");
#endif
}
