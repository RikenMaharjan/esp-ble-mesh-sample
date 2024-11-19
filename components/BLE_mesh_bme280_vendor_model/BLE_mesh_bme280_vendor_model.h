
#include "sdkconfig.h"

#if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)
#ifndef _BLE_MESH_BME680_VENDOR_MODEL_H_
#define _BLE_MESH_BME680_VENDOR_MODEL_H_

typedef struct
{
    float temperature;
    float pressure;
    float humidity;
} bme680_data_t;

void BLE_mesh_bme280_vendor_model_initialize_device();
void BLE_mesh_bme280_vendor_model_register_callback();

#endif // _BLE_MESH_BME680_VENDOR_MODEL_H_

#endif // if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)
