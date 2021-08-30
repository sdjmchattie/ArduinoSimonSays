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
#include "MarioFanfare.h"

#define SPEAKER_PIN  7

MarioFanfare marioFanfare(SPEAKER_PIN);

void setup() {
  Serial.begin(9600);  // start serial to PC
  marioFanfare.startPlayback();
}

void loop() {
  marioFanfare.update();
}
