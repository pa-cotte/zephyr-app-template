#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>


LOG_MODULE_REGISTER(app);

auto main() -> int
{
  k_thread_suspend(k_current_get());
}