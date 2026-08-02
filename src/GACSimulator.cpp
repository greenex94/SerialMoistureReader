#include "GACSimulator.h"

HardwareSerial SimSerial(1);


void GACSimulator::begin()
{
    Serial.println("Starting GAC Simulator...");

    // UART1
    // TX = GPIO25
    SimSerial.begin(
        1200,
        SERIAL_8N1,
        -1,
        25
    );
}


void GACSimulator::update()
{
    if (millis() - lastSend > 10000)
    {
        lastSend = millis();

        Serial.println("Sending simulated GAC ticket...");

        SimSerial.println();
        SimSerial.println("DICKEY-john Corp.");
        SimSerial.println("    GAC 500XT");
        SimSerial.println();
        SimSerial.println("S/N: 50960");
        SimSerial.println();
        SimSerial.println("Wheat SRW");
        SimSerial.println("070327N");
        SimSerial.println();

        SimSerial.println("Moist.:");
        SimSerial.println("    12.5 %");
        SimSerial.println();

        SimSerial.println("TW:");
        SimSerial.println("    60.5 lb/Bu");
        SimSerial.println();

        SimSerial.println("Temp.:");
        SimSerial.println("    101.3 F");

        SimSerial.println("=================");
        SimSerial.println();
    }
}