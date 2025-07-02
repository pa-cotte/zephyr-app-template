#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <stdint.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);


auto main() -> int
{
  k_thread_suspend(k_current_get());
}