#include "barometer.h"

namespace BMP{

Adafruit_BMP280 bmp;

const int numReadings = 20; 
double pressureReadings[numReadings];
int readIndex = 0;
double pressureMean = 0;

void initBarometer()
{
    while(!bmp.begin(0x76))
    {
        Serial.println("Ooops, no BMP280 detected ... Check your wiring!");
        delay(10);
    }
}

void rollingAvg()
{
    pressureMean -= pressureReadings[numReadings];

    pressureReadings[numReadings] = bmp.readPressure();

    pressureMean += pressureReadings[numReadings];

    readIndex = (readIndex + 1) % numReadings;
}

double groundPressure = 0;

void calibrateBarometer()
{
    for(int i = 0; i < 15; ++i)
    {
        groundPressure += bmp.readPressure();
        delay(1000);
    }

    groundPressure = (groundPressure / 100.0) / 15.0;
}

void printBarometerData()
{
    //Serial.print(bmp.readPressure() / 100.0);
    //Serial.print(",");
    rollingAvg();
    Serial.print(pressureMean / (double)numReadings);
    Serial.print(",");
    Serial.println(bmp.readTemperature());
}

void setupHighPrecisionBMP(Adafruit_BMP280 &bmp) {
  // Dokumentacja zaleca tryb "Ultra High Resolution" dla najwyższej dokładności[cite: 192].
  // Konfigurujemy parametry zgodnie z tabelą 7 (Indoor navigation/Elevator)[cite: 326].

  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,     /* Tryb pracy: Normal (ciągły pomiar) [cite: 181] */
    Adafruit_BMP280::SAMPLING_X2,     /* Oversampling Temp: x2 (17 bit) [cite: 273, 290] */
    Adafruit_BMP280::SAMPLING_X16,    /* Oversampling Ciśnienia: x16 (20 bit)  */
    Adafruit_BMP280::FILTER_X16,      /* Filtr IIR: współczynnik 16 (najsilniejszy) [cite: 317] */
    Adafruit_BMP280::STANDBY_MS_500
  );
  
  Serial.println("BMP280: Tryb Ultra High Resolution aktywowany.");
}

}