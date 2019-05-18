#define pinSensor 8
int pinLed = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinSensor, INPUT);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(pinSensor) == HIGH)
  {
    digitalWrite(pinLed, HIGH);
  } else {
    digitalWrite(pinLed, LOW);
  }

}
