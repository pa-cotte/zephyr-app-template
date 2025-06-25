#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_DBG);

auto main() -> int
{
  k_thread_suspend(k_current_get());
}