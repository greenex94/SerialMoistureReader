#pragma once

#include <Arduino.h>
#include <WiFi.h>

class WiFiManager
{
public:
    void begin();
    void update();

private:
    void startAccessPoint();
};