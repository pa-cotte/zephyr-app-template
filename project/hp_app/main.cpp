#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

#define RED_LED_NODE DT_ALIAS(led0)
#define SPI3_NODE DT_NODELABEL(spi3)

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);


auto main() -> int
{
  k_thread_suspend(k_current_get());
}