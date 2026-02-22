#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','4','7','*'},
  {'2','5','8','0'},
  {'3','6','9','#'},
  {'A','B','C','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {13, 12, 11, 10};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const int ledAlb1Pin = 3;
const int ledAlb2Pin = 5;
const int senzorLuminaPin = A0;

int intensitateAlb1 = 0;  // 0-9, controlat de tastatura

void setup() {
  Serial.begin(9600);
  pinMode(ledAlb1Pin, OUTPUT);
  pinMode(ledAlb2Pin, OUTPUT);
  Serial.println("Start control led alb si lumina ambientala");
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    Serial.print("Tasta detectata: ");
    Serial.println(key);

    if (key >= '0' && key <= '9') {
      intensitateAlb1 = key - '0';
    } else if (key == 'A') {
      intensitateAlb1 = 0;
    }
  }

  int pwmAlb1 = map(intensitateAlb1, 0, 9, 0, 255);
  analogWrite(ledAlb1Pin, pwmAlb1);

  int valoareLumina = analogRead(senzorLuminaPin);
  Serial.print("Valoare senzor lumina: ");
  Serial.println(valoareLumina);



  int intensitateAlb2;

 
    intensitateAlb2= map(valoareLumina, 0, 1023, 255, 0); 
  analogWrite(ledAlb2Pin,  intensitateAlb2);

  Serial.print("Intensitate alb1: ");
  Serial.print(pwmAlb1);
  Serial.print(" | Intensitate alb2: ");
  Serial.println(intensitateAlb2);

  delay(100);
}
