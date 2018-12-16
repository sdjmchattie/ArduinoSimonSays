/*
  Melody.cpp - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#include "Arduino.h"
#include "Melody.h"

class Melody {
  Melody::Melody(int speakerPin, int notes[], int durations[]) {
    _speakerPin = speakerPin;
    _notes = notes;
    _durations = durations;
  }

  void Melody::Update() {

  }
};
