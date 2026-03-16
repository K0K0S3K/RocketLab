#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>

namespace BMP {

extern Adafruit_BMP280 bmp;
extern double groundPressure;

extern const int numReadings;
extern double pressureReadings[];
extern int readIndex;
extern double pressureMean;

void initBarometer();
void printBarometerData();
void calibrateBarometer();
void setupHighPrecisionBMP(Adafruit_BMP280 &bmp);
}
#endif