/*
  melody.cpp - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#include "Arduino.h"
#include "melody.h"

Melody::Melody(int speakerPin, int notes[], int durations[], int noteCount)
{
  _melodyLength = noteCount;
  _speakerPin = speakerPin;
  memcpy(_notes, notes, noteCount * sizeof(notes[0]));
  memcpy(_durations, durations, noteCount * sizeof(notes[0]));

  _state = Stopped;
  _previousMils = 0;
  _isPlaying = false;
  _playPosition = 0;

  _millisPerDuration = 32.0;
  _noteGapMillis = 10.0;

  noTone(_speakerPin);
}

void Melody::setTempo(float tempo)
{
  _millisPerDuration = 1000 / tempo;
}

void Melody::setNoteGaps(unsigned long millis)
{
  _noteGapMillis = millis;
}

void Melody::startPlayback()
{
  noTone(_speakerPin);
  _playPosition = 0;
  _state = StartNextNote;
}

void Melody::update()
{
  unsigned long mils = millis();

  switch (_state)
  {
  case Stopped:
    noTone(_speakerPin);
    break;
  case StartNextNote:
  {
    int frequency = _notes[_playPosition];
    if (frequency == 0)
    {
      // Pause instead of playing a note
      noTone(_speakerPin);
    }
    else
    {
      // Play the note of a given frequency
      tone(_speakerPin, _notes[_playPosition]);
    }
    _previousMils = mils;
    _state = PlayingNote;
  }
  break;
  case PlayingNote:
    if (mils - _previousMils >= (unsigned long)(_millisPerDuration * _durations[_playPosition]))
    {
      noTone(_speakerPin);
      if (_playPosition == _melodyLength - 1)
      {
        _playPosition = 0;
        _state = Stopped;
      }
      else
      {
        _previousMils = mils;
        _state = PlayingGap;
      }
    }
    break;
  case PlayingGap:
    if (mils - _previousMils >= _noteGapMillis)
    {
      _playPosition++;
      _previousMils = mils;
      _state = StartNextNote;
    }
    break;
  }
}

bool Melody::isStopped()
{
  return _state == Stopped;
}
