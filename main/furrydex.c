#include <stdbool.h>
#include <stdint.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"

#define LED_GPIO 8
#define BLINK_PERIOD_MS 500

static const char *TAG = "furrydex";

static led_strip_handle_t led;

static void led_init(void)
{
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_GPIO,
        .max_leds = 1,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,  // 10 MHz
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led));
    ESP_ERROR_CHECK(led_strip_clear(led));
}

static void led_set(bool on)
{
    if (on) {
        ESP_ERROR_CHECK(led_strip_set_pixel(led, 0, 16, 16, 16));
        ESP_ERROR_CHECK(led_strip_refresh(led));
    } else {
        ESP_ERROR_CHECK(led_strip_clear(led));
    }
}

void app_main(void)
{
    led_init();
    ESP_LOGI(TAG, "Blink started on GPIO %d", LED_GPIO);

    bool on = false;
    uint32_t count = 0;

    while (true) {
        on = !on;
        led_set(on);
        ESP_LOGI(TAG, "#%lu LED %s", (unsigned long)++count, on ? "ON" : "OFF");
        vTaskDelay(pdMS_TO_TICKS(BLINK_PERIOD_MS));
    }
}
