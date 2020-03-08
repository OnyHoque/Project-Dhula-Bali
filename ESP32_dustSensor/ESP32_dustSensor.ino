#include <GP2Y1010AU0F.h>

int measurePin = 33;   // Connect dust sensor analog measure pin to esp32 26 pin
int ledPin     = 27;    // Connect dust sensor LED pin to esp32 pin 27

GP2Y1010AU0F dustSensor(ledPin, measurePin); // Construct dust sensor global object
float dustDensity = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("GP2Y1010AU0F Dust Sensor Library Example"));

  dustSensor.begin();
}

void loop() {
  dustDensity = dustSensor.read();
  
  Serial.print("Dust Density = ");
  
  double dustDensity1 = map(dustDensity,0 , 4096,0, 1023);
  Serial.print(dustDensity1);
  Serial.println(" ug/m3");
  Serial.println(dustDensity);

  delay(5000);
}
