#pragma once

#include <Arduino.h>
#include <WebServer.h>

#include "MoistureQueue.h"


class WebPortal
{
public:

    void begin(MoistureQueue* queue);

    void update();

    void setLastReceived(String timestamp);

    void setLastUpload(String timestamp);


private:

    WebServer* server = nullptr;

    MoistureQueue* moistureQueue = nullptr;


    String lastReceived = "None";

    String lastUpload = "None";


    void handleRoot();
};