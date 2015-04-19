#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <Wire.h>
#include <nunchuck_funcs.h>

#include "songs.h"

#define LIGHT_THRESHOLD 500
#define SCALE_TYPES 4

#define MAIN_MENU 0
#define FREE 1
#define GAME 2
#define SONG_SELECT 3

SoftwareSerial midiSerial(2,3);
byte resetMIDI = 4;
int ledPin = 13;
int harpPins[] = {A0, A1, A2, A3, A4, A5, A8, A9};
int scale[] = {60, 62, 64, 65, 67, 69, 71, 72};
int speakerPin = 12;
int instrument = 46;
int scaleType = 0;

int mode = 0;
int selectedSong = 0;
int time = 0;

boolean noteValues[] = {false, false, false, false, false, false, false, false};

int lastTimeScored[] = {0, 0, 0, 0, 0, 0, 0, 0};

unsigned long lastUpdate = 0;

void setup() {
  midiSerial.begin(31250);
  pinMode(speakerPin, OUTPUT);
  Serial.begin(9600);
  
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  
  nunchuck_setpowerpins();
  nunchuck_init();
  
  initializeMIDI(instrument);
  initDisplay();
}

void loop() {
  if (mode != MAIN_MENU) {
    scanNotes();
  }
  if (millis() - 15 > lastUpdate) {
    showFrame(songs[selectedSong], songLengths[selectedSong]);
    lastUpdate = millis();
    if(time % 14 == 0 && mode == GAME) playMetronome();
  }
  scanNunchuck();
}

void changeScale(int newStart) {
  switch (scaleType) {
    case 0:
      scale[0] = newStart;
      scale[1] = newStart + 2;
      scale[2] = newStart + 4;
      scale[3] = newStart + 5;
      scale[4] = newStart + 7;
      scale[5] = newStart + 9;
      scale[6] = newStart + 11;
      scale[7] = newStart + 12;
      break;
     case 1:
      scale[0] = newStart;
      scale[1] = newStart + 2;
      scale[2] = newStart + 3;
      scale[3] = newStart + 5;
      scale[4] = newStart + 7;
      scale[5] = newStart + 8;
      scale[6] = newStart + 10;
      scale[7] = newStart + 12;
      break;
     case 2:
      scale[0] = newStart;
      scale[1] = newStart + 2;
      scale[2] = newStart + 4;
      scale[3] = newStart + 7;
      scale[4] = newStart + 9;
      scale[5] = newStart + 12;
      scale[6] = newStart + 14;
      scale[7] = newStart + 16;
      break;
     case 3:
      scale[0] = newStart;
      scale[1] = newStart + 3;
      scale[2] = newStart + 5;
      scale[3] = newStart + 6;
      scale[4] = newStart + 7;
      scale[5] = newStart + 10;
      scale[6] = newStart + 12;
      scale[7] = newStart + 15;
  }
}

void timerIsr() {
  //Serial.println("ISR Triggered");
  //showFrame(notes, noteLength);
}
