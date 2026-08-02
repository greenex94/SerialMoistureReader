#include "GACReader.h"

HardwareSerial GACSerial(2);


void GACReader::begin()
{
    Serial.println("Starting GAC Reader...");

    // UART2
    // RX = GPIO16
    // TX = GPIO17
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

        // Temporary ticket boundary detection
        if (buffer.endsWith("=================\n"))
        {
            Serial.println();
            Serial.println("---- COMPLETE TICKET ----");

            buffer = "";
        }
    }
}