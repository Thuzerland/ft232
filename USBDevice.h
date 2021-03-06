#ifndef _USBDEVICE_H_
#define _USBDEVICE_H_


#include <QString>

class USBDevice {
public:
    USBDevice(libusb_device *device);
    QString toString();
    bool isFT232();

private:
    libusb_device *device = nullptr;
};


#endif // _USBDEVICE_H_
