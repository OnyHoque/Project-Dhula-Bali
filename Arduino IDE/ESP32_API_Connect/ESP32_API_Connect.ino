#include <WiFi.h>
#include <HTTPClient.h>
#include <TinyGPS++.h>
 
const char* ssid = "Ony wifi 2";
const char* password = "2107199500";
HTTPClient http;

const int potPin = 34;


int potValue = 0;


#define RXD2 16
#define TXD2 17

TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(1000);
  con();
}

void loop() {



  if (gps.encode(Serial2.read()))
    {
      if (gps.location.isValid())
      {
        float LAT = gps.location.lat();
        float LNG = gps.location.lng();
        Serial.print("LAT:");
        Serial.print(LAT);
        Serial.print("    LNG:");
        Serial.println(LNG);
      }
    }
    
















  

//  String str = "http://192.168.68.112/dsd/post.php?f2="+String(potValue)+"&f3=20";
//  Serial.println (str);
//  http.begin(str);
//  int httpCode = http.GET();
//  if (httpCode > 0) { //Check for the returning code
// 
//      String payload = http.getString();
//      Serial.println(httpCode);
//      Serial.println(payload);
//    }
//    else {
//      Serial.println("Error on HTTP request");
//    }
//    http.end();
    
  delay(500);
}


void con(){
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected : ");
  Serial.println(WiFi.localIP());
}
