

#include "DHT.h"    //  
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h, t, f;
char luz = 'a';
int GREEN = 10; //VERDE
int BLUE = 9; //AZUL
int RED = 8; //RO

void setup() {
  Serial.begin(9600);
  Serial.println("Prueba de temperatura");
  dht.begin();

}

void loop() {
  delay(5000);  // tiempo entre medidas  puede cambiarse a 5000
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true); //  el true dice que es farenheit.  si no tiene true lee en celsius
  if (isnan(h) || isnan(t) || isnan(f)) // isnan verifica si la lectura es un numero.  pudiera ser un simbolo y debe salir error en la medición. isnan = is not a number
  {
    Serial.println("Error en la medición");
    return;
  }

  if (t > 25.0) {
    luz = 'r';
  } else if (t > 24.6 && t <= 24.9) {
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

  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%\t");   // el \t  deja una tabulación
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.println(" *F\t");
}
