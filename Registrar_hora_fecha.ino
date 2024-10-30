#include <Arduino.h>
#include <Ds1302.h>

// Definición de los pines para la conexión del módulo DS1302
#define PIN_RST   4// Pin de reinicio (RST) del DS1302
#define PIN_CLK   3// Pin de reloj (CLK) del DS1302
#define PIN_DAT   2// Pin de datos (DAT) del DS1302

// Instancia del objeto DS1302 para manejar el RTC (Real Time Clock)
Ds1302 rtc(PIN_RST, PIN_CLK, PIN_DAT);

// Función para convertir una cadena de caracteres a un número de 8 bits
uint8_t parseDigits(char* str, uint8_t count)
{
    uint8_t val = 0;
    while(count-- > 0) val = (val * 10) + (*str++ - '0');  // Convierte cada dígito de la cadena en un número
    return val;
}

void setup()
{
    rtc.init();  // Inicializa el módulo DS1302
    Serial.begin(9600);  // Inicia la comunicación serial a 9600 bps
    Serial.println();
    Serial.println("Ingresa la fecha y la hora (AAMMDDWhhmmss): ");  // Mensaje para el usuario
}

void loop()
{
    static char buffer[13];  // Buffer para almacenar los caracteres ingresados
    static uint8_t char_idx = 0;  // Índice para controlar la posición en el buffer

    // Si se han ingresado 13 caracteres, se procesa la fecha y hora
    if (char_idx == 13)
    {
        // Estructura para almacenar la fecha y hora a configurar
        Ds1302::DateTime dt;

        // Asignación de valores a la estructura dt a partir del buffer
        dt.year = parseDigits(buffer, 2);      // Años
        dt.month = parseDigits(buffer + 2, 2); // Meses
        dt.day = parseDigits(buffer + 4, 2);   // Días
        dt.dow = parseDigits(buffer + 6, 1);   // Día de la semana
        dt.hour = parseDigits(buffer + 7, 2);  // Horas
        dt.minute = parseDigits(buffer + 9, 2);// Minutos
        dt.second = parseDigits(buffer + 11, 2);// Segundos

        rtc.setDateTime(&dt);  // Configura la fecha y hora en el RTC

        char_idx = 0;  // Reinicia el índice del buffer para la próxima entrada
    }

    // Si hay datos disponibles en el puerto serial, se leen y se almacenan en el buffer
    if (Serial.available())
    {
        buffer[char_idx++] = Serial.read();  // Lee un carácter del puerto serial y lo almacena en el buffer
        
  }
}