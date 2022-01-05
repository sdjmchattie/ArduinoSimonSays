/*
This is the source code to operate a Simon Says game with a piezo speaker,
four arcade buttons in different colours, each with 6 LEDs of a matching colour.

CONNECTIONS:

Passive Speaker       ARDUINO
-                     GND
+                     D12

LED Transistors (PWM) ARDUINO
Blue                  D3
Yellow                D6
Red                   D9
Green                 D5

Arcade Buttons        ARDUINO
Blue                  D2
Yellow                D7
Red                   D8
Green                 D4
*/

#include <Arduino.h>
#include <Bounce2.h>
#include <jled.h>

#include "led_multi_flash.h"
#include "melody_player.h"

#define SPEAKER_PIN 12

#define BLUE_LEDS 3
#define YELLOW_LEDS 6
#define RED_LEDS 9
#define GREEN_LEDS 5

#define BLUE_BUTTON 2
#define YELLOW_BUTTON 7
#define RED_BUTTON 8
#define GREEN_BUTTON 4

#define BLUE_FREQ 349
#define YELLOW_FREQ 262
#define RED_FREQ 233
#define GREEN_FREQ 208

enum State
{
  PowerOn,
  Initial,
  Pause,
  PlayingMelody,
  ChooseDifficulty,
  StartGame,
  PlaySequence,
  InputSequence,
  Win,
  Fail
};

State state = PowerOn;

enum Difficulty
{
  None,
  Easy,
  Medium,
  Hard,
};

Difficulty difficulty = None;

LedMultiFlash multiFlash(3);

MelodyPlayer melodyPlayer(SPEAKER_PIN);

JLed blueLeds = JLed(BLUE_LEDS);
JLed yellowLeds = JLed(YELLOW_LEDS);
JLed redLeds = JLed(RED_LEDS);
JLed greenLeds = JLed(GREEN_LEDS);

Bounce2::Button blueButton = Bounce2::Button();
Bounce2::Button yellowButton = Bounce2::Button();
Bounce2::Button redButton = Bounce2::Button();
Bounce2::Button greenButton = Bounce2::Button();

char colours[4] = {'b', 'y', 'r', 'g'};
String sequence;

enum PlaySequenceState
{
  StartNext,
  Playing,
  Paused
};

PlaySequenceState playSequenceState;

uint8_t seqIndex;
uint8_t playLength;
unsigned long previousMils;

State stateAfterMelody = Initial;
unsigned long pauseMilsAfterMelody = 1000;

State stateAfterPause = Initial;
unsigned long pauseMils = 1000;

void doUpdates()
{
  blueButton.update();
  yellowButton.update();
  redButton.update();
  greenButton.update();
  blueLeds.Update();
  yellowLeds.Update();
  redLeds.Update();
  greenLeds.Update();
}

void resetLeds()
{
  blueLeds.Off().DelayBefore(0).DelayAfter(0);
  yellowLeds.Off().DelayBefore(0).DelayAfter(0);
  redLeds.Off().DelayBefore(0).DelayAfter(0);
  greenLeds.Off().DelayBefore(0).DelayAfter(0);
}

void pause(unsigned long mils, State stateAfter)
{
  previousMils = millis();
  stateAfterPause = stateAfter;
  pauseMils = mils;
  state = Pause;
}

void playMelody(MelodyChoice melodyChoice, unsigned long pauseMilsAfter, State stateAfter)
{
  pauseMilsAfterMelody = pauseMilsAfter;
  stateAfterMelody = stateAfter;
  melodyPlayer.setMelodyChoice(melodyChoice);
  melodyPlayer.startPlayback();
  state = PlayingMelody;
}

void setDifficulty(Difficulty newDifficulty)
{
  blueLeds.Breathe(2000).Forever();
  yellowLeds.Breathe(2000).Forever();
  redLeds.Breathe(2000).Forever();
  greenLeds.Off();
  greenLeds.UserFunc(&multiFlash).Forever().DelayBefore(750).DelayAfter(1400);

  difficulty = newDifficulty;
  switch (difficulty)
  {
  case None:
    // Turn off the flash on the green button
    greenLeds.Stop();
    break;
  case Easy:
    blueLeds.On();
    break;
  case Medium:
    yellowLeds.On();
    break;
  case Hard:
    redLeds.On();
    break;
  }
}

void chooseDifficulty()
{
  if (blueButton.pressed() && difficulty != Easy)
  {
    setDifficulty(Easy);
  }
  else if (yellowButton.pressed() && difficulty != Medium)
  {
    setDifficulty(Medium);
  }
  else if (redButton.pressed() && difficulty != Hard)
  {
    setDifficulty(Hard);
  }
  else if (greenButton.pressed() && difficulty != None)
  {
    resetLeds();
    pause(1000, StartGame);
  }
}

void generateSequence()
{
  int length;
  switch (difficulty)
  {
  case None:
  case Easy:
    length = 8;
    break;
  case Medium:
    length = 16;
    break;
  case Hard:
    length = 24;
    break;
  }

  sequence = "";
  srand(millis());
  for (int i = 0; i < length; i++)
  {
    sequence = sequence + colours[rand() % 4];
  }

  seqIndex = 0;
}

unsigned int noteLength()
{
  if (playLength < 5)
  {
    return 500;
  }
  else if (playLength < 10)
  {
    return 400;
  }
  else if (playLength < 15)
  {
    return 300;
  }
  else
  {
    return 200;
  }
}

