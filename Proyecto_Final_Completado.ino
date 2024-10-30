#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include "Max6675.h"
#include <stdlib.h> 
#include <LCD.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
// Configura la dirección I2C del LCD (por defecto suele ser 0x27 o 0x3F)
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);

// Instancia del objeto RTC DS3231
RTC_DS3231 rtc;
int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2; 

void setup(void) {
    // Inicia la comunicación serial
  Serial.begin(9600);
  
  // Inicia el LCD con 16 columnas y 2 filas
  lcd.begin(16, 2);
  lcd.setBacklightPin(3, POSITIVE); // Pin 3 positivo
  lcd.setBacklight(HIGH);           // Mantener retroiluminación activada
  
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);


  lcd.begin(16,2); // Inicia LCD con 16 columnas x 2 renglones
  lcd.setBacklightPin(3,POSITIVE); // Pin 3 Poistivo
  lcd.setBacklight(HIGH);  // Mantener en ALTO      

  // Verifica si el RTC está presente
  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("No RTC found");
    while (1);
  }

  // Verifica si el reloj está detenido, si es así, lo pone en marcha
  if (rtc.lostPower()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC lost power");
    lcd.setCursor(0, 1);
    lcd.print("Adjusting time");
    // Establece la fecha y hora en el RTC (modifica esta línea con la fecha/hora actual)
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }


}

String floatToString(float x, byte precision = 4) {
  char tmp[50];
  dtostrf(x, 0, precision, tmp);
  return String(tmp);
  
}

float Temp;
char Msj[16];
char strAux[5];
String ObjStrAux;

void loop(void) {
  for (int i = strlen(Msj); i>=0; i--){
  Temp = thermocouple.readCelsius(); // Lectura de termocupla con el metodo readCelcius
  Serial.print("Temp = ");  // Visualizo en monitor Serie
  Serial.println(Temp);    // Visualizo valor de la variable temp
  lcd.clear();
  lcd.setCursor (0, 0);
  
  ObjStrAux = floatToString(Temp, 3);
  ObjStrAux.toCharArray(strAux,5);
  strcpy(Msj,"Temp = ");
  strcat(Msj,strAux);
  lcd.print(Msj + i);
  delay(500);
  }
   // Obtiene la fecha y hora actual desde el RTC
  DateTime now = rtc.now();

  // Convierte la hora de 24 horas a 12 horas
  int hour = now.hour();
  String ampm = "AM";
  
  if (hour == 0) {  // Medianoche (00:00)
    hour = 12;      // Mostrar como 12:XX AM
  } else if (hour == 12) {  // Mediodía (12:00)
    ampm = "PM";    // Mostrar como 12:XX PM
  } else if (hour > 12) {  // Hora después del mediodía
    hour -= 12;     // Convertir al formato de 12 horas
    ampm = "PM";    // Mostrar PM
  }

  // Muestra la fecha en formato (dd/mm/aaaa) en la segunda fila del LCD
  lcd.setCursor(0, 0);
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);

  // Muestra la hora en formato de 12 horas (hh:mm:ss AM/PM) en la segunda fila del LCD
  lcd.setCursor(0, 1);
  lcd.print(hour);           // Hora en formato de 12 horas
  lcd.print(':');
  lcd.print(now.minute() < 10 ? "0" : ""); // Añade un cero si es menor a 10
  lcd.print(now.minute());
  lcd.print(':');
  lcd.print(now.second() < 10 ? "0" : ""); // Añade un cero si es menor a 10
  lcd.print(now.second());
  lcd.print(" ");
  lcd.print(ampm);          // Imprime "AM" o "PM"

  //u8g2.clearBuffer();					// Limpiar la memoria interna
 
 
  delay(1000);  // Espera de 1 segundo
}