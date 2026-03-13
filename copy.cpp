#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

struct accelerometerData
{
    float x;
    float y;
    float z;

    accelerometerData(float X, float Y, float Z) : x(X), y(Y), z(Z) {};
};

const int numReadings = 15; // Im więcej, tym "spokojniejszy" odczyt, ale wolniejsza reakcja
float readingsX[numReadings], readingsY[numReadings], readingsZ[numReadings];
int readIndex = 0;
float totalX = 0, totalY = 0, totalZ = 0;

void initAccelerometer();
accelerometerData getAccelerometerData();

void setup(void) 
{

    Wire.begin(21,22);
    Serial.begin(115200);

    initAccelerometer();
}

uint32_t lastRead = 0;
const uint64_t dTime = 1000;

void loop(void)
{

    
}

void initAccelerometer()
{
    while(!accel.begin(0x1D))
    {
        /* There was a problem detecting the ADXL345 ... check your connections */
        Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
        delay(10);
    }
}

accelerometerData getAccelerometerData()
{
    const float scaleX = 0.9604; //best 0.9595
    const float scaleY = 0.9566; //best 0.956661355
    const float scaleZ = 0.9751; //best 0.9704

    const float offsetX = 0.5701; //best 0.5400
    const float offsetY = 0.1397; //best 0.148329931
    const float offsetZ = 2.3834; //best 2.4903

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

    uint32_t currentTime = millis();

    if(currentTime - lastRead >= dTime)
    {
        lastRead = currentTime;

        accelerometerData data = getAccelerometerData();

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

    
}