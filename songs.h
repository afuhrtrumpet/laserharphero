#ifndef __SONGS_H__
#define __SONGS_H__

#define NOTE_0  0b00000001
#define NOTE_1  0b00000010
#define NOTE_2  0b00000100
#define NOTE_3  0b00001000
#define NOTE_4  0b00010000
#define NOTE_5  0b00100000
#define NOTE_6  0b01000000
#define NOTE_7  0b10000000
#define NOTE_REST 0

int numberOfSongs = 2;
char *songTitles[] = {"Ode to Joy", "Mary Had a Little Lamb"};

byte ode[] = {NOTE_2, NOTE_2, NOTE_3, NOTE_4, NOTE_4,
    NOTE_3, NOTE_2, NOTE_1, NOTE_0, NOTE_0, NOTE_1, NOTE_2,
    NOTE_2, NOTE_REST, NOTE_1, NOTE_1};
byte mary[] = {NOTE_2, NOTE_1, NOTE_0, NOTE_1, NOTE_2, NOTE_2, NOTE_2,
    NOTE_REST, NOTE_1, NOTE_1, NOTE_1, NOTE_REST, NOTE_2,
    NOTE_4, NOTE_4, NOTE_REST, NOTE_2, NOTE_1, NOTE_0, NOTE_1,
    NOTE_2, NOTE_2, NOTE_2, NOTE_2, NOTE_1, NOTE_1, NOTE_2,
    NOTE_1, NOTE_0};

byte *songs[] = {ode, mary};
    
int songLengths[] = {16, 29};

#endif
