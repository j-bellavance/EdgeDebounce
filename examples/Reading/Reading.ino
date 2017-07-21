/*
 * Reading.ino
 * By Jacques Bellavance, July 20 2017
 * Reading a switch is when you are only interested to know
 * if it changed state.
 * This sketch will poll the switch and only report when its state has changed.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

bool newState;
bool currentState = button.closed();
String msg[2] = {"Now open", "Now closed"};

void setup() {
  Serial.begin(9600);
  Serial.println(msg[0]);
}

void loop() {
  newState = button.closed();
  if (newState != currentState) {
    currentState = newState;
    Serial.println(msg[newState]);
  }  
//Do other stuff
}

