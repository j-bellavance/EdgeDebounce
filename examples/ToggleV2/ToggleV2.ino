/*
 * ToggleV2.ino
 * By Jacques Bellavance, July 20 2017
 * Transform a momentary button switch into an on/off switch
 * Pressing (and releasing the button) makes the switchState variable
 * go from on to off and vice versa.
 * Another flag (stateChanged) will allow us to take an action only if the state changed
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2
#define LED_PIN 13
#define IS_ON true
#define IS_OFF false

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

bool switchState;
bool stateChanged;

void setup() {
  pinMode(LED_PIN, OUTPUT);  
}

void loop() {
  if (button.closed()) {            //If the button is closed
    while (button.closed()) {;}       //Wait for it to be released
    switchState = !switchState;       //Toggle state
    stateChanged = true;              //Rise the flag
  }
  if (stateChanged) {                                        //If the state changed
    switch (switchState) {                                     //According to its actual state
      case IS_ON: { digitalWrite(LED_PIN, HIGH); break; }      //Action 1
      case IS_OFF: { digitalWrite(LED_PIN, LOW); break; }      //Action 2
    }
    stateChanged = false;                                    //We took care of the change of state 
  }
  //Do other stuff
}

