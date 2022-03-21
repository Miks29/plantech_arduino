
const int lightSensor = A4;                                      //Light sensor pin in arduino
int lightSensorValue = 0;                                         //somewhere to store the value read from the light sensor
String lightSensorReading;
const int light = 5;

void setup() {
  pinMode(lightSensor,INPUT);
  digitalWrite(light,LOW);
  pinMode(light,OUTPUT);
  Serial.begin(9600);
}

void loop() {
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
}
