# LIDAR-Vibra (LVES) - LiDAR Feedback System

## Overview
LIDAR-Vibra (LVES) est un système de rétroaction tactile conçu pour aider les personnes malvoyantes en utilisant un capteur LiDAR pour mesurer la distance et fournir une rétroaction par vibration en fonction de la proximité des objets. Ce projet intègre un Arduino avec un capteur LiDAR (VL53L0X) et des moteurs de vibration pour créer une solution accessible à la navigation.

## Features
- **Mesure de Distance en Temps Réel** : Utilise un capteur LiDAR (VL53L0X) pour mesurer la distance aux objets proches.
- **Rétroaction par Vibration** : Fournit une rétroaction par vibrations grâce à des moteurs qui changent d’intensité en fonction de la proximité des obstacles.
- **Intégration Simple avec Arduino** : Ce projet est conçu avec Arduino, ce qui facilite son déploiement et sa modification pour différents cas d’utilisation.

## Components
- **Arduino Uno** (ou toute autre carte compatible Arduino)
- **Capteur LiDAR** : VL53L0X ou similaire
- **Moteurs de Vibration** : Disques de moteur vibrant mini Adafruit
- **Transistor** : 2N2222 (pour contrôler l’alimentation des moteurs)
- **Source d’Alimentation** : Batterie rechargeable LiPo 3.7V
- **Câblage** : Fils de connexion, connecteurs
- **Divers** : Résistances, boutons poussoirs, LEDs, matériaux de montage

## Installation

### Prérequis
- Installe l'[IDE Arduino](https://www.arduino.cc/en/software) si tu ne l’as pas déjà.
- Installe les bibliothèques nécessaires pour le capteur LiDAR. Ouvre l’IDE Arduino et va dans **Sketch -> Include Library -> Manage Libraries**, puis cherche **Adafruit VL53L0X** et installe-le.

### Téléversement du Code
1. Connecte ton Arduino à ton ordinateur via un câble USB.
2. Télécharge ou clone ce repository.
3. Ouvre le fichier `.ino` dans l’IDE Arduino.
4. Sélectionne le bon type de carte et le bon port (par exemple **Arduino Uno**).
5. Clique sur le bouton **Upload** dans l’IDE Arduino pour téléverser le code sur ton Arduino.

### Schéma de Câblage
1. **Capteur LiDAR (VL53L0X)** :
   - Connecte la broche **VCC** du LiDAR à la broche **5V** de l’Arduino.
   - Connecte la broche **GND** du LiDAR à la broche **GND** de l’Arduino.
   - Connecte la broche **SCL** du LiDAR à la broche **A5** (SCL) de l’Arduino.
   - Connecte la broche **SDA** du LiDAR à la broche **A4** (SDA) de l’Arduino.
   
2. **Moteurs de Vibration** :
   - Connecte les moteurs de vibration aux broches numériques de l’Arduino (par exemple, **D9**).
   - Utilise un transistor (par exemple, **2N2222**) pour contrôler l’alimentation des moteurs, en connectant le terminal positif du moteur à l’alimentation 5V et le terminal négatif à la broche collecteur du transistor.
   
3. **Alimentation** :
   - Utilise une batterie rechargeable **LiPo 3.7V** pour alimenter le circuit. Connecte le terminal positif de la batterie à la broche **5V** et le terminal négatif à **GND**.

## Explication du Code

Le code utilise la bibliothèque **Adafruit VL53L0X** pour interagir avec le capteur LiDAR et mesurer la distance aux objets proches. En fonction de la distance mesurée, le code ajuste l’intensité des vibrations des moteurs connectés. Plus l’objet est proche, plus les vibrations seront fortes.

### Fonctions Clés :
- `setup()`: Initialise le capteur LiDAR et les broches des moteurs de vibration.
- `loop()`: Lit la distance à partir du capteur LiDAR et ajuste les moteurs de vibration en fonction de la proximité.
- `map()`: Mappe la distance mesurée à l’intensité des vibrations, fournissant ainsi une expérience de rétroaction tactile.

## Utilisation

Une fois le matériel connecté et le code téléversé sur l’Arduino :
1. Place le système sur un vêtement portable (comme un gilet).
2. Allume le système.
3. Le capteur LiDAR commencera à mesurer les distances.
4. Les moteurs de vibration fourniront des retours en fonction de la distance, les vibrations devenant plus fortes lorsque l’objet est plus proche.

## Contribuer
N’hésite pas à forker ce repository et à apporter des améliorations. Les contributions, les rapports de bogues et les demandes de fonctionnalités sont toujours les bienvenues !

### Exemple de Contributions :
- Améliorer le code pour gérer plusieurs capteurs LiDAR.
- Créer un design plus ergonomique pour le vêtement portable.
- Améliorer le système de rétroaction pour différents cas d’utilisation.

## License
Ce projet est sous licence MIT - voir le fichier [LICENSE.md](LICENSE.md) pour plus de détails.

## Remerciements
- Adafruit pour le capteur **VL53L0X** et les shields de moteur.
- La communauté Arduino pour sa documentation et son support exceptionnels.
- Tous ceux qui contribuent à améliorer l’accessibilité par la technologie.
