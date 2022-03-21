//install wifi manager from library

#include <WiFiManager.h>
WiFiManager wifiManager;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

//wifi credentials
wifiManager.autoConnect("Access point name/wifi name", "password");
}

void loop() {
  // put your main code here, to run repeatedly:

}
