#include <TimerOne.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define LIGHT_THRESHOLD 500

SoftwareSerial midiSerial(2,3);
byte resetMIDI = 4;
int ledPin = 13;
int harpPins[] = {A0, A1, A2, A3, A4, A5, A8, A9};
int speakerPin = 12;
int instrument = 46;

boolean noteValues[] = {false, false, false, false, false, false, false, false};

byte notes[] = {0b00010000, 0b10000001, 0b10010010};
int lastTimeScored[] = {0, 0, 0, 0, 0, 0, 0, 0};
int noteLength = 3;

unsigned long lastUpdate = 0;

void setup() {
  midiSerial.begin(31250);
  pinMode(speakerPin, OUTPUT);
  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerIsr);
  Serial.begin(9600);
  
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  
  initializeMIDI(instrument);
  initDisplay();
}

void loop() {
  scanNotes();
  if (millis() - 25 > lastUpdate) {
    showFrame(notes, noteLength);
    lastUpdate = millis();
  }
}

void timerIsr() {
  //Serial.println("ISR Triggered");
  //showFrame(notes, noteLength);
}
