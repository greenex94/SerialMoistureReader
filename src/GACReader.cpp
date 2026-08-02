#include "GACReader.h"
#include "GoogleSheets.h"

HardwareSerial GACSerial(2);


void GACReader::begin(
    TimeManager* tm,
    MoistureQueue* queue,
    GoogleSheets* sheets
)
{
    timeManager = tm;
    moistureQueue = queue;
    googleSheets = sheets;

    Serial.println("Starting GAC Reader...");

    GACSerial.begin(
        1200,
        SERIAL_8N1,
        16,
        17
    );
}


void GACReader::update()
{
    while (GACSerial.available())
    {
        char c = GACSerial.read();

        Serial.write(c);

        buffer += c;

        if (buffer.length() > 500)
        {
            Serial.println();
            Serial.println("BUFFER OVERFLOW - RESETTING");
            buffer = "";
        }


        // Detect end of GAC ticket
        if (buffer.indexOf("=================") >= 0)
        {
            Serial.println();
            Serial.println("---- COMPLETE TICKET ----");


            MoistureReading reading;

            if (timeManager != nullptr)
            {
                reading.timestamp = timeManager->getTimestamp();
            }
            else
            {
                reading.timestamp = "NO_TIME";
            }

            if (parser.parse(buffer, reading))
            {
                Serial.println();
                Serial.println("Parsed Reading:");
                
                Serial.print("Timestamp: ");
                Serial.println(reading.timestamp);

                Serial.print("Crop: ");
                Serial.println(reading.crop);

                Serial.print("Moisture: ");
                Serial.println(reading.moisture);

                Serial.print("Test Weight: ");
                Serial.println(reading.testWeight);

                Serial.print("Temperature: ");
                Serial.println(reading.temperature);

                if (moistureQueue != nullptr)
                {
                    if (googleSheets != nullptr)
                    {
                        if (googleSheets->upload(reading))
                        {
                            Serial.println("Uploaded to Google Sheets.");
                        }
                        else
                        {
                            Serial.println("Google upload failed. Saving locally.");
                            moistureQueue->add(reading);
                        }
                    }
                    else
                    {
                        moistureQueue->add(reading);
                    }
                }
            }


            // Clear for next ticket
            buffer = "";
        }
    }
}