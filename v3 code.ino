#include <Wire.h>
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
  Wire.begin(); // Initialisation de la communication I2C
  AFMS.begin(); // Initialisation du shield de moteurs
  Serial.begin(9600); // Initialisation de la communication série pour le debug
}

void loop() {
  // Lire la distance du capteur LiDAR avant
  distanceFront = getDistance(LIDAR_ADDRESS);
  Serial.print("Distance Front: ");
  Serial.println(distanceFront);

  // Lire la distance du capteur LiDAR arrière (si installé)
  distanceBack = getDistance(LIDAR_ADDRESS); // Changez l'adresse si un second capteur est utilisé
  Serial.print("Distance Back: ");
  Serial.println(distanceBack);

  // Contrôler les moteurs de vibration en fonction de la distance
  controlVibration(vibrator1, distanceFront);
  controlVibration(vibrator2, distanceBack);

  delay(100); // Délai pour éviter de surcharger le capteur
}

int getDistance(int address) {
  Wire.beginTransmission(address);
  Wire.write(LIDAR_MEASURE); // Envoie la commande de mesure
  Wire.endTransmission();

  delay(20); // Temps d'attente pour la mesure

  Wire.beginTransmission(address);
  Wire.write(LIDAR_DISTANCE); // Demande la distance mesurée
  Wire.endTransmission();

  Wire.requestFrom(address, 2); // Demande 2 octets depuis le capteur
  if (Wire.available() >= 2) {
    int distance = Wire.read() << 8; // Premier octet
    distance |= Wire.read(); // Second octet
    return distance;
  } else {
    return -1; // Retourne -1 en cas d'erreur de lecture
  }
}

void controlVibration(Adafruit_DCMotor *vibrator, int distance) {
  if (distance > 0 && distance < 2000) { // Vérifie si la distance est dans une plage valide
    int speed = map(distance, 0, 2000, 255, 0); // Ajuste la vitesse de 0 à 255 selon la distance
    vibrator->setSpeed(speed);
    vibrator->run(FORWARD);
  } else {
    vibrator->setSpeed(0); // Arrête le moteur si la distance est hors plage
    vibrator->run(RELEASE);
  }
}
