#ifndef USB_H
#define USB_H

#include <libusb-1.0/libusb.h>
#include "USBDevice.h"

class USBBus
{
public:
    USBBus();

    int enumerateDevices(USBDevice ***devices, size_t *cnt);
    int enumerateFT232();

    virtual ~USBBus();

private:
    libusb_context *libusb_ctx;
    libusb_device **list = nullptr;
};

#endif // USB_H
