#include "WebPortal.h"
#include <ESPmDNS.h>


void WebPortal::begin(MoistureQueue* queue)
{
    moistureQueue = queue;


    if (MDNS.begin("moisture"))
    {
        Serial.println("mDNS started.");
        Serial.println("Address: http://moisture.local");
    }
    else
    {
        Serial.println("mDNS failed.");
    }


    server = new WebServer(80);


    server->on("/", HTTP_GET, [this]()
    {
        handleRoot();
    });


    server->begin();


    Serial.println("Web portal started.");
}



void WebPortal::update()
{
    if (server != nullptr)
    {
        server->handleClient();
    }
}



void WebPortal::handleRoot()
{
    String page;


    page += "<!DOCTYPE html>";
    page += "<html>";

    page += "<head>";

    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<meta http-equiv='refresh' content='10'>";

    page += "<title>Serial Moisture Reader</title>";


    page += "<style>";

    page += "body {";
    page += "font-family: Arial, sans-serif;";
    page += "margin:20px;";
    page += "background:#f2f2f2;";
    page += "}";


    page += ".card {";
    page += "background:white;";
    page += "padding:15px;";
    page += "border-radius:10px;";
    page += "margin-bottom:15px;";
    page += "}";


    page += "h1 {";
    page += "font-size:26px;";
    page += "}";


    page += "</style>";

    page += "</head>";



    page += "<body>";


    page += "<h1>Moisture Tester</h1>";



    page += "<div class='card'>";

    page += "<h2>Status</h2>";


    if (moistureQueue != nullptr)
    {
        page += "<p><b>Pending samples:</b> ";

        page += String(
            moistureQueue->getQueueCount()
        );

        page += "</p>";
    }
    else
    {
        page += "<p>Queue unavailable</p>";
    }



    page += "<p><b>Last received sample:</b><br>";

    if (moistureQueue != nullptr)
    {
        page += moistureQueue->getLastReceived();
    }
    else
    {
        page += "Unknown";
    }

    page += "</p>";



    page += "<p><b>Last Google upload:</b><br>";

    if (moistureQueue != nullptr)
    {
        page += moistureQueue->getLastUpload();
    }
    else
    {
        page += "Unknown";
    }

    page += "</p>";



    page += "<p><b>Auto refresh:</b> 10 seconds</p>";

    page += "</div>";




    page += "<div class='card'>";

    page += "<h2>Queue Data</h2>";


    if (moistureQueue != nullptr)
    {
        page += moistureQueue->getQueueContents();
    }
    else
    {
        page += "No queue data";
    }


    page += "</div>";



    page += "</body>";

    page += "</html>";



    server->send(
        200,
        "text/html",
        page
    );
}