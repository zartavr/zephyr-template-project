/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "drivers/rangemeter/rangemeter.hpp"
#include "drivers/siren/siren.hpp"
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>

LOG_MODULE_REGISTER(main);

BUILD_ASSERT(
    DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
    "Console device is not ACM CDC UART device"
);

int main(void)
{
    const struct device* const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
    uint32_t                   dtr = 0;

#if defined(CONFIG_USB_DEVICE_STACK_NEXT)
    if (enable_usb_device_next()) {
        return 0;
    }
#else
    if (usb_enable(NULL)) {
        return 0;
    }
#endif

    using Rangemeter = etl::singleton<drivers::rangemeter::Rangemeter>;
    Rangemeter::create(DEVICE_DT_GET_ONE(st_vl53l0x));
    auto& rangemeter = Rangemeter::instance();

    drivers::siren::Siren siren;

    /* Poll if the DTR flag was set */
    while (!dtr) {
        uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        /* Give CPU resources to low priority threads. */
        k_sleep(K_MSEC(100));
    }


    while (1) {
        uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
        auto ret = rangemeter.fetch();
        if (ret != 0) {
            LOG_ERR("sensor_sample_fetch failed ret %d \n", ret);
            return 0;
        }

        int32_t range = rangemeter.get_range();
        if (dtr) {
            printk("%6d", range);
        }
        k_sleep(K_MSEC(50));
    }
}
