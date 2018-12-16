/*
  Melody.cpp - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#include <Arduino.h>
#include "Melody.h"

bool isPlaying = false;
int playPosition = -1;
int melodyLength;

Melody::Melody(int speakerPin, int notes[], int durations[]) {
  melodyLength = sizeof(notes) / sizeof(notes[0]);
  _speakerPin = speakerPin;
  memcpy(_notes, notes, sizeof(notes));
  memcpy(_durations, durations, sizeof(notes));
}

void Melody::startPlayback() {
  noTone(_speakerPin);
  playPosition = -1;
  isPlaying = true;
}

void Melody::update() {

}
