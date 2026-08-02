#include <Arduino.h>

#include "WiFiManager.h"
#include "WebPortal.h"

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


    wifi.begin();


    if (!wifi.isConnected())
    {
        portal.begin();
    }
}


void loop()
{
    wifi.update();

    portal.update();
}