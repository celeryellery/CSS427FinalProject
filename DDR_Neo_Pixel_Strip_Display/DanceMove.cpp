// -----------------------------DanceMove.cpp-----------------------------------
// Implementation file for the DanceMove class. This class represents an
// instruction that the player must follow and is represented by a colored
// LED on the strip of Neo Pixels.
// -----------------------------------------------------------------------------

#include "Arduino.h"
#include "DanceMove.h"

// default values for bounds of Dance Zone
#define DEFAULT_LOWER_BOUND 20
#define DEFAULT_UPPER_BOUND 23

// -----------------------------------------------------------------------------
// Default Constructor with initialization list
// -----------------------------------------------------------------------------
DanceMove::DanceMove() : NUM_LEDS(0), strip(NULL), isExpired(false), 
  danceMovePosition(-1), lowerBound(DEFAULT_LOWER_BOUND), 
  upperBound(DEFAULT_UPPER_BOUND) { }

// -----------------------------------------------------------------------------
// Default Destructor
// -----------------------------------------------------------------------------
DanceMove::~DanceMove() { }

// -----------------------------------------------------------------------------
// Constructor that defines the maximum number of LEDs on a strip
// -----------------------------------------------------------------------------

DanceMove::DanceMove(int num, Adafruit_NeoPixel& LEDStrip, uint8_t c, 
  int lower, int upper) : NUM_LEDS(num), lowerBound(lower), upperBound(upper)
{
  strip = &LEDStrip;
  danceMovePosition = -1; 
  color = c;
  isExpired = false;
}

// -----------------------------------------------------------------------------
// UpdateDanceMove function. This function updates the position of the DanceMove
// instruction along the Neo Pixel strip.
// -----------------------------------------------------------------------------
void DanceMove::updateDanceMove()
{
  if (!isExpired)
  {
     // turn off the previous pixel or set it back to white if in the Dance Zone
     if (danceMovePosition >= lowerBound && danceMovePosition <= upperBound)
	strip->setPixelColor(danceMovePosition++, 64, 64, 64);
     else
	strip->setPixelColor(danceMovePosition++, 0, 0, 0);
     
     // turn on the current pixel
     strip->setPixelColor(danceMovePosition, Wheel(color));
     
     // remove DanceMove when it moves past the end of the Neo Pixel strip
     if (danceMovePosition > NUM_LEDS - 1)
	setExpired();
  }
}

// -----------------------------------------------------------------------------
// Adafruit's Wheel function.
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// -----------------------------------------------------------------------------
uint32_t DanceMove::Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// -----------------------------------------------------------------------------
// setExpired function. This function marks a DanceMove as expired so that it
// will no longer update and will be deleted on the next update cycle
// -----------------------------------------------------------------------------
void DanceMove::setExpired()
{
	isExpired = true;
}

// -----------------------------------------------------------------------------
// getExpired function. Returns whether or not the DanceMove is expired.
// -----------------------------------------------------------------------------
bool DanceMove::getExpired() const
{
	return isExpired;
}

// -----------------------------------------------------------------------------
// getColor function. Returns the color wheel value of the Dance Move's color
// -----------------------------------------------------------------------------
uint8_t DanceMove::getColor() const
{ 
  return color; 
}
