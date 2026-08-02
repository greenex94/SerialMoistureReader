#pragma once

#include <Arduino.h>

class GACReader
{
public:
    void begin();
    void update();

private:
    String buffer;
};