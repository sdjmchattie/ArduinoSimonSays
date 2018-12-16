/*
This is the source code to operate a Simon Says game with a piezo speaker,
four arcade buttons in different colours, each with 6 LEDs of a matching colour.

CONNECTIONS:

Passive Speaker       ARDUINO
-                     GND
+                     D2

LED Transisitors      ARDUINO
Blue                  D3
Green                 D4
Yellow                D5
Red                   D6

Arcade Buttons        ARDUINO
Blue                  D7
Green                 D8
Yellow                D9
Red                   D10
*/

#include <Arduino.h>

#include "Melody.h"
#include "Notes.h"

#define SPEAKER_PIN  2

#define CROTCHET     4
#define MINIM        8
#define SEMI_BREVE   16

int notes[] =     {
                    NOTE_G3,  NOTE_C4,  NOTE_E4,  NOTE_G4,  NOTE_C5,  NOTE_E5,  NOTE_G5,  NOTE_E5,
                    NOTE_GS3, NOTE_C4,  NOTE_DS4, NOTE_GS4, NOTE_C5,  NOTE_DS5, NOTE_GS5, NOTE_DS5,
                    NOTE_AS3, NOTE_D4,  NOTE_F4,  NOTE_AS4, NOTE_D5,  NOTE_F5,  NOTE_AS5,
                    NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_C6
                  };
int durations[] = {
                    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM,    MINIM,
                    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM,    MINIM,
                    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM,
                    CROTCHET, CROTCHET, CROTCHET, SEMI_BREVE
                  };
Melody superMarioFanfare(SPEAKER_PIN, notes, durations, sizeof(notes) / sizeof(notes[0]));

void setup() {
  Serial.begin(9600);  // start serial to PC
  superMarioFanfare.setTempo(35);
  superMarioFanfare.setNoteGaps(15);
  superMarioFanfare.startPlayback();
}

void loop() {
  superMarioFanfare.update();
}
