/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"
#include <CapacitiveSensor.h>

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
  //2, 4, 4, 2, 2, 2, 2, 2
  //8, 16, 16, 8, 8, 8, 8, 8
};

int long stepThreshhold = 4000;
int melodyCounter = 0;

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup() {
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

boolean isSteppedOn(long pressurePlateValue) {
  return (pressurePlateValue > stepThreshhold);
}

void loop() {
      

    long total1 =  cs_4_2.capacitiveSensor(30);
    Serial.print("Value: ");
    Serial.println(total1);

    
    
    if (isSteppedOn(total1)){
      Serial.println("Stepped on!");
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / noteDurations[melodyCounter];
      tone(8, melody[melodyCounter], noteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(8);
      if (melodyCounter < 8){
        melodyCounter++;
      }
      else {
        melodyCounter = 0;
      }
      //delay(10);
    }
  
}
