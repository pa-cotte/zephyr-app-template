#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
// #include <zephyr/drivers/gpio.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);

// #define GPIO_CLICKBOARD_ENABLE DT_ALIAS(clickboard_enable)

auto main() -> int
{
  // static const struct gpio_dt_spec gpio_clickboard_enable = GPIO_DT_SPEC_GET(GPIO_CLICKBOARD_ENABLE, gpios);

  // if (!gpio_is_ready_dt(&gpio_clickboard_enable))
  // {
  //   LOG_ERR("GPIO clickboard enable device not ready");
  //   return -1;
  // }

  // int ret = gpio_pin_configure_dt(&gpio_clickboard_enable, GPIO_OUTPUT_HIGH);
  // if (ret != 0)
  // {
  //   LOG_ERR("Error configuring GPIO clickboard enable pin: %d", ret);
  //   return -1;
  // }

  // LOG_INF("GPIO clickboard enable pin configured successfully");

  // while (true)
  // {
  //   k_sleep(K_SECONDS(10)); // Simulate some work
  // }
  
  LOG_INF("Running main loop...");
  k_thread_suspend(k_current_get());
}