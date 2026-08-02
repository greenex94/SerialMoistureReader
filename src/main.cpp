#include <Arduino.h>

#include "WiFiManager.h"
#include "WebPortal.h"

#include <Preferences.h>

WiFiManager wifi;
WebPortal portal;

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" Serial Moisture Reader");
    Serial.println("==============================");

    Preferences prefs;

    prefs.begin("wifi", true);

    String ssid = prefs.getString("ssid", "");
    String password = prefs.getString("password", "");

    prefs.end();

    Serial.println("Stored WiFi credentials:");

    Serial.print("SSID: ");
    Serial.println(ssid);

    Serial.print("Password: ");
    Serial.println(password);

    wifi.begin();

    portal.begin();
}

void loop()
{
    wifi.update();
    portal.update();
}