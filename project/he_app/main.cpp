#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/fs/fs.h>
#include <zephyr/storage/flash_map.h>

#define GREEN_LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(GREEN_LED_NODE, gpios);

LOG_MODULE_REGISTER(app);

auto main() -> int
{
  int ret;

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



  // --- OSPI FLASH TEST BEGIN ---


  FS_FSTAB_DECLARE_ENTRY(DT_NODELABEL(lfs2));
  ret = fs_mount(&FS_FSTAB_ENTRY(DT_NODELABEL(lfs2)));
  if (ret < 0)
  {
    LOG_ERR("Failed to mount external flash storage: %d", ret);
    return -1;
  }
  LOG_INF("External flash storage mounted successfully at %s", FS_FSTAB_ENTRY(DT_NODELABEL(lfs2)).mnt_point);




  // Test OSPI flash storage
  LOG_INF("Testing OSPI flash storage...");

  const char *test_file = "/external/ospi_test.txt";
  const char *test_data = "Hello OSPI Flash!";
  char read_buffer[64];

  // Test write
  struct fs_file_t file;
  fs_file_t_init(&file);

  ret = fs_open(&file, test_file, FS_O_CREATE | FS_O_WRITE);
  if (ret < 0)
  {
    LOG_ERR("Failed to open file for write: %d", ret);
  }
  else
  {
    ssize_t written = fs_write(&file, test_data, strlen(test_data));
    if (written < 0)
    {
      LOG_ERR("Failed to write to file: %d", (int)written);
    }
    else
    {
      LOG_INF("Written %d bytes to OSPI flash", (int)written);
    }
    fs_close(&file);
  }

  // Test read
  ret = fs_open(&file, test_file, FS_O_READ);
  if (ret < 0)
  {
    LOG_ERR("Failed to open file for read: %d", ret);
  }
  else
  {
    ssize_t bytes_read = fs_read(&file, read_buffer, sizeof(read_buffer) - 1);
    if (bytes_read < 0)
    {
      LOG_ERR("Failed to read from file: %d", (int)bytes_read);
    }
    else
    {
      read_buffer[bytes_read] = '\0';
      LOG_INF("Read %d bytes from OSPI flash: '%s'", (int)bytes_read, read_buffer);

      if (strcmp(test_data, read_buffer) == 0)
      {
        LOG_INF("OSPI flash test PASSED!");
      }
      else
      {
        LOG_ERR("OSPI flash test FAILED - data mismatch");
      }
    }
    fs_close(&file);
  }

  // --- OSPI FLASH TEST END ---






  while (true)
  {
    LOG_INF("HE green Blink !");
    ret = gpio_pin_toggle_dt(&led);
    if (ret < 0)
    {
      LOG_ERR("Led toggle failed");
      return 0;
    }

    k_msleep(500);
  }
}