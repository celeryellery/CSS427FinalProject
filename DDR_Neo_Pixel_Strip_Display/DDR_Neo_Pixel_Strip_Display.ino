// -------------------DDR_Neo_Pixel_Strip_Display.ino---------------------------
// This file was adapted from Adafruit's strandtest.ino.
// This makes use of a 1-meter 30 NeoPixel strip as a display for DDR.
// -----------------------------------------------------------------------------

#include <Adafruit_NeoPixel.h>
#include "DanceMove.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9 // data pin to drive the NeoPixel strip
#define NUM_LEDS 30 // how many LEDs are used for the display
#define UPDATE_INTERVAL 100 // time between updates of light strip in ms
#define DANCE_MOVE_CREATE_INTERVAL 2000 // ms
#define MAX_DANCE_MOVES NUM_LEDS / (DANCE_MOVE_CREATE_INTERVAL / UPDATE_INTERVAL) + 1 // maximum number of dance moves at one time
#define DANCE_ZONE_LOWER_BOUND 20 // LED 20
#define DANCE_ZONE_UPPER_BOUND 23 // LED 23
#define COLOR_MAX 64 // maximum color value (determines brightness)

// analog input pin for seeding random() with noise
#define RANDOM_SEED_PIN 5 // A5

// color wheel values for primary and secondary colors
#define RED      0
#define YELLOW   43
#define GREEN    85
#define CYAN     128
#define BLUE     170
#define MAGENTA  213

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

DanceMove* danceMoveArray[MAX_DANCE_MOVES];

int createDanceMoveTimer;
int updateTimer;

void setup() 
{
  createDanceMoveTimer = millis();
  updateTimer = millis();
  Serial.begin(9600);
  randomSeed(analogRead(RANDOM_SEED_PIN));     // seed the random function with noise on analog input pin 5

  setupStrip(); // setup the dance strip
  
  // initialize danceMoveArray
  for (int i = 0; i < MAX_DANCE_MOVES; i++)
     danceMoveArray[i] = NULL; 
}

void loop() 
{
  int time = millis();

  // create a new Dance Move at a regular interval
  if (time - createDanceMoveTimer > DANCE_MOVE_CREATE_INTERVAL)
    createDanceMove();
  
  // update the strip
  if (time - updateTimer > UPDATE_INTERVAL)
    updateStrip();
}

// updates the NeoPixel strip with the new positions of each DanceMove
void updateStrip()
{
  updateTimer = millis();

  for (int i = 0; i < MAX_DANCE_MOVES; i++)
  {
     if (danceMoveArray[i] == NULL)
       continue;
     if (danceMoveArray[i]->getExpired())
     {
       delete danceMoveArray[i];
       danceMoveArray[i] = NULL;
     }
     else 
       danceMoveArray[i]->updateDanceMove();
  }

  //maintainDanceZone(); // refresh the dance zone
  strip.show();  
}

// creates a DanceMove to display on the NeoPixel strip
void createDanceMove()
{
   createDanceMoveTimer = millis();

   for (int i = 0; i < MAX_DANCE_MOVES; i++)
   {
      if (danceMoveArray[i] == NULL)
      {
         danceMoveArray[i] = new DanceMove(NUM_LEDS, strip, (random() % 6) * (255 / 6), 
           DANCE_ZONE_LOWER_BOUND, DANCE_ZONE_UPPER_BOUND);
         break;
      } 
   } 
}

// sets up the NeoPixel strip by initializing it and creating the Dance Zone
void setupStrip()
{
  strip.begin();
  maintainDanceZone(); // Initialize strip with Dance Zone  
  strip.show();  
}

// prevents DanceMoves from erasing the DanceZone when passing over it
void maintainDanceZone()
{
for (int i = DANCE_ZONE_LOWER_BOUND; i <= DANCE_ZONE_UPPER_BOUND; i++)
    strip.setPixelColor(i, COLOR_MAX, COLOR_MAX, COLOR_MAX);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
