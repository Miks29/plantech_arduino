
const int waterLevelSensor =A3;                              // Analog pin water level sensor is connected to
int waterLevelThreshold = 300;                                    // threshold for a low water level in the water container

void setup() {
  pinMode(waterLevelSensor,INPUT);
  Serial.begin(9600);
}

void loop() {
  // check water level sensor
    WaterLevelsensorValue = analogRead(waterLevelSensor);              //read the value of the water level sensor
  Serial.print("Water level sensor value: ");                     //print it to the serial monitor
  Serial.println(WaterLevelsensorValue);

}
