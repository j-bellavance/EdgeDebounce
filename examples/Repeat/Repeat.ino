/*
 * Repeat.ino
 * By Jacques Bellavance, July 20 2017
 * Sometimes we want to use the switch just like
 * the keys on the keyboard.
 * When we press the key, the character is sent to the computer.
 * If we keep the key pressed until a predetermidened time, it will send repeatedly the same key
 * over and over at a specific rate until we release the key.
 * To implement this, we will need two chronometers to check the two delays
 * - startTime (After which delay do we start sending repeats)
 * - burstTime (At which rate do we send repeats)
 * The button can take two states (open or closed)
 * That means that we can be confronted to 4 state changes:
 * - Open to open     (Do nothing)
 * - Open to closed   (Send a char & reset chrono)
 * - Closed to open   (Stop sending chars & clean-up)
 * - Closed to closed 
 *   - If not in burst mode (Do nothing)
 *   - If in burst mode     (Send a char at a specific rate)
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

unsigned long startTime = 1000;       //milliseconds (1 second)
unsigned long burstTime = 100;        //milliseconds (1/10th of a second)
unsigned long chronoStart = millis(); //Set chronometer
unsigned long chronoBurst = millis(); //Set chronometer
bool isClosed = button.closed();      //Current state of button
bool burstMode = false;               //Are we in burst mode right now

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (!isClosed && button.closed())  {  //Just closed?
    isClosed = true;                      //button is now closed
    chronoStart = millis();               //Reset Chrono
    Serial.print(F("A"));                 //Send character
    }
  if (isClosed && !button.closed()) {   //Just opened?
    Serial.println();                     //Not needed. Just separates the sequences on the monitor
    isClosed = false;                     //button is now open
    burstMode = false;                    //Deactivate burstMode
  }
  if (isClosed && millis() - chronoStart >= startTime) {      //Still closed && passed repeat start time?
    if (!burstMode) {                                           //If not in burst mode yet
      burstMode = true;                                           //Activate burst mode
      chronoBurst = millis() + burstTime + 1;                     //Set burst chrono passed burst time
    }
    if (burstMode && millis() - chronoBurst >= burstTime) {     //If passed burst time
      Serial.print(F("A"));                                       //Send character
      chronoBurst = millis();                                     //Reset burst chrono
    }   
  }
  //Do other stuff
}
