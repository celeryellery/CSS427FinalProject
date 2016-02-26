/*
 Melodies
 Interactive game that allows players to make notes based on which
 capacitive touch pad they step on. 

 circuit:
 * 8-ohm speaker on digital pin 8
 * 5 capacitive touch sensors and corresponding resistors

 Based on code by Tom Igoe, which can be found here: 
 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"
#include <CapacitiveSensor.h>

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

int long stepThreshhold = 200;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_1_0 = CapacitiveSensor(1,0);        // 10M resistor between pins 1 & 0, pin 0 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_6_5 = CapacitiveSensor(6,5);        // 10M resistor between pins 6 & 5, pin 5 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_10_9 = CapacitiveSensor(10,9);      // 10M resistor between pins 10 & 9, pin 9 is sensor pin, add a wire and or foil if desired
//CapacitiveSensor   cs_12_11 = CapacitiveSensor(12,11);    // 10M resistor between pins 12 & 11, pin 11 is sensor pin, add a wire and or foil if desired

// Create long ints to hold output values of sensors:
long total1 = 0;
//long total2 = 0;
//long total3 = 0;
//long total4 = 0;
//long total5 = 0;

void setup() {
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   //cs_1_0.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   //cs_6_5.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   //cs_10_9.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   //cs_12_11.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   Serial.begin(9600);

   pinMode(sensor1pin, OUTPUT);
   //pinMode(sensor2pin, OUTPUT);
   //pinMode(sensor3pin, OUTPUT);
   //pinMode(sensor4pin, OUTPUT);
   //pinMode(sensor5pin, OUTPUT);
}

boolean isSteppedOn(long pressurePlateValue) {
  return (pressurePlateValue > stepThreshhold);
}

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
// end temporary code ------------------------------------------------------------------------------------------------------------------

void loop() {
    // Take a reading from each sensor
    total1 =  cs_4_2.capacitiveSensor(30);
    //total2 =  cs_1_0.capacitiveSensor(30);
    //total3 =  cs_6_5.capacitiveSensor(30);
    //total4 =  cs_10_9.capacitiveSensor(30);
    //total5 =  cs_12_11.capacitiveSensor(30);

    // Print that reading for debugging purposes
    Serial.print("Value1: ");
    Serial.println(total1);
    /*
    Serial.print("Value2: ");
    Serial.print(total2);
    Serial.print("Value3: ");
    Serial.print(total3);
    Serial.print("Value4: ");
    Serial.print(total4);
    Serial.print("Value5: ");
    Serial.println(total5); */

    // If a step is detected, play the next note in the song
    if (isSteppedOn(total1)){
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
