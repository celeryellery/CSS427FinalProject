// -------------------DDR_Neo_Pixel_Strip_Display.ino---------------------------
// This file implements a DDR-like game with a 1-meter 30 LED NeoPixel display
// and a piezo buzzer for audio ouput.
// -----------------------------------------------------------------------------
#include "pitches.h"
#include <CapacitiveSensor.h>

#include <Adafruit_NeoPixel.h>
#include "DanceMove.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

// game constants
#define UPDATE_INTERVAL 100 // time between updates of light strip in ms
#define DANCE_MOVE_CREATE_INTERVAL 1000 // ms
#define MAX_DANCE_MOVES NUM_LEDS / (DANCE_MOVE_CREATE_INTERVAL / UPDATE_INTERVAL) + 20 // maximum number of dance moves at one time (+1 +1 to account for delay)
#define DANCE_ZONE_LOWER_BOUND 20 // LED 20
#define DANCE_ZONE_UPPER_BOUND 23 // LED 23
#define DELAY_BEFORE_GAME 2000 // time that the player has to get ready before a song starts (ms)

// player input pins
#define RED_BUTTON   5
#define GREEN_BUTTON 6
#define BLUE_BUTTON  7

// analog input pin for seeding random() with noise
#define RANDOM_SEED_PIN 5 // A5

// pin for the sound
const int PIEZO = 8;

const char* songNames[7] = { "", "Shave and a Haircut", "Hot Crossed Buns",
                           "Jasmine Flower", "Twinkle Twinkle Little Start", 
                           "I'm a Little Teapot", "Super Mario"
                         };
// -----------------------------------------------------------------------------
// Color Constants
// -----------------------------------------------------------------------------
// color wheel values for primary and secondary colors
#define RED      0
#define YELLOW   42
#define GREEN    85
#define CYAN     115
#define BLUE     170
#define MAGENTA  212
const int color[6] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
#define COLOR_MAX 64 // maximum color value (determines brightness)
// -----------------------------------------------------------------------------
// End Color Constants
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// NeoPixel Strip
// -----------------------------------------------------------------------------
#define PIN 9 // data pin to drive the NeoPixel strip
#define NUM_LEDS 30 // how many LEDs are used for the display

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
// -----------------------------------------------------------------------------
// End NeoPixel Strip
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Game Objects, State Variables, and Timers
// -----------------------------------------------------------------------------
DanceMove* danceMoveArray[MAX_DANCE_MOVES];

int createDanceMoveTimer;
int updateTimer;

// game state variables
int whichSong = 0;
int score = 0;
bool gameOver;
// -----------------------------------------------------------------------------
// End Game Objects, State Variables, and Timers
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Input Variables
// -----------------------------------------------------------------------------
bool isRedButtonPressed;
bool isGreenButtonPressed;
bool isBlueButtonPressed;

int previousRedSensorVal;
int previousGreenSensorVal;
int previousBlueSensorVal;
// -----------------------------------------------------------------------------
// End Input Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Capacitive Sensor Variables
// -----------------------------------------------------------------------------
CapacitiveSensor   cs_green = CapacitiveSensor(4,2);
CapacitiveSensor   cs_red = CapacitiveSensor(13, 12);
CapacitiveSensor   cs_blue = CapacitiveSensor(11,10);

// amount of change between sensor readings to cause a button press event
int sensorThreshold = 150;

// Create long ints to hold output values of sensors:
long totalgreen = 0;
long totalred = 0;
long totalblue = 0;
// -----------------------------------------------------------------------------
// End Capacitive Sensor Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Sonar Variables
// -----------------------------------------------------------------------------
int ThreshHold_LO = 15;
int ThreshHold_HI = 35;

int TonesO4[] = {NOTE_C4,NOTE_D5,
NOTE_E4,NOTE_F5,NOTE_G4,NOTE_A5,NOTE_B4,NOTE_C5,NOTE_D4, 
NOTE_E5, NOTE_F4,NOTE_G5, NOTE_A4, NOTE_B5};

