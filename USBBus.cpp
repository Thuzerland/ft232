#include <stdio.h>
#include <libusb-1.0/libusb.h>

#include "USBBus.h"

USBBus::USBBus()
{
    libusb_device **list = NULL;
    int rc = 0;
    ssize_t count = 0;

    rc = libusb_init(&this->libusb_ctx);
    assert(rc == 0);

//    count = libusb_get_device_list(this->libusb_ctx, &list);
//    assert(count > 0);
//
//    for (size_t idx = 0; idx < count; ++idx) {
//        libusb_device *device = list[idx];
//        libusb_device_descriptor desc = {0};
//
//        rc = libusb_get_device_descriptor(device, &desc);
//        assert(rc == 0);
//
//        printf("Vendor:Device = %04x:%04x\n", desc.idVendor, desc.idProduct);
//    }
}

USBBus::~USBBus()
{
    libusb_exit(this->libusb_ctx);
}

int USBBus::enumerateDevices(USBDevice ***devices, size_t *cnt)
{
    ssize_t count;
    int rc = 0;

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
