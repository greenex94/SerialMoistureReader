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



bool MoistureQueue::hasItems()
{
    File file = LittleFS.open(
        filename,
        FILE_READ
    );

    if (!file)
    {
        return false;
    }

    bool result = file.available();

    file.close();

    return result;
}



bool MoistureQueue::peek(MoistureReading &reading)
{
    File file = LittleFS.open(
        filename,
        FILE_READ
    );


    if (!file)
    {
        return false;
    }


    if (!file.available())
    {
        file.close();
        return false;
    }


    String line = file.readStringUntil('\n');

    file.close();


    return jsonToReading(
        line,
        reading
    );
}



bool MoistureQueue::pop()
{
    File source = LittleFS.open(
        filename,
        FILE_READ
    );


    if (!source)
    {
        return false;
    }


    String remaining;

    bool firstLine = true;


    while (source.available())
    {
        String line = source.readStringUntil('\n');


        if (firstLine)
        {
            firstLine = false;
            continue;
        }


        if (line.length() > 0)
        {
            remaining += line;
            remaining += "\n";
        }
    }


    source.close();


    File destination = LittleFS.open(
        filename,
        FILE_WRITE
    );


    if (!destination)
    {
        return false;
    }


    destination.print(remaining);

    destination.close();


    return true;
}



bool MoistureQueue::jsonToReading(
    String json,
    MoistureReading &reading
)
{
    int pos;


    pos = json.indexOf("\"timestamp\":\"");
    if (pos >= 0)
    {
        pos += 13;

        reading.timestamp =
            json.substring(
                pos,
                json.indexOf("\"", pos)
            );
    }


    pos = json.indexOf("\"crop\":\"");
    if (pos >= 0)
    {
        pos += 8;

        reading.crop =
            json.substring(
                pos,
                json.indexOf("\"", pos)
            );
    }


    pos = json.indexOf("\"moisture\":");
    if (pos >= 0)
    {
        pos += 11;

        reading.moisture =
            json.substring(
                pos,
                json.indexOf(",", pos)
            ).toFloat();
    }


    pos = json.indexOf("\"testWeight\":");
    if (pos >= 0)
    {
        pos += 13;

        reading.testWeight =
            json.substring(
                pos,
                json.indexOf(",", pos)
            ).toFloat();
    }


    pos = json.indexOf("\"temperature\":");
    if (pos >= 0)
    {
        pos += 14;

        reading.temperature =
            json.substring(
                pos,
                json.indexOf("}", pos)
            ).toFloat();
    }


    return true;
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

String MoistureQueue::getLastReceived()
{
    return lastReceived;
}


String MoistureQueue::getLastUpload()
{
    return lastUpload;
}


void MoistureQueue::setLastReceived(String timestamp)
{
    lastReceived = timestamp;
}


void MoistureQueue::setLastUpload(String timestamp)
{
    lastUpload = timestamp;
}