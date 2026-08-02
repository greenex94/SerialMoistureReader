#include <Arduino.h>
#include "WiFiManager.h"
#include "WebPortal.h"
#include "GACReader.h"
#include "GACSimulator.h"
#include "TimeManager.h"
#include "MoistureQueue.h"
#include <ESPmDNS.h>
#include "GoogleSheets.h"

TimeManager timeManager;
WiFiManager wifi;
WebPortal portal;
GACReader gacReader;
GoogleSheets googleSheets;
GACSimulator gacSimulator;
MoistureQueue moistureQueue;

void setup()
{
    Serial.begin(115200);

    delay(1000);

    Serial.println();
    Serial.println("==============================");
    Serial.println(" Serial Moisture Reader");
    Serial.println("==============================");


    wifi.begin();


    timeManager.begin();


    moistureQueue.begin();


    portal.begin(
        &moistureQueue
    );


    gacReader.begin(
        &timeManager,
        &moistureQueue,
        &googleSheets
    );


    gacSimulator.begin();
    googleSheets.begin();

    moistureQueue.printQueue();
}


void loop()
{
    wifi.update();

    portal.update();

    gacReader.update();
    gacSimulator.update();
}