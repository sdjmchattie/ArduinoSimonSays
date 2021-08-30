/*
  MarioFanfare.h - Mario Fanfare using Melody.
  Created by Stuart D.J. McHattie, August 30, 2021.
*/

#ifndef MarioFanfare_h
#define MarioFanfare_h

#include "Melody.h"

class MarioFanfare
{
  public:
    MarioFanfare(int speakerPin);
    MarioFanfare() = default;
    void startPlayback();
    void update();
  private:
    Melody _marioFanfare;
};

#endif
