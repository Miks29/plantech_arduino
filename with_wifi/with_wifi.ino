#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <DNSServer.h>

//firebase and wifi
#define FIREBASE_HOST "plantech-9bf52-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "FCdLjOCPshJhLCxr3rsgtXqxXjyPiWqxQ9vBoLu6"

// Global temp values
String values,sensor_data;
String light_level_value = "Dark";

void setup() {
Serial.begin(9600);
//wifi credentials
WiFiManager wifiManager;
wifiManager.resetSettings();
wifiManager.startConfigPortal("PlanTech");

Serial.println("connected...yeey :)");
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(2000);
}

void loop() {
   Firebase.setString("Connection","connected");
   
bool Sr =false;
  while(Serial.available()){
        //get sensor data from serial put in sensor_data
        sensor_data=Serial.readString(); 
        Sr=true;    
    }
    delay(1000);

  if(Sr==true){  
    
  values=sensor_data;
  
  //get comma indexes from values variable
  int firstCommaIndex = values.indexOf(',');
  String soil_moisture_value = values.substring(0, firstCommaIndex);
  
  int secondCommaIndex = values.indexOf(',', firstCommaIndex+1);
  String water_level_value = values.substring(firstCommaIndex+1, secondCommaIndex);
  
  int thirdCommaIndex = values.indexOf(',', secondCommaIndex+1);
  String light_level_value = values.substring(secondCommaIndex+1);
  
  //get sensors data from values variable by  spliting by commas and put in to variables  
  
  //store soil moisture sensor data in firebase 
  Firebase.setFloat("Soil moisture value",soil_moisture_value.toFloat());
   delay(10);
  //store water level sensor data in firebase 
  Firebase.setFloat("Water level value",water_level_value.toFloat());
   delay(10);
  //store light level sensor data in firebase 
  Firebase.setString("Light level",light_level_value);
 

  delay(1000);
  
  //store previous sensors data as string in firebase
  
/*  Firebase.pushFloat("Previous soil moisture value",soil_moisture_value);
   delay(10);
  Firebase.pushFloat("Previous water level value",water_level_value);
   delay(10);
  Firebase.pushString("Previous light sensor reading",light_level_value);
  
  
  delay(1000);
  */
  if (Firebase.failed()) {  
      return;
  }
}   
}
