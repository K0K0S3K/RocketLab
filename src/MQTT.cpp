#include "MQTT.h"

namespace MQTT
{

    const char* ssid = "Router"; //nazwa twojej sieci
    const char* password = "123456789"; //hasło do sieci

    const char* mqtt_server = "10.89.187.141"; //adres brokera mqtt

    WiFiClient espClient;
    PubSubClient client(espClient);

    unsigned long lastMsg = 0;

    void setup_wifi() {
        delay(10);
        Serial.println("Łączenie z WiFi...");
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
        }
        Serial.println("\nWiFi połączone. Adres IP: ");
        Serial.println(WiFi.localIP());
    }

    void reconnect() {
        while (!client.connected()) {
            Serial.print("Próba połączenia MQTT...");
            if (client.connect("ESP32_BlackBox_001")) {
                Serial.println("połączono");
            } else {
                Serial.print("błąd, rc=");
                Serial.print(client.state());
                delay(2000);
            }
        }
    }
}