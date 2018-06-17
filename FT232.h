#ifndef _FT232_H_
#define _FT232_H_

#include <QString>
#include "ftd2xx.h"

class FT232 {
public:
    FT232(int idx);
    QString toString();
    void togglePin(int pin);

private:
    int index;
};

#endif // _FT232_H_
