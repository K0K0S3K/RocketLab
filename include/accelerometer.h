#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>

namespace ADXL {

// Deklaracje - mówimy kompilatorowi: "Gdzieś tam jest taki obiekt"
extern Adafruit_ADXL345_Unified accel;
extern const int numReadings;
extern float readingsX[], readingsY[], readingsZ[];
extern int readIndex;
extern float sumX, sumY, sumZ;

struct accelerometerData
{
    float x;
    float y;
    float z;

    accelerometerData(float X = 0, float Y = 0, float Z = 0) : x(X), y(Y), z(Z) {};
};

//Funkcje
void initAccelerometer();
accelerometerData getAccelerometerData();
void rollingAvg(accelerometerData &data);
void printAccelerometerData();
void initRollingAvg();
//Koniec

}
#endif