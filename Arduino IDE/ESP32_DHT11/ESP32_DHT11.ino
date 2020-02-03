#include <DHT.h>
#include <DHT_U.h>

DHT_Unified dht(14, DHT11);

void setup() {
  Serial.begin(115200);
  dht.begin();

}
float a[2];
void loop() {
  getDHT11();
  Serial.println(String(a[0])+" "+String(a[1]));
  delay(3000);
}

void getDHT11(){

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    a[0] = event.temperature;
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    a[1] = event.relative_humidity;
  }
}
