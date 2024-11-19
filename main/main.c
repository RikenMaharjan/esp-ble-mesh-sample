/* main.c - Application main entry point */

/*
 * SPDX-FileCopyrightText: 2017 Intel Corporation
 * SPDX-FileContributor: 2018-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "esp_log.h"
#include "nvs_flash.h"

#include "ble_mesh_example_init.h"
#include "BLE_mesh_initializer.h"
#include "BLE_mesh_led_model.h"
#include "BLE_mesh_bme280_vendor_model.h"

#define TAG "main"
static uint8_t dev_uuid[2] = {0xdd, 0xdd};
void app_main(void)
{
    esp_err_t err;

    ESP_LOGI(TAG, "Initializing...");

    BLE_mesh_led_model_initialize_device();
    ble_mesh_led_model_register_callbacks();

#if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)
    BLE_mesh_bme280_vendor_model_initialize_device();
    BLE_mesh_bme280_vendor_model_register_callback();
#endif // if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)

    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);

    err = bluetooth_init();
    if (err)
    {
        ESP_LOGE(TAG, "esp32_bluetooth_init failed (err %d)", err);
        return;
    }

    ble_mesh_get_dev_uuid(dev_uuid);
    /* Initialize the Bluetooth Mesh Subsystem */
    err = ble_mesh_init();
    if (err)
    {
        ESP_LOGE(TAG, "Bluetooth mesh init failed (err %d)", err);
    }
}
