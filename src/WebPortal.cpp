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


    page += "<html>";
    page += "<head>";
    page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    page += "<title>Serial Moisture Reader</title>";
    page += "</head>";

    page += "<body>";

    page += "<h1>Serial Moisture Reader</h1>";

    page += "<h2>Queue</h2>";


    if (moistureQueue != nullptr)
    {
        page += "<p>Pending samples: ";
        page += String(moistureQueue->getQueueCount());
        page += "</p>";

        page += "<hr>";

        page += moistureQueue->getQueueContents();
    }
    else
    {
        page += "Queue unavailable";
    }


    page += "</body>";
    page += "</html>";


    server->send(
        200,
        "text/html",
        page
    );
}