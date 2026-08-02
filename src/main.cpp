#include <Arduino.h>
#include "WiFiManager.h"

WiFiManager wifi;

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("=================================");
    Serial.println(" Serial Reader Starting");
    Serial.println("=================================");

    wifi.begin();
}

void loop()
{
    wifi.update();
}