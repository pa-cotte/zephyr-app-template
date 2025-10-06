#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define GREEN_LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const struct device *i3c = DEVICE_DT_GET(DT_NODELABEL(i3c0));
static const struct device *pca = DEVICE_DT_GET(DT_NODELABEL(pca9685));

LOG_MODULE_REGISTER(app);

auto main() -> int
{
  int ret;

  if (!gpio_is_ready_dt(&led))
  {
    LOG_ERR("Led not ready\n");
    return 0;
  }

  if(!device_is_ready(i3c))
  {
    LOG_ERR("I3C device not ready\n");
    return 0;
  }else{
    LOG_INF("I3C device is ready\n");
  }

  if(!device_is_ready(pca))
  {
    LOG_ERR("PCA9685 device not ready\n");
    return 0;
  }else{
    LOG_INF("PCA9685 device is ready\n");
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0)
  {
    LOG_ERR("Led config failed\n");
    return 0;
  }

  // while (true)
  // {
  //   LOG_INF("HE green Blink !");
  //   ret = gpio_pin_toggle_dt(&led);
  //   if (ret < 0)
  //   {
  //     LOG_ERR("Led toggle failed");
  //     return 0;
  //   }

  //   k_msleep(500);
  // }
}