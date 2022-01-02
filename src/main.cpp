/*
This is the source code to operate a Simon Says game with a piezo speaker,
four arcade buttons in different colours, each with 6 LEDs of a matching colour.

CONNECTIONS:

Passive Speaker       ARDUINO
-                     GND
+                     D10

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

#define BLUE_LEDS      3
#define YELLOW_LEDS    6
#define RED_LEDS       9
#define GREEN_LEDS     5
#define SPEAKER_PIN    10
#define BLUE_BUTTON    2
#define YELLOW_BUTTON  7
#define RED_BUTTON     8
#define GREEN_BUTTON   4

enum State {
  INITIAL,
  CHOOSE_DIFFICULTY,
};

State state = INITIAL;

enum Difficulty {
  NONE,
  EASY,
  MEDIUM,
  HARD,
};

Difficulty difficulty = NONE;

JLed blueLeds = JLed(BLUE_LEDS);
JLed yellowLeds = JLed(YELLOW_LEDS);
JLed redLeds = JLed(RED_LEDS);
JLed greenLeds = JLed(GREEN_LEDS);

Bounce2::Button blueButton = Bounce2::Button();
Bounce2::Button greenButton = Bounce2::Button();
Bounce2::Button yellowButton = Bounce2::Button();
Bounce2::Button redButton = Bounce2::Button();

void doUpdates() {
  blueButton.update();
  yellowButton.update();
  redButton.update();
  greenButton.update();
  blueLeds.Update();
  yellowLeds.Update();
  redLeds.Update();
  greenLeds.Update();
}

void setDifficulty(Difficulty newDifficulty) {
  blueLeds.Breathe(1000).Forever();
  yellowLeds.Breathe(1000).Forever();
  redLeds.Breathe(1000).Forever();
  greenLeds.Off();

  difficulty = newDifficulty;
  switch (difficulty) {
    case NONE:
      // Nothing special to do for NONE case.
      break;
    case EASY:
      blueLeds.Breathe(200).Forever();
      break;
    case MEDIUM:
      yellowLeds.Breathe(200).Forever();
      break;
    case HARD:
      redLeds.Breathe(200).Forever();
      break;
  }
}

void chooseDifficulty() {

}

void inputButtonSequece() {
    if (blueButton.pressed()) {
    tone(SPEAKER_PIN, 523);
    blueLeds.On();
  } else if (blueButton.released()) {
    noTone(SPEAKER_PIN);
    blueLeds.Off();
  }

  if (greenButton.pressed()) {
    tone(SPEAKER_PIN, 587);
    greenLeds.On();
  } else if (greenButton.released()) {
    noTone(SPEAKER_PIN);
    greenLeds.Off();
  }

  if (yellowButton.pressed()) {
    tone(SPEAKER_PIN, 659);
    yellowLeds.On();
  } else if (yellowButton.released()) {
    noTone(SPEAKER_PIN);
    yellowLeds.Off();
  }

  if (redButton.pressed()) {
    tone(SPEAKER_PIN, 698);
    redLeds.On();
  } else if (redButton.released()) {
    noTone(SPEAKER_PIN);
    redLeds.Off();
  }
}

void setup() {
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

void loop() {
  doUpdates();

  switch (state) {
    case INITIAL:
      setDifficulty(NONE);
      state = CHOOSE_DIFFICULTY;
      break;
    case CHOOSE_DIFFICULTY:
      chooseDifficulty();
      break;
  }
}
