# ESP32 Telemetry System 🚀

System zbierania i przesyłania danych telemetrycznych w czasie rzeczywistym. Projekt stworzony na potrzeby rekrutacji do koła **PUT RocketLab** - aby sprawdzić się w pracy z wymienionymi w formularzu rekrutacyjnym technologiami.

## 📋 Opis Projektu
Głównym zadaniem aplikacji jest agregacja danych z czujników pokładowych i ich bezprzewodowa transmisja za pośrednictwem protokołu **MQTT**.

## ✨ Kluczowe Funkcjonalności
* **Real-time Telemetry:** Przesyłanie danych w formacie JSON do brokera MQTT.
* **Signal Filtering:** Implementacja cyfrowego przetwarzania sygnałów w celu redukcji szumów.

## 🛠 Stos Technologiczny & Komunikacja
* **Hardware:** ESP32, BMP280, ADXL345.
* **Język:** C++.
* **Protokół:** MQTT (PubSubClient).
* **Magistrala I2C (Inter-Integrated Circuit):** * Wszystkie sensory (BMP280, ADXL345) komunikują się z jednostką centralną za pomocą magistrali I2C.
    * Wykorzystanie wspólnej linii SDA/SCL pozwala na minimalizację okablowania przy zachowaniu pełnej adresowalności urządzeń.
    * Implementacja obejmuje sprawdzanie dostępności urządzeń na magistrali przy starcie systemu.

## 📊 Przetwarzanie Danych: Średnia Krocząca
W celu zapewnienia wiarygodności telemetrii, projekt wykorzystuje algorytm **prostej średniej kroczącej (Simple Moving Average - SMA)**. 

**Zastosowanie filtra pozwala na:**
* **Redukcję szumu:** Wyeliminowanie zakłóceń pomiarowych.
* **Stabilizację odczytów:** Wygładzenie wykresów wysokości i przyspieszenia.
* **Optymalizację:** Algorytm działa w oparciu o bufor kołowy, co zapewnia stałą złożoność obliczeniową $O(1)$ dla każdego nowego pomiaru.

## ⚙️ Sensory
* **BMP280:** Precyzyjne pomiary ciśnienia atmosferycznego i temperatury.
* **ADXL345:** 3-osiowy akcelerometr do monitorowania przeciążeń i orientacji rakiety.

## 🚀 Szybki Start

### Wymagania
* **Środowisko:** PlatformIO.
* **Biblioteki:** `PubSubClient`, `Adafruit BMP280`, `Adafruit ADXL345`.
 ### Instalacja

   ```bash

   1. git clone https://github.com/K0K0S3K/RocketLab

   2. Skonfiguruj dane dostępowe w pliku src/MQTT.cpp (SSID, Hasło, Broker IP).

   3. Skompiluj i wgraj program na mikrokontroler
