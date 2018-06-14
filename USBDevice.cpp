#include <libusb-1.0/libusb.h>
#include "USBDevice.h"

USBDevice::USBDevice(libusb_device *dvc)
{
    device = dvc;
}

QString USBDevice::toString()
{
    int rc = 0;
    char buf[128] = {0};
    libusb_device_descriptor desc = {0};

    rc = libusb_get_device_descriptor(device, &desc);
    assert(rc == 0);

    sprintf(buf, "%04x:%04x", desc.idVendor, desc.idProduct);

    return QString(buf);
}
