
#define ARRAY_SIZE(array) (sizeof((array))/sizeof((array[0])))

//#include "Arduino.h"
#include <stdio.h>
using namespace std;

class Song
{
public:
    // constructor
    Song();
    Song(int* melody,int* duration);
    ~Song();
    
    // methods
    int getCurrentNote();
    int getCurrentDuration();
    int getLength();
    int getCurrent();
    void popNextNote();
    
private:
    // variables
    int melody[100];
    int duration[100];
    int length;
    int current;
};

// constructor
Song::Song()
{
    this->length = 0;
    this->current = 0;
}
Song::Song(int* melody, int* duration)
{
    this->length = ARRAY_SIZE(melody);
    this->current = 0;
    
    for(int i = 0; i < this->length; i++)
    {
        this->melody[i] = melody[i];
        this->duration[i] = duration[i];
    }
}

Song::~Song()
{
    
}
// methods
int Song::getCurrentNote()
{
    return melody[current];
}

int Song::getCurrentDuration()
{
    return duration[current];
}

int Song::getLength()
{
    return length;
}

int Song::getCurrent()
{
    return current;
}

void Song::popNextNote()
{
    current++;
    
    if(current >= length)
    {
        current = 0;
    }
}