

int rojo = 7 ;
int azul = 8 ;
int verde = 9;
//void BT (char estado = '0');
char estado = '0';
void setup() {
  // put your setup code here, to run once:

  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(rojo, OUTPUT);
  pinMode(azul, OUTPUT);
  pinMode(verde, OUTPUT);

}

void loop()
{

  //BT();
  if (Serial1.available() > 0)
  {
    estado = Serial1.read();
    BT();
  }


}

void BT () {
  /*if (Serial1.available() > 0)
    {
    estado = Serial1.read();
    }*/


  Serial.print(estado);
  if (estado == '1')
  {
    digitalWrite(rojo, HIGH);

  }

  if (estado == '2')
  {
    digitalWrite(rojo, LOW);

  }
  if (estado == '3')
  {
    estado = '0';
    digitalWrite(azul, HIGH);
    delay(2000);
    digitalWrite(azul, LOW);
  }
}
