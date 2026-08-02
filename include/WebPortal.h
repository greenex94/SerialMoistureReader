#pragma once

#include <Arduino.h>
#include <WebServer.h>

#include "MoistureQueue.h"


class WebPortal
{
public:

    void begin(MoistureQueue* queue);

    void update();


private:

    WebServer* server = nullptr;

    MoistureQueue* moistureQueue = nullptr;

    void handleRoot();
};