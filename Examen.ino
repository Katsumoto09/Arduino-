#include <stdlib.h>
#include <Wire.h>
#include "Max6675.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Ds1302.h>

// Pines para el MAX6675
int thermoDO = 4;
int thermoCS = 3;
int thermoCLK = 2;

// Pines para el DS1302
#define PIN_RST 7  // Pin de reinicio (RST) del DS1302
#define PIN_CLK 6  // Pin de reloj (CLK) del DS1302
#define PIN_DAT 5  // Pin de datos (DAT) del DS1302

// Instancias para el termopar y el RTC
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
Ds1302 rtc(PIN_RST, PIN_CLK, PIN_DAT);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // LCD de 16x2

// Días de la semana
const static char* DiasdelaSemana[] = {
    "Lun", "Mar", "Mie", "Jue", "Vie", "Sab", "Dom"
};

void setup() {
  Serial.begin(9600);
  
  // Inicia LCD
  lcd.begin(16, 2);                  // 16 columnas, 2 filas
  lcd.setBacklightPin(3, POSITIVE);   // Configurar el backlight
  lcd.setBacklight(HIGH);             // Encender backlight
  lcd.clear();                        // Limpiar la pantalla
  
  // Inicializar el RTC
  rtc.init();
}

String floatToString(float x, byte precision = 2) {
  char tmp[16];
  dtostrf(x, 0, precision, tmp);      // Convertir el float a string
  return String(tmp);
}

void loop() {
  // Lectura de temperatura
  float Temp = thermocouple.readCelsius();

  // Obtiene la fecha y hora actual del RTC
  Ds1302::DateTime now;
  rtc.getDateTime(&now);
  
  static uint8_t ultimo_segundo = 0;

  // Actualiza solo si ha cambiado el segundo
  if (ultimo_segundo != now.second) {
    ultimo_segundo = now.second;

    // Muestra la hora y fecha en el monitor serial
    char buffer[30];
    sprintf(buffer, "%02d:%02d:%02d %s",
            now.hour, now.minute, now.second,
            DiasdelaSemana[now.dow - 1]);
    Serial.println(buffer);

    // Mostrar hora y día de la semana en la primera línea del LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(buffer);  // Mostrar hora y día en la primera línea

    // Mostrar temperatura en la segunda línea del LCD
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(floatToString(Temp, 2));
    lcd.print(" C");
  }

  delay(500);  // Actualización cada 500 ms
}