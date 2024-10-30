#include <Arduino.h>
#include <Ds1302.h>

// Definimos los pines de conexión para el módulo DS1302
#define PIN_RST   4// Pin de reinicio (RST) del DS1302
#define PIN_CLK   3// Pin de reloj (CLK) del DS1302
#define PIN_DAT   2// Pin de datos (DAT) del DS1302

// Instancia del objeto DS1302 para manejar el RTC (Real Time Clock)
Ds1302 rtc(PIN_RST, PIN_CLK, PIN_DAT);

// Definimos un arreglo de cadenas para representar los días de la semana
const static char* DiasdelaSemana[] =
{
    "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
};

void setup()
{
    Serial.begin(9600);  // Inicia la comunicación serial a 9600 bps
    rtc.init();          // Inicializa el módulo DS1302
}

void loop()
{
    // Estructura para almacenar la fecha y hora actual
    Ds1302::DateTime now;
    rtc.getDateTime(&now);  // Obtiene la fecha y hora del RTC y la guarda en 'now'

    static uint8_t ultimo_segundo = 0;  // Variable para almacenar el último segundo registrado

    // Verifica si ha pasado un segundo desde la última vez que se actualizó
    if (ultimo_segundo != now.second)
    {
        ultimo_segundo = now.second;  // Actualiza la variable 'ultimo_segundo' con el segundo actual

        // Buffer para almacenar la cadena formateada de fecha y hora
        char buffer[30];
        sprintf(buffer, "20%02d-%02d-%02d %s %02d:%02d:%02d",
                now.year, now.month, now.day,                          // Año, mes, día
                DiasdelaSemana[now.dow - 1],                           // Día de la semana
                now.hour, now.minute, now.second);                     // Hora, minuto, segundo

        Serial.println(buffer);  // Imprime la cadena formateada en la consola serial
    }
    
    delay(100);  // Pequeño retraso para evitar saturar el loop
}