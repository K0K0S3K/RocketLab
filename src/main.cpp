#include <Wire.h>
#include <accelerometer.h>
#include <barometer.h>
#include <SPI.h>
#include <SD.h>
#include <MQTT.h>


void setup(void) 
{
    Wire.begin(21,22);
    Serial.begin(115200);

    /*while (!SD.begin(5)) {
        Serial.println("Błąd: Nie wykryto karty SD!");
        delay(10);
    }

    Serial.println("Zainicjalizowana kartę SD");
    delay(5000);
    */

    ADXL::initAccelerometer();
    BMP::initBarometer();
    BMP::setupHighPrecisionBMP(BMP::bmp);
    BMP::calibrateBarometer();

    MQTT::setup_wifi();
    MQTT::client.setServer(MQTT::mqtt_server, 1883);

    
}



void mergeDataToJSON(char jsonBuffer[256], size_t size)
{
    ADXL::accelerometerData aData = ADXL::getAccelerometerData();
    BMP::barometerData bData = BMP::getBarometerData();

    float vectorSum = sqrt(aData.x * aData.x + aData.y * aData.y + aData.z * aData.z);
    
    snprintf(jsonBuffer, size,
        "{"
            "\"acc\":{"
                "\"x\":%.2f,"
                "\"y\":%.2f,"
                "\"z\":%.2f,"
                "\"total\":%.2f"
            "},"
            "\"press\":%.2f,"
            "\"temp\":%.2f"
           // "\"alt\":%.2f"
        "}",
        aData.x, aData.y, aData.z, vectorSum,
        bData.pressure, bData.temperature//, bData.altitude
    );
}

uint32_t lastRead = 0;
const uint64_t dTime = 1000;

void loop(void)
{

    uint32_t currentTime = millis();

    if (!MQTT::client.connected()) {
        MQTT::reconnect();
    }
    MQTT::client.loop();

    ADXL::accelerometerData data = ADXL::getAccelerometerData();
    ADXL::rollingAvg(data);

    if(currentTime - lastRead >= dTime)
    {
        lastRead = currentTime;
    
        char buffer[256]{};

        for(int i = 0; i < 256; ++i)
        {
            buffer[i] = ' ';
        }

        mergeDataToJSON(buffer,sizeof(buffer));

        MQTT::client.publish("esp32/data", buffer);

        for(int i = 0; i < 256; ++i)
        {
            if(buffer[i] == ' ')
            {
                Serial.println();
                break;
            }
            Serial.print(buffer[i]);
        }


    }

    
    
}
