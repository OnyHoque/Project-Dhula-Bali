/*  Pinout
 *  GPS connection:
 *  RX-16
 *  TX-17
 *  
 * 
 */

#include <TinyGPS++.h>
#include <HardwareSerial.h>



#define RXD2 16 //RXX2 pin
#define TXD2 17 //TX2 pin
TinyGPSPlus gps;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop(){
  while (Serial2.available() > 0){
    gps.encode(Serial2.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
}
