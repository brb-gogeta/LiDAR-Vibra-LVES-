#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_MotorShield.h>

// Configuration du capteur LiDAR
#define LIDAR_ADDRESS 0x62
#define LIDAR_MEASURE 0x00
#define LIDAR_DISTANCE 0x8f

// Configuration des moteurs de vibration
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *vibrator1 = AFMS.getMotor(1);
Adafruit_DCMotor *vibrator2 = AFMS.getMotor(2);

// Variables pour stocker les distances
int distanceFront = 0;
int distanceBack = 0;

void setup() {
  Wire.begin();
  AFMS.begin();
  Serial.begin(9600);
}

void loop() {
  // Lire la distance du capteur LiDAR avant
  distanceFront = getDistance(LIDAR_ADDRESS);
  Serial.print("Distance Front: ");
  Serial.println(distanceFront);

  // Lire la distance du capteur LiDAR arrière (si installé)
  distanceBack = getDistance(LIDAR_ADDRESS);
  Serial.print("Distance Back: ");
  Serial.println(distanceBack);

  // Contrôler les moteurs de vibration en fonction de la distance
  controlVibration(vibrator1, distanceFront);
  controlVibration(vibrator2, distanceBack);

  delay(100);
}

int getDistance(int address) {
  Wire.beginTransmission(address);
  Wire.write(LIDAR_MEASURE);
  Wire.endTransmission();
  delay(20);
  Wire.beginTransmission(address);
  Wire.write(LIDAR_DISTANCE);
  Wire.endTransmission();
  Wire.requestFrom(address, 2);
  int distance = Wire.read() << 8;
  distance |= Wire.read();
  return distance;
}

void controlVibration(Adafruit_DCMotor *vibrator, int distance) {
  int speed = map(distance, 0, 2000, 255, 0); // Ajuster la plage de distance
  vibrator->setSpeed(speed);
  vibrator->run(FORWARD);
}
