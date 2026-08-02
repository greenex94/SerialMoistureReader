#include "WiFiManager.h"

void WiFiManager::begin()
{
    startAccessPoint();
}

void WiFiManager::update()
{
    // Nothing to do yet.
}

void WiFiManager::startAccessPoint()
{
    WiFi.mode(WIFI_AP_STA);

    uint64_t chipId = ESP.getEfuseMac();

    char ssid[32];

    snprintf(
        ssid,
        sizeof(ssid),
        "SerialMoistureReader-%04X",
        (uint16_t)(chipId & 0xFFFF)
    );

    Serial.println();
    Serial.println("Starting Access Point...");
    Serial.print("SSID: ");
    Serial.println(ssid);

    if (WiFi.softAP(ssid))
    {
        Serial.println("Access Point started.");
        Serial.print("AP IP Address: ");
        Serial.println(WiFi.softAPIP());
    }
    else
    {
        Serial.println("Failed to start Access Point!");
    }
}