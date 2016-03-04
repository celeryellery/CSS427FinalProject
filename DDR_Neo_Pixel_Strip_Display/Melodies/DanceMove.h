// ----------------------------DanceMove.h--------------------------------------
// Header file for DanceMove class. This class represents a single instruction
// that the player must follow which is displayed via the Neo Pixel strip.
// -----------------------------------------------------------------------------

#ifndef DanceMove_h
#define DanceMove_h

#include "Arduino.h"

// Neo Pixel libraries
#include "Adafruit_NeoPixel/Adafruit_NeoPixel.h"

#ifdef __AVR__
  #include <avr/power.h>
#endif

class DanceMove
{
public:
  DanceMove();    // default constructor
  DanceMove(int, Adafruit_NeoPixel&, uint8_t, int, int); // constructor with numLEDs parameter
  ~DanceMove();   // destructor
  
  void updateDanceMove();   // moves the DanceMove instruction to the next LED on the strip
  bool getExpired() const;  // check if the DanceMove has expired
  uint8_t getColor() const;
  bool isSteppedOn(uint8_t);    // returns whether this DanceMove was successfully stepped on
  
private:
  Adafruit_NeoPixel* strip; // Neo Pixel strip being used for the DDR game
  int danceMovePosition;    // which LED the DanceMove instruction is currently on
  uint8_t color;            // color of the LED (0-255 Wheel value) that represents the DanceMove instruction
  const int NUM_LEDS;       // maximum number of LEDs on the strip
  bool isExpired;      // if the DanceMove has expired
  const uint8_t lowerBound; // lower bound of Dance Zone
  const uint8_t upperBound; // upper bonud of Dance Zone
  
  // utility functions
  void setExpired();
  uint32_t Wheel(byte);     // Color Wheel color chooser
};

#endif

