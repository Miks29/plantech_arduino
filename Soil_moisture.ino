#include <elapsedMillis.h>

elapsedMillis soilMoistureTimer;
elapsedMillis amountToPumpTimer;

const int moistureSensor=A0;                                     // Soil moisture sensor pin in arduino
const int moistureRelay=3;                                       // Relay pin in arduino to on and off the pump

int checkInterval = 5400000;                                      //time to wait before checking the soil moisture level - default it to an hour = 1800000
int soilMoistureThreshold = 500;                                  // threshold for the soil moisture to detect to start pumping water
int amountToPump = 10000;                                           // how long in milliseconds the pump should pump water for when the plant needs it

int SoilmoistureSensorValue = 0;                                       //somewhere to store the value read from the soil moisture sensor

void setup() {
  pinMode(moistureSensor,INPUT);
  pinMode(moistureRelay,OUTPUT);
  digitalWrite(moistureRelay,HIGH);
  Serial.begin(9600);
}

void loop() {
  // check soil moisture level
//if (soilMoistureTimer >= checkInterval)                       //check if timer is equal to three hours to check the soil moisture again
    //{
      soilMoistureTimer = 0;  //reset timer to 0
      SoilmoistureSensorValue = analogRead(moistureSensor);       //read the moisture sensor and save the value
      Serial.print("Soil moisture sensor is currently: ");
      Serial.print(SoilmoistureSensorValue);

      if (SoilmoistureSensorValue < soilMoistureThreshold){         //check if sensorvalue is less than 500                                         
        digitalWrite(moistureRelay, HIGH);
          Serial.println(" pump on");                              //pulse the pump 
          if (amountToPumpTimer > amountToPump){                     //seconds to keep the pumping of water
        digitalWrite(moistureRelay, LOW);                       //stop the pump
         Serial.println(" pump off");
         amountToPumpTimer = 0;                         //reset timer to 0
          }
    }
//}
}
