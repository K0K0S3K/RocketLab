#include <Wire.h>
#include <accelerometer.h>

void setup(void) 
{
    Wire.begin(21,22);
    Serial.begin(115200);

    initAccelerometer();
}

uint32_t lastRead = 0;
const uint64_t dTime = 100;

void loop(void)
{

    uint32_t currentTime = millis();

    accelerometerData data = getAccelerometerData();
    rollingAvg(data);

    if(currentTime - lastRead >= dTime)
    {
        lastRead = currentTime;
        printAccelerometerData();
    }

    
    
}

