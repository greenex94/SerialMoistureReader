#include "GoogleSheets.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>


void GoogleSheets::begin()
{
    Serial.println("Google Sheets uploader ready.");
}


bool GoogleSheets::upload(MoistureReading reading)
{
    if (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("Google upload skipped - WiFi disconnected.");
        return false;
    }

    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient http;

    Serial.println("Uploading to Google Sheets...");

    if (!http.begin(client, scriptURL))
    {
        Serial.println("HTTP begin failed.");
        return false;
    }

    http.addHeader("Content-Type", "application/json");

    String payload;

    payload += "{";
    payload += "\"timestamp\":\"" + reading.timestamp + "\",";
    payload += "\"crop\":\"" + reading.crop + "\",";
    payload += "\"moisture\":" + String(reading.moisture, 2) + ",";
    payload += "\"testWeight\":" + String(reading.testWeight, 2) + ",";
    payload += "\"temperature\":" + String(reading.temperature, 2);
    payload += "}";

    Serial.println(payload);

    int response = http.POST(payload);

    Serial.print("Google response: ");
    Serial.println(response);

    if (response == 200)
    {
        Serial.println("Uploaded to Google Sheets.");
        http.end();
        return true;
    }

    if (response == 302)
    {
        Serial.println("Upload accepted (HTTP 302).");
        http.end();
        return true;
    }

    Serial.println("Upload failed.");

    http.end();
    return false;
}