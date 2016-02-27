#include "CapacitiveSensor/CapacitiveSensor.h"

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

CapacitiveSensor cs_RED = CapacitiveSensor(1,0);        // 10M resistor between pins 1 & 0, pin 0 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_GREEN = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired
CapacitiveSensor cs_BLUE = CapacitiveSensor(10,11);        // 10M resistor between pins 10 & 11, pin 11 is sensor pin, add a wire and or foil if desired

void initCapacitiveSensor()                    
{
   cs_RED.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   cs_GREEN.set_CS_AutocaL_Millis(0xFFFFFFFF); 
   cs_BLUE.set_CS_AutocaL_Millis(0xFFFFFFFF); 
}

int csOutput(char csColor)
{
  switch (csColor) 
  {
    case 'R':
      return cs_RED.capacitiveSensor(30);
      break;
    case 'G':
      return cs_GREEN.capacitiveSensor(30);
      break;
    case 'B':
      return cs_BLUE.capacitiveSensor(30);
      break;
  }
}

int long stepThreshhold = 180;

boolean isSteppedOn(char csColor) 
{
  switch (csColor) 
  {
    case 'R':
      return cs_RED.capacitiveSensor(30) > stepThreshhold);
      break;
    case 'G':
      return cs_GREEN.capacitiveSensor(30) > stepThreshhold);
      break;
    case 'B':
      return cs_BLUE.capacitiveSensor(30) > stepThreshhold);
      break;
  }
}
