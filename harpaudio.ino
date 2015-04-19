  #define TONE_LENGTH 200

int scale[] = {60, 62, 64, 65, 67, 69, 71, 72};

void initializeMIDI(int instrument) {
  talkMIDI(0xB0, 0x07, 127);
  talkMIDI(0xB0, 0, 0x00);
  for (int i = 0; i <= 8; i++) {
    talkMIDI(0xC0+i, instrument, 0);
  }
}

void scanNotes() {
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
