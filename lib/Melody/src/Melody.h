/*
  Melody.h - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#ifndef Melody_h
#define Melody_h

class Melody
{
  public:
    Melody(int speakerPin, int notes[], int durations[], int noteCount);
    void setTempo(float tempo); // durations per second
    void setNoteGaps(unsigned long millis); // milliseconds between notes
    void startPlayback();
    void update();
  private:
    int _speakerPin;
    int _notes[200];
    int _durations[200];
};

#endif
