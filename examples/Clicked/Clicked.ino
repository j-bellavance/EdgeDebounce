/*
 * Clicked.ino
 * By Jacques Bellavance, July 20 2017
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the EdgeDebounce Library 
 * As seen in the Polling.ino Sketch, the human hand is a lot slower than Arduino
 * To help the user, we will wait for the switch to be re-opened before
 * carrying out the action.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 4

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  


void setup() {
  button.begin();
  Serial.begin(9600);
}

void loop() {
  if(button.fell()) {                     //If the switch closed and re-opened
    Serial.println(F("Was pressed"));         //Do the action
  }  
  //Do other stuff
}

