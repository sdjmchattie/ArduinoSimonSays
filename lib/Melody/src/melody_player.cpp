/*
  melody_player.cpp - Mario Fanfare using Melody.
  Created by Stuart D.J. McHattie, August 30, 2021.
*/

#include "melody_player.h"
#include "notes.h"

#define SEMI_QUAVER 1
#define QUAVER 2
#define CROTCHET 4
#define CROTCHET_PLUS 6
#define MINIM 8
#define MINIM_PLUS 10
#define SEMI_BREVE 16

int angryBirdsIntroNotes[] = {
    NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_E3, NOTE_B3,
    NOTE_E3, NOTE_FS3, NOTE_G3, NOTE_E3, NOTE_B3,
    NOTE_B3, NOTE_C4, NOTE_B3, NOTE_A3, NOTE_G3,
    NOTE_A3, NOTE_G3, NOTE_FS3, NOTE_E3};
int angryBirdsIntroDurations[] = {
    QUAVER, QUAVER, CROTCHET, CROTCHET, CROTCHET,
    QUAVER, QUAVER, CROTCHET, CROTCHET, CROTCHET_PLUS,
    QUAVER, QUAVER, QUAVER, QUAVER, QUAVER,
    QUAVER, QUAVER, QUAVER, CROTCHET};

int superMarioFanfareNotes[] = {
    NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5,
    NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5, NOTE_GS5, NOTE_DS5,
    NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_F5, NOTE_AS5,
    NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_C6};
int superMarioFanfareDurations[] = {
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM, MINIM_PLUS,
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM, MINIM_PLUS,
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM,
    CROTCHET, CROTCHET, CROTCHET, SEMI_BREVE};

int superMarioGameOverNotes[] = {
    NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3,
    NOTE_B3, NOTE_A3, NOTE_GS3, NOTE_AS3,
    NOTE_GS3, NOTE_G3, NOTE_FS3, NOTE_G3};
int superMarioGameOverDurations[] = {
    MINIM, MINIM, MINIM, CROTCHET,
    CROTCHET, CROTCHET, CROTCHET, CROTCHET,
    CROTCHET, QUAVER, QUAVER, SEMI_BREVE};

void MelodyPlayer::setMelodyChoice(MelodyChoice melodyChoice)
{
  switch (melodyChoice)
  {
  case AngryBirdsIntro:
    _melody = Melody(
        _speakerPin,
        angryBirdsIntroNotes,
        angryBirdsIntroDurations,
        sizeof(angryBirdsIntroNotes) / sizeof(angryBirdsIntroNotes[0]));
    _melody.setTempo(15);
    break;
  case SuperMarioFanfare:
    _melody = Melody(
        _speakerPin,
        superMarioFanfareNotes,
        superMarioFanfareDurations,
        sizeof(superMarioFanfareNotes) / sizeof(superMarioFanfareNotes[0]));
    break;
  case SuperMarioGameOver:
    _melody = Melody(
        _speakerPin,
        superMarioGameOverNotes,
        superMarioGameOverDurations,
        sizeof(superMarioGameOverNotes) / sizeof(superMarioGameOverNotes[0]));
    _melody.setTempo(20);
    break;
  }
}

void MelodyPlayer::startPlayback()
{
  _melody.startPlayback();
}

void MelodyPlayer::update()
{
  _melody.update();
}

bool MelodyPlayer::isStopped()
{
  return _melody.isStopped();
}