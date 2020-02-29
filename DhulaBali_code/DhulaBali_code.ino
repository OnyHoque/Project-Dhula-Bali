/*  Pinout
 *  GPS connection:
 *  16 RX
 *  17 TX
 *  
 *  DTH11 Sensor
 *  2 - Data Input
 *  
 *  Sharp Dust Sensor
 *  Pin 1 (BLU) - IR LED power (5V via supplied 150 Ohm resistor)
 *  Pin 2 (GRN) - GND
 *  Pin 3 (WHT) - pin 27
 *  Pin 4 (YEL) - GND (connected to case)
 *  Pin 5 (BLK) - pin 26
 *  Pin 6 (RED) - 5V power
 *  
 *  
 */

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <GP2Y1010AU0F.h>
#include "DHT.h"



#define RXD2 16
#define TXD2 17
#define measurePin 26
#define ledPin 27
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
GP2Y1010AU0F dustSensor(ledPin, measurePin);
TinyGPSPlus gps;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  dustSensor.begin();

  Serial.println("ESP32: Loop begins");
}


String gps_lat="";
String gps_lng="";
String temp="";
String humidity="";
String dustDensity = "";

void loop(){
  getGPS();
  getTempandHumidity();
  getDustDensity();

//  Serial.print("LAT:"+gps_lat);
//  Serial.print("    ");
//  Serial.print("LNG:"+gps_lng);
//  Serial.print("    ");
//  Serial.print("TEMP:"+temp);
//  Serial.print("    ");
//  Serial.print("Humidity:"+humidity);
  Serial.print("Dust Density:"+dustDensity);
  Serial.println();
  delay(2000);
}

void getGPS(){
  while (Serial2.available() > 0){
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      gps_lat = String(gps.location.lat(), 6);
      gps_lng = String(gps.location.lng(), 6);
    }
  }
}

void getDustDensity(){
  dustDensity = String(dustSensor.read());
}

void getTempandHumidity(){
  humidity = String(dht.readHumidity());
  temp = String(dht.readTemperature());
}
