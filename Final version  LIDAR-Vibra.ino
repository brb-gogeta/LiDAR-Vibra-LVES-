#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <Adafruit_MotorShield.h>
#include <Adafruit_SleepyDog.h>

// Configuration des capteurs LiDAR et des moteurs de vibration
Adafruit_VL53L0X lidarFront = Adafruit_VL53L0X();
Adafruit_VL53L0X lidarBack = Adafruit_VL53L0X(); // Ajout d'un second capteur pour l'arrière
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *vibratorFront = AFMS.getMotor(1);
Adafruit_DCMotor *vibratorBack = AFMS.getMotor(2);

// Seuils de distance en millimètres
const int minDistance = 30;
const int maxDistance = 2000;
const int lowPowerThreshold = 50;  // Valeur pour le mode basse consommation

// Variables pour stocker les distances
int distanceFront = 0;
int distanceBack = 0;

// Optimisation de la gestion d'énergie
bool lowPowerMode = false;

void setup() {
  Serial.begin(115200);
  
  // Initialisation des capteurs LiDAR
  if (!lidarFront.begin() || !lidarBack.begin()) {
    Serial.println(F("Échec d'initialisation des capteurs VL53L0X"));
    while (1);  // Boucle infinie si les capteurs échouent
  }

  Serial.println(F("Capteurs VL53L0X prêts"));
  
  // Initialisation du moteur de vibration
  AFMS.begin();  // Démarrage du shield moteur

  // Réglages d'économie d'énergie
  Watchdog.enable(8000);  // Configurer le Watchdog pour un redémarrage en cas de blocage
  setLowPowerMode(false); // Mode de démarrage normal
}

void loop() {
  Watchdog.reset();  // Réinitialisation du Watchdog pour prévenir les redémarrages intempestifs

  // Lecture des distances des capteurs LiDAR
  distanceFront = getDistance(lidarFront);
  distanceBack = getDistance(lidarBack);

  // Affichage des distances pour debug
  Serial.print("Distance Avant: ");
  Serial.println(distanceFront);
  Serial.print("Distance Arrière: ");
  Serial.println(distanceBack);

  // Contrôler les moteurs de vibration en fonction des distances
  controlVibration(vibratorFront, distanceFront);
  controlVibration(vibratorBack, distanceBack);

  // Basculer en mode basse consommation si aucune détection d'obstacle
  if (distanceFront > maxDistance && distanceBack > maxDistance) {
    setLowPowerMode(true);
  } else {
    setLowPowerMode(false);
  }

  delay(100);  // Délai pour éviter de surcharger les capteurs
}

// Fonction pour lire la distance d'un capteur LiDAR
int getDistance(Adafruit_VL53L0X &lidar) {
  VL53L0X_RangingMeasurementData_t measure;
  lidar.rangingTest(&measure, false);

  if (measure.RangeStatus != 4) {  // Capteur opérationnel
    return measure.RangeMilliMeter;
  } else {
    return maxDistance + 1;  // Retourner une valeur hors plage pour éviter les erreurs
  }
}

// Fonction pour contrôler les vibrations en fonction de la distance
void controlVibration(Adafruit_DCMotor *vibrator, int distance) {
  if (distance >= minDistance && distance <= maxDistance) {
    int speed = map(distance, minDistance, maxDistance, 255, 0);  // Ajustement de l'intensité
    vibrator->setSpeed(speed);
    vibrator->run(FORWARD);  // Activation du moteur
  } else {
    vibrator->setSpeed(0);  // Arrêt du moteur en dehors de la plage de distance
    vibrator->run(RELEASE);
  }
}

// Fonction pour gérer le mode basse consommation
void setLowPowerMode(bool activate) {
  if (activate && !lowPowerMode) {
    Serial.println(F("Mode basse consommation activé"));
    analogWrite(A0, 0);  // Désactivation des composants inutiles
    lowPowerMode = true;
  } else if (!activate && lowPowerMode) {
    Serial.println(F("Mode normal activé"));
    analogWrite(A0, 255);  // Réactivation des composants
    lowPowerMode = false;
  }
}
