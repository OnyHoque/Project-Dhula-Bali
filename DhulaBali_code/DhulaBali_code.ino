/*  Pinout
 *  GPS connection:
 *  16 RX
 *  17 TX
 *  
 *  DTH11 Sensor
 *  2 - Data Input
 *  
 */

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include "DHT.h"



#define RXD2 16
#define TXD2 17
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
TinyGPSPlus gps;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();

  Serial.println("ESP32: Loop begins");
}


String gps_lat="";
String gps_lng="";
String temp="";
String humidity="";

void loop(){
  getGPS();
  getTempandHumidity();

  Serial.print("LAT:"+gps_lat);
  Serial.print("    ");
  Serial.print("LNG:"+gps_lng);
  Serial.print("    ");
  Serial.print("TEMP:"+temp);
  Serial.print("    ");
  Serial.print("Humidity:"+humidity);
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

void getTempandHumidity(){
  humidity = String(dht.readHumidity());
  temp = String(dht.readTemperature());
}
