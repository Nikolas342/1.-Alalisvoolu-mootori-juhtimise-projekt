// Viikude määramine (H-sild / L298N)
const int pinENA = 9;  // PWM viik (kiirus)
const int pinIN1 = 8;  // Suunaviik 1
const int pinIN2 = 7;  // Suunaviik 2

int hetkeKiirus = 0;   // Mootori praegune kiirus (0-255)
int sihtKiirus = 255;  // Soovitud kiirus
bool isRunning = false;
bool suundEdasi = true; // true = päripäeva, false = vastupäeva

void setup() {
  pinMode(pinENA, OUTPUT);
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);

  // Alguses mootor seisab
  seadistaSuund(suundEdasi);
  analogWrite(pinENA, 0);

  Serial.begin(9600);
  while (!Serial) { ; }

  Serial.println("--- DC Mootori Juhtimine ---");
  Serial.println("Käsud: 'start', 'stop', 'dir' (suund), '0-255' (kiirus)");
}

void loop() {
  // Loe Seriast sisendit
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.length() == 0) return;

    if (input.equalsIgnoreCase("start")) {
      isRunning = true;
      Serial.println("Mootor käivitatud.");
    } 
    else if (input.equalsIgnoreCase("stop")) {
      isRunning = false;
      Serial.println("Mootor peatatud.");
    } 
    else if (input.equalsIgnoreCase("dir")) {
      suundEdasi = !suundEdasi;
      seadistaSuund(suundEdasi);
      Serial.print("Suund muudetud: ");
      Serial.println(suundEdasi ? "Edasi (CW)" : "Tagasi (CCW)");
    } 
    else if (input.toInt() > 0 || input == "0") {
      int val = input.toInt();
      if (val >= 0 && val <= 255) {
        sihtKiirus = val;
        Serial.print("Uus sihtkiirus: ");
        Serial.println(sihtKiirus);
      } else {
        Serial.println("Viga: Kiirus peab olema 0-255!");
      }
    }
  }

  // Sujuv kiirendus ja aeglustus (Ramp loogika)
  aeglustaJaMuudaKiirust();
}

// Mootori pöörlemissuuna määramine
void seadistaSuund(bool edasi) {
  if (edasi) {
    digitalWrite(pinIN1, HIGH);
    digitalWrite(pinIN2, LOW);
  } else {
    digitalWrite(pinIN1, LOW);
    digitalWrite(pinIN2, HIGH);
  }
}

// Sujuv kiiruse muutmine (0.015 sekundi tagant 1 samm)
void aeglustaJaMuudaKiirust() {
  static unsigned long viimaneAeg = 0;
  if (millis() - viimaneAeg >= 15) { // 15 ms sammu vahe
    viimaneAeg = millis();

    int soovitav = isRunning ? sihtKiirus : 0;

    if (hetkeKiirus < soovitav) {
      hetkeKiirus++;
    } else if (hetkeKiirus > soovitav) {
      hetkeKiirus--;
    }

    analogWrite(pinENA, hetkeKiirus);
  }
}