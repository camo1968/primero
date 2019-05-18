#define Trigger 2 //pin digital para el Trigger
#define Echo 3  //pin digital para el Echo
#define Buzz 6

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //inicializamos la comunicación
  pinMode(Trigger, OUTPUT);//pin como salida
  pinMode(Echo, INPUT);//pin como entrada
  pinMode(Buzz, OUTPUT); //pin como salida
  digitalWrite(Trigger, LOW); //inicializamos el pin con 0
  digitalWrite(Buzz, LOW);
}
void loop() {
  if (sensorUltraSonido() <= 10) {
    //Serial.println(sensorUltraSonido());
    Serial.println("Ojo se va chocar");
  } else if (sensorUltraSonido() <= 5) {
    digitalWrite(Buzz, HIGH);
    
  } else {
    //{
    Serial.println(sensorUltraSonido());
    digitalWrite(Buzz, LOW);
    // }
  }
}


long sensorUltraSonido() {
  // put your main code here, to run repeatedly:
  long t;//tiempo que demora en llegar el eco
  long d;//distancia en cm
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);//enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);
  t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
  d = t / 59; //escalamos el tiempo a una distancia en cm
  //Serial.print("Distancia: ");
  //Serial.print(d);//enviamos serialmente el valor de la distancia
  //Serial.print("cm");
  //Serial.println();
  //delay(1000);//hacemos una pausa
  return d;
}
