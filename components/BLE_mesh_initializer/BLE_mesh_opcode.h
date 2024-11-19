

#ifndef _BLE_MESH_OPCODE_H_
#define _BLE_MESH_OPCODE_H_

#include "BLE_mesh_definitions.h"

static esp_ble_mesh_model_op_t vnd_op[] = {
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_OP_SET, 1),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_OP_GET, 1),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_OP_STATUS, 1),
    ESP_BLE_MESH_MODEL_OP_END,
};

#if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)
static esp_ble_mesh_model_op_t bme280_op[] = {
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_BME280_TEMPERATURE_GET_OP_CODE, 1),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_BME280_HUMIDITY_GET_OP_CODE, 1),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_BME280_PRESSURE_GET_OP_CODE, 1),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_BME280_STATUS_OP_CODE, 4),
    ESP_BLE_MESH_MODEL_OP(ESP_BLE_MESH_VND_MODEL_BME280_PUB_STATUS_OP_CODE, 13),
    ESP_BLE_MESH_MODEL_OP_END,
};
#endif //  if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)


#endif // _BLE_MESH_OPCODE_H_