int Len = sizeof(TonesO4)/sizeof(TonesO4[1]);
// -----------------------------------------------------------------------------
// End Sonar Variables
// -----------------------------------------------------------------------------
void setup() 
{
  // sonar pins
  pinMode(A13, INPUT);
  pinMode(3, OUTPUT); 
  
  Serial.begin(9600);
  setupDDR();
}

void loop() 
{
  mainMenu(); // choose which song then start the game
  Serial.print("\nYou've Chosen: "); Serial.println(songNames[whichSong]);
  delay(DELAY_BEFORE_GAME); // give player time to get ready for the game
  playDDR();
}

se// allow the player to choose a song to play
void mainMenu()
{
  displayOptions();
  getMenuInput(); // sets the isButtonPressed variables
  whichSong = selectSong(); // chooses the song based on state of isButtonSet(rgb) variables
}

// show the player which songs can be picked
void displayOptions()
{
  Serial.println("\nSelect one of the following songs to play, by standing on the corresponding pressure plate(s).");
  Serial.println("Red: Shave and a Haircut");
  Serial.println("Green: Hot Crossed Buns");
  Serial.println("Blue: Jasmine Flower");
  Serial.println("Yellow: Twinkle Twinkle Little Star");
  Serial.println("Cyan: I'm a Little Teapot");
  Serial.println("Magenta: Super Mario");
}

// reads the capacitive sensors for menu input
void getMenuInput()
{
  do
  {
    int currentTime = millis();
    // allow for some time tolerance so that two pads can be stepped on "simultaneously"
    if (currentTime > updateTimer + UPDATE_INTERVAL)
    {
      checkPlayerInput();
      updateTimer = millis();
    }
  } while (!(isRedButtonPressed || isGreenButtonPressed || isBlueButtonPressed));
}

void playSonar()
{
  for (;;)
  {
    // put your main code here, to run repeatedly:
    int inRead = analogRead(A13);
    Serial.print("inRead: "); Serial.println(inRead);
    /** Test / Debug
     * Serial.print("Volt/Dist: "); 
     * Serial.print(inRead);
     * Serial.println(); */
    
    if(inRead >= ThreshHold_LO & inRead <= ThreshHold_HI)
    {
      int mapping = map(inRead, ThreshHold_LO, ThreshHold_HI, 0, Len-1);
      tone(3, TonesO4[mapping]); 
      delay(300);
      /** Test / Debug
       * Serial.print("Mapped Dist: ");
       * Serial.print(mapping);
       * Serial.println(); */
    }
    else
    {
      noTone(3);
    }
  }
}

void playDDR()
{
  setupDDR();
  while (!gameOver)
  {
    int time = millis();
  
    // constantly monitor the player's input for minimal delay
    checkPlayerInput();
    
    // create a new Dance Move at a regular interval
    if (time - createDanceMoveTimer > DANCE_MOVE_CREATE_INTERVAL)
      createDanceMove();
    
    // update the strip
    if (time - updateTimer > UPDATE_INTERVAL)
    {
      processPlayerInput();
      updateStrip();
    }
  }
  // reset the NeoPixel strip
  for (int i = 0; i < NUM_LEDS; i++)
    strip.setPixelColor(i, 0, 0, 0);
  strip.show();
  delay(5000);
}

// setup all the variables and pins to play DDR
void setupDDR() 
{
  gameOver = false;
  score = 0;
  initCapacitiveSensor();
 
  pinMode(PIEZO, OUTPUT);
  
  createDanceMoveTimer = millis();
  updateTimer = millis();

  // initialize player input
  isRedButtonPressed = false;
  isGreenButtonPressed = false;
  isBlueButtonPressed = false;

  previousRedSensorVal = 0;
  previousGreenSensorVal = 0;
  previousBlueSensorVal = 0;
  
  // seed the random function with noise on analog input pin 5
  randomSeed(analogRead(RANDOM_SEED_PIN));

  // setup the dance strip
  setupStrip();
  
  // initialize danceMoveArray
  for (int i = 0; i < MAX_DANCE_MOVES; i++)
     danceMoveArray[i] = NULL; 
}

