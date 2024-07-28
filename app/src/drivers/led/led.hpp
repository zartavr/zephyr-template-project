#pragma once

#include <zephyr/drivers/gpio.h>

namespace drivers::led {

enum Color { GREEN = 0, RED = 1 };

class Led {
public:
  Led();
  void toggle(Color type);
  void on(Color type);
  void off(Color type);

private:
  gpio_dt_spec _green_led;
  gpio_dt_spec _red_led;
};

} // namespace drivers::led
