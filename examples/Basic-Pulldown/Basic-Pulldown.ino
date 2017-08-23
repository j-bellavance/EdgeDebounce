/*
 * Basic-Pulldowwn.ino
 * By Jacques Bellavance, July 7 2017
 * Released into the public domain
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the Debounce Library
 * This sketch is for switches that uses an external pulldown resistor
 * Switch pin A : Vcc
 * Switch pin B : Arduino's pin 2
 * Switch pin B : 10Kohm resistor tied to Ground
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 6

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLDOWN mode
EdgeDebounce button(BUTTON_PIN, PULLDOWN);  

void setup() {
  button.begin();        //button's pinMode()
  pinMode(13, OUTPUT);   //LED's pinMode()
}

//Debug LED on pin 13 will light up when the button is pressed
void loop() {
  if (button.closed()) digitalWrite(13, HIGH);  //The .closed method returns true if there is a contact
  else                 digitalWrite(13, LOW);
}

