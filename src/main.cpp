#include <Wire.h>
#include <accelerometer.h>
#include <barometer.h>



void setup(void) 
{
    Wire.begin(21,22);
    Serial.begin(115200);

    ADXL::initAccelerometer();
    BMP::initBarometer();
    BMP::setupHighPrecisionBMP(BMP::bmp);
    BMP::calibrateBarometer();
}

uint32_t lastRead = 0;
const uint64_t dTime = 1000;

void loop(void)
{

    uint32_t currentTime = millis();

    ADXL::accelerometerData data = ADXL::getAccelerometerData();
    rollingAvg(data);

    if(currentTime - lastRead >= dTime)
    {
        lastRead = currentTime;
        //printAccelerometerData();

        BMP::printBarometerData();

    }

    
    
}
