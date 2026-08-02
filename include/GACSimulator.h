#pragma once

#include <Arduino.h>

class GACSimulator
{
public:
    void begin();
    void update();

private:
    unsigned long lastSend = 0;
};