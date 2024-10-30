#include <stdlib.h>  //set to whatever is the location of floatToStrig
#include <LiquidCrystal_I2C.h>
#include "Max6675.h"
#include <Wire.h>

int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 5;
int gndPin = 6;

int LedPin = 9;
void setup() {

  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);

  pinMode(LedPin, OUTPUT);
}

String floatToString(float x, byte precision = 3) {
  char tmp[50];
  dtostrf(x, 0, precision, tmp);
  return String(tmp);
}


void loop() {
  float Temp;
  char Msj[16];
  char strAux[5];
  String ObjStrAux;
  
  strcpy(Msj,"°C = "); 
  Temp = thermocouple.readCelsius();
  ObjStrAux = floatToString(Temp, 2);
  ObjStrAux.toCharArray(strAux,5);
  strcat(Msj,strAux);


  Serial.print(Msj);
  Serial.println();
  
  strcpy(strAux,"");
  delay(1000);
}