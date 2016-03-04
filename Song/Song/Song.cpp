
#include "Song.h"

// constructor
Song::Song(int melody[], int duration[])
{
    this->length = ARRAY_SIZE(melody);
    this->current = 0;
    
    for(int i = 0; i < this->length; i++)
    {
        this->melody[i] = melody[i];
        this->duration[i] = duration[i];
    }
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

void Song::popNextNote()
{
    current++;
    
    if(current >= length)
    {
        current = 0;
    }
}