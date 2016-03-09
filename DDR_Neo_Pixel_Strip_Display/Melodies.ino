int allSongNotes[7][42] = {
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              },
              {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              }, 
              {NOTE_E4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4,
               NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4,
               NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4,
               NOTE_E4, NOTE_D4, NOTE_C4, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0
              },
              {NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, 
               NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
               NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, 
               NOTE_F5, NOTE_D5,
               NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
               NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_C5, 
               NOTE_D5, NOTE_D5, NOTE_C5, 
               NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5,
               NOTE_G4, NOTE_A4,
               NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, 0
              },  
              {NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4,
               NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4,
               NOTE_D4, NOTE_C4, 
               NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, 
               NOTE_E4, NOTE_D4,
               NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4,
               NOTE_E4, NOTE_D4,
               NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4,
               NOTE_A4, NOTE_G4,
               NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, 
               NOTE_D4, NOTE_C4
              }, 
              {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_C5, 
               NOTE_A4, NOTE_C5, NOTE_G4,
               NOTE_F4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, 
               NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4,
               NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, 
               NOTE_C5,
               NOTE_A4, NOTE_C5, NOTE_G4,
               NOTE_C5, NOTE_A4, NOTE_G4, NOTE_G4, 
               NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, 
               0, 0, 0, 0, 0, 0, 0
               }, 
              { NOTE_E5, NOTE_E5, NOTE_E5, NOTE_C5, NOTE_E5,
                NOTE_G5, NOTE_G4, 
                NOTE_C5, NOTE_G4, NOTE_E4, 
                NOTE_E4, NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4, 
                  NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, 
                NOTE_G5, 
                NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, 
                  NOTE_C5, NOTE_G4, NOTE_E4, 
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              } 
};


int allNoteDurations[7][42] = {
              {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              },
              {4, 8, 8, 4, 4, 4, 4, 4,
               0, 0, 0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              }, 
              {4, 4, 2, 4, 4, 2, 
                             8, 8, 8, 8, 8, 8, 8, 8, 
                             4, 4, 2,
               0, 0, 0, 0, 
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
               0, 0, 0, 0, 0, 0, 0
              },
              {4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
               4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
               4, 4, 4, 8, 8, 4, 4, 2, 
               4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2,
               0
              },  
              {4, 4, 4, 4, 4, 4, 2, 
                   4, 4, 4, 4, 4, 4, 2, 
               4, 4, 4, 4, 4, 4, 2,
               4, 4, 4, 4, 4, 4, 2,
               4, 4, 4, 4, 4, 4, 2,
               4, 4, 4, 4, 4, 4, 2
              }, 
              {8, 8, 8, 8, 4, 4, 
               4, 4, 2, 
               4, 8, 8, 4, 4, 
               4, 8, 8, 2, 
               8, 8, 8, 8, 4, 4, 
               4, 4, 2,
               4, 8, 8, 8, 4, 
               4, 4, 2,
               0, 0, 0, 0, 0, 0, 0
               }, 
              {8, 4, 4, 8, 4, 
               2, 2, 
               4, 2, 4, 
               8, 4, 4, 8, 4, 
               8, 8, 8, 4, 8, 8, 
               4, 8, 8, 2, 
               4, 4, 4,
               0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
              } 
};

int songLengths[7] = { 0, 8, 17, 41, 42, 35, 28};
int melodyCounter;

int selectSong() {
  int melodyCode = 0;
  
    uint8_t input = isRedButtonPressed * 2 * 2 + 
            isGreenButtonPressed * 2 + isBlueButtonPressed;
  switch (input) {
    case 4:   // 1 0 0 (red)
            melodyCode = 1; 
         break;
       case 2:   // 0 1 0 (green)
            melodyCode = 2;   
         break;
       case 1:   // 0 0 1 (blue)
            melodyCode = 3;  
         break;
       case 6:   // 1 1 0 (yellow)
             melodyCode = 4;     
         break;
       case 3:   // 0 1 1 (cyan)
             melodyCode = 5;        
         break;
       case 5:   // 1 0 1 (magenta)
             melodyCode = 6;     
         break;
       default:  // 0 0 0
         break;
  }
  return melodyCode;
}

void playNextNote() {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / allNoteDurations[whichSong][melodyCounter];
      tone(PIEZO, allSongNotes[whichSong][melodyCounter], noteDuration); 
  
      if (melodyCounter < songLengths[whichSong] - 1){
        melodyCounter++;
      }
      else {
        melodyCounter = 0;
        gameOver = true;
      }
      
      return;
}

void incrementWhichSong() {
      // temporary loop used to change songs until we take user input to do this
    if (whichSong < 66){
        whichSong++;
      }
      else {
        whichSong = 0;
      }
}
