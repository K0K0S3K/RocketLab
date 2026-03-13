#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

float dx = 0;
float dy = 0;
float dz = 0;

float scaleX = 0.9595; //best 0.9595
float scaleY = 0.956661355;
float scaleZ = 0.9704;

float offsetX = 0.5400; //best 0.5400
float offsetY = 0.148329931;
float offsetZ = 2.4903;


void initAccelerometer();
void calibrateAccelerometer(float &dx, float &dy, float &dz);

void setup(void) 
{

    Wire.begin(21,22);

    Serial.begin(115200);
    Serial.println("ADXL345 Accelerometer Calibration"); 
    Serial.println("");
    
    initAccelerometer();
}

uint32_t lastRead = 0;
const uint64_t dTime = 1000;

void loop(void)
{

    uint32_t currentTime = millis();

    if(currentTime - lastRead >= dTime)
    {
        lastRead = currentTime;

        sensors_event_t accelEvent;  

        accel.getEvent(&accelEvent);

        Serial.print("x : ");
        Serial.print((((accelEvent.acceleration.x - offsetX) * scaleX)));
        Serial.print(" m/s^2 | ");
        Serial.print("y : ");
        Serial.print((((accelEvent.acceleration.y - offsetY) * scaleY)));
        Serial.print(" m/s^2 | ");
        Serial.print("z : ");
        Serial.print(((accelEvent.acceleration.z - offsetZ) * scaleZ));
        Serial.println(" m/s^2");
        Serial.print("Sum");
        Serial.println(abs(((accelEvent.acceleration.y - offsetY) * scaleY)) + abs(((accelEvent.acceleration.x - offsetX) * scaleX)) + abs((accelEvent.acceleration.z - offsetZ) * scaleZ));

        /*
        Serial.print("x : ");
        Serial.print(dx);
        Serial.print(" m/s^2 | ");
        Serial.print("y : ");
        Serial.print(dy);
        Serial.print(" m/s^2 | ");
        Serial.print("z : ");
        Serial.print(dz);
        Serial.println(" m/s^2");
        */
    }

    
}

void initAccelerometer()
{
    /* Initialise the sensor */
    while(!accel.begin(0x1D))
    {
        /* There was a problem detecting the ADXL345 ... check your connections */
        Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
        delay(10);
    }

    calibrateAccelerometer(dx,dy,dz);
}

void calibrateAccelerometer(float &deltax, float &deltay, float &deltaz)
{
    Serial.println("Calibrating accelerometer");

    const int nSteps = 1000;

    deltax = 0;
    deltay = 0;
    deltaz = 0;

    sensors_event_t accelEvent;  

    for(int step = 0; step < nSteps; ++step)
    {
        accel.getEvent(&accelEvent);

        deltax += ((accelEvent.acceleration.x - offsetX) * scaleX);
        deltay += ((accelEvent.acceleration.y - offsetY) * scaleY);
        deltaz += ((accelEvent.acceleration.z - offsetZ) * scaleZ);
        delay(10);
    }

    deltax = deltax / (float)nSteps;
    deltay = deltay / (float)nSteps;
    deltaz = deltaz / (float)nSteps;

}

void printAccelerometerData(float data, float delta)
{

}