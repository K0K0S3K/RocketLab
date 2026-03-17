#ifndef MQTT_h
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

namespace MQTT
{
    extern const char* ssid;
    extern const char* password;
    extern const char* mqtt_server;

    extern WiFiClient espClient;
    extern PubSubClient client;

    extern unsigned long lastMsg;

    void setup_wifi();
    void reconnect();


}


#endif