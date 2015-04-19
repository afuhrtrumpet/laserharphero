#ifndef __SONGS_H__
#define __SONGS_H__

#define NOTE_C  0b00000001
#define NOTE_D  0b00000010
#define NOTE_E  0b00000100
#define NOTE_F  0b00001000
#define NOTE_G  0b00010000
#define NOTE_A  0b00100000
#define NOTE_B  0b01000000
#define NOTE_C2 0b10000000
#define NOTE_REST 0

int numberOfSongs = 2;
char *songTitles[] = {"Ode to Joy", "Mary Had a Little Lamb"};

byte ode[] = {NOTE_E, NOTE_E, NOTE_F, NOTE_G, NOTE_G,
    NOTE_F, NOTE_E, NOTE_D, NOTE_C, NOTE_C, NOTE_D, NOTE_E,
    NOTE_E, NOTE_REST, NOTE_D, NOTE_D};
byte mary[] = {NOTE_E, NOTE_D, NOTE_C, NOTE_D, NOTE_E, NOTE_E, NOTE_E,
    NOTE_REST, NOTE_D, NOTE_D, NOTE_D, NOTE_REST, NOTE_E,
    NOTE_G, NOTE_G, NOTE_REST, NOTE_E, NOTE_D, NOTE_C, NOTE_D,
    NOTE_E, NOTE_E, NOTE_E, NOTE_E, NOTE_D, NOTE_D, NOTE_E,
    NOTE_D, NOTE_C};

byte *songs[] = {ode, mary};
    
int songLengths[] = {16, 29};

#endif
