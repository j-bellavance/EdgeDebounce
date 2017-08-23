/*
 *EdgeDebounce.cpp 
 *Created by: Jacques bellavance, July 7 2017
 *Released into the public domain
 *GNU GENERAL PUBLIC LICENSE V3
 *Version 1.2 :
 *  Added a .begin() method
 *  Renamed .pressed() as .debounce()  (kept .pressed() for backward compatibility)
 *  Added .open()
 *  Added .rose()
 *  Added .fell()
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

//Constructor=======================================
//pin: the pin connected to the switch
//--------------------------------------------------
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
}//Debounce------------------------------------------

void EdgeDebounce::begin() {
	if (MYmode == PULLUP) pinMode(MYpin, INPUT_PULLUP);
  else                  pinMode(MYpin, INPUT);
}


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

//debounce=================================================================================================
//Debounces the switch connected to "MYpin"
//The switch is read 16 times (~60us) to look for 16 consecutive HIGH or LOW
//If unsuccessfull, it means that a change is occuring at that same moment
//and that either a rising or falling edge of the signal is actualy occuring.
//It can also mean that there is currently some Electro Mechanic Interferences (EMI) occuring
//The pin is reread repetetively 16 times until the signal is confirmed stable.
//---------------------------------------------------------------------------------------------------------------
int EdgeDebounce::debounce() {
  unsigned long pinStatus;
  do {
    pinStatus = 0xffffffff;
    for (byte i = 1; i <= MYsensitivity; i++) pinStatus = (pinStatus << 1) | digitalRead(MYpin);
  } while ((pinStatus != debounceDontCare) && (pinStatus != 0xffffffff));
  return byte(pinStatus & 0x00000001);  
}//debounce------------------------------------------------------------------------------------------------

//pressed================================
//Left here for backward compatibility
//---------------------------------------
int EdgeDebounce::pressed() {
	return debounce();
}//pressed-------------------------------

//updateStatus===================================================================
//After releasing EdgeDebounceLite, I realized that EdgeDebounce could do more
//With this small piece of code, EdgeDebounce can return if a switch is
//  .closed();  //Conducting current
//  .open();    //Not conducting current
//  .rose();    //Just went from open to closed
//  .fell();    //just went from closed to open
//-------------------------------------------------------------------------------
byte EdgeDebounce::update() {
  byte newStatus = debounce();
	if (MYmode == PULLUP) newStatus = !newStatus;
	if (MYstatus == newStatus) MYtransition = STABLE;
	else {
		if (MYstatus == OPEN && newStatus == CLOSED) MYtransition = RISING;
		if (MYstatus == CLOSED && newStatus == OPEN) MYtransition = FALLING;
	}
	MYstatus = newStatus;
  return newStatus;
}//update-------------------------------------------------------------------------

//statusMethods===============================================
bool EdgeDebounce::closed() { update(); return  MYstatus; }
bool EdgeDebounce::open()   { update(); return !MYstatus; }

//transition methods=====================================================
bool EdgeDebounce::rose() { update(); return MYtransition == RISING; }
bool EdgeDebounce::fell() { update(); return MYtransition == FALLING; }