void playSequence()
{
  unsigned long mils = millis();

  switch (playSequenceState)
  {
  case StartNext:
    switch (sequence[seqIndex])
    {
    case 'b':
      tone(SPEAKER_PIN, BLUE_FREQ);
      blueLeds.On();
      break;
    case 'y':
      tone(SPEAKER_PIN, YELLOW_FREQ);
      yellowLeds.On();
      break;
    case 'r':
      tone(SPEAKER_PIN, RED_FREQ);
      redLeds.On();
      break;
    case 'g':
      tone(SPEAKER_PIN, GREEN_FREQ);
      greenLeds.On();
      break;
    }

    previousMils = mils;
    playSequenceState = Playing;
    break;
  case Playing:
    if (mils - previousMils >= noteLength())
    {
      noTone(SPEAKER_PIN);
      resetLeds();
      previousMils = mils;
      playSequenceState = Paused;
    }
    break;
  case Paused:
    if (mils - previousMils >= noteLength() / 5)
    {
      seqIndex++;
      previousMils = mils;
      playSequenceState = StartNext;
    }
    break;
  }
}

int buttonsDown()
{
  return (blueButton.isPressed() ? 1 : 0) +
         (yellowButton.isPressed() ? 1 : 0) +
         (redButton.isPressed() ? 1 : 0) +
         (greenButton.isPressed() ? 1 : 0);
}

void inputSequence()
{
  unsigned long mils = millis();

  if (mils - previousMils >= 5000)
  {
    state = Fail;
    return;
  }

  if (buttonsDown() == 1)
  {
    if (blueButton.pressed())
    {
      if (sequence[seqIndex] == 'b')
      {
        tone(SPEAKER_PIN, BLUE_FREQ);
        blueLeds.On();
      }
      else
      {
        state = Fail;
      }
    }
    if (yellowButton.pressed())
    {
      if (sequence[seqIndex] == 'y')
      {
        tone(SPEAKER_PIN, YELLOW_FREQ);
        yellowLeds.On();
      }
      else
      {
        state = Fail;
      }
    }
    if (redButton.pressed())
    {
      if (sequence[seqIndex] == 'r')
      {
        tone(SPEAKER_PIN, RED_FREQ);
        redLeds.On();
      }
      else
      {
        state = Fail;
      }
    }
    if (greenButton.pressed())
    {
      if (sequence[seqIndex] == 'g')
      {
        tone(SPEAKER_PIN, GREEN_FREQ);
        greenLeds.On();
      }
      else
      {
        state = Fail;
      }
    }
  }

  if (buttonsDown() == 0 &&
      (blueButton.released() ||
       yellowButton.released() ||
       redButton.released() ||
       greenButton.released()))
  {
    noTone(SPEAKER_PIN);
    resetLeds();
    previousMils = mils;
    seqIndex++;
  }
}

void setup()
{
  // Set the speaker up
  pinMode(SPEAKER_PIN, OUTPUT);
  noTone(SPEAKER_PIN);

  // Setup button pins
  blueButton.attach(BLUE_BUTTON, INPUT_PULLUP);
  yellowButton.attach(YELLOW_BUTTON, INPUT_PULLUP);
  redButton.attach(RED_BUTTON, INPUT_PULLUP);
  greenButton.attach(GREEN_BUTTON, INPUT_PULLUP);

  // Setup debounce delay
  blueButton.interval(15);
  yellowButton.interval(15);
  redButton.interval(15);
  greenButton.interval(15);

  // Setup pushed state for buttons
  blueButton.setPressedState(LOW);
  yellowButton.setPressedState(LOW);
  redButton.setPressedState(LOW);
  greenButton.setPressedState(LOW);
}

void loop()
{
  doUpdates();

  switch (state)
  {
  case PowerOn:
    playMelody(AngryBirdsIntro, 100, Initial);
    break;
  case Initial:
    resetLeds();
    setDifficulty(None);
    state = ChooseDifficulty;
    break;
  case Pause:
    if (millis() - previousMils >= pauseMils)
    {
      state = stateAfterPause;
    }
    break;
  case PlayingMelody:
    melodyPlayer.update();
    if (melodyPlayer.isStopped())
    {
      pause(pauseMilsAfterMelody, stateAfterMelody);
    }
    break;
  case ChooseDifficulty:
    chooseDifficulty();
    break;
  case StartGame:
    generateSequence();
    seqIndex = 0;
    playLength = 1;
    playSequenceState = StartNext;
    state = PlaySequence;
    break;
  case PlaySequence:
    playSequence();
    if (seqIndex == playLength)
    {
      seqIndex = 0;
      state = InputSequence;
    }
    break;
  case InputSequence:
    inputSequence();
    if (seqIndex == playLength)
    {
      playLength++;
      seqIndex = 0;

      if (playLength > sequence.length())
      {
        state = Win;
      }
      else
      {
        pause(1000, PlaySequence);
      }
    }
    break;
  case Win:
    blueLeds.Blink(100, 300);
    yellowLeds.Blink(100, 300).DelayBefore(100);
    greenLeds.Blink(100, 300).DelayBefore(200);
    redLeds.Blink(100, 300).DelayBefore(300);
    playMelody(SuperMarioFanfare, 1000, Initial);
    break;
  case Fail:
    blueLeds.Blink(200, 300);
    yellowLeds.Blink(200, 300);
    redLeds.Blink(200, 300);
    greenLeds.Blink(200, 300);
    playMelody(SuperMarioGameOver, 1000, Initial);
    break;
  }
}
