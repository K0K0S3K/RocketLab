# Telemetry System 🚀

System zbierania i przesyłania danych telemetrycznych w czasie rzeczywistym, zaprojektowany z myślą o monitorowaniu parametrów lotu rakiet sondujących. Projekt stworzony na potrzeby rekrutacji do koła PUT RocketLab - aby sprawdzić się w pracy z technologiami wymienionymi w formularzu rekrutacyjny.

## 📋 Opis Projektu
Głównym zadaniem aplikacji jest agregacja danych z czujników pokładowych (ciśnienie, temperatura, orientacja) i ich bezprzewodowa transmisja do stacji naziemnej za pośrednictwem protokołu **MQTT**.



## ✨ Kluczowe Funkcjonalności
* **Real-time Telemetry:** Przesyłanie danych w formacie JSON do brokera MQTT.
* **Modular Sensor Interface:** Abstrakcja warstwy czujników pozwalająca na łatwą rozbudowę.

## 🛠 Stos Technologiczny
* **Hardware:** ESP32.
* **Język:** C++.
* **Protokół:** MQTT (PubSubClient).
* **Sensory:** BMP280 (ciśnienie/wysokość), ADXL345 (akcelerometr).

## 🚀 Szybki Start

### Wymagania
* PlatformIO.
* Biblioteki: `PubSubClient`, `Adafruit BMP280`, `ArduinoJson`.

### Instalacja
1. Sklonuj repozytorium:
   ```bash
   git clone [https://github.com/K0K0S3K/RocketLab.git](https://github.com/K0K0S3K/RocketLab.git)
