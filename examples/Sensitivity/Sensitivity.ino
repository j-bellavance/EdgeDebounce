/*
 * Sensitivity.ino
 * By Jacques Bellavance, July 7 2017
 * Released into the public domain
 * GNU GENERAL PUBLIC LICENSE V3
 * 
 * Shows how to change the sensitivity of the EdgeDebounce Library
 * This sketch is for switches that uses the internal pullup resistor
 * Switch pin A : Ground
 * Switch pin B : Arduino's pin 2
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2
#define LED_PIN 13

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

void setup() {
  button.begin();
  button.setSensitivity(8); //sensitivity defaults to 16. Now changed to 8
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (button.closed()) digitalWrite(13, HIGH);  //The .closed method returns true if there is a contact
  else                 digitalWrite(13, LOW);
}

