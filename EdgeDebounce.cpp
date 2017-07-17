/*
 *EdgeDebounce.cpp 
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

#include <Arduino.h>
#include "EdgeDebounce.h"

//Constructor===============================
//pin: the pin connected to the switch
//------------------------------------------
EdgeDebounce::EdgeDebounce(byte pin, byte mode) {
  MYpin = pin;
  if (mode == PULLUP) {
    pinMode(pin, INPUT_PULLUP);
    MYmode = PULLUP;
  }
  else {
    pinMode(pin, INPUT);
    MYmode = PULLDOWN;
  }
}//Debounce---------------------------------


//setSensitivity==================================================================
//Sets the number of times a switch is read repeatedly by the debouncer routine
//It defaults to 16 times. Allowable values are 1..32
//--------------------------------------------------------------------------------
void EdgeDebounce::setSensitivity(byte w) {
	if (w >= 1 && w <= 32) {
		MYsensitivity = w;
		debounceDontCare = 0xffffffff;
		for (byte i = 0; i < w; i++) debounceDontCare = debounceDontCare << 1 | 0;
	}
}//setSensitivity--------------------------------------------------------------------

 //getSensitivity==================================================================
 //Returns the current sensitivity of Debounce
 //--------------------------------------------------------------------------------
byte EdgeDebounce::getSensitivity() {
  return MYsensitivity;
}//getSensitivity--------------------------------------------------------------------

//pressed=========================================================================================================
//Debounces the switch connected to "MYpin"
//The switch is read 16 times (~60us) to look for 16 consecutive HIGH or LOW
//If unsuccessfull, it means that a change is occuring at that same moment
//and that either a rising or falling edge of the signal is actualy occuring.
//The pin is reread repetetively 16 times until the edge is confirmed.
//If the switch has been declared PULLDOWN: Returns 0 if open or 1 if closed
//If the switch has been declared PULLUP: Returns 1 if open or 0 if closed
//---------------------------------------------------------------------------------------------------------------
int EdgeDebounce::pressed() {
  unsigned long pinStatus;
  do {
    pinStatus = 0xffffffff;
    for (byte i = 1; i <= MYsensitivity; i++) pinStatus = (pinStatus << 1) | digitalRead(MYpin);
  } while ((pinStatus != debounceDontCare) && (pinStatus != 0xffffffff));
  return byte(pinStatus & 0x00000001);
}//pressed--------------------------------------------------------------------------------------------------------

//closed==============================================
//Returns true if the switch is closed (or ON)
//-----------------------------------------------------
bool EdgeDebounce::closed() {
  if (MYmode == PULLUP) return !pressed();
  else                  return pressed();
}//closed---------------------------------------------

