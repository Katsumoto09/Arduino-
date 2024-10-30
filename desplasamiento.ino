#include <stdlib.h> 
#include <Wire.h>
#include "Max6675.h"
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 5;
int gndPin = 6; 
LiquidCrystal_I2C lcd (0x27,2, 1, 0, 4, 5, 6, 7);

void setup() {

  Serial.begin(9600);
  // Configura LCD
   pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  pinMode(LedPin, OUTPUT);

  lcd.begin(16,2); // Inicia LCD con 16 columnas x 2 renglones
  lcd.setBacklightPin(3,POSITIVE); // Pin 3 Poistivo
  lcd.setBacklight(HIGH);  // Mantener en ALTO      
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

void loop() {
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
}
