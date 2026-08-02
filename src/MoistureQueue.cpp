#include "MoistureQueue.h"

#include <LittleFS.h>


bool MoistureQueue::begin()
{
    Serial.println("Starting LittleFS...");

    if (!LittleFS.begin(true))
    {
        Serial.println("LittleFS mount failed!");
        return false;
    }

    Serial.println("LittleFS mounted.");

    return true;
}



bool MoistureQueue::add(MoistureReading reading)
{
    File file = LittleFS.open(
        filename,
        FILE_APPEND
    );


    if (!file)
    {
        Serial.println("Failed to open queue file");
        return false;
    }


    String json = readingToJson(reading);

    file.println(json);

    file.close();


    Serial.println("Reading added to queue:");
    Serial.println(json);


    return true;
}



String MoistureQueue::readingToJson(MoistureReading reading)
{
    String json = "{";

    json += "\"timestamp\":\"";
    json += reading.timestamp;
    json += "\",";


    json += "\"crop\":\"";
    json += reading.crop;
    json += "\",";


    json += "\"moisture\":";
    json += String(reading.moisture, 2);
    json += ",";


    json += "\"testWeight\":";
    json += String(reading.testWeight, 2);
    json += ",";


    json += "\"temperature\":";
    json += String(reading.temperature, 2);


    json += "}";


    return json;
}



void MoistureQueue::printQueue()
{
    File file = LittleFS.open(
        filename,
        FILE_READ
    );


    if (!file)
    {
        Serial.println("Queue empty.");
        return;
    }


    Serial.println();
    Serial.println("===== QUEUE =====");


    while (file.available())
    {
        Serial.write(file.read());
    }


    file.close();


    Serial.println();
    Serial.println("=================");
}

String MoistureQueue::getQueueContents()
{
    File file = LittleFS.open(
        filename,
        FILE_READ
    );


    if (!file)
    {
        return "Queue empty";
    }


    String contents;


    while (file.available())
    {
        contents += file.readStringUntil('\n');
        contents += "<br>";
    }


    file.close();

    return contents;
}



int MoistureQueue::getQueueCount()
{
    File file = LittleFS.open(
        filename,
        FILE_READ
    );


    if (!file)
    {
        return 0;
    }


    int count = 0;


    while (file.available())
    {
        file.readStringUntil('\n');
        count++;
    }


    file.close();

    return count;
}