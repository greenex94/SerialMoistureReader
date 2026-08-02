#pragma once

#include <Arduino.h>

#include "MoistureReading.h"
#include "TimeManager.h"
#include "GACParser.h"


class GACReader
{
public:

    void begin(TimeManager* tm);
    void update();


private:

    String buffer;

    TimeManager* timeManager = nullptr;

    GACParser parser;
};