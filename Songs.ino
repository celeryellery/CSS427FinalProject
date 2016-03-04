#include "Melodies/pitches.h"
#include "Melodies/Song.h"

#define SONG_LIST_SIZE 3
Song songs[10];
int currentSong = 1;

void initSongLib()
{
  int m1[] = {NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
  int dur1[] = {4, 8, 8, 4, 4, 4, 4, 4};
  int m2[] = {NOTE_E4, NOTE_D4, NOTE_C4, NOTE_E4, NOTE_D4, NOTE_C4, 
                        NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, 
                        NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, 
                        NOTE_E4, NOTE_D4, NOTE_C4};
  int dur2[] = {4, 4, 2, 4, 4, 2, 
                       8, 8, 8, 8, 8, 8, 8, 8, 
                       4, 4, 2};
  int m3[] = {NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, 
                       NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5, 
                       NOTE_A4, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_F5, NOTE_F5, NOTE_D5, 
                       NOTE_C5, NOTE_C5, NOTE_D5, NOTE_C5,
                       NOTE_C5, NOTE_C5, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, NOTE_D5, NOTE_C5, 
                       NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_C5, NOTE_G4, NOTE_A4, 
                       NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4};
  int dur3[] = {4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
                         4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2, 
                         4, 4, 4, 8, 8, 4, 4, 2, 
                         4, 8, 8, 8, 8, 8, 8, 4, 8, 8, 2};
                                         
  songs[1] = Song(m1, dur1);
  songs[2] = Song(m2, dur2);
  songs[3] = Song(m3, dur3);
}

int getCurrentNote(int id)
{
  return songs[id].getCurrentNote();
}

int getCurrentDuration(int id)
{
  return songs[id].getCurrentDuration();
}

int getCurrent(int id)
{
  return songs[id].getCurrent();  
}

int getLength(int id)
{
  return songs[id].getLength();  
}

void popNextNote(int id)
{
    songs[id].popNextNote();
}
