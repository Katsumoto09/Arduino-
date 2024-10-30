#include <LiquidCrystal_I2C.h> // Asegúrate de incluir esta librería
#include <Wire.h>

int vccPin = 3;
int gndPin = 2;

LiquidCrystal_I2C lcd (0x27,2, 1, 0, 4, 5, 6, 7);

void setup() {
  lcd.begin(16,2); // Inicia LCD con 16 columnas x 2 renglones
  lcd.setBacklightPin(3,POSITIVE); // Pin 3 Poistivo
  lcd.setBacklight(HIGH);  // Mantener en ALTO                   // Ativa a retroiluminação do LCD
}
char Msj[16];
char strAux[5];
String ObjStrAux; 
 	
void loop() {
  for (int i = strlen(Msj); i>=0; i--){
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.begin(16,2); // Inicia la pantalla LCD con 16 columnas y 2 filas
  lcd.setBacklight(HIGH);  // Activa la luz de fondo si es necesario
  lcd.setCursor(0, 0); // Coloca el cursor en la primera columna, primer renglón
  lcd.print("Texto fijo");  // Imprime el texto que deseas
  delay(500);
   }
}
