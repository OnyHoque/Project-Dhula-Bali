/*  Pinout
 *  GPS connection:
 *  16 RX
 *  17 TX
 *  
 *  DTH11 Sensor
 *  4 - Data Input
 *  
 *  Sharp Dust Sensor
 *  Pin 1 (BLU) - IR LED power (5V via supplied 150 Ohm resistor)
 *  Pin 2 (GRN) - GND
 *  Pin 3 (WHT) - pin 27
 *  Pin 4 (YEL) - GND (connected to case)
 *  Pin 5 (BLK) - pin 33
 *  Pin 6 (RED) - 5V power
 *  
 *  LDR light intensity
 *  pin 34
 */
 
// pin used up : 4, 16, 17, 26, 27, 33


#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <GP2Y1010AU0F.h>
#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 21600;
const int   daylightOffset_sec = 3600;


#define RXD2 16
#define TXD2 17
#define measurePin 33
#define ledPin 27
#define DHTPIN 4
#define LDR1 34
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
GP2Y1010AU0F dustSensor(ledPin, measurePin);
TinyGPSPlus gps;
HTTPClient http;


const char* ssid = "Ony wifi 2";
const char* password = "2107199500";

String gps_lat="";
String gps_lng="";
String temp="";
String humidity="";
String dustDensity = "";
String lightIntensity = "";
String dt = "";

void setup(){
  Serial.begin(115200);
  delay(5000);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(" . ");
  }
  Serial.println(" . ");
  Serial.println("!!!Connected!!!");
  Serial.println(WiFi.localIP());
  
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  dht.begin();
  dustSensor.begin();
  pinMode(LDR1,INPUT);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  Serial.println("ESP32: Loop begins");
}

void loop(){
  getGPS();
  getTempandHumidity();
  getDustDensity();
  getLDR();
  getLocalTime();

//  Serial.print("LAT:"+gps_lat);
//  Serial.print("    ");
//  Serial.print("LNG:"+gps_lng);
//  Serial.print("    ");
  Serial.print("TEMP:"+temp);
  Serial.print("    ");
  Serial.print("Humidity:"+humidity);
  Serial.print("    ");
  Serial.print("Dust Density:"+dustDensity);
  Serial.print("    ");
//  Serial.print("Light intensity:"+lightIntensity);
  Serial.println();
  Serial.println(dt);
  uploadData();
  delay(4000);
}

void uploadData(){
  String str = "http://118.179.43.155:5001/dsd/post.php?f2="+dt;
  str = str + "&f3="+gps_lat;
  str = str + "&f4="+gps_lng;
  str = str + "&f5="+temp;
  str = str + "&f6="+humidity;
  str = str + "&f7="+dustDensity;
  str = str + "&f8="+lightIntensity;

  http.begin(str);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("Uploading successful.");
    String payload = http.getString();
    Serial.print("Payload: ");
    Serial.println(payload);
  }else{
    Serial.println("Uploading failed.");
  }
}

void getLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  char timeStringBuff[50];
  strftime(timeStringBuff, sizeof(timeStringBuff), "%d_%H_%M_%S", &timeinfo);
  dt = String(timeStringBuff);
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
  float val = dustSensor.read();
  val = map(val,0 , 4096,0, 1023);
  dustDensity = String(val);
}

void getLDR(){
  int val1 = analogRead(LDR1);
  lightIntensity = String(val1);
}

void getTempandHumidity(){
  humidity = String(dht.readHumidity());
  temp = String(dht.readTemperature());
}
