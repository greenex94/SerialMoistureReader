#include "GACParser.h"

bool GACParser::parse(String ticket, MoistureReading &reading)
{
    Serial.println("Parsing GAC ticket...");

    int cropStart = ticket.indexOf("Wheat");

    if (cropStart >= 0)
    {
        int cropEnd = ticket.indexOf("\n", cropStart);

        reading.crop = ticket.substring(
            cropStart,
            cropEnd
        );

        reading.crop.trim();
    }


    int moisturePos = ticket.indexOf("Moist.");

    if (moisturePos >= 0)
    {
        String section = ticket.substring(
            moisturePos,
            moisturePos + 40
        );

        reading.moisture = extractNumber(section);
    }


    int twPos = ticket.indexOf("TW:");

    if (twPos >= 0)
    {
        String section = ticket.substring(
            twPos,
            twPos + 25
        );

        reading.testWeight = extractNumber(section);
    }


    int tempPos = ticket.indexOf("Temp.");

    if (tempPos >= 0)
    {
        String section = ticket.substring(
            tempPos,
            tempPos + 25
        );

        reading.temperature = extractNumber(section);
    }


    return true;
}


float GACParser::extractNumber(String text)
{
    String number;
    bool started = false;
    bool decimalFound = false;


    for (int i = 0; i < text.length(); i++)
    {
        char c = text[i];


        if (isdigit(c))
        {
            number += c;
            started = true;
        }
        else if (c == '.' && started && !decimalFound)
        {
            number += c;
            decimalFound = true;
        }
        else if (started)
        {
            // We already started a number,
            // and now hit a non-number character.
            break;
        }
    }


    Serial.print("Extracted number: ");
    Serial.println(number);


    return number.toFloat();
}