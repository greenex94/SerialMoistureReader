#pragma once

#include <Arduino.h>
#include "MoistureReading.h"

class GoogleSheets
{
public:

    void begin();

    bool upload(
        MoistureReading reading
    );

private:

    const char* scriptURL =
        "https://script.google.com/macros/s/AKfycbz_QSbt0FrCaq-FZk6rn5Llvj_OPBnmgPxQx7dlMWRcQtaOwY_eDlIrbudvQl23gF34IQ/exec";
};