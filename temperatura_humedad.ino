
/*DHT
  incluir las siguientes librerias
  adafruit unified sensor (es para manejar sensores unificados).  escojer la ultima del listado
  DHT sensor library .  escojer la de adafruit
*/
#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float humidity, temperature, temp_in_F ;


/* LCD
  incluir la libreria liquidcrystal I2C .   la de Frank de Brabander
*/
#include <Wire.h>                 // libreria necesaria para bus I2C
#include <LiquidCrystal_I2C.h>    // libreria necesaria para display I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // configuramos el LCD en la direccion de bus I2C que es
//    0x27 y el tamaño columnas x filas 16x2



/*RF
*/
#define botonA 29
#define botonB 31
#define botonC 33
#define botonD 27


/*LED
*/
int LED = 8;


void setup() {
  // put your setup code here, to run once:


  Serial.begin(9600);
  Serial.println("prueba de temperatura y humedad");
  Serial.println();

  //DHT
  dht.begin();

  //LCD
  lcd.init();                     // initialza el lcd
  lcd.backlight();                // enciende la luz de fondo del display
  lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
  lcd.print("prueba de");        // imprimimos el texto entre ""
  lcd.setCursor(0, 1);
  lcd.print("temp y humedad");        // imprimimos el texto entre ""

  //RF
  pinMode(botonA, INPUT_PULLUP);
  pinMode(botonB, INPUT_PULLUP);
  pinMode(botonC, INPUT_PULLUP);
  pinMode(botonD, INPUT_PULLUP);


  //LED
  pinMode(LED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  temp_in_F = dht.readTemperature(true);



  if (isnan(humidity) || isnan(temperature) || isnan(temp_in_F))
  {
    Serial.println("Error en la medición");
    lcd.setCursor(0, 0);
    lcd.print("Error en la medición");
    return;
  }

    Serial.print("Humedad: ");
    Serial.print(humidity);
    Serial.print("%\t");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.print(" *C ");
    Serial.print(temp_in_F);
    Serial.println(" *F\t");

  if (digitalRead(botonA) == HIGH) {
    Serial.println("boton A");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("boton A     ");
    lcd.setCursor(0, 1);
    Serial.print(humidity);
    lcd.print(String(humidity) + " relativa");
  }
  if (digitalRead(botonB) == HIGH) {
    Serial.println("boton B");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("boton B     ");
    lcd.setCursor(0, 1);
    Serial.print(String(temperature) + " G c");
    lcd.print(String(temperature) + " grados celsius");
  }
  if (digitalRead(botonC) == HIGH) {
    Serial.println("boton C");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("boton C     ");
    lcd.setCursor(0, 1);
    Serial.print(String(temp_in_F) + " G Farenheit");
    lcd.print(String(temp_in_F) + " grados Farenheit");
  }
  if (digitalRead(botonD) == HIGH) {
    Serial.println("boton D");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("boton D     ");
    lcd.setCursor(0, 1);
    lcd.print("                     ");
    digitalWrite(LED, HIGH);
    delay(3000);
    digitalWrite(LED, LOW);

  }
}
