#include <WiFi.h>
#include <HTTPClient.h>
 
const char* ssid = "Ony wifi 2";
const char* password = "2107199500";
HTTPClient http;

const int potPin = 34;

// variable for storing the potentiometer value
int potValue = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  con();
}

void loop() {

  String str = "http://192.168.68.112/dsd/post.php?f2="+String(potValue)+"&f3=20";
  Serial.println (str);
  http.begin(str);
  int httpCode = http.GET();
  if (httpCode > 0) { //Check for the returning code
 
      String payload = http.getString();
      Serial.println(httpCode);
      //Serial.println(payload);
    }
    else {
      Serial.println("Error on HTTP request");
    }
    http.end();
    
  delay(5000);
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
