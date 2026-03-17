#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

namespace BMP
{

    struct barometerData
    {
        float pressure;
        float temperature;
        float altitude;

        barometerData(float p = 0, float t = 0, float a = 0) : pressure(p), temperature(t),altitude(a) {} 
    };

    extern Adafruit_BMP280 bmp;
    extern float groundPressure;

    extern const int numReadings;
    extern float pressureReadings[];
    extern int readIndex;
    extern float pressureMean;

    void initBarometer();
    void printBarometerData();
    void calibrateBarometer();
    void setupHighPrecisionBMP(Adafruit_BMP280 &bmp);
    void rollingAvg(barometerData &data);
    float readAltitude(float zeroLevelhPa);
    void initRollingAvg();
    barometerData getBarometerData();

}
#endif