#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup(void) {
  Serial.begin(115200);
  if(!accel.begin(0x1D)) { // Sprawdź adres (0x53 lub 0x1D)
    Serial.println("Nie znaleziono ADXL345!");
    while(1);
  }
  
  float z_max = 0, z_min = 0, y_max = 0, y_min = 0, x_min = 0, x_max = 0;
  sensors_event_t event;

  // KROK 1: Pomiar Z-up
  Serial.println("KROK 1: Poloz sensor PLASKO na stole (Z skierowane do gory).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    z_max += event.acceleration.z;
    delay(10);
  }
  z_max /= 1000.0;
  Serial.print("Zmierzono Z_max: "); Serial.println(z_max);

  // KROK 2: Pomiar Z-down
  Serial.println("\nKROK 2: Obroc sensor O 180 STOPNI (Z skierowane w dol).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    z_min += event.acceleration.z;
    delay(10);
  }
  z_min /= 1000.0;
  Serial.print("Zmierzono Z_min: "); Serial.println(z_min);

  // KROK 1: Pomiar Y-up
  Serial.println("KROK 1: Poloz sensor BOKIEM na stole (Y skierowane do gory).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    y_max += event.acceleration.y;
    delay(10);
  }
  y_max /= 1000.0;
  Serial.print("Zmierzono Y_max: "); Serial.println(y_max);

  // KROK 2: Pomiar Y-down
  Serial.println("\nKROK 2: Obroc sensor O 180 STOPNI (Y skierowane w dol).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    y_min += event.acceleration.y;
    delay(10);
  }
  y_min /= 1000.0;
  Serial.print("Zmierzono Y_min: "); Serial.println(y_min);

  // KROK 1: Pomiar Z-up
  Serial.println("KROK 1: Poloz sensor DOŁEM na stole (X skierowane do gory).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    x_max += event.acceleration.x;
    delay(10);
  }
  x_max /= 1000.0;
  Serial.print("Zmierzono X_max: "); Serial.println(x_max);

  // KROK 2: Pomiar Z-down
  Serial.println("\nKROK 2: Obroc sensor O 180 STOPNI (X skierowane w dol).");
  Serial.println("Pomiar za 5 sekund...");
  delay(5000);
  for(int i=0; i<1000; i++) {
    accel.getEvent(&event);
    x_min += event.acceleration.x;
    delay(10);
  }
  x_min /= 1000.0;
  Serial.print("Zmierzono X_min: "); Serial.println(x_min);






  // OBLICZENIA
  float offsetZ = (z_max + z_min) / 2.0;
  float scaleZ = (2.0 * 9.80665) / (z_max - z_min);

  float offsetY = (y_max + y_min) / 2.0;
  float scaleY = (2.0 * 9.80665) / (y_max - y_min);

  float offsetX = (x_max + x_min) / 2.0;
  float scaleX = (2.0 * 9.80665) / (x_max - x_min);



  Serial.println("\n--- WYNIKI KALIBRACJI DLA OSI X ---");
  Serial.print("Offset X: "); Serial.println(offsetX, 4);
  Serial.print("Scale X:  "); Serial.println(scaleX, 4);
  Serial.println("-----------------------------------");

  Serial.println("\n--- WYNIKI KALIBRACJI DLA OSI Y ---");
  Serial.print("Offset Y: "); Serial.println(offsetY, 4);
  Serial.print("Scale Y:  "); Serial.println(scaleY, 4);
  Serial.println("-----------------------------------");

  Serial.println("\n--- WYNIKI KALIBRACJI DLA OSI Z ---");
  Serial.print("Offset Z: "); Serial.println(offsetZ, 4);
  Serial.print("Scale Z:  "); Serial.println(scaleZ, 4);
  Serial.println("-----------------------------------");


  Serial.println("Wpisz te wartosci do swojego glownego kodu.");
}

void loop() {}