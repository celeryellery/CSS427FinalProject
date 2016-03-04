// -------------------DDR_Neo_Pixel_Strip_Display.ino---------------------------
// This file was adapted from Adafruit's strandtest.ino.
// This makes use of a 1-meter 30 NeoPixel strip as a display for DDR.
// -----------------------------------------------------------------------------
/*
 Melodies
 Interactive game that allows players to make notes based on which
 capacitive touch pad they step on. 
 circuit:
 * 8-ohm speaker on digital pin 8
 * 5 capacitive touch sensors and corresponding resistors
 Based on code by Tom Igoe, which can be found here: 
 http://www.arduino.cc/en/Tutorial/Tone
 */
#include "pitches.h"
#include <CapacitiveSensor.h>

#include <Adafruit_NeoPixel.h>
#include "DanceMove.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 9 // data pin to drive the NeoPixel strip
#define NUM_LEDS 30 // how many LEDs are used for the display
#define UPDATE_INTERVAL 100 // time between updates of light strip in ms
#define DANCE_MOVE_CREATE_INTERVAL 1000 // ms
#define MAX_DANCE_MOVES NUM_LEDS / (DANCE_MOVE_CREATE_INTERVAL / UPDATE_INTERVAL) + 2 // maximum number of dance moves at one time (+1 +1 to account for delay)
#define DANCE_ZONE_LOWER_BOUND 20 // LED 20
#define DANCE_ZONE_UPPER_BOUND 23 // LED 23
#define COLOR_MAX 64 // maximum color value (determines brightness)

// player input pins
#define RED_BUTTON   5
#define GREEN_BUTTON 6
#define BLUE_BUTTON  7

// analog input pin for seeding random() with noise
#define RANDOM_SEED_PIN 5 // A5

// color wheel values for primary and secondary colors
#define RED      0
#define YELLOW   42
#define GREEN    85
#define CYAN     115
#define BLUE     170
#define MAGENTA  212

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
int color[6] = {RED, YELLOW, GREEN, CYAN, BLUE, MAGENTA};
bool isRedButtonPressed;
bool isGreenButtonPressed;
bool isBlueButtonPressed;
bool gameOver;

const int sensor1pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor2pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor3pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor4pin = 8; // connect the first sensor to pin 8 on the Arduino Mega
//const int sensor5pin = 8; // connect the first sensor to pin 8 on the Arduino Mega

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

int long stepThreshholdRed = 2400;
int long stepThreshholdGreen = 2500;
int long stepThreshholdBlue = 2400;

CapacitiveSensor   cs_green = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_red = CapacitiveSensor(13, 12);        // 10M resistor between pins 1 & 0, pin 0 is sensor pin, add a wire and or foil if desired
CapacitiveSensor   cs_blue = CapacitiveSensor(11,10);        // 10M resistor between pins 6 & 5, pin 5 is sensor pin, add a wire and or foil if desired

// Create long ints to hold output values of sensors:
long totalgreen = 0;
long totalred = 0;
long totalblue = 0;
//long total4 = 0;
//long total5 = 0;

int whichSong = 0;
int songLengths[7] = { 0, 8, 17, 41, 42, 35, 28};
int melodyCounter;

void setup() 
{
  gameOver = false;
  
  cs_green.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
  cs_red.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  cs_blue.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   //cs_10_9.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   //cs_12_11.set_CS_AutocaL_Millis(0xFFFFFFFF); 
  // initialize timers
 
   pinMode(sensor1pin, OUTPUT);
   //pinMode(sensor2pin, OUTPUT);
   //pinMode(sensor3pin, OUTPUT);
   //pinMode(sensor4pin, OUTPUT);
   //pinMode(sensor5pin, OUTPUT);
  
  createDanceMoveTimer = millis();
  updateTimer = millis();

  // initialize player input
  isRedButtonPressed = false;
  isGreenButtonPressed = false;
  isBlueButtonPressed = false;

  Serial.begin(9600);
  
  // seed the random function with noise on analog input pin 5
  randomSeed(analogRead(RANDOM_SEED_PIN));

  // setup the dance strip
  setupStrip();
  
  // initialize danceMoveArray
  for (int i = 0; i < MAX_DANCE_MOVES; i++)
     danceMoveArray[i] = NULL; 
}

