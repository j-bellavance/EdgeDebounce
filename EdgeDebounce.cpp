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
EdgeDebounce::EdgeDebounce(byte pin, pinType mode) {
  MYpin = pin;
  MYmode = mode;
}//Debounce------------------------------------------

//begin================================================
void EdgeDebounce::begin() {
	if (MYmode == PULLUP) pinMode(MYpin, INPUT_PULLUP);
  else                  pinMode(MYpin, INPUT);
}//begin-----------------------------------------------


//setSensitivity==================================================================
//Sets the number of times a switch is read repeatedly by the debouncer routine
//It defaults to 16 times. Allowable values are 1..32
//Thanks to Jiggy-Ninja for the expression
//--------------------------------------------------------------------------------
void EdgeDebounce::setSensitivity(byte w) {
	if (w >= 1 && w <= 32) {
		MYsensitivity = w;
    debounceDontCare = ~((1UL<<w)-1);
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
//A counter, MYsensitivity, can be set between 1 and 32. 
//This value represents how many times the switch is read consecutively. 
//The switch is read MYsensitivity times to look for MYsensitivity consecutive HIGH or LOW
//If unsuccessfull, it means that a change is occuring at that same moment
//and that either a rising or falling edge of the signal is actualy occuring.
//It can also mean that there is currently some Electro Mechanic Interferences (EMI) occuring
//The pin is reread repetetively MYsensitivity times until the signal is confirmed stable.
//---------------------------------------------------------------------------------------------------------------
byte EdgeDebounce::debounce() {
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
byte EdgeDebounce::pressed() {
	return debounce();
}//pressed-------------------------------

//updateStatus===================================================================
//After releasing EdgeDebounceLite, I realized that EdgeDebounce could do more
//With this small piece of code, EdgeDebounce can return if a switch is
//  .isclosed();  //Conducting current
//  .isopen();    //Not conducting current
//  .rose();      //Just went from open to closed
//  .fell();      //just went from closed to open
//-------------------------------------------------------------------------------
void EdgeDebounce::update() {
  byte newStatus = debounce();
	if (MYmode == PULLUP) newStatus = !newStatus;
  if (MYstatus == OPEN && newStatus == CLOSED) MYrose = true;
  else                                         MYrose = false; 
	if (MYstatus == CLOSED && newStatus == OPEN) MYfell = true;
  else                                         MYfell = false;
	MYstatus = newStatus;
}//update-------------------------------------------------------------------------

//updatingMethods=============================================
bool EdgeDebounce::closed()  { update(); return MYstatus; }
bool EdgeDebounce::open()    { update(); return !MYstatus; }
bool EdgeDebounce::rose()    { update(); return MYrose; }
bool EdgeDebounce::fell()    { update(); return MYfell; }

//statusMethods=====================================================
bool EdgeDebounce::getClosed() const { return MYstatus; }
bool EdgeDebounce::getOpen()   const { return !MYstatus; }
bool EdgeDebounce::getRose() const { return MYrose; }
bool EdgeDebounce::getFell() const { return MYfell; }

