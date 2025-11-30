#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static const uint32_t sleep_time_ms = 100;
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(BUTTON_NODE, gpios, {0});

#define BUTTON_NODE DT_NODELABEL(button)
#define BUTTON_GPIO_PIN DT_GPIO_PIN(BUTTON_NODE, gpios)

int main(void) {
  printk("Hello from simple-button!\n");

  if (!gpio_is_ready_dt(&button)) {
    printk("Error: button device %s is not ready\n", button.port->name);
    return 0;
  }

  if (gpio_pin_configure_dt(&button, GPIO_INPUT) < 0) {
    printk("Error %d: failed to configure %s pin %d\n", -errno,
           button.port->name, button.pin);
    return 0;
  }

  printk("Button state flags: 0x%08x\n", button.dt_flags);

  return 0;
}
