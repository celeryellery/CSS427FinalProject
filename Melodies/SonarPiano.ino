#include "pitches.h"

//Distance ThreshHold 
int ThreshHold = 50;

//Full Range of Piezo Frequencies as Pitches
int Tones[] = {
 NOTE_B0, NOTE_C1,NOTE_CS1, NOTE_D1,NOTE_DS1,
 NOTE_E1, NOTE_F1, NOTE_FS1, NOTE_G1, NOTE_GS1,
 NOTE_A1,NOTE_AS1, NOTE_B1,NOTE_C2,NOTE_CS2,
 NOTE_D2,NOTE_DS2,NOTE_E2,NOTE_F2,NOTE_FS2, NOTE_G2,
 NOTE_GS2,NOTE_A2,NOTE_AS2,NOTE_B2,NOTE_C3,NOTE_CS3,
 NOTE_D3,NOTE_DS3,NOTE_E3,NOTE_F3,NOTE_FS3,NOTE_G3,NOTE_GS3, 
 NOTE_A3, NOTE_AS3,NOTE_B3,NOTE_C4,NOTE_CS4,NOTE_D4,NOTE_DS4,
 NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,
 NOTE_B4, NOTE_C5,NOTE_CS5,NOTE_D5,NOTE_DS5,NOTE_E5,NOTE_F5,
 NOTE_FS5,NOTE_G5,NOTE_GS5, NOTE_AS5,NOTE_B5,NOTE_C6,NOTE_CS6,
 NOTE_D6,NOTE_DS6,NOTE_E6,NOTE_F6,NOTE_FS6,NOTE_G6,NOTE_GS6,
 NOTE_A6,NOTE_AS6,NOTE_B6,NOTE_C7,NOTE_CS7,NOTE_D7,NOTE_DS7,
 NOTE_E7,NOTE_F7,NOTE_FS7,NOTE_G7,NOTE_GS7,NOTE_A7, NOTE_AS7,
 NOTE_B7,NOTE_C8,NOTE_CS8,NOTE_D8,NOTE_DS8};

//One Octave of Piezo Frequencies as Pitches
int TonesO4[] = {NOTE_C4,NOTE_CS4,
 NOTE_D4,NOTE_DS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4, 
 NOTE_A4, NOTE_AS4,NOTE_B4};

//Length of Array 
int Len = sizeof(TonesO4)/sizeof(TonesO4[1]);

void setup() {
  //Serial.begin(9600);
  //Setup analog input pin and PWM output pin 
  pinMode(A2, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  int inRead = analogRead(A2);
  
  //Test if input is in distance range
  if(inRead <= ThreshHold)
  {
    //Map distance to pitch in array
    int mapping = map(inRead, 0, ThreshHold, 0, Len-1);
    tone(13, TonesO4[mapping]); 
    
    //delay for sonar update (speed of sound) 
    delay(300);
  }
  else
  {
    //Cut of output
    noTone(13);
  }
  //delay(400);
}
