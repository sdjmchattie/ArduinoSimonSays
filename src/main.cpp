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

#define SPEAKER_PIN 12

#define BLUE_LEDS 3
#define YELLOW_LEDS 6
#define RED_LEDS 9
#define GREEN_LEDS 5

#define BLUE_BUTTON 2
#define YELLOW_BUTTON 7
#define RED_BUTTON 8
#define GREEN_BUTTON 4

#define BLUE_FREQ 523
#define YELLOW_FREQ 587
#define RED_FREQ 659
#define GREEN_FREQ 698

enum State
{
  Initial,
  ChooseDifficulty,
  StartGame,
  PlaySequence,
  InputSequence,
};

State state = Initial;

enum Difficulty
{
  None,
  Easy,
  Medium,
  Hard,
};

Difficulty difficulty = None;

LedMultiFlash multiFlash(3);

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
unsigned long previousMils;

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
  blueLeds.Off();
  yellowLeds.Off();
  redLeds.Off();
  greenLeds.Off().DelayBefore(0).DelayAfter(0);
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
    state = StartGame;
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

bool playSequence()
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
    if (mils - previousMils >= 750)
    {
      noTone(SPEAKER_PIN);
      resetLeds();
      previousMils = mils;
      playSequenceState = Paused;
    }
    break;
  case Paused:
    if (mils - previousMils >= 200)
    {
      seqIndex++;
      previousMils = mils;
      playSequenceState = StartNext;
      return seqIndex >= sequence.length();
    }
    break;
  }

  return false;
}

void setup()
{
  // Start serial connection to PC
  Serial.begin(9600);

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
  case Initial:
    setDifficulty(None);
    state = ChooseDifficulty;
    break;
  case ChooseDifficulty:
    chooseDifficulty();
    break;
  case StartGame:
    generateSequence();
    seqIndex = 0;
    playSequenceState = StartNext;
    state = PlaySequence;
    break;
  case PlaySequence:
    if (playSequence())
    {
      state = InputSequence;
    }
    break;
  case InputSequence:
    break;
  }
}
