/*
 * Basic.ino
 * By Jacques Bellavance, July 7 2017
 * Shows how to use the Debounce Library
 * This sketch is for switches that uses the internal pullup resistor
 * Switch pin A : Ground
 * Switch pin B : Arduino's pin 2
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

void setup() {
  //Nothing to do here. The Library has declared pinMode(BUTTON_PIN, INPUT_PILLUP) for you
}

void loop() {
  if (button.closed()) digitalWrite(13, HIGH);  //The .closed method returns true if there is contact
  else                 digitalWrite(13, LOW);
}

