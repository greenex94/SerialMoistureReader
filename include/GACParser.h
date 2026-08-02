#pragma once

#include <Arduino.h>
#include "MoistureReading.h"

class GACParser
{
public:
    bool parse(String ticket, MoistureReading &reading);

private:
    float extractNumber(String text);
};