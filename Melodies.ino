#include "Melodies/pitches.h"
#include "Melodies/Song.h"

#define SONG_LIST_SIZE 3

const int sensor1pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor2pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor3pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor4pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor5pin = 8; // connect the first sensor to pin 8 on the Arduino Mega

long csOutput_RED = 0, csOutput_GREEN = 0, csOutput_BLUE = 0;
int currentSong = 1;

void initMelodies()
{
  pinMode(sensor1pin, OUTPUT);  
}

void playNextNote() 
{
      ;
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration_ms = 1000 / getCurrentDuration(currentSong);
      tone(sensor1pin, getCurrentNote(currentSong), noteDuration_ms); 
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration_ms * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(sensor1pin);
      
      if(getLength(currentSong) == getCurrent(currentSong))
      {
        if(currentSong == SONG_LIST_SIZE)
        {
          currentSong = 1;  
        }
        else
        {
          currentSong++;  
        }
      }
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
    if (isSteppedOn(csOutput_GREEN))
    {
      Serial.println("Stepped on!");

      playNextNote();
    }
}
