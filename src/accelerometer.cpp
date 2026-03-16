#include "accelerometer.h"

namespace ADXL {

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

//Dane dotyczące akcelerometru
const int numReadings = 15; // Im więcej, tym "spokojniejszy" odczyt, ale wolniejsza reakcja
float readingsX[numReadings], readingsY[numReadings], readingsZ[numReadings];
int readIndex = 0;
float sumX = 0, sumY = 0, sumZ = 0;
//Koniec

void initAccelerometer()
{
    while(!accel.begin(0x1D))
    {
        /* There was a problem detecting the ADXL345 ... check your connections */
        Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
        delay(10);
    }

    initRollingAvg();
}

void rollingAvg(accelerometerData &data)
{
    sumX -= readingsX[readIndex];
    sumY -= readingsY[readIndex];
    sumZ -= readingsZ[readIndex];

    readingsX[readIndex] = data.x;
    readingsY[readIndex] = data.y;
    readingsZ[readIndex] = data.z;

    sumX += readingsX[readIndex];
    sumY += readingsY[readIndex];
    sumZ += readingsZ[readIndex];

    readIndex = (readIndex + 1) % numReadings;

    accelerometerData avg;
    data.x = sumX / (float)numReadings;
    data.y = sumY / (float)numReadings;
    data.z = sumZ / (float)numReadings;

}



accelerometerData getAccelerometerData()
{
    const float scaleX = 0.9604; //best 0.9595
    const float scaleY = 0.9566; //best 0.956661355
    const float scaleZ = 0.9704; //best 0.9704, 0.9751

    const float offsetX = 0.5701; //best 0.5400
    const float offsetY = 0.1397; //best 0.148329931
    const float offsetZ = 2.4903; //best 2.4903, 2.3834

    sensors_event_t accelEvent;  

    accel.getEvent(&accelEvent);

    accelerometerData data(
        ((accelEvent.acceleration.x - offsetX) * scaleX),
        ((accelEvent.acceleration.y - offsetY) * scaleY),
        ((accelEvent.acceleration.z - offsetZ) * scaleZ)
    );

    return data;
}

void printAccelerometerData()
{

    accelerometerData data = getAccelerometerData();
    rollingAvg(data);

    float x = data.x;
    float y = data.y;
    float z = data.z;

    Serial.print("x : ");
    Serial.print(x);
    Serial.print(" m/s^2 | ");
    Serial.print("y : ");
    Serial.print(y);
    Serial.print(" m/s^2 | ");
    Serial.print("z : ");
    Serial.print(z);
    Serial.println(" m/s^2");
    Serial.print("Sum");

    float sum = sqrt(x * x + y * y + z * z);

    Serial.println(sum);
}

void initRollingAvg()
{

    for(int i = 0; i < numReadings; ++i)
    {
        readingsX[i] = 0;
        readingsY[i] = 0;
        readingsZ[i] = 0;
    }

    for(int i = 0; i < numReadings; ++i)
    {
        accelerometerData data = getAccelerometerData();
        rollingAvg(data);
    }

}
}