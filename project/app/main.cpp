#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app);

auto main() -> int
{
  while (true)
  {
    LOG_INF("Hello World");
    k_msleep(1000);
  }
}