

#include "DHT.h"    //  fdsff
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h, t, f;

char luz = 'a';
int GREEN = 10; //VERDE
int BLUE = 9; //AZUL
int RED = 8; //RO

#include <Wire.h>                 // libreria necesaria para bus I2C
#include <LiquidCrystal_I2C.h>    // libreria necesaria para display I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // configuramos el LCD en la direccion de bus I2C que es   (el nombre lcd lo puedo cambiar por ejemplo a mipantalla)
//    0x27 y el tamaño columnas x filas 16x2    (el 0x27 es un lugar de memoria que el arduino casi nunca accede)
//    en nuestro caso la pantalla es de 16x2 pero puede haber otras


int fila = 1;
void setup() {
  Serial.begin(9600);
  Serial.println("Prueba de temperatura");
  dht.begin();

  lcd.init();                     // initialza el lcd
  lcd.backlight();                // enciende la luz de fondo del display
  lcd.setCursor(4, 0);            // apuntamos el cursor a la primera fila y primer caracter
  lcd.print("TEMPERATURA");        // imprimimos el texto entre ""

  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);

}

void loop() {
  delay(3000);  // tiempo entre medidas  puede cambiarse a 5000
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true); //  el true dice que es farenheit.  si no tiene true lee en celsius
  if (isnan(h) || isnan(t) || isnan(f)) // isnan verifica si la lectura es un numero.  pudiera ser un simbolo y debe salir error en la medición. isnan = is not a number
  {
    Serial.println("Error en la medición");
    return;
  }
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%\t");   // el \t  deja una tabulación
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");

  if (fila == 0) {
    fila = 1;
  } else {
    fila = 0;
  }

  lcd.setCursor(0, fila);      // apuntamos el cursor al primer caracter de la segunda fila
  //lcd.print(millis() / 1000); // imprimimos el tiempo transcurrido en segundos
  lcd.print(t);    // y el texto a continuacion
  lcd.print("-grados cent");    // y el texto a continuacion

  if (t >= 25.0) {
    luz = 'r';
  } else if (t >= 24.7 && t <= 24.9) {
    luz = 'v';
  } else {
    luz = 'a';
  }

  switch (luz) {

    case 'r':
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, HIGH);
      break;
    case 'v':
      digitalWrite(BLUE, LOW);
      digitalWrite(GREEN, HIGH);
      digitalWrite(RED, LOW);
      break;
    case 'a':
      digitalWrite(BLUE, HIGH);
      digitalWrite(GREEN, LOW);
      digitalWrite(RED, LOW);
      break;
  }

}
