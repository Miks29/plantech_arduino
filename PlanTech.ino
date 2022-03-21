#include <elapsedMillis.h>

elapsedMillis soilMoistureTimer;
elapsedMillis amountToPumpTimer;
elapsedMillis wifiReadsensorTimer;

//pins in arduino
const int moistureSensor=A0;                                     // Soil moisture sensor pin in arduino
const int moistureRelay=3;                                       // Relay pin in arduino to on and off the pump
const int waterLevelSensor =A2;                              // Analog pin water level sensor is connected to
const int lightSensor = A4;                                      //Light sensor pin in arduino
const int light = 4;

// Values that can be edited
int soilMoistureInterval = 5400000;                                      //time to wait before checking the soil moisture level - default it to an hour = 1800000
int soilMoistureThreshold = 500;                                  // threshold for the soil moisture to detect to start pumping water
int waterLevelThreshold = 300;                                    // threshold for a low water level in the water container
int amountToPump = 5000;                                           // how long in milliseconds the pump should pump water for when the plant needs it

// Global temp values
int WaterLevelsensorValue = 0;                                      // somewhere to store the value read from the water level sensor
int SoilmoistureSensorValue = 0;                                       //somewhere to store the value read from the soil moisture sensor
int lightSensorValue = 0;                                         //somewhere to store the value read from the light sensor
String lightSensorReading = "Dark";
String values;

void setup() {
pinMode(moistureSensor,INPUT);
pinMode(waterLevelSensor,INPUT);
pinMode(lightSensor,INPUT);
pinMode(moistureRelay,OUTPUT);
digitalWrite(moistureRelay,HIGH);
pinMode(light,OUTPUT);
Serial.begin(9600);
delay(2000);
}

void loop() {
  // get sensors data and put in to values variables as a string.
   values = (soil_data()+','+water_level_data()+','+light_sensor_data()); 
       delay(1000);
       // removed any buffered previous serial data.
       Serial.flush();
       delay(1000);
       // sent sensors data to serial (sent sensors data to ESP8266)
       Serial.print(values);
       delay(2000);
}

String soil_data(){
  //check soil moisture data
//if (soilMoistureTimer >= soilMoistureInterval)                       //check if timer is equal to three hours to check the soil moisture again
    //{
      soilMoistureInterval = 0;  //reset timer to 0
      SoilmoistureSensorValue = analogRead(moistureSensor);       //read the moisture sensor and save the value
      //Serial.print("Soil moisture sensor is currently: ");
      //Serial.print(SoilmoistureSensorValue);
      Serial.println();

      if (SoilmoistureSensorValue < soilMoistureThreshold){         //check if sensorvalue is less than 500                                         
        digitalWrite(moistureRelay, HIGH);
          //Serial.println("pump on");                              //pulse the pump 
          delay(amountToPump);               //seconds to keep the pumping of water
        digitalWrite(moistureRelay, LOW);                       //stop the pump
        // Serial.println("pump off");
         amountToPumpTimer = 0;                                 //reset timer to 0
         String soilData = String(SoilmoistureSensorValue);
         return String(soilData);
      }
}
  
String water_level_data(){
  // check water level sensor
  WaterLevelsensorValue = analogRead(waterLevelSensor);              //read the value of the water level sensor
  //Serial.print("Water level sensor value: ");                     //print it to the serial monitor
  //Serial.println(WaterLevelsensorValue);
   Serial.println();
  delay(1000);
  String waterData = String(WaterLevelsensorValue);
  return String(waterData);
}

String light_sensor_data(){
  // check light level sensor
    
  String lightData = lightSensorReading;
  lightSensorValue = analogRead(lightSensor);                        // reads the input on analog pin A0 (value between 0 and 1023)
  Serial.print("Analog reading: ");
  Serial.print(lightSensorValue);                               // the raw analog reading
   Serial.println(); 
  // We'll have a few threshholds, qualitatively determined
  if (lightSensorValue > 850) {
    lightSensorReading = "Dark";
     digitalWrite(light, LOW);
    //Serial.println(lightSensorReading);
  } else {
    lightSensorReading = "Very Bright";
    digitalWrite(light, HIGH  );
    //Serial.println(lightSensorReading);
  }
  return String(lightData);
}
