#pragma once

#include <Arduino.h>
#include "MoistureReading.h"

class MoistureQueue
{
public:

    bool begin();

    bool add(MoistureReading reading);

    bool hasItems();

    bool peek(MoistureReading &reading);

    bool pop();

    void printQueue();

    String getQueueContents();

    int getQueueCount();
    
    String getLastReceived();

    String getLastUpload();

    void setLastReceived(String timestamp);

    void setLastUpload(String timestamp);


private:

    const char* filename = "/queue.jsonl";

    String readingToJson(MoistureReading reading);

    bool jsonToReading(String json, MoistureReading &reading);

    String lastReceived = "Never";
    
    String lastUpload = "Never";
};