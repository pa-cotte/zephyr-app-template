#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define GREEN_LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);
static const struct gpio_dt_spec gpioTest = GPIO_DT_SPEC_GET(DT_ALIAS(cover_eoc_switch), gpios);

LOG_MODULE_REGISTER(app);

auto main() -> int
{
  int ret;

  if (!gpio_is_ready_dt(&led))
  {
    LOG_ERR("Led not ready\n");
    return 0;
  }

  if (!gpio_is_ready_dt(&gpioTest))
  {
    LOG_ERR("GPIO Test not ready");
  }
  else
  {
    gpio_pin_configure_dt(&gpioTest, GPIO_INPUT);
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0)
  {
    LOG_ERR("Led config failed\n");
    return 0;
  }

  while (true)
  {
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0)
    {
      LOG_ERR("Led toggle failed");
      return 0;
    }
    LOG_INF("Valeur GPIO: %d", gpio_pin_get_dt(&gpioTest));

    k_msleep(500);
  }
}