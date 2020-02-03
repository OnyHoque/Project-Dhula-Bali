#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS++.h>


long data;
long arr[6];
TinyGPSPlus gps;
float la = 10.1011, lo = 10.1011;


LiquidCrystal_I2C lcd(0x27, 16, 2);


SoftwareSerial s(D6,D5);


#define FIREBASE_HOST "cse461-f2fd3.firebaseio.com"
#define FIREBASE_AUTH "jgNkx7mym5i9TZcUkCECyIfNOuDF9pqQr6Y9Kb5D"
#define WIFI_SSID "Ony Wifi Hotspot_plus"
#define WIFI_PASSWORD "2107199500"


void setup() {
  pinMode(D0,OUTPUT);
  digitalWrite(D0,LOW);
  Serial.begin(9600);
  s.begin(9600);
  lcd.init();                      
  lcd.backlight();
  lcd.init();                     
  lcd.backlight();
  
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("NodeMCU");
  lcd.setCursor(0, 1);
  lcd.print("Starting . .");

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("connected: ");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(2000);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(D8,OUTPUT);
  digitalWrite(D8,LOW);
}


int c = 0;
bool flag = true;
bool flag2 = false;
void loop() {

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Arduino");
  lcd.setCursor(0,1);
  lcd.print("Reboot . .");
  digitalWrite(D8,HIGH);
  delay(100);
  digitalWrite(D8,LOW);
  c = 0;
  int i = 0;
  while(c<6 && i<500){
    if(s.available()>0){

    data = s.read();
    arr[c] = data;
    c++;
    }
    i++;
  }

  if(arr[0]>100){
    flag2 = true;
  }else{
    flag2 = false;
  }
  if(flag){
    digitalWrite(D0,HIGH);
  }
  else{
    digitalWrite(D0,LOW);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("T:"+String(arr[1])+" H:"+String(arr[2])+" D:"+String(arr[0]));
  lcd.setCursor(0,1);
  lcd.print(" "+String(arr[3])+" "+String(arr[4])+" "+String(arr[5]));
  delay(3000);
  //Dust 0
  //Temp 1
  //Hum  2
  //MQ4  3
  //MQ8  4
  //MQ9  5

  while (Serial.available() > 0 && flag)
  {
    
    if (gps.encode(Serial.read()))
    {
      if (gps.location.isValid())
      {
        flag = false;
        
        la = gps.location.lat();
        lo = gps.location.lng();
 
        String LAT = String(la*100);
        String LNG = String(lo*100);
        
        LAT[4] = LAT[3];
        LAT[3] = LAT[2];
        LAT[2] = ',';
        LNG[4] = LNG[3];
        LNG[3] = LNG[2];
        LNG[2] = ',';
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("LAT:"+LAT);
        lcd.setCursor(0,1);
        lcd.print("LNG:"+LNG);
        delay(2000);
        
        String str = LAT+" "+LNG+"/";
        
        Firebase.setFloat(str+"Dust", float(arr[0]) );
        Firebase.setFloat(str+"Temperature", float(arr[1]) );
        Firebase.setFloat(str+"Humidity", float(arr[2]) );
        Firebase.setFloat(str+"MQ4", float(arr[3]) );
        Firebase.setFloat(str+"MQ8", float(arr[4]) );
        Firebase.setFloat(str+"MQ9", float(arr[5]) );
        Firebase.setFloat(str+"LAT", float(la) );
        Firebase.setFloat(str+"LNG", float(lo) );
        if (Firebase.failed()) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("(T) Firebase");
          lcd.setCursor(0,1);
          lcd.print("Upload Failed");
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("(T) Firebase");
          lcd.setCursor(0,1);
          lcd.print("Upload Success");
        }
        delay(2000);
      }
      else{

        flag = false;
        
        String LAT = String(la*100);
        String LNG = String(lo*100);
        
        LAT[4] = LAT[3];
        LAT[3] = LAT[2];
        LAT[2] = ',';
        LNG[4] = LNG[3];
        LNG[3] = LNG[2];
        LNG[2] = ',';
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("LAT:"+LAT);
        lcd.setCursor(0,1);
        lcd.print("LNG:"+LNG);
        delay(2000);
        
        String str = LAT+" "+LNG+"/";
        
        Firebase.setFloat(str+"Dust", float(arr[0]) );
        Firebase.setFloat(str+"Temperature", float(arr[1]) );
        Firebase.setFloat(str+"Humidity", float(arr[2]) );
        Firebase.setFloat(str+"MQ4", float(arr[3]) );
        Firebase.setFloat(str+"MQ8", float(arr[4]) );
        Firebase.setFloat(str+"MQ9", float(arr[5]) );
        Firebase.setFloat(str+"LAT", float(la) );
        Firebase.setFloat(str+"LNG", float(lo) );
        if (Firebase.failed()) {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("(F) Firebase");
          lcd.setCursor(0,1);
          lcd.print("Upload Failed");
        }
        else{
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("(F) Firebase");
          lcd.setCursor(0,1);
          lcd.print("Upload Success");
        }
        delay(2000);
      }
    }
  }
  flag = true;
}
