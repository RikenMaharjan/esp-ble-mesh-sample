
#include "driver/gpio.h"
#include "esp_err.h"
// #include "led_strip.h"
// #include "led_strip_types.h"
// #include "led_strip_rmt.h"
#include "esp_log.h"
#include "BLE_mesh_prov_indicator.h"

#if defined(CONFIG_IDF_TARGET_ESP32S3)
#define INDICATOR_LED GPIO_NUM_48
#elif defined(CONFIG_IDF_TARGET_ESP32)
#define INDICATOR_LED GPIO_NUM_2
#else
#define INDICATOR_LED GPIO_NUM_33
#endif // CONFIG_IDF_TARGET_ESP32S3

#if defined(CONFIG_IDF_TARGET_ESP32S3)
static gpio_config_t led_prov_indi_config = {
    .pin_bit_mask = (1ULL << INDICATOR_LED),
    .mode = GPIO_MODE_OUTPUT,
    .intr_type = GPIO_INTR_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_ENABLE,
    .pull_up_en = GPIO_PULLUP_DISABLE,
};
static bool led_state = 0;

// static led_strip_handle_t indicator_led_strip_handle = NULL;

// static led_strip_config_t indicator_led_strip_config = {
//     .strip_gpio_num = INDICATOR_LED,
//     .max_leds = 1,
//     .led_pixel_format = LED_PIXEL_FORMAT_GRB,
//     .led_model = LED_MODEL_WS2812,
//     .flags.invert_out = false,
// };

// static led_strip_rmt_config_t indicator_led_rmt_config = {
//     .clk_src = RMT_CLK_SRC_DEFAULT,
//     .resolution_hz = 10 * 1000 * 1000, // 10MHz
//     .flags.with_dma = false,
// };
#endif // CONFIG_IDF_TARGET_ESP32S3

int BLE_mesh_indicator_init(void)
{
    int ret = -1;
#if defined(CONFIG_IDF_TARGET_ESP32S3)
    ESP_ERROR_CHECK(gpio_config(&led_prov_indi_config));
    gpio_set_level(INDICATOR_LED, 1);

    //blink twice

    // if (0 == led_strip_new_rmt_device(&indicator_led_strip_config, &indicator_led_rmt_config, &indicator_led_strip_handle))
    // {
    //     printf("Indicator initialized...\n");
    //     ESP_ERROR_CHECK(led_strip_clear(indicator_led_strip_handle));
    //     ESP_ERROR_CHECK(led_strip_set_pixel(indicator_led_strip_handle, 0, 255, 0, 0));
    //     ESP_ERROR_CHECK(led_strip_refresh(indicator_led_strip_handle));
    //     ret = 0;
    // }
    gpio_set_level(INDICATOR_LED, 0);

#else
    ESP_LOGE(__FILE__, "No LED indicator available for %s", CONFIG_IDF_TARGET);
#endif // CONFIG_IDF_TARGET_ESP32S3
    return ret;
}

void BLE_mesh_prov_link_open_indicate(void)
{
#if defined(CONFIG_IDF_TARGET_ESP32S3)

    // blink 3 times

    // if (indicator_led_strip_handle)
    // {
    //     ESP_ERROR_CHECK(led_strip_clear(indicator_led_strip_handle));
    //     ESP_ERROR_CHECK(led_strip_set_pixel(indicator_led_strip_handle, 0, 0, 0, 255));
    //     ESP_ERROR_CHECK(led_strip_refresh(indicator_led_strip_handle));
    // }
#else
    ESP_LOGE(__FILE__, "No LED indicator available for %s", CONFIG_IDF_TARGET);
#endif // CONFIG_IDF_TARGET_ESP32S3
}

void BLE_mesh_prov_complete_indicate(void)
{
#if defined(CONFIG_IDF_TARGET_ESP32S3)

    // blink once

    // if (indicator_led_strip_handle)
    // {
    //     ESP_ERROR_CHECK(led_strip_clear(indicator_led_strip_handle));
    //     ESP_ERROR_CHECK(led_strip_set_pixel(indicator_led_strip_handle, 0, 0, 255, 0));
    //     ESP_ERROR_CHECK(led_strip_refresh(indicator_led_strip_handle));
    // }


    // reset the led-gpio to default.
#else
    ESP_LOGE(__FILE__, "No LED indicator available for %s", CONFIG_IDF_TARGET);
#endif // CONFIG_IDF_TARGET_ESP32S3
}
