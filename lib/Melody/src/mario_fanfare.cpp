/*
  mario_fanfare.cpp - Mario Fanfare using Melody.
  Created by Stuart D.J. McHattie, August 30, 2021.
*/

#include "mario_fanfare.h"
#include "notes.h"

#define CROTCHET 4
#define MINIM 8
#define MINIM_PLUS 10
#define SEMI_BREVE 16

int notes[] = {
    NOTE_G3, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5,
    NOTE_GS3, NOTE_C4, NOTE_DS4, NOTE_GS4, NOTE_C5, NOTE_DS5, NOTE_GS5, NOTE_DS5,
    NOTE_AS3, NOTE_D4, NOTE_F4, NOTE_AS4, NOTE_D5, NOTE_F5, NOTE_AS5,
    NOTE_AS5, NOTE_AS5, NOTE_AS5, NOTE_C6};
int durations[] = {
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM, MINIM_PLUS,
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM, MINIM_PLUS,
    CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, CROTCHET, MINIM,
    CROTCHET, CROTCHET, CROTCHET, SEMI_BREVE};

MarioFanfare::MarioFanfare(int speakerPin)
{
  _marioFanfare = Melody(speakerPin, notes, durations, sizeof(notes) / sizeof(notes[0]));
}

void MarioFanfare::startPlayback()
{
  _marioFanfare.startPlayback();
}

void MarioFanfare::update()
{
  _marioFanfare.update();
}

bool MarioFanfare::isStopped()
{
  return _marioFanfare.isStopped();
}