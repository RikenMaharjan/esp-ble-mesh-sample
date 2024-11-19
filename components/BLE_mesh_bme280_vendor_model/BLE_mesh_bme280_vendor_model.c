
#include "sdkconfig.h"

#if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "esp_log.h"
#include "esp_err.h"
#include "bmp280.h"

#include "esp_ble_mesh_networking_api.h"

#include "BLE_mesh_definitions.h"
#include "BLE_mesh_initializer.h"
#include "BLE_mesh_bme280_vendor_model.h"

#define BME280_SDA 18
#define BME280_SCL 17
#define BME280_ADDRESS 0x76
#define BME280_I2C I2C_NUM_0

static i2c_master_bus_config_t i2c_mst_config = {
    .clk_source = I2C_CLK_SRC_DEFAULT,
    .i2c_port = BME280_I2C,
    .scl_io_num = BME280_SCL,
    .sda_io_num = BME280_SDA,
    .glitch_ignore_cnt = 7,
    .flags.enable_internal_pullup = true,
};
static i2c_master_bus_handle_t bus_handle = NULL;

i2c_device_config_t dev_cfg = {
    .dev_addr_length = I2C_ADDR_BIT_LEN_7,
    .device_address = BME280_ADDRESS,
    .scl_speed_hz = 100000,
};
static i2c_master_dev_handle_t device_handle = NULL;
static bmp280_t dev;

static void bme280_model_callback(esp_ble_mesh_model_cb_param_t *param, void *user_data);
static void bme280_publication_callback(esp_ble_mesh_model_t *model, void *user_data);

void BLE_mesh_bme280_vendor_model_initialize_device()
{
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));
    if (!bus_handle)
    {
        return;
    }
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &device_handle));
    if (!device_handle)
    {
        return;
    }

    bmp280_params_t params;
    bmp280_init_default_params(&params);
    dev.device_handle = device_handle;
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));
}

void BLE_mesh_bme280_vendor_model_register_callback()
{
    ble_mesh_register_vendor_model_user_args(
        1,                                    // Element id
        ESP_BLE_MESH_VND_MODEL_BME280_SERVER, // Model ID
        bme280_model_callback,                // Mesh model callback
        bme280_publication_callback,          // Mesh model publication callback
        NULL                                  // User data
    );
}

static void bme280_publication_callback(esp_ble_mesh_model_t *model, void *user_data)
{
    uint8_t publication_data[14];
    memset(publication_data, 0, sizeof(publication_data));
    printf("Publishing bme280 data\n");
    ESP_ERROR_CHECK(esp_ble_mesh_model_publish(
        model,
        ESP_BLE_MESH_VND_MODEL_BME280_PUB_STATUS_OP_CODE,
        sizeof(publication_data),
        publication_data,
        ROLE_NODE));
}

static void bme280_model_callback(esp_ble_mesh_model_cb_param_t *param, void *user_data)
{
    if (param->model_operation.length != 1)
    {
        return;
    }

    uint8_t message = *param->model_operation.msg;
    if (message != 1)
    {
        return;
    }

    uint8_t array[4];
    float temperature, pressure, humidity;
    bmp280_read_float(&dev, &temperature, &pressure, &humidity);
    switch (param->model_operation.opcode)
    {
    case ESP_BLE_MESH_VND_MODEL_BME280_TEMPERATURE_GET_OP_CODE:
    {
        printf("ESP_BLE_MESH_VND_MODEL_TEMPERATURE_GET_OP_CODE\n");
        int32_t temperature_int32 = (int32_t)temperature;
        memcpy(array, &temperature_int32, sizeof(array));
        printf("Temperature: float: %f int32_t: %ld and hex: 0x%lx\n", temperature, temperature_int32, temperature_int32);

        esp_ble_mesh_server_model_send_msg(
            param->model_operation.model,
            param->model_operation.ctx,
            ESP_BLE_MESH_VND_MODEL_BME280_STATUS_OP_CODE,
            sizeof(array),
            array);
        break;
    }
    case ESP_BLE_MESH_VND_MODEL_BME280_HUMIDITY_GET_OP_CODE:
    {
        printf("ESP_BLE_MESH_VND_MODEL_HUMIDITY_GET_OP_CODE\n");
        int32_t humidity_int32 = (int32_t)humidity;
        memcpy(array, &humidity_int32, sizeof(array));
        printf("Humidity: float: %f int32_t: %ld and hex: 0x%lx\n", humidity, humidity_int32, humidity_int32);

        esp_ble_mesh_server_model_send_msg(
            param->model_operation.model,
            param->model_operation.ctx,
            ESP_BLE_MESH_VND_MODEL_BME280_STATUS_OP_CODE,
            sizeof(array),
            array);
        break;
    }
    case ESP_BLE_MESH_VND_MODEL_BME280_PRESSURE_GET_OP_CODE:
    {
        printf("ESP_BLE_MESH_VND_MODEL_PRESSURE_GET_OP_CODE\n");
        int32_t pressure_int32 = (int32_t)pressure;
        memcpy(array, &pressure_int32, sizeof(array));
        printf("Pressure: float: %f int32_t: %ld and hex: 0x%lx\n", pressure, pressure_int32, pressure_int32);

        esp_ble_mesh_server_model_send_msg(
            param->model_operation.model,
            param->model_operation.ctx,
            ESP_BLE_MESH_VND_MODEL_BME280_STATUS_OP_CODE,
            sizeof(array),
            array);
        break;
    }
    default:
    {
        break;
    }
    }
}

#endif // if defined(CONFIG_BLE_MESH_BME280_VENDOR_MODEL_ENABLE)