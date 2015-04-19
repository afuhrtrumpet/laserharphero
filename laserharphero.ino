#include <TimerOne.h>
#include <SoftwareSerial.h>

#define LIGHT_THRESHOLD 500
#define TONE_LENGTH 200

int harpPins[] = {A0, A1, A2, A3, A4, A5, A8, A9};
int speakerPin = 12;
int scale[] = {60, 62, 64, 65, 67, 69, 71, 72};
boolean noteValues[] = {false, false, false, false, false, false, false, false};
unsigned long lastNoteTime = 0;

SoftwareSerial midiSerial(2,3);
byte resetMIDI = 4;
int ledPin = 13;

void setup() {
  midiSerial.begin(31250);
  pinMode(speakerPin, OUTPUT);
  Timer1.initialize(10000);
  Timer1.attachInterrupt(timerIsr);
  Serial.begin(9600);
  
  pinMode(resetMIDI, OUTPUT);
  digitalWrite(resetMIDI, LOW);
  delay(100);
  digitalWrite(resetMIDI, HIGH);
  delay(100);
  talkMIDI(0xB0, 0x07, 127);
  
  talkMIDI(0xB0, 0, 0x00);
  talkMIDI(0xC0, 47, 0);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    //Serial.print(i);
    //Serial.print(": ");
    //Serial.println(analogRead(harpPins[i]));
    if (analogRead(harpPins[i]) < LIGHT_THRESHOLD) {
      if (!noteValues[i]) {
        noteOn(i+1, scale[i], 90);
        Serial.print("Note output on string ");
        Serial.println(i);
        noteValues[i] = true;
      }
    } else {
      if (noteValues[i]) {
        noteOff(i+1, scale[i], 90);
        noteValues[i] = false;
      }
    }
  }
}

void timerIsr() {
  //if (millis() - TONE_LENGTH > lastNoteTime)
    //noTone(speakerPin);
}

//Send a MIDI note-on message.  Like pressing a piano key
//channel ranges from 0-15
void noteOn(byte channel, byte note, byte attack_velocity) {
  talkMIDI( (0x90 | channel), note, attack_velocity);
}

//Send a MIDI note-off message.  Like releasing a piano key
void noteOff(byte channel, byte note, byte release_velocity) {
  talkMIDI( (0x80 | channel), note, release_velocity);
}

//Plays a MIDI note. Doesn't check to see that cmd is greater than 127, or that data values are less than 127
void talkMIDI(byte cmd, byte data1, byte data2) {
  digitalWrite(ledPin, HIGH);
  midiSerial.write(cmd);
  midiSerial.write(data1);

  //Some commands only have one data byte. All cmds less than 0xBn have 2 data bytes 
  //(sort of: http://253.ccarh.org/handout/midiprotocol/)
  if( (cmd & 0xF0) <= 0xB0)
    midiSerial.write(data2);

  digitalWrite(ledPin, LOW);
}
