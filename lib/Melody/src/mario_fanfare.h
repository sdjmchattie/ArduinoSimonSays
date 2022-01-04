/*
  mario_fanfare.h - Mario Fanfare using Melody.
  Created by Stuart D.J. McHattie, August 30, 2021.
*/

#ifndef mario_fanfare_h
#define mario_fanfare_h

#include "melody.h"

class MarioFanfare
{
public:
  MarioFanfare(int speakerPin);
  MarioFanfare() = default;
  void startPlayback();
  void update();
  bool isStopped();

private:
  Melody _marioFanfare;
};

#endif
