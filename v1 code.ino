#include <Wire.h>
#include <Adafruit_VL53L0X.h>

#define VIBRATION_PIN 9

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  pinMode(VIBRATION_PIN, OUTPUT);
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  Serial.println(F("VL53L0X ready"));
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  lox.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {  // if the sensor is not out of range
    int distance = measure.RangeMilliMeter;
    Serial.print("Distance (mm): "); Serial.println(distance);
    int vibration_strength = map(distance, 30, 2000, 255, 0); // Mapping distance to vibration strength
    vibration_strength = constrain(vibration_strength, 0, 255); // Ensure it's between 0 and 255
    analogWrite(VIBRATION_PIN, vibration_strength);
  } else {
    Serial.println("Out of range");
    analogWrite(VIBRATION_PIN, 0); // No vibration if out of range
  }
  delay(100);
}
