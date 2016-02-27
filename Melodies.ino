#include "Melodies/pitches.h"

const int sensor1pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor2pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor3pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor4pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor5pin = 8; // connect the first sensor to pin 8 on the Arduino Mega

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
long csOutput_RED = 0, csOutput_GREEN = 0, csOutput_BLUE = 0;

int playNextNote(int noteDurations[], int melodyCounter, int melody[], int melodyLength) {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[melodyCounter];
      tone(sensor1pin, melody[melodyCounter], noteDuration); 
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(sensor1pin);

      if (melodyCounter < melodyLength){
        melodyCounter++;
      }
      else {
        melodyCounter = 0;
      }
      
      return melodyCounter;
}
//-----------------------Temporary code to alternate songs until we set things up to take user input instead -------------------------
int songArray[] = {1, 1, 1, 1, 1, 1, 1, 1, // temporary; just used to switch up which song is next until we take user input for this
                     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
                     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
                     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; 
int whichSong = 0;

void incrementWhichSong() {
      // temporary loop used to change songs until we take user input to do this
    if (whichSong < 66){
        whichSong++;
      }
      else {
        whichSong = 0;
      }
}

void initMelodies()
{
  pinMode(sensor1pin, OUTPUT);  
}

void melodies() 
{
    // Check the capacitive sensor values 
    csOutput_RED = csOutput('R');
    csOutput_GREEN = csOutput('G');
    csOutput_BLUE = csOutput('B');
    
    Serial.print("RED: ");
    Serial.println(csOutput_RED);
    Serial.print("GREEN: ");
    Serial.println(csOutput_GREEN);
    Serial.print("BLUE: ");
    Serial.println(csOutput_BLUE);

    //tone(8, NOTE_E4, 100);
    delay(500);
    
    // If a step is detected, play the next note in the song
    if (isSteppedOn(csOutput_GREEN)){
      Serial.println("Stepped on!");
      switch(songArray[whichSong]) { // Will need to change the variable here to take user input
          case 1 : 
          melody1Counter = playNextNote(noteDurations1, melody1Counter, melody1, melody1Length);
          incrementWhichSong(); // temporary -- remove later when taking user input instead
          break;

          case 2 : 
          melody2Counter = playNextNote(noteDurations2, melody2Counter, melody2, melody2Length);
          incrementWhichSong(); // temporary -- remove later when taking user input instead
          break;

          case 3 :
          melody3Counter = playNextNote(noteDurations3, melody3Counter, melody3, melody3Length);
          incrementWhichSong(); // temporary -- remove later when taking user input instead
          break;
      }
       delay(10);
    }
}
