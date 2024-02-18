#include <SparkFun_Bio_Sensor_Hub_Library.h>
#include <Wire.h>
 
const int resPin = 4; // Reset pin for cortexM4 processor
const int mfioPin = 5; // Data collection mode

// Sensor Hub requirements for processing the data
SparkFun_Bio_Sensor_Hub bioHub(resPin, mfioPin);

bioData body; // Original oximeter & heart rate sensor variable
// bioData bp;

void setup() {

  Serial.begin(115200);
  Wire.begin();
  int result = bioHub.begin();
  if (!result) // Zero errors!
    Serial.println("Sensor started!");
  else
    Serial.println("Could not communicate with the sensor!!!");
  
  Serial.println("Configuring Sensor...");
  int error = bioHub.configBpm(MODE_ONE); // COnfiguring just the BPM settings.
  if (!error) { // Zero errors!
    Serial.println("Sensor configured.");
  }
  else {
    Serial.println("Error configuring sensor.");
    Serial.print("Error: ");
    Serial.println(error);
  }
  // Data lags a bit behind the sensor, if your finger is on the sensor when
  // it's being configured this delay will give some time for the data to catch up.
  delay(4000);
}

void loop(){
  // Information from the readBpm function will be saved to our "body" variable
  body = bioHub.readBpm();
  // bp = 1
  Serial.print("Heartrate: ");
  Serial.println(body.heartRate); // Display heartRate on serial monitor
  Serial.print("Confidence: ");
  Serial.println(body.confidence); // Display data acquisition confidence level
  Serial.print("Oxygen: ");
  Serial.println(body.oxygen); // Display oxygen level
  Serial.print("Blood Pressure: ");
  // Serial.println(bp); // Display BP level from PPG peak
  Serial.print("Status: ");
  Serial.println(body.status); // Display if anything is detected by sensor
  delay(250); // Delay for sensor stabilization
}