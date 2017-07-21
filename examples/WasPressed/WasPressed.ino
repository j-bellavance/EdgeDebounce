/*
 * Reading.ino
 * By Jacques Bellavance, July 20 2017
 * As seen in the Polling.ino Sketch, the human hand is a lot slower than Arduino
 * To help the user, we will wait for the switch to be re-opened before
 * carrying out the action.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  


void setup() {
  Serial.begin(9600);
}

void loop() {
  if(button.closed()) {                     //If the switch is closed
    while (button.closed()) {;}               //Wait until it is re-opened
    Serial.println(F("Was pressed"));         //Do the action
  }  
  //Do other stuff
}

