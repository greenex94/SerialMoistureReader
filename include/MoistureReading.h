#pragma once

#include <Arduino.h>


struct MoistureReading
{
    String timestamp;

    String crop;
    String sampleId;

    float moisture = 0.0;
    float testWeight = 0.0;
    float temperature = 0.0;

    bool uploaded = false;
};