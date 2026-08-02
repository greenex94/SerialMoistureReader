#include "TimeManager.h"

#include <time.h>


void TimeManager::begin()
{
    Serial.println("Starting time synchronization...");

    // Central US timezone with daylight saving
    configTime(
        -6 * 3600,
        3600,
        "pool.ntp.org",
        "time.nist.gov"
    );


    struct tm timeinfo;

    Serial.print("Waiting for NTP");

    while (!getLocalTime(&timeinfo))
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println();

    Serial.println("Time synchronized!");

    Serial.println(getTimestamp());

    synced = true;
}


String TimeManager::getTimestamp()
{
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        return "NO_TIME";
    }


    char buffer[32];

    strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%d %H:%M:%S",
        &timeinfo
    );


    return String(buffer);
}