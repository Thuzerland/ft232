#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#include <libusb-1.0/libusb.h>
#include <ftd2xx.h>

#include "USBBus.h"

USBBus::USBBus()
{
    libusb_device **list = NULL;
    int rc = 0;
    ssize_t count = 0;

    rc = libusb_init(&this->libusb_ctx);
    assert(rc == 0);
}

USBBus::~USBBus()
{
    libusb_exit(this->libusb_ctx);
}

int USBBus::enumerateDevices(USBDevice ***devices, size_t *cnt)
{
    ssize_t count;

    count = libusb_get_device_list(this->libusb_ctx, &list);
    assert(count > 0);

    if (cnt != nullptr) {
        *cnt = count;
    }

    if (devices != nullptr) {
        *devices = static_cast<USBDevice **>(calloc(count, sizeof(USBDevice *)));
        assert(*devices != nullptr);
    }

    for (size_t idx = 0; idx < count; ++idx) {
        libusb_device *device = list[idx];

        (*devices)[idx] = new USBDevice(device);
    }

    return 0;
}

int USBBus::enumerateFT232()
{
    FT_STATUS ftStatus;
    DWORD numDevs;


    ftStatus = FT_ListDevices(&numDevs, NULL, FT_LIST_NUMBER_ONLY);
    assert(ftStatus == FT_OK);

    return numDevs;
}
