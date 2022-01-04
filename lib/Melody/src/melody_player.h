/*
  melody_player.h - Mario Fanfare using Melody.
  Created by Stuart D.J. McHattie, August 30, 2021.
*/

#ifndef melody_player_h
#define melody_player_h

#include "melody.h"

enum MelodyChoice
{
  AngryBirdsIntro,
  SuperMarioFanfare,
  SuperMarioGameOver,
};

class MelodyPlayer
{
public:
  MelodyPlayer() = delete;
  MelodyPlayer(int speakerPin) : _speakerPin(speakerPin){};
  void setMelodyChoice(MelodyChoice melody);
  void startPlayback();
  void update();
  bool isStopped();

private:
  int _speakerPin;
  Melody _melody;
};

#endif
