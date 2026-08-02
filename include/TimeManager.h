#pragma once

#include <Arduino.h>

class TimeManager
{
public:
    void begin();
    String getTimestamp();

private:
    bool synced = false;
};