/*
 * ShortAndLong.ino
 * By Jacques Bellavance, July 20 2017
 * At times, you may want to have the switch to do different things
 * if the swich is pressed for a short time or
 * if it is pressed for a long time.
 * In order to do this, we have to detect two events:
 * - The moment that the switch's state changes from open to closed
 *   At this point we need to reset the chronometer and 
 *   remember that the switch has been closed
 * - The moment that the switch's state changes from closed to open
 *   At this point, we can determine how long the switch has been pressed
 *   and take the appropriate action. (Printing "Short" or "Long")
 *   We need also to remember that the switch is now open
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

unsigned long chrono = millis(); //Set chronometer
unsigned long limit = 2000;      //milliseconds (2 seconds)
bool isClosed = button.closed(); //Current state of button

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (!isClosed && button.closed())  {                             //Just closed?
    chrono = millis();                                              //Reset Chrono
    isClosed = true;                                                //button is now closed
    }  
  if (isClosed && !button.closed()) {                             //Just opened?
    if (millis() - chrono < limit) Serial.println(F("Short"));      //If lower than limit print "Short"
    else                           Serial.println(F("Long"));       //otherwise print "Long"
    isClosed = false;                                               //button is now open
  }
  //Do other stuff
}
