#include <zephyr/logging/log.h>
#include "drivers/led/led.hpp"
#include "zephyr/kernel.h"

LOG_MODULE_REGISTER(main);

int main(void) {
    drivers::led::Led led;

    while (true) {
        led.toggle(drivers::led::Color::GREEN);
        k_sleep(K_MSEC(500));
    }
}
