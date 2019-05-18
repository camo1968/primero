#define sensor A4
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A4,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(analogRead(A4)>600){
    Serial.println(analogRead(A4));
    Serial.println("Hay silenciio");  
    digitalWrite(13,LOW);
  }else{
    Serial.println(analogRead(A4));
    digitalWrite(13,HIGH);
  }
  
}
