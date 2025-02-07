// Définir la broche connectée au capteur YF-S201
const int flowPin = 2;  // Broche numérique D2 (peut être ajustée)
volatile int flowCount = 0;  // Compteur d'impulsions

// Variables pour le calcul du débit
float flowRate = 0.0;  // Débit en L/min
unsigned long lastTime = 0;  // Dernier temps de lecture

void setup() {
  // Initialisation de la communication série
  Serial.begin(9600);

  // Initialiser la broche de capteur comme entrée avec une interruption
  pinMode(flowPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowPin), countFlow, RISING);  // Compter les impulsions sur front montant
}

void loop() {
  // Calculer le débit tous les 1 seconde
  if (millis() - lastTime >= 1000) {
    // Calculer le débit en L/min
    flowRate = (flowCount / 7.5);  // 7.5 impulsions correspondent à 1 litre d'eau

    // Check si le debit est inférieur au seuil
    if (flowRate < 0.5) {
      // Afficher le msg de fuite
      Serial.println("Il y a une fuite dans le système !");
    }
    else {
      Serial.println("Tout est à marche !");
    }

    // Réinitialiser le compteur d'impulsions
    flowCount = 0;
    lastTime = millis();
  }
}

// Fonction d'interruption pour compter les impulsions
void countFlow() {
  flowCount++;  // Incrémenter le compteur d'impulsions à chaque passage d'eau
}
