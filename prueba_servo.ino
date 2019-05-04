#include <Servo.h> //  incluir la libreria que ya está por defecto en arduino

Servo miServo;   // esto es una variable tipo servo  miServo se puede cambiar por lo que uno quiera

int angulo = 0; //la posicion que queremos
int i = 1; //para controlar 

void setup() {
  miServo.attach(3); //el cable datos se conecta allí
  Serial.begin(9600); //para ver el angulo
  miServo.write(0);
}

void loop() {

  if(i==1){
    angulo++;  // se le agrega 1 al angulo
  }
  else{
    angulo--;  // se le quita de a 1
  }
  
  Serial.println(angulo);

  if(angulo<=1) {     // cuando llega a 1 pone i en 1 para que empiece a subir
    angulo = 1;
    i = 1;
    delay(200);
  }

  if(angulo>=255) {    // cuando llega a 180 grados pone i en cero para que empiece a bajar
    angulo = 255;
    i = 0;
    delay(200);
  }

  miServo.write(angulo);
  delay(10);
}
