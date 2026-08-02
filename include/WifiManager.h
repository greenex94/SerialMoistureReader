#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <Preferences.h>

class WiFiManager
{
public:
    void begin();
    void update();

    bool isConnected();

private:
    void loadCredentials();
    bool connectToWiFi();
    void startAccessPoint();

    Preferences preferences;

    String ssid;
    String password;

    bool connected = false;
};