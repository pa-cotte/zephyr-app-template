#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/device.h>

#define RED_LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(RED_LED_NODE, gpios);
static const struct gpio_dt_spec gpioTest = GPIO_DT_SPEC_GET(DT_ALIAS(cover_eoc_switch), gpios);

LOG_MODULE_REGISTER(app);

auto main() -> int
{
  int ret;

  k_msleep(1000);

  
  if (!gpio_is_ready_dt(&led))
  {
    LOG_ERR("Led not ready\n");
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0)
  {
    LOG_ERR("Led config failed\n");
    return 0;
  }





 if (!gpio_is_ready_dt(&gpioTest))
  {
    LOG_ERR("GPIO Test not ready");
  }
  else
  {

    // static struct gpio_callback gpio14_cb;
    // gpio_init_callback(
    //     &gpio14_cb,
    //     [](const struct device *dev, struct gpio_callback *cb, uint32_t pins) {
    //       int val = gpio_pin_get(dev, gpio14.pin);
    //       LOG_INF("GPIO14 changed: %d", val);
    //     },
    //     BIT(gpio14.pin));
    // gpio_add_callback(gpio14.port, &gpio14_cb);
    // gpio_pin_interrupt_configure(gpio14.port, gpio14.pin, GPIO_INT_EDGE_BOTH);
    // LOG_INF("GPIO14 monitoring enabled");

    gpio_pin_configure_dt(&gpioTest, GPIO_INPUT);
  }



  while (true)
  {
    // LOG_INF("HP red Blink !");
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0)
    {
      LOG_ERR("Led toggle failed");
      return 0;
    }

    LOG_INF("Valeur GPIO: %d", gpio_pin_get_dt(&gpioTest));

    k_msleep(1000);
  }
}