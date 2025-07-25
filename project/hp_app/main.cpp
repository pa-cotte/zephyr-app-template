#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

// #define RED_LED_NODE DT_ALIAS(led0)

// static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(RED_LED_NODE, gpios);

LOG_MODULE_REGISTER(app);

auto main() -> int
{
k_thread_suspend(k_current_get());
}