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
 *  LDR light intensity
 *  pin 34
 */
 
// pin used up : 2, 16, 17, 26, 27, 34


#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <GP2Y1010AU0F.h>
#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>



#define RXD2 16
#define TXD2 17
#define measurePin 26
#define ledPin 27
#define DHTPIN 2
#define LDR1 34
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
GP2Y1010AU0F dustSensor(ledPin, measurePin);
TinyGPSPlus gps;
HTTPClient http;


const char* ssid = "Ony wifi 2";
const char* password = "2107199500";

void setup(){
  Serial.begin(115200);
  delay(5000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" . ");
  } 
  Serial.println("Connected to the WiFi network");

  
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  dustSensor.begin();
  pinMode(LDR1,INPUT);

  Serial.println("ESP32: Loop begins");
}


String gps_lat="";
String gps_lng="";
String temp="";
String humidity="";
String dustDensity = "";
String lightIntensity = "";

void loop(){
  getGPS();
  getTempandHumidity();
  getDustDensity();
  getLDR();

  Serial.print("LAT:"+gps_lat);
  Serial.print("    ");
  Serial.print("LNG:"+gps_lng);
  Serial.print("    ");
  Serial.print("TEMP:"+temp);
  Serial.print("    ");
  Serial.print("Humidity:"+humidity);
  Serial.print("    ");
  Serial.print("Dust Density:"+dustDensity);
  Serial.print("    ");
  Serial.print("Light intensity:"+lightIntensity);
  Serial.println();

//  http.begin("");
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

void getLDR(){
  int val1 = analogRead(LDR1);
  lightIntensity = String(val1);
}

void getTempandHumidity(){
  humidity = String(dht.readHumidity());
  temp = String(dht.readTemperature());
}
