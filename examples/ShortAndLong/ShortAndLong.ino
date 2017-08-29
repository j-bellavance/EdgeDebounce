/*
 * ShortAndLong.ino
 * By Jacques Bellavance, July 20 2017
 * GNU GENERAL PUBLIC LICENSE V3
 *
 * Shows how to use the EdgeDebounce Library 
 * At times, you may want to do different things
 * if the swich is pressed for a short time or
 * if it is pressed for a long time.
 * In order to do this, we have to detect two events:
 * - The moment that the switch's state changes from open to closed
 *   At this point we need to reset the chronometer and 
 * - The moment that the switch's state changes from closed to open
 *   At this point, we can determine how long the switch has been pressed
 *   and take the appropriate action. (Printing "Short" or "Long")
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 4
#define LED_PIN 13

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

unsigned long chrono;         //Set chronometer
unsigned long limit = 500;   //milliseconds (2 seconds)

void setup() {
  button.begin();
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  button.update();
  if (button.getRose())  {                //Just closed?
    chrono = millis();                   //Reset Chrono
  }  
  if (button.getFell()) {                 //Just opened?
    if (millis() - chrono < limit)       //If lower than limit
      Serial.println(F("Short"));          //print "Short"
    else                                 //Otherwise
      Serial.println(F("Long"));           //print "Long"
  }
  //Do other stuff
}
