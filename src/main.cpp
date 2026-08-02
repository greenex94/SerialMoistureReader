#include <Arduino.h>
#include "WiFiManager.h"
#include "WebPortal.h"
#include "GACReader.h"
#include "GACSimulator.h"
#include "TimeManager.h"

TimeManager timeManager;
WiFiManager wifi;
WebPortal portal;
GACReader gacReader;
GACSimulator gacSimulator;

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

    gacReader.begin(&timeManager);
    gacSimulator.begin();
    timeManager.begin();
}


void loop()
{
    wifi.update();

    portal.update();

    gacReader.update();
    gacSimulator.update();
}