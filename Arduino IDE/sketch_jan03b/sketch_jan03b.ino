void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);

}

void loop() {
  digitalWrite(2,1);
  digitalWrite(3,0);
  delay(1000);
  digitalWrite(2,0);
  digitalWrite(3,1);
  delay(1000);

  digitalWrite(4,1);
  digitalWrite(5,0);
  delay(1000);
  digitalWrite(4,0);
  digitalWrite(5,1);
  delay(1000);
}
