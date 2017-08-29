/*
 * TestButton.ino
 * By Jacques Bellavance, August 23, 2017
 *Released into the public domain
 *GNU GENERAL PUBLIC LICENSE V3
 * 
 * To test what Sensitivity is best for a particular switch / application
 * Debug LED on pin 13 will light up when TEST_BUTTON is pressed
 * Pressing the MORE button will increase the sensitivity
 * Pressing the LESS button will decrease the sensitivity
 * The serial monitor will display the current sensitivity
 * Uses the internal pullup resistors
 * Arduino pin 2 --- LESS button ---+---GND
 * Arduino pin 3 --- TEST button ---|
 * Arduino pin 4 --- MORE button ---|
*/

#include <EdgeDebounce.h>

#define LESS_PIN 2      //decrease sensititivity
#define TEST_PIN 3      //Fires the test LED on pin 13 when pressed
#define MORE_PIN 4      //increase sensititivity
#define LED_PIN 13      //Debug led on pin 13

EdgeDebounce less(LESS_PIN, PULLUP);  
EdgeDebounce test(TEST_PIN, PULLUP);  
EdgeDebounce more(MORE_PIN, PULLUP);  

void setup() {
  less.begin();
  test.begin();
  more.begin();
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial.println(F("Begining testing..."));
  Serial.print(F("Sensitivity is now at: "));
  Serial.println(test.getSensitivity());
  Serial.println(F("---------------------------"));
}

void loop() {
  if (more.fell()) {
    test.setSensitivity(test.getSensitivity() + 1);
    Serial.print(F("Sensitivity is now at: "));
    Serial.println(test.getSensitivity());
  }
  if (less.fell()) {
    test.setSensitivity(test.getSensitivity() - 1);
    Serial.print(F("Sensitivity is now at: "));
    Serial.println(test.getSensitivity());
  }
  //Place your test code here, using the test button
  if (test.closed()) digitalWrite(LED_PIN, HIGH); 
  else               digitalWrite(LED_PIN, LOW); 
}

