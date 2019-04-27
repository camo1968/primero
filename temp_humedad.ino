

#include "DHT.h"    //  fdsff
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float h,t,f;

void setup() {
  Serial.begin(9600);
  Serial.println("Prueba de temperatura");
  dht.begin();

}

void loop() {
  delay(5000);  // tiempo entre medidas  puede cambiarse a 5000
  h=dht.readHumidity();
  t=dht.readTemperature();
  f=dht.readTemperature(true);  //  el true dice que es farenheit.  si no tiene true lee en celsius
   if(isnan(h)||isnan(t)||isnan(f))   // isnan verifica si la lectura es un numero.  pudiera ser un simbolo y debe salir error en la medición. isnan = is not a number
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
}
