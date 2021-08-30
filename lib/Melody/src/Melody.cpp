/*
  Melody.cpp - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#include "Arduino.h"
#include "Melody.h"

enum MelodyState {
  Stopped = 0,
  StartNextNote = 1,
  PlayingNote = 2,
  PlayingGap = 3
};

bool isPlaying = false;
MelodyState state = Stopped;
int playPosition = 0;
unsigned long previousMils = 0;

int melodyLength;
float millisPerDuration = 32.0;
unsigned long noteGapMillis = 10.0;

Melody::Melody(int speakerPin, int notes[], int durations[], int noteCount) {
  melodyLength = noteCount;
  _speakerPin = speakerPin;
  memcpy(_notes, notes, noteCount * sizeof(notes[0]));
  memcpy(_durations, durations, noteCount * sizeof(notes[0]));

  pinMode(_speakerPin, OUTPUT);
  noTone(_speakerPin);
}

void Melody::setTempo(float tempo) {
  millisPerDuration = 1000 / tempo;
}

void Melody::setNoteGaps(unsigned long millis) {
  noteGapMillis = millis;
}

void Melody::startPlayback() {
  noTone(_speakerPin);
  playPosition = 0;
  state = StartNextNote;
}

void Melody::update() {
  unsigned long mils = millis();

  switch (state) {
    case Stopped: {
      noTone(_speakerPin);
    } break;
    case StartNextNote: {
      int frequency = _notes[playPosition];
      if (frequency == 0) {
        // Pause instead of playing a note
        noTone(_speakerPin);
      } else {
        // Play the note of a given frequency
        tone(_speakerPin, _notes[playPosition]);
      }
      previousMils = mils;
      state = PlayingNote;
    } break;
    case PlayingNote: {
      if (mils - previousMils >= (unsigned long)(millisPerDuration * _durations[playPosition])) {
        if (playPosition == melodyLength - 1) {
          playPosition = 0;
          state = Stopped;
        } else {
          noTone(_speakerPin);
          previousMils = mils;
          state = PlayingGap;
        }
      }
    } break;
    case PlayingGap: {
      if (mils - previousMils >= noteGapMillis) {
        playPosition++;
        previousMils = mils;
        state = StartNextNote;
      }
    } break;
  }
}
