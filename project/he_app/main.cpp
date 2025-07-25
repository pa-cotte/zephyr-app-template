#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#define GPIO_IRQ_HANDLER DT_ALIAS(irq_handler)
#define GPIO_IRQ_GENERATOR DT_ALIAS(irq_generator)

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);

static void gpio_callback(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
    LOG_INF("GPIO interrupt triggered! Pins: %u", pins);
}

static struct gpio_callback gpio_cb;

auto main() -> int
{
    int ret;

    static const struct gpio_dt_spec gpio_generator_dev = GPIO_DT_SPEC_GET(GPIO_IRQ_GENERATOR, gpios);
    static const struct gpio_dt_spec gpio_handler_dev = GPIO_DT_SPEC_GET(GPIO_IRQ_HANDLER, gpios);


    if (!gpio_is_ready_dt(&gpio_handler_dev))
    {
        LOG_ERR("GPIO handler device not ready");
        return -1;
    }

    if (!gpio_is_ready_dt(&gpio_generator_dev))
    {
        LOG_ERR("GPIO generator device not ready");
        return -1;
    }

    ret = gpio_pin_configure_dt(&gpio_generator_dev, GPIO_OUTPUT_LOW);
    if (ret != 0)
    {
        LOG_ERR("Error configuring GPIO generator pin: %d", ret);
        return -1;
    }

    ret = gpio_pin_configure_dt(&gpio_handler_dev, GPIO_INPUT);
    if (ret != 0)
    {
        LOG_ERR("Error configuring GPIO handler pin: %d", ret);
        return -1;
    }

    ret = gpio_pin_interrupt_configure_dt(&gpio_handler_dev, GPIO_INT_EDGE_FALLING);
    if (ret != 0)
    {
        LOG_ERR("Error configuring GPIO handler interrupt: %d", ret);
        return -1;
    }

    gpio_init_callback(&gpio_cb, gpio_callback, BIT(gpio_handler_dev.pin));
    ret = gpio_add_callback(gpio_handler_dev.port, &gpio_cb);
    if (ret != 0)
    {
        LOG_ERR("Error adding GPIO callback: %d", ret);
        return -1;
    }

    while (1)
    {
        gpio_pin_toggle_dt(&gpio_generator_dev);
        LOG_INF("Pin toggled");
        k_sleep(K_MSEC(1000));
    }
    return 0;
}