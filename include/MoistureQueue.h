#pragma once

#include <Arduino.h>
#include "MoistureReading.h"

class MoistureQueue
{
public:

    bool begin();

    bool add(MoistureReading reading);

    void printQueue();

    String getQueueContents();

    int getQueueCount();


private:

    const char* filename = "/queue.jsonl";

    String readingToJson(MoistureReading reading);
};