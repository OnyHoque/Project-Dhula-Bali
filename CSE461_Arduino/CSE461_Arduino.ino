/* Documentation
SD Card Module
   MOSI - pin 11
   MISO - pin 12
   CLK  - pin 13
   CS   - pin 4

Dust Senor
   R - VCC
   B - Output (A0)
   Y - GND
   W - LED (7)
   G - GND
   B - VCC using 220 Ohm Resistor
   
DTH11 Temperature and Humidity Module
   DHT11_PIN 3

Gas Sensors
   MQ4 = A3
   High Sensivity  - CH4, Natural Gas
   Low  Sensivity  - Alcohol
   MQ8 = A2
   High Sensivity  - Hydrogen Gas
   Low  Sensivity  - 
   MQ9 = A1
   High Sensivity  - CO Gas, Flammable Gas
   Low  Sensivity  - 
   
*/
#include <SPI.h>
#include <SD.h>
#include <dht.h>
#include <SoftwareSerial.h>
SoftwareSerial s(5,6);

int CS_PIN = 4;
int measurePin = A0;
int ledPower = 7;
int DHT11_PIN = 3;
int MQ4 = A3;
int MQ8 = A2;
int MQ9 = A1;

File dataFile;
dht DHT;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup() {
  Serial.begin(9600);
  s.begin(9600);
  
  if (SD.begin(CS_PIN)){Serial.println("SD card Module success");}
  else{Serial.println("SD card module Failure");}


 pinMode(ledPower,OUTPUT);
 pinMode(A1,INPUT);
 pinMode(A2,INPUT);
 pinMode(A3,INPUT);
 
 delay(1000);
}

void loop() {
  int chk = DHT.read11(DHT11_PIN);
 
  float dust = getDust()*100;
  float temp = getTemp();
  float hum = getHum();
  float mq4 = getMQ4();
  float mq8 = getMQ8();
  float mq9 = getMQ9();

  Serial.print("Dust Density: "+String(dust)+"   ");
  
  Serial.print("Temperature : "+String(temp)+"   ");
  
  Serial.print("Humidity : "+String(hum)+"   ");
  
  Serial.print("MQ4 : "+String(mq4)+"   ");
  
  Serial.print("MQ8 : "+String(mq8)+"   ");
  
  Serial.println("MQ9 : "+String(mq9) );

  

  
  s.write(long(dust));
  delay(5);
  s.write(long(temp));
  delay(5);
  s.write(long(hum));
  delay(5);
  s.write(long(mq4));
  delay(5);
  s.write(long(mq8));
  delay(5);
  s.write(long(mq9));
  
  writeSD("Dust Amount: "+String( getDust() )+";  Temperature:"+String( getTemp() )+";  Humidity:"+String( getHum() )+";  MQ4:"+String( getMQ4() )+";  MQ8:"+String( getMQ8() )+";  MQ9:"+String( getMQ9() ));
 
 delay(2000);
}

void writeSD(String str){
  dataFile = SD.open("data.txt", FILE_WRITE);
  dataFile.println(str);
  dataFile.close();
}

float getDust(){
  digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);
  voMeasured = analogRead(measurePin);
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);
  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage;
  //if( dustDensity < 0){dustDensity = 0.00;}
  return dustDensity;
}

float getTemp(){
  return DHT.temperature;
}

float getHum(){
  return DHT.humidity;
}

float getMQ4(){
  return float(analogRead(MQ4));
}

float getMQ8(){
  return float(analogRead(MQ8));
}

float getMQ9(){
  return float(analogRead(MQ9));
}