void initCapacitiveSensor()                    
{
   cs_red.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_green.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   cs_blue.set_CS_AutocaL_Millis(0xFFFFFFFF); 
}

// updates the NeoPixel strip with the new positions of each DanceMove
void updateStrip()
{
  updateTimer = millis();
  maintainDanceZone(); // refresh the dance zone

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
         danceMoveArray[i] = new DanceMove(NUM_LEDS, strip, color[(random() % 6)], 
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
  for (int i = 0; i < NUM_LEDS; i++)
  {
     if ( i >= DANCE_ZONE_LOWER_BOUND && i <= DANCE_ZONE_UPPER_BOUND)
       strip.setPixelColor(i, COLOR_MAX, COLOR_MAX, COLOR_MAX);
     else
       strip.setPixelColor(i, 0, 0, 0); 
  }
}

// checks for input from the player on each input pin
void checkPlayerInput()
{
    totalgreen =  cs_green.capacitiveSensor(30);
    totalred =  cs_red.capacitiveSensor(30);
    totalblue =  cs_blue.capacitiveSensor(30);
    
  // check to see if the reading has increased by a certain threshold
  // since the last reading was taken. This will detect a button
  // "event" rather than checking for the button to be in a specific state
  if (!isRedButtonPressed)
  {
    isRedButtonPressed = totalred > previousRedSensorVal + sensorThreshold;
  }
  if (!isGreenButtonPressed)
  {
    isGreenButtonPressed = totalgreen > previousGreenSensorVal + sensorThreshold;
  }
  if (!isBlueButtonPressed)
  {
    isBlueButtonPressed = totalblue > previousBlueSensorVal + sensorThreshold;
  }

  // update the previous values to the current values
  previousRedSensorVal = totalred;
  previousGreenSensorVal = totalgreen;
  previousBlueSensorVal = totalblue;
}

// determines if the players input matches the right instruction at the right time
void processPlayerInput()
{
  // check each DanceMove to see if it is matched by the input
  // and lies in the DanceMove zone
  uint8_t input = isRedButtonPressed * 2 * 2 + 
    isGreenButtonPressed * 2 + isBlueButtonPressed;

  for (int i = 0; i < MAX_DANCE_MOVES; i++)
  {
    if (danceMoveArray[i] == NULL || danceMoveArray[i]->getExpired())
      continue;
      
    // process the input as a 3-bit number where red is the MSB, blue is the LSB,
    // and green is in between
    switch(input)
    {
       case 4:   // 1 0 0 (red)
         if (danceMoveArray[i]->isSteppedOn(RED))
          playNextNote();  
         break;
       case 2:   // 0 1 0 (green)
         if (danceMoveArray[i]->isSteppedOn(GREEN))
          playNextNote();
         break;
       case 1:   // 0 0 1 (blue)
         if (danceMoveArray[i]->isSteppedOn(BLUE))
          playNextNote();
         break;
       case 6:   // 1 1 0 (yellow)
         if (danceMoveArray[i]->isSteppedOn(YELLOW))
          playNextNote();   
         break;
       case 3:   // 0 1 1 (cyan)
         if (danceMoveArray[i]->isSteppedOn(CYAN))
          playNextNote();     
         break;
       case 5:   // 1 0 1 (magenta)
         if (danceMoveArray[i]->isSteppedOn(MAGENTA))
          playNextNote();
         break;
       default:  // 0 0 0
         break;
    }
  }

  // reset player input after processing it
  isRedButtonPressed = false;
  isGreenButtonPressed = false;
  isBlueButtonPressed = false;
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
