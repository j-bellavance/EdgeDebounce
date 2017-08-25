/*
 * Reading.ino
 * By Jacques Bellavance, July 20 2017
 * Released into the public domain
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the EdgeDebounce Library
 * Reading a switch is when you are only interested to know if it changed state.
 * This sketch will poll the switch and only report when its state has changed.
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

bool newState;
bool currentState;
String msg[2] = {"Now open", "Now closed"};

void setup() {
  button.begin();                         //Setup button
  currentState  = button.closed();        //Set current state
  Serial.begin(9600);                     //Set Serial
  Serial.println(msg[currentState]);      //print current state
}

void loop() {
  newState = button.closed();        //Read new state
  if (newState != currentState) {    //If it changed
    currentState = newState;           //Record new state
    Serial.println(msg[newState]);     //Print new state
  }  
//Do other stuff
}

