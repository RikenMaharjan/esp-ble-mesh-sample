
#ifndef _BLE_MESH_DEFINITIONS_H_
#define _BLE_MESH_DEFINITIONS_H_

#include "esp_ble_mesh_defs.h"
#include "esp_ble_mesh_generic_model_api.h"

#define CID_ESP 0x02E5

// BLE mesh model IDS
#define ESP_BLE_MESH_VND_MODEL_ID_SERVER 0x2000
// #define ESP_BLE_MESH_VND_MODEL_BME280_SERVER 0x2001

// BLE mesh opcode IDs
#define ESP_BLE_MESH_VND_MODEL_OP_SET ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_GET ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_STATUS ESP_BLE_MESH_MODEL_OP_3(0x02, CID_ESP)

// Op-codes for bme680
// #define ESP_BLE_MESH_VND_MODEL_BME280_TEMPERATURE_GET_OP_CODE ESP_BLE_MESH_MODEL_OP_3(0x00, CID_ESP)
// #define ESP_BLE_MESH_VND_MODEL_BME280_HUMIDITY_GET_OP_CODE ESP_BLE_MESH_MODEL_OP_3(0x01, CID_ESP)
// #define ESP_BLE_MESH_VND_MODEL_BME280_PRESSURE_GET_OP_CODE ESP_BLE_MESH_MODEL_OP_3(0x02, CID_ESP)
// #define ESP_BLE_MESH_VND_MODEL_BME280_STATUS_OP_CODE ESP_BLE_MESH_MODEL_OP_3(0x03, CID_ESP)
// #define ESP_BLE_MESH_VND_MODEL_BME280_PUB_STATUS_OP_CODE ESP_BLE_MESH_MODEL_OP_3(0x03, CID_ESP)

typedef void (*custom_model_callback)(esp_ble_mesh_model_cb_param_t *param, void *user_data);
typedef void (*custom_model_publication_callback)(esp_ble_mesh_model_t *model, void *user_data);

typedef void (*sig_model_callback)(esp_ble_mesh_generic_server_cb_param_t *param, void *user_data);

typedef struct s_custom_model_user_data_struct
{
    uint16_t element_id;
    uint16_t model_id;
    union
    {
        custom_model_callback custom_model_cb;
        sig_model_callback sig_model_cb;
    } model_cb;
    union
    {
        custom_model_publication_callback custom_publication_cb;
    } publication_cb;
    void *args;
} s_custom_model_user_data_struct_t;

#endif // _BLE_MESH_DEFINITIONS_H_
