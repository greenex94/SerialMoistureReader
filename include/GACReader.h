#pragma once

#include <Arduino.h>
#include "TimeManager.h"
#include "MoistureQueue.h"
#include "GACParser.h"


class GoogleSheets;


class GACReader
{

public:

    void begin(
        TimeManager* time,
        MoistureQueue* queue,
        GoogleSheets* sheets
    );

    void update();


private:

    TimeManager* timeManager = nullptr;

    MoistureQueue* moistureQueue = nullptr;

    GoogleSheets* googleSheets = nullptr;

    GACParser parser;

    String buffer;

};