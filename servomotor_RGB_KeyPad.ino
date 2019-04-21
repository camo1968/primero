
#include <Servo.h>
//#include <Key.h>
#include <Keypad.h>

const byte Filas = 4;          //KeyPad de 4 filas
const byte Cols = 3;           //y 3 columnas

byte Pins_Filas[] = {8, 7, 6, 5};     //Pines Arduino para las filas.
byte Pins_Cols[] = { 4, 3, 2};     // Pines Arduino para las columnas.

char Teclas [ Filas ][ Cols ] =
{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

Keypad Teclado1 = Keypad(makeKeymap(Teclas), Pins_Filas, Pins_Cols, Filas, Cols);


String contrasenaFija = "251287*";
String passw1 = "";

float inicio = 0, fin = 0;
# define RED 30
# define GREEN 31
# define BLUE 32
Servo servoMotor; // Definicion variable SERVOMOTOR

void setup()
{
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  servoMotor.attach(9); // Servomotor trabaja con el PIN 9 *ANALOGO*
  servoMotor.write(0); // Siempre comienza en 0;
  digitalWrite(BLUE, HIGH);

}

void loop()
{
  char pulsacion = Teclado1.getKey() ;

  if ( pulsacion)
  {
    passw1 = passw1 + pulsacion;
    Serial.println(passw1);      // se ha pulsado ninguna tecla
    inicio = millis();
  }

  if (passw1.length() < 7)
  {
    fin = millis();
    if ((fin - inicio) >= 8000)
    {
      passw1 = "";
      Serial.println("");
      digitalWrite(BLUE, HIGH);
    }
  }
  else {
    if (passw1 == contrasenaFija )
    {
      Serial.println("Puedes entrar");
      digitalWrite(GREEN, HIGH);
      digitalWrite(BLUE, LOW);
      delay(3000);
      servoMotor.write(180);
     
                // adicion Carlos Montoya
                // se incluyò una nueva lectura del keypad para que la puerta se cierre no por tiempo (8 seg) porque puede ser
                // que no haya pasado aùn el carro o persona, sino por oprimir la tecla # en el keypad
      
      //      delay(8000);

      char closedoor = '*';

      while (closedoor != '#')
      {
        closedoor = Teclado1.getKey() ;
      }

                // aquì termina la adiciòn del cerrado de la puerta al oprimir # en el keypad
      
      digitalWrite(GREEN, LOW);
      servoMotor.write(0);
      passw1 = "";
      return true;
    }

    else
    {
      Serial.println("Error en codigo");
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      delay(8000);
      digitalWrite(RED, LOW);
      passw1 = "";
      return false;
    }
  }
}
