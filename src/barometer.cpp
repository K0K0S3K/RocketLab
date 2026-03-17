#include "barometer.h"

namespace BMP
{

    Adafruit_BMP280 bmp = Adafruit_BMP280();

    const int numReadings = 10;
    float pressureReadings[numReadings];
    int readIndex = 0;
    float pressureMean = 0;

    void initBarometer()
    {
        while (!bmp.begin(0x76))
        {
            Serial.println("Nie wykryto BMP280");
            delay(10);
        }

        initRollingAvg();
    }

    void rollingAvg(barometerData &data)
    {
        pressureMean -= pressureReadings[readIndex];

        pressureReadings[readIndex] = data.pressure;

        pressureMean += pressureReadings[readIndex];

        readIndex = (readIndex + 1) % numReadings;
    }

    void initRollingAvg()
    {
        for (int i = 0; i < numReadings; ++i)
        {
            pressureReadings[i] = 0;
        }

        for (int i = 0; i < numReadings; ++i)
        {
            barometerData data = getBarometerData();
            rollingAvg(data);
        }
    }

    float groundPressure = 0;

    void calibrateBarometer()
    {

        for(int i = 0; i < 50; ++i)
        {
            barometerData data = getBarometerData();
            delay(500);
        }

        for (int i = 0; i < 30; ++i)
        {
            groundPressure += bmp.readPressure();
            delay(500);
        }

        groundPressure = (groundPressure / 100.0) / 30.0;
    }

    void printBarometerData()
    {
        barometerData data = getBarometerData();
        
        Serial.print(data.pressure);
        Serial.print(" hPa, ");
        Serial.print(data.altitude);
        Serial.print(" m, ");
        Serial.print(data.temperature);
        Serial.println(" °C");
    }

    void setupHighPrecisionBMP(Adafruit_BMP280 &bmp)
    {
        bmp.setSampling(
            Adafruit_BMP280::MODE_NORMAL,  
            Adafruit_BMP280::SAMPLING_X1,  
            Adafruit_BMP280::SAMPLING_X16, 
            Adafruit_BMP280::FILTER_X16,   
            Adafruit_BMP280::STANDBY_MS_250);

        Serial.println("BMP280: Tryb Ultra High Resolution aktywowany.");

    }

    float readAltitude(float zeroLevelhPa)
    {
        float altitude;

        float pressure = pressureMean / (float)numReadings;

        altitude = 44330 * (1.0 - pow(pressure / zeroLevelhPa, 0.1903));

        return altitude;
    }

    barometerData getBarometerData()
    {
        barometerData data = barometerData(bmp.readPressure() / 100.0, bmp.readTemperature(), readAltitude(groundPressure));

        rollingAvg(data);

        return data;
    }

}