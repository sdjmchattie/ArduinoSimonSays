/*
This is the source code to operate a Simon Says game with a piezo speaker,
four arcade buttons in different colours, each with 6 LEDs of a matching colour.

CONNECTIONS:

Passive Speaker       ARDUINO
-                     GND
+                     D2

LED Transisitors      ARDUINO
Blue                  D3
Green                 D4
Yellow                D5
Red                   D6

Arcade Buttons        ARDUINO
Blue                  D7
Green                 D8
Yellow                D9
Red                   D10
*/

#include <Arduino.h>

void playMelody();
void parseAndPlayNote(char noteName[], char noteDuration[]);
void playNote(float noteDelay, long noteDuration);
void getNoteNameAtIndex(int index, char noteName[]);
void getNoteDurationAtIndex(int index, char noteDuration[]);
void getMelodySubString(int offset, int nBytes, char output[]);
float getNoteDelay(char noteName[]);
long getNoteDuration(char noteDuration[]);
void printString(char charArray[], int arrayLength);

#define SPEAKERPIN 2

unsigned long previousMillis = 0;

const int NOTE_SYNTAX_LENGTH = 6;
const int NOTE_NAME_START_INDEX = 0;
const int NOTE_NAME_END_INDEX = 2;
const int NOTE_NAME_LENGTH = NOTE_NAME_END_INDEX - NOTE_NAME_START_INDEX + 1;
const int NOTE_DURATION_START_INDEX = 3;
const int NOTE_DURATION_END_INDEX = 4;
const int NOTE_DURATION_LENGTH = NOTE_DURATION_END_INDEX - NOTE_DURATION_START_INDEX + 1;

const int NOTE_COUNT = 37;
const int MELODY_SIZE = 27;
const int OVERALL_TEMPO = 25000;

char notes[][4] =     {   "c3n",   "c3s",   "d3n",   "d3s",   "e3n",   "f3n",   "f3s",   "g3n",   "g3s",   "a3n",   "a3s",   "b3n",   "c4n",   "c4s",   "d4n",   "d4s",   "e4n",   "f4n",   "f4s",   "g4n",   "g4s",   "a4n",   "a4s",   "b4n",   "c5n",   "c5s",   "d5n",   "d5s",   "e5n",   "f5n",   "f5s",   "g5n",   "g5s",   "a5n",   "a5s",   "b5n",  "c6n" };
float note_delays[] = { 7644.50, 7215.47, 6810.50, 6428.26, 6067.44, 5726.91, 5405.49, 5102.09, 4815.74, 4545.45, 4290.33, 4049.53, 3822.25, 3607.72, 3405.24, 3214.12, 3033.72, 2863.45, 2702.74, 2551.05, 2407.86, 2272.72, 2145.16, 2024.77, 1911.12, 1803.86, 1702.62, 1607.06, 1516.86, 1431.72, 1351.37, 1275.52, 1203.93, 1136.36, 1072.58, 1012.38, 955.57 };
char melody[] = "g3n04,c4n04,e4n04,g4n04,c5n04,e5n04,g5n08,e5n08,g3s04,c4n04,d4s04,g4s04,c5n04,d5s04,g5s08,d5s08,a3s04,d4n04,f4n04,a4s04,d5n04,f5n04,a5s08,b5n04,b5n04,b5n04,c6n16,";

void setup() {
  Serial.begin(9600);  // start serial to PC

  pinMode(SPEAKERPIN, OUTPUT);
  digitalWrite(SPEAKERPIN, LOW);

  playMelody();
}

void loop() {

}

void playMelody() {
  analogWrite(SPEAKERPIN, 0);
  Serial.println("Beginning to play melody");
  for (int melodyIndex = 0; melodyIndex < MELODY_SIZE; melodyIndex++) {
    char noteName[NOTE_NAME_LENGTH];
    getNoteNameAtIndex(melodyIndex, noteName);
    char noteDuration[NOTE_DURATION_LENGTH];
    getNoteDurationAtIndex(melodyIndex, noteDuration);
    parseAndPlayNote(noteName, noteDuration);
  }
}

void parseAndPlayNote(char noteName[], char noteDuration[]) {
  Serial.print("Preparing to play note ");
  printString(noteName, NOTE_NAME_LENGTH);
  Serial.print(" with duration ");
  printString(noteDuration, NOTE_DURATION_LENGTH);
  Serial.println();
  playNote(getNoteDelay(noteName), getNoteDuration(noteDuration));
}

void playNote(float noteDelay, long noteDuration) {
  Serial.print("Playing note with delay ");
  Serial.print(noteDelay);
  Serial.print(" and duration ");
  Serial.println(noteDuration);

  if (noteDelay == 0) {
    // Pause before next note
    delayMicroseconds(noteDuration);
  } else {
    long numberOfOscillations = (long)(noteDuration / noteDelay);
    for (long i = 0; i < numberOfOscillations; i++) {
      analogWrite(SPEAKERPIN,500);
      delayMicroseconds(noteDelay / 2);
      analogWrite(SPEAKERPIN, 0);
      delayMicroseconds(noteDelay / 2);
    }
  }
}

void getNoteNameAtIndex(int index, char noteName[]) {
  getMelodySubString(index * NOTE_SYNTAX_LENGTH + NOTE_NAME_START_INDEX, NOTE_NAME_LENGTH, noteName);
}

void getNoteDurationAtIndex(int index, char noteDuration[]) {
  getMelodySubString(index * NOTE_SYNTAX_LENGTH + NOTE_DURATION_START_INDEX, NOTE_DURATION_LENGTH, noteDuration);
}

void getMelodySubString(int offset, int nBytes, char output[]) {
  for (int i = 0; i < nBytes; i++)
  {
    output[i] = melody[offset + i];
  }

  output[nBytes] = 0;
}

float getNoteDelay(char noteName[]) {
  for (int i = 0; i < NOTE_COUNT; i++) {
    bool match = true;
    for (int j = 0; j < NOTE_NAME_LENGTH; j++) {
      if (notes[i][j] != noteName[j]) {
        match = false;
        break;
      }
    }

    if (match) {
      return note_delays[i];
    }
  }

  return 0;
}

long getNoteDuration(char noteDuration[]) {
  char *remainder[NOTE_DURATION_LENGTH];
  long duration = strtol(noteDuration, remainder, 10);
  return duration * OVERALL_TEMPO;
}

void printString(char charArray[], int arrayLength) {
  for (int i = 0; i < arrayLength; i++)
  {
    Serial.print(charArray[i]);
  }
}
