#include "pitches.h"
/**Distances Corresponding to TonesO4 array values with current settings:
 * 0: 15-16
 * 1: 17-18
 * 2: 19
 * 3: 20-21
 * 4: 22
 * 5: 23-24
 * 6: 25
 * 7: 26-27
 * 8: 28
 * 9: 29-30
 * 10: 31-32
 * 11: 32-33
 * 12: 34-35 
 * Beware of noise, make sure space is totally cleared
 * and account for slow response and physical limitations
 *
 */

int ThreshHold_LO = 15;
int ThreshHold_HI = 35;
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

int TonesO4[] = {NOTE_C4,NOTE_D5,
 NOTE_E4,NOTE_F5,NOTE_G4,NOTE_A5,NOTE_B4,NOTE_C5,NOTE_D4, 
 NOTE_E5, NOTE_F4,NOTE_G5, NOTE_A4, NOTE_B5};

 
int Len = sizeof(TonesO4)/sizeof(TonesO4[1]);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A2, INPUT);
  pinMode(13, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int inRead = analogRead(A2);
  /** Test / Debug
   * Serial.print("Volt/Dist: "); 
   * Serial.print(inRead);
   * Serial.println(); */
  
  if(inRead >= ThreshHold_LO & inRead <= ThreshHold_HI)
  {
    int mapping = map(inRead, ThreshHold_LO, ThreshHold_HI, 0, Len-1);
    tone(13, TonesO4[mapping]); 
    delay(300);
    /** Test / Debug
     * Serial.print("Mapped Dist: ");
     * Serial.print(mapping);
     * Serial.println(); */
  }
  else
  {
    noTone(13);
  }
 
}
