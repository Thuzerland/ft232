#include <libusb-1.0/libusb.h>
#include <assert.h>
#include "USBDevice.h"

#define FTDI_DEFAULT_VID     0x0403
#define FT232H_DEFAULT_PID   0x6014

USBDevice::USBDevice(libusb_device *dvc)
{
    device = dvc;
}

QString USBDevice::toString()
{
    int rc = 0;
    char buf[128] = {0};
    const char *description;
    libusb_device_descriptor desc = {0};

    rc = libusb_get_device_descriptor(device, &desc);
    assert(rc == 0);
    /* Lets check only by PID for test purposes. */
    description = (desc.idVendor == FTDI_DEFAULT_VID)/* && (desc.idProduct == FT232H_DEFAULT_PID) */? " <-- FT232" : "";
    sprintf(buf, "%04x:%04x%s", desc.idVendor, desc.idProduct, description);

    return QString(buf);
}

bool USBDevice::isFT232()
{
    int rc = 0;
    libusb_device_descriptor desc = {0};

    rc = libusb_get_device_descriptor(device, &desc);
    assert(rc == 0);

    return (desc.idVendor == FTDI_DEFAULT_VID) && (desc.idProduct == FT232H_DEFAULT_PID);
}
