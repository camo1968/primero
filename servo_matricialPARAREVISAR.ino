#include <Servo.h>
#include <LiquidCrystal_I2C.h>  // la de Frank Brabander  // libreria necesaria para display I2C
#include <Wire.h>   // libreria necesaria para bus I2C
#include <Keypad.h>  // la de Mark Stanley y otro


const byte Filas = 4;          //KeyPad de 4 filas
const byte Cols = 3;           //y 3 columnas


LiquidCrystal_I2C lcd(0x27, 16, 2); // configuramos el LCD en la direccion de bus I2C que es   (el nombre lcd lo puedo cambiar por ejemplo a mipantalla)
//    0x27 y el tamaño columnas x filas 16x2    (el 0x27 es un lugar de memoria que el arduino casi nunca accede)
//    en nuestro caso la pantalla es de 16x2 pero puede haber otras

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


String contrasenaFija = "111111*";
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
  servoMotor.attach(3); // Servomotor trabaja con el PIN 3 PWM  *ANALOGO*
  servoMotor.write(0); // Siempre comienza en 0;
  digitalWrite(BLUE, HIGH);

  lcd.init();                     // initialza el lcd
  lcd.backlight();                // enciende la luz de fondo del display
  lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
  lcd.print("hola mundo");        // imprimimos el texto entre ""


}

void loop()
{

  lcd.setCursor(0, 1);       // apuntamos el cursor al primer caracter de la segunda fila

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
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("Error en codigoA");    // y el texto a continuacion
      delay(5000);
      lcd.setCursor(1, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("               ");    // y el texto a continuacion


    }
  }
  else {
    if (passw1 == contrasenaFija )
    {
      Serial.println("Puedes entrar");
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("Puedes entrar");    // y el texto a continuacion
      delay(5000);
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("               ");    // y el texto a continuacion
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

      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("bienvenido");    // y el texto a continuacion
      delay(5000);
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("               ");    // y el texto a continuacion
      // aquì termina la adiciòn del cerrado de la puerta al oprimir # en el keypad

      digitalWrite(GREEN, LOW);
      servoMotor.write(0);
      passw1 = "";
      return true;
    }

    else
    {
      Serial.println("Error en codigo");
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("Error en codigo");    // y el texto a continuacion
      delay(5000);
      lcd.setCursor(0, 0);            // apuntamos el cursor a la primera fila y primer caracter
      lcd.print("               ");    // y el texto a continuacion
      digitalWrite(RED, HIGH);
      digitalWrite(BLUE, LOW);
      delay(8000);
      digitalWrite(RED, LOW);
      passw1 = "";
      return false;
    }
  }
}
