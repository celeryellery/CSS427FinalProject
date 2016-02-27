#include "Melodies/pitches.h"

// Original Melody--------------------------------------------------------------
int melody1Code = 1;
// notes in the melody:
int melody1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {4, 8, 8, 4, 4, 4, 4, 4};

int melody1Length = 8;
int melody1Counter = 0;
//-------------------------------------------------------------------------------

// Hot Crossed Buns--------------------------------------------------------------
int melody2Code = 2;
int melody2[] =        {NOTE_E4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, 
                        NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, 
                        NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 
                        NOTE_E4, NOTE_D4, NOTE_C4};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations2[] = {4, 4, 2, 4, 4, 2, 
                       8, 8, 8, 8, 8, 8, 8, 8, 
                       4, 4, 2};
int melody2Length = 17;
int melody2Counter = 0;
//-------------------------------------------------------------------------------

// Jasmine Flower----------------------------------------------------------------
int melody3Code = 2;
int melody3[] = {NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, 
                       NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, 
                       NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, 
                       NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
                       NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_C5, 
                       NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_G4, NOTE_A4, 
                       NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4};

int noteDurations3[] = {4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
                         4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
                         4, 4, 4, 8, 8, 4, 4, 2, 
                         4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2};

int melody3Length = 41;
int melody3Counter = 0;
//-------------------------------------------------------------------------------

int long stepThreshhold = 200;

long csOutput_RED = 0, csOutput_GREEN = 0, csOutput_BLUE = 0;

boolean isSteppedOn(long pressurePlateValue) {
  return (pressurePlateValue > stepThreshhold);
}


