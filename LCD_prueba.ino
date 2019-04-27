#include <Wire.h>                 // libreria necesaria para bus I2C
#include <LiquidCrystal_I2C.h>    // libreria necesaria para display I2C
 
LiquidCrystal_I2C lcd(0x27,16,2);  // configuramos el LCD en la direccion de bus I2C que es   (el nombre lcd lo puedo cambiar por ejemplo a mipantalla)
                                  //    0x27 y el tamaño columnas x filas 16x2    (el 0x27 es un lugar de memoria que el arduino casi nunca accede)  
                                  //    en nuestro caso la pantalla es de 16x2 pero puede haber otras
void setup()
{
  lcd.init();                     // initialza el lcd 
  lcd.backlight();                // enciende la luz de fondo del display
  lcd.setCursor(4,0);             // apuntamos el cursor a la primera fila y primer caracter 
  lcd.print("hola mundo");        // imprimimos el texto entre ""
}
 
void loop()
{
  lcd.setCursor(0, 1);       // apuntamos el cursor al primer caracter de la segunda fila
  lcd.print(millis()/1000);  // imprimimos el tiempo transcurrido en segundos
  lcd.print("-segundos");    // y el texto a continuacion
 
}
