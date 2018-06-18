#include "FT232.h"

#include <assert.h>

#define MAX_PIN_NUMBER  4 /* FT232R has only 4 CBUS pins */

#define FT_BIT_BANG_CBUS_MODE  0x20

FT232::FT232(int idx)
{
    this->index = idx;
}

QString FT232::toString()
{
    FT_STATUS  status;
    char buf[64] = {0};

    status = FT_ListDevices((PVOID)index, buf, FT_LIST_BY_INDEX|FT_OPEN_BY_SERIAL_NUMBER);
    assert(status == FT_OK);

    return QString(buf);
}

void FT232::togglePin(int pin)
{
    assert(pin >= 0 && pin < MAX_PIN_NUMBER);

    FT_STATUS  status;
    FT_HANDLE handle;
    unsigned char mask;


    status = FT_Open(index, &handle);
    assert(status == FT_OK);

    /*TODO: to use CBUS Bit Bang for the FT232R, the CBUS must be configured for CBUS Bit Bang in the EEPROM. */
    /* Get current pin states. */
    status = FT_GetBitMode(handle, &mask);
    assert(status == FT_OK);

    mask ^= (1 << pin); /* Toggle selected bit in lower nibble. */

    /* Write mask with toggled pin. */
    status = FT_SetBitMode(handle, mask, FT_BIT_BANG_CBUS_MODE);
    assert(status == FT_OK);

    FT_Close(handle);
}
