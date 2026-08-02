#include "WiFiManager.h"


void WiFiManager::begin()
{
    if (setupButtonPressed())
    {
        startAccessPoint();
        return;
    }

    loadCredentials();

    if (ssid.length() > 0)
    {
        if (connectToWiFi())
        {
            connected = true;
            return;
        }
    }

    startAccessPoint();
}


void WiFiManager::update()
{
    // Future reconnect logic will go here.
}


bool WiFiManager::isConnected()
{
    return connected;
}


void WiFiManager::loadCredentials()
{
    preferences.begin("wifi", true);

    ssid = preferences.getString("ssid", "");
    password = preferences.getString("password", "");

    preferences.end();

    Serial.println("Loaded WiFi credentials:");

    Serial.print("SSID length: ");
    Serial.println(ssid.length());

}


bool WiFiManager::connectToWiFi()
{
    Serial.println();
    Serial.println("Connecting to WiFi...");
    Serial.println(ssid);

    WiFi.disconnect(true);
    delay(500);

    WiFi.mode(WIFI_STA);

    WiFi.begin(
        ssid.c_str(),
        password.c_str()
    );

    unsigned long startTime = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");

        if (millis() - startTime > 20000)
        {
            Serial.println();
            Serial.println("WiFi connection failed.");

            Serial.print("WiFi status code: ");
            Serial.println(WiFi.status());

            return false;
        }
    }

    Serial.println();
    Serial.println("WiFi connected!");

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    return true;
}


void WiFiManager::startAccessPoint()
{
    WiFi.mode(WIFI_AP_STA);

    uint64_t chipId = ESP.getEfuseMac();

    char apName[32];

    snprintf(
        apName,
        sizeof(apName),
        "SerialMoistureReader-%04X",
        (uint16_t)(chipId & 0xFFFF)
    );


    Serial.println();
    Serial.println("Starting Access Point...");

    Serial.print("SSID: ");
    Serial.println(apName);


    if (WiFi.softAP(apName))
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

bool WiFiManager::setupButtonPressed()
{
    pinMode(0, INPUT_PULLUP);

    Serial.println("Checking setup button...");

    unsigned long start = millis();

    while (millis() - start < 3000)
    {
        if (digitalRead(0) == LOW)
        {
            Serial.println("Setup button pressed.");
            return true;
        }

        delay(50);
    }

    return false;
}