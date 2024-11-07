

#include "esp_ble_mesh_defs.h"
#include "esp_ble_mesh_networking_api.h"
#include "driver/gpio.h"
#include "esp_err.h"

#include "BLE_mesh_definitions.h"
#include "BLE_mesh_initializer.h"
#include "BLE_mesh_led_model.h"

static gpio_config_t led_server_config = {
    .pin_bit_mask = (1ULL << GPIO_NUM_2),
    .mode = GPIO_MODE_OUTPUT,
    .intr_type = GPIO_INTR_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
};
static bool led_state = 0;

static int ble_mesh_led_model_opcode_set_exec(uint32_t state)
{
    int ret = -1;
    if ((0 == state) || (1 == state))
    {
        gpio_set_level(GPIO_NUM_2, state);
        led_state = state;
        ret = -1;
    }
    return ret;
}

static void ble_mesh_led_model_publication_exec(esp_ble_mesh_model_t *model, void *user_data)
{
    ESP_ERROR_CHECK(esp_ble_mesh_model_publish(
        model,
        ESP_BLE_MESH_VND_MODEL_OP_STATUS, 1, (uint8_t *)&led_state, ROLE_NODE));
}

static void ble_mesh_led_model_callback(esp_ble_mesh_model_cb_param_t *param, void *user_data)
{
    switch (param->model_operation.opcode)
    {
    case ESP_BLE_MESH_VND_MODEL_OP_SET:
    {
        ble_mesh_led_model_opcode_set_exec((uint32_t)*param->model_operation.msg);
        esp_ble_mesh_server_model_send_msg(
            param->model_operation.model,
            param->model_operation.ctx,
            ESP_BLE_MESH_VND_MODEL_OP_STATUS,
            sizeof(led_state),
            (uint8_t *)&led_state);
        break;
    }
    case ESP_BLE_MESH_VND_MODEL_OP_GET:
    {
        esp_ble_mesh_server_model_send_msg(
            param->model_operation.model,
            param->model_operation.ctx,
            ESP_BLE_MESH_VND_MODEL_OP_STATUS,
            sizeof(led_state),
            (uint8_t *)&led_state);
        break;
    }
    case ESP_BLE_MESH_VND_MODEL_OP_STATUS:
    {
        break;
    }
    default:
    {
        printf("Unknown model opcode: %ld\n", param->model_operation.opcode);
        break;
    }
    }
}

static void ble_mesh_led_sig_model_callback(esp_ble_mesh_generic_server_cb_param_t *param, void *user_data)
{
    switch (param->ctx.recv_op)
    {
    case ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET:
    {
        ble_mesh_led_model_opcode_set_exec(param->value.set.onoff.onoff);
        uint8_t data[1] = {led_state};
        param->model->pub->msg->data = data;
        param->model->pub->msg->len = sizeof(data);

        esp_ble_mesh_server_model_send_msg(
            param->model,
            &param->ctx,
            ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
            sizeof(led_state),
            (uint8_t *)&led_state);
        break;
    }
    case ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET:
    {
        esp_ble_mesh_server_model_send_msg(
            param->model,
            &param->ctx,
            ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS,
            sizeof(led_state),
            (uint8_t *)&led_state);
        break;
    }
    default:
    {
        printf("Unknown model opcode: %ld\n", param->ctx.recv_op);
        break;
    }
    }
}

void BLE_mesh_led_model_initialize_device()
{
    ESP_ERROR_CHECK(gpio_config(&led_server_config));
    gpio_set_level(GPIO_NUM_2, led_state);
}

void ble_mesh_led_model_register_callbacks()
{
    ble_mesh_register_vendor_model_user_args(
        0,                                   // Element id
        ESP_BLE_MESH_VND_MODEL_ID_SERVER,    // Model ID
        ble_mesh_led_model_callback,         // Mesh model callback
        ble_mesh_led_model_publication_exec, // Mesh model publication callback
        NULL                                 // User data
    );

    ble_mesh_register_sig_model_user_args(
        0,                                   // Element id
        ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV, // Model ID
        ble_mesh_led_sig_model_callback,     // Mesh model callback
        NULL                                 // User data
    );
}



