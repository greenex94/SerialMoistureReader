#pragma once

#include <Arduino.h>
#include <WebServer.h>

class WebPortal
{
public:
    void begin();
    void update();

private:
    WebServer* server = nullptr;

    void handleRoot();
    void handleSave();
    void handleNotFound();
};