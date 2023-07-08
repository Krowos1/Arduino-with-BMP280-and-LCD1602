#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// Инициализация объектов датчика BMP280 и экрана LCD 1602
Adafruit_BMP280 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2); // Адрес экрана и количество символов (16x2)

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); // Инициализация экрана
  
  // Подключение датчика BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Настройка экрана
  lcd.backlight(); // Включение подсветки экрана
  lcd.begin(16,2);
  Serial.begin(9600);
  Serial.println(F("BMP280 test"));
  lcd.print("Welcome to ");
  lcd.setCursor(0,1);
  lcd.print("CIRCUIT DIGEST");
  delay(1000);
  lcd.clear();
  if (!bmp.begin(0x76)) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
    while (1);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
  // Чтение данных с датчика BMP280
  Serial.print(F("Temperature = "));
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
  lcd.setCursor(0,0);
  lcd.print("Temp=  ");
  lcd.print(bmp.readTemperature());

  Serial.print(F("Pressure = "));
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  lcd.setCursor(0,1);
  lcd.print("Press= ");
  lcd.print(bmp.readPressure());
  Serial.print(F("Approx altitude = "));
  Serial.print(bmp.readAltitude(1018)); /* Adjusted to local forecast! */
  Serial.println(" m");
  Serial.println();
  delay(1000);
}
