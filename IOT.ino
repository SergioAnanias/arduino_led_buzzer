
#include "BluetoothSerial.h"
#include <EasyBuzzer.h>
#include <analogWrite.h>
byte freq;
int LED_RED = 21;
int LED_WHITE = 22;
int LED_BLUE = 23;
int BUZZER_PIN = 14;
int POTValue;
int LDRValue;
char command;
BluetoothSerial SerialBT;
void setup() {
  Serial.begin(9600);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  SerialBT.begin("ESP32test");
  EasyBuzzer.setPin(BUZZER_PIN);
}

void loop() {
  if (SerialBT.available()) {
    command = SerialBT.read();
    SerialBT.flush();
  }
  if (command == '1') {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_WHITE, LOW);
    while (!SerialBT.available()) {
      Serial.println(analogRead(34));
      POTValue = analogRead(34);
      EasyBuzzer.update();
      EasyBuzzer.beep(POTValue);
    }
  }
  if (command == '2') {
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_WHITE, LOW);
    digitalWrite(LED_RED, LOW);
    while (!SerialBT.available()) {
      Serial.println(analogRead(15));
      LDRValue = analogRead(15);
      EasyBuzzer.update();
      EasyBuzzer.beep(LDRValue);
    }

  }

  if (command == '3') {
    EasyBuzzer.stopBeep();
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_WHITE, HIGH);
    delay(5000);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_WHITE, LOW);
    delay(1000);
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_WHITE, HIGH);
    delay(2000);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_WHITE, LOW);
    SerialBT.flush();
    command='4';
  }
}