void loop() 
{
  mainMenu(); // choose which song then start the game
  Serial.print("Which Song: "); Serial.println(whichSong);
  playDDR();
}

// allow the player to choose a song to play
void mainMenu()
{
  displayOptions();
  getMenuInput(); // sets the isButtonPressed variables
  whichSong = selectSong(); // chooses the song based on state of isButtonSet(rgb) variables
}

// show the player which songs can be picked
void displayOptions()
{
  Serial.println("Select one of the following songs to play, by standing on the corresponding pressure plate(s).");
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
    totalgreen =  cs_green.capacitiveSensor(30);
    delay(250);
    totalred =  cs_red.capacitiveSensor(30);
    delay(250);
    totalblue =  cs_blue.capacitiveSensor(30);
    delay(250);
    if (!isRedButtonPressed)
    {
      isRedButtonPressed = totalred > stepThreshholdRed;
      if (isRedButtonPressed)
        Serial.println("Red stepped on!");
    }
    if (!isGreenButtonPressed)
    {
      isGreenButtonPressed = totalgreen > stepThreshholdGreen;
      if (isGreenButtonPressed)
        Serial.println("Green stepped on!");
    }
    if (!isBlueButtonPressed)
    {
      isBlueButtonPressed = totalblue > stepThreshholdBlue;
      if (isBlueButtonPressed)
        Serial.println("Blue stepped on!");
    }
  } while (!(isRedButtonPressed || isGreenButtonPressed || isBlueButtonPressed));
}

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
  initCapacitiveSensor();
 
  pinMode(sensor1pin, OUTPUT);
  
  createDanceMoveTimer = millis();
  updateTimer = millis();

  // initialize player input
  isRedButtonPressed = false;
  isGreenButtonPressed = false;
  isBlueButtonPressed = false;
  
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

boolean isSteppedOn(long pressurePlateValue) {
  return ((pressurePlateValue > stepThreshholdRed) || 
          (pressurePlateValue > stepThreshholdGreen) || 
          (pressurePlateValue > stepThreshholdBlue));
}

void playNextNote() {
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / allNoteDurations[whichSong][melodyCounter];
      tone(sensor1pin, allSongNotes[whichSong][melodyCounter], noteDuration); 
  
      if (melodyCounter < songLengths[whichSong]){
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
// end temporary code ------------------------------------------------------------------------------------------------------------------

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
  // only take a reading if the button has not been pressed since the last update
  
  
    totalgreen =  cs_green.capacitiveSensor(30);
    Serial.print("ValueG: ");
    Serial.print(totalgreen);
    totalred =  cs_red.capacitiveSensor(30);
    Serial.print("\tValueR: ");
    Serial.print(totalred);
    totalblue =  cs_blue.capacitiveSensor(30);
    Serial.print("\tValueB: ");
    Serial.println(totalblue);
  if (!isRedButtonPressed)
  {
    isRedButtonPressed = totalred > stepThreshholdRed;
  }
  if (!isGreenButtonPressed)
  {
    isGreenButtonPressed = totalgreen > stepThreshholdGreen;
  }
  if (!isBlueButtonPressed)
  {

    isBlueButtonPressed = totalblue > stepThreshholdBlue;
  }

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
         {
          Serial.println("Stepped on!");
          playNextNote();  
         }
         break;
       case 2:   // 0 1 0 (green)
         if (danceMoveArray[i]->isSteppedOn(GREEN))
         {
          Serial.println("Stepped on!");
          playNextNote();
         }
         break;
       case 1:   // 0 0 1 (blue)
         if (danceMoveArray[i]->isSteppedOn(BLUE))
         {
          Serial.println("Stepped on!");
          playNextNote();
         }
         break;
       case 6:   // 1 1 0 (yellow)
         if (danceMoveArray[i]->isSteppedOn(YELLOW))
         {
          Serial.println("Stepped on!");
          playNextNote();
         }    
         break;
       case 3:   // 0 1 1 (cyan)
         if (danceMoveArray[i]->isSteppedOn(CYAN))
         {
          Serial.println("Stepped on!");
          playNextNote();
         }       
         break;
       case 5:   // 1 0 1 (magenta)
         if (danceMoveArray[i]->isSteppedOn(MAGENTA))
         {
          Serial.println("Stepped on!");
          playNextNote();
         }    
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
