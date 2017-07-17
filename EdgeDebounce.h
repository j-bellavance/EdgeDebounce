/*
 *EdgeDebounce.h 
 *Created by: Jacques bellavance, July 7 2017
 *Released into the public domain
 *GNU GENERAL PUBLIC LICENSE V3
 *
 *This library is designed to debounce switches.
 *It was inspired by this article: http://www.ganssle.com/debouncing.htm
 *It is designed to be lightweight
 *PSEUDOCODE
 * 1) Repeat
 * 1)   Read the switch 16 times
 * 2) Until all reads are identical
 * 3) Return the switch's status
 *    
 *The number of times the switch is repetitively read can be set between 1 and 32
 *Switches can use either an external pulldown resistor or the internal pullup resistor
 *pinMode() is set by the constructor
*/
 
#ifndef EdgeDebounce_h
#define EdgeDebounce_h

#include "Arduino.h"

#define PULLUP 0
#define PULLDOWN 1
#define OPEN 0
#define CLOSED 1

class EdgeDebounce
{
  public:
    //methods
    EdgeDebounce(byte pin, byte mode);  //Constructor
    bool closed();                      //PULLDOWN mode: ON=1, OFF=0 ; PULLUP mode ON=0, OFF=1
    int pressed();                      //Returns true if pressed (closed, ON)
    void setSensitivity(byte w);        //Set debounce reads (1..32)
    byte getSensitivity();              //Returns the current sensitivity of Debounce
    
  private:
    //methods
    //Attributes
    byte MYpin;                                   //The switch's pin
    byte MYmode;                                  //The switch's mode (PULLUP or PULLDOWN)
		byte MYsensitivity = 16;                      //Current sensitivity (1..32)
		unsigned long debounceDontCare = 0xffff0000;  //Don't care mask
};

#endif;
