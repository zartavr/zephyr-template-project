#include "led.hpp"

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

namespace drivers::led {

LOG_MODULE_REGISTER(led);

Led::Led()
{
    // Init class fields
    _green_led = GPIO_DT_SPEC_GET(DT_ALIAS(user_led), gpios);

    int ret = 0;

    // Config all user leds to output states
    ret = gpio_pin_configure_dt(&_green_led, GPIO_OUTPUT_INACTIVE);

    if (ret != 0) {
        LOG_WRN("GPIO init fail.");
    }
}

void Led::toggle(Color type)
{
    int ret = 0;

    switch (type) {
        case GREEN: {
            ret = gpio_pin_toggle_dt(&_green_led);
            break;
        }

        case RED: {
            ret = gpio_pin_toggle_dt(&_red_led);
            break;
        }

        default: {
            ret = -1;
            break;
        }
    }

    if (ret != 0) {
        LOG_ERR("GPIO toggling fail.");
    }
}

void Led::on(Color type)
{
    int ret = 0;

    switch (type) {
        case GREEN: {
            ret = gpio_pin_set_dt(&_green_led, 1);
            break;
        }

        case RED: {
            ret = gpio_pin_set_dt(&_red_led, 1);
            break;
        }

        default: {
            ret = -1;
            break;
        }
    }

    if (ret != 0) {
        LOG_ERR("GPIO toggling fail.");
    }
}

void Led::off(Color type)
{
    int ret = 0;

    switch (type) {
        case GREEN: {
            ret = gpio_pin_set_dt(&_green_led, 0);
            break;
        }

        case RED: {
            ret = gpio_pin_set_dt(&_red_led, 0);
            break;
        }

        default: {
            ret = -1;
            break;
        }
    }

    if (ret != 0) {
        LOG_ERR("GPIO toggling fail.");
    }
}

}  // namespace drivers::led
