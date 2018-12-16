/*
  Melody.h - Library for playing a melody on a piezo speaker.
  Created by Stuart D.J. McHattie, December 16, 2018.
*/

#ifndef Melody_h
#define Melody_h

class Melody
{
  public:
    Melody(int speakerPin, int notes[], int durations[]);
    void startPlayback();
    void update();
  private:
    int _speakerPin;
    int _notes[];
    int _durations[];
};

#endif
