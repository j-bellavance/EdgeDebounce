/*
 * Repeat.ino
 * By Jacques Bellavance, July 20 2017
 * Released into the public domain
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the EdgeDebounce Library
 * Sometimes we want to use the switch just like the keys on the keyboard.
 * When we press the key, the character is sent to the computer.
 * If we keep the key pressed until a predetermidened time, it will send repeatedly the same key
 * over and over at a specific rate until we release the key.
 * 
 * We will use another switch to simulate the enter key.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2
#define ENTER_PIN 3

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);
EdgeDebounce enter(ENTER_PIN, PULLUP);

unsigned long start = 1000;     //milliseconds (1 second)
unsigned long burst = 100;      //milliseconds (1/10th of a second)
unsigned long chrono;           //Set chronometer

void setup() {
  button.begin();
  enter.begin();
  Serial.begin(9600);
}

//repeatRequired===============================================================================
bool repeatRequired() {
  button.update();
  if (button.rose()) {                             //If the switch was just closed
     chrono = millis() + start;                      //Set chronometer to when the bursts should start
     return true;                                    //And return "Required"
  }
  if (button.isClosed() && millis() >= chrono) {   //If time is up
    chrono = millis() + burst;                       //Reset chronometer for next burst
    return true;                                     //And return "Required"
  }
  return false;
}//repeatRequired------------------------------------------------------------------------------

void loop() {
  if (repeatRequired()) Serial.print('A');
  enter.update();
  if (enter.fell()) Serial.println();
  
  //Do other stuff
}
