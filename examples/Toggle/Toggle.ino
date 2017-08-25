/*
 * Toggle.ino
 * By Jacques Bellavance, July 20 2017
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the EdgeDebounce Library 
 * Transform a momentary button switch into an on/off switch
 * Pressing (and releasing the button) makes the switchState variable
 * go from on to off and vice versa.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 4
#define LED_PIN 13

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

bool switchState;

void setup() {
  button.begin();                   //Set up button
  pinMode(LED_PIN, OUTPUT);         //Set up LED pin
  switchState = button.closed();    //Set up state to current pin state
}

void loop() {
  button.update();
  if (button.fell()) {            //If the button clicked (rose and then fell)
    switchState = !switchState;   //Toggle state
  }
  digitalWrite(LED_PIN, switchState);
  //Do other stuff
}

