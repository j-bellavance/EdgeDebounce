/*
 *EdgeDebounce.h 
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
 
#ifndef EdgeDebounce_h
#define EdgeDebounce_h

#include "Arduino.h"


enum pinType {PULLUP, PULLDOWN};
enum pinStatus {OPEN, CLOSED};

class EdgeDebounce
{
  public:
    //methods
    EdgeDebounce();
    EdgeDebounce(byte pin, pinType mode);  //Constructor
    void begin();                          //Perform pinMode() initialisation
    byte debounce();                       //PULLDOWN mode: ON=1, OFF=0 ; PULLUP mode ON=0, OFF=1
    byte debounce(byte pin);
    byte pin(byte pin);
    byte pressed();                        //Same as debounce(): Kept for compatibility with V1.1 
    void update();
    bool closed();
    bool open();
    bool rose();
    bool fell();
    bool getClosed() const;                //Returns true if the switch is closed
    bool getOpen() const;                  //Returns true if the switch is open
    bool getRose() const;                  //Returns true if on the rising edge of the signal (Just closed)
    bool getFell() const;                  //Returns true if on the falling edge of the signal (Just opened)
    void setSensitivity(byte w);           //Set debounce reads (1..32)
    byte getSensitivity();                 //Returns the current sensitivity of Debounce
    
  private:
    //methods
    //attributes
    byte MYpin;                                   //The switch's pin
    pinType MYmode = PULLUP;                      //The switch's mode (PULLUP or PULLDOWN)
    pinStatus MYstatus;                           //The current Status of the pin
    bool MYrose;                                  //True if the pin is rising
    bool MYfell;                                  //True if the pin is falling
    byte MYsensitivity = 16;                      //Current sensitivity (1..32)
    unsigned long debounceDontCare = 0xffff0000;  //Don't care mask
};

#endif;
