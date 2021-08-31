/*
This is the source code to operate a Simon Says game with a piezo speaker,
four arcade buttons in different colours, each with 6 LEDs of a matching colour.

CONNECTIONS:

Passive Speaker       ARDUINO
-                     GND
+                     D7

LED Transisitors      ARDUINO
Blue                  D3
Green                 D4
Yellow                D5
Red                   D6

Arcade Buttons        ARDUINO
Blue                  D8
Green                 D9
Yellow                D10
Red                   D11
*/

#include <Arduino.h>

#define BLUE_LEDS      3
#define GREEN_LEDS     4
#define YELLOW_LEDS    5
#define RED_LEDS       6
#define SPEAKER_PIN    7
#define BLUE_BUTTON    8
#define GREEN_BUTTON   9
#define YELLOW_BUTTON  10
#define RED_BUTTON     11

int red_val = 1;

void setup() {
  // Start serial connection to PC
  Serial.begin(9600);

  // Set the mode of all the pins we're using
  pinMode(BLUE_LEDS, OUTPUT);
  pinMode(GREEN_LEDS, OUTPUT);
  pinMode(YELLOW_LEDS, OUTPUT);
  pinMode(RED_LEDS, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(YELLOW_BUTTON, INPUT_PULLUP);
  pinMode(RED_BUTTON, INPUT_PULLUP);

  // Write initial values to outputs
  digitalWrite(BLUE_LEDS, LOW);
  digitalWrite(GREEN_LEDS, LOW);
  digitalWrite(YELLOW_LEDS, LOW);
  digitalWrite(RED_LEDS, LOW);
  noTone(SPEAKER_PIN);
}

void loop() {
  if (digitalRead(BLUE_BUTTON) == LOW) {
    tone(SPEAKER_PIN, 523);
    digitalWrite(BLUE_LEDS, HIGH);
  } else {
    digitalWrite(BLUE_LEDS, LOW);
  }

  if (digitalRead(GREEN_BUTTON) == LOW) {
    tone(SPEAKER_PIN, 587);
    digitalWrite(GREEN_LEDS, HIGH);
  } else {
    digitalWrite(GREEN_LEDS, LOW);
  }

  if (digitalRead(YELLOW_BUTTON) == LOW) {
    tone(SPEAKER_PIN, 659);
    digitalWrite(YELLOW_LEDS, HIGH);
  } else {
    digitalWrite(YELLOW_LEDS, LOW);
  }

  if (digitalRead(RED_BUTTON) == LOW) {
    tone(SPEAKER_PIN, 698);
    digitalWrite(RED_LEDS, HIGH);
  } else {
    digitalWrite(RED_LEDS, LOW);
  }

  if (digitalRead(BLUE_BUTTON) == HIGH &&
      digitalRead(GREEN_BUTTON) == HIGH &&
      digitalRead(YELLOW_BUTTON) == HIGH &&
      digitalRead(RED_BUTTON) == HIGH) {
    noTone(SPEAKER_PIN);
  }
}
