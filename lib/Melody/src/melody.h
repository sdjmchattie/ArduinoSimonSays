/*
  melody.h - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#ifndef melody_h
#define melody_h

enum MelodyState
{
  Stopped = 0,
  StartNextNote = 1,
  PlayingNote = 2,
  PlayingGap = 3
};

class Melody
{
public:
  Melody(int speakerPin, int notes[], int durations[], int noteCount);
  Melody() = default;
  void setTempo(float tempo);             // durations per second
  void setNoteGaps(unsigned long millis); // milliseconds between notes
  void startPlayback();
  void update();
  bool isStopped();

private:
  int _speakerPin;
  int _notes[200];
  int _durations[200];
  int _melodyLength;

  MelodyState _state;
  unsigned long _previousMils;

  bool _isPlaying;
  int _playPosition;

  float _millisPerDuration;
  unsigned long _noteGapMillis;
};

#endif
