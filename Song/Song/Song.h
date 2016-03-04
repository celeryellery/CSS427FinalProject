
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

#ifndef Song_h
#define Song_h

#endif
//#include "Arduino.h"
#include <stdio.h>
using namespace std;

class Song
{
public:
    // constructor
    Song(int melody[],int duration[]);
    
    // methods
    int getCurrentNote();
    int getCurrentDuration();
    int getLength();
    void popNextNote();
    
private:
    // variables
    int melody[100];
    int duration[100];
    int length;
    int current;
};
