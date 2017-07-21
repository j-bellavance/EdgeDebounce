/*
 * Polling.ino
 * By Jacques Bellavance, July 20 2017
 * Polling a switch means : At this exact time, in what position is the switch
 * Polling is realy fast compared to a human hand.
 * Even pressing and releasing the switch as fast as you can,
 * it will be polled many times.
 * 
 * This sketch will test how fast you can press and release the switch.
 * The button.close() method takes 90 microseconds if no bouncing is detected.
 * If there is some bouncing, it will take at most 180 microseconds after the bouncing stops
 * When the sketch is uploaded to the Arduino, open the serial monitor.
 * It will be displaying "Waiting..."
 * When you press and release the button, Arduino will display how many times 
 * the button was polled like this "Polled 671 times."
*/

#include <EdgeDebounce.h>

#define BUTTON_PIN 2

//Create an instance of Debounce and name it button
//button is tied to pin BUTTON_PIN and is in PULLUP mode
EdgeDebounce button(BUTTON_PIN, PULLUP);  

void setup() {
  Serial.begin(9600);
  Serial.println(F("Waiting..."));
}

void loop() {
  int count = 0;                         //Reset the count
  if (button.closed()) {                 //If the button is closed
    count = 1;                             //Count the first poll
    while (button.closed()) count += 1;    //Keep polling and counting while the switch remains closed
    Serial.print(F("Polled "));            //Report the result
    Serial.print(count);
    Serial.println(F(" times."));
    Serial.println(F("Waiting..."));       //Get ready for the next try
  }  
}

