#include <Keypad.h>
#include <Servo.h>
int angulo = 0;
Servo miServo ;
const byte Filas = 4;          //KeyPad de 4 filas
const byte Cols = 3;           //y 3 columnas

byte Pins_Filas[] = {13, 12, 11, 10};     //Pines Arduino para las filas.
byte Pins_Cols[] = { 9, 8, 7};     // Pines Arduino para las columnas.

char Teclas [ Filas ][ Cols ] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);

String clave = "123";
String entrada = "";
int inicio = 0;
int fin = 0;
int diferencia = 0;


void setup()
{
  Serial.begin(9600);
  miServo.attach(3);
}

void loop()
{
  char pulsacion = Teclado1.getKey() ;

  if (pulsacion) {             // Si el valor es 0 es que no se
    entrada = entrada + pulsacion;
    Serial.println(entrada);      // se ha pulsado ninguna tecla
    inicio = millis();
  }
  if (entrada == clave) {
    Serial.println("bienvenido");      // se ha pulsado ninguna tecla
    delay(2000);
    abrirPuerta();
    entrada ="";
  }
  fin = millis();
  diferencia = fin - inicio;
  if (diferencia > 5000) {
 //    Serial.println("tiempo vencido");      // se ha pulsado ninguna tecla
 //    delay(2000);
    entrada = "";
  }

}









void abrirPuerta () {
for (angulo=1;angulo<=180;angulo++) {
  miServo.write(angulo);
  delay(50);
}
delay(1000);
for (angulo=180;angulo>=1;angulo--) {
  miServo.write(angulo);
  delay(50);
}
}
