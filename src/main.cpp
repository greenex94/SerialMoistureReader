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
unsigned long lastQueueCheck = 0;

const unsigned long QUEUE_CHECK_INTERVAL = 1000;

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


    googleSheets.begin();
    //gacSimulator.begin();
    

    moistureQueue.printQueue();
}

void processQueue()
{
    if (!moistureQueue.hasItems())
    {
        return;
    }


    Serial.println("Processing queued samples...");


    int uploadedCount = 0;


    while (moistureQueue.hasItems())
    {
        MoistureReading reading;


        if (!moistureQueue.peek(reading))
        {
            break;
        }


        Serial.println("Uploading queued sample:");
        Serial.println(reading.timestamp);


        bool uploaded = googleSheets.upload(reading);


        if (uploaded)
        {
            moistureQueue.pop();

            uploadedCount++;

            Serial.println("Queued sample removed.");
        }
        else
        {
            Serial.println("Upload failed. Leaving queue intact.");

            break;
        }


        delay(250);
    }


    if (uploadedCount > 0)
    {
        Serial.print("Uploaded queued samples: ");
        Serial.println(uploadedCount);
    }
}

void loop()
{
    wifi.update();

    portal.update();

    gacReader.update();

    //gacSimulator.update();



    if (millis() - lastQueueCheck > QUEUE_CHECK_INTERVAL)
    {
        lastQueueCheck = millis();

        processQueue();
    }
}