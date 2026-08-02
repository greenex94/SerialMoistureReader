#include "WebPortal.h"
#include <Preferences.h>

void WebPortal::begin()
{
    server = new WebServer(80);

    server->on("/", [this]()
    {
        handleRoot();
    });

    server->on("/save", HTTP_POST, [this]()
    {
        handleSave();
    });

    server->onNotFound([this]()
    {
        handleNotFound();
    });

    server->begin();

    Serial.println("Web portal started.");
}


void WebPortal::update()
{
    if (server)
    {
        server->handleClient();
    }
}


void WebPortal::handleRoot()
{
    String html = R"rawliteral(
<!DOCTYPE html>
<html>

<head>
<title>Serial Moisture Reader Setup</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>

<h2>Serial Moisture Reader Setup</h2>

<form method="POST" action="/save">

<label>WiFi SSID</label><br>
<input type="text" name="ssid"><br><br>

<label>Password</label><br>
<input type="password" name="password"><br><br>

<input type="submit" value="Save">

</form>

</body>
</html>
)rawliteral";

    server->send(
        200,
        "text/html",
        html
    );
}


void WebPortal::handleSave()
{
    if (!server->hasArg("ssid") ||
        !server->hasArg("password"))
    {
        server->send(
            400,
            "text/plain",
            "Missing fields"
        );

        return;
    }

    String ssid = server->arg("ssid");
    String password = server->arg("password");

    Serial.println("Saving WiFi credentials:");
    Serial.println(ssid);

    Preferences preferences;

    preferences.begin("wifi", false);

    preferences.putString(
        "ssid",
        ssid
    );

    preferences.putString(
        "password",
        password
    );

    preferences.end();
        
    server->send(
        200,
        "text/html",
        "<h2>Saved!</h2><p>Reboot the device.</p>"
    );
}

void WebPortal::handleNotFound()
{
    server->send(
        404,
        "text/plain",
        "Not found"
    );
}