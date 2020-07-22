/*                                                                                                                                     
 * DigiPot.pde - Example sketch for Arduino library for managing digital potentiometers X9C1xxx (xxx = 102,103,104,503).
 * By Timo Fager, Jul 29, 2011.                                                                                                        
 * Released to public domain.                                                                                                          
 *
 * For this example, connect your X9C103P (or the like) as follows:
 * 1 - INC - Arduino pin 3
 * 2 - U/D - Arduino pin 2
 * 3 - VH  - 5V
 * 4 - VSS - GND
 * 5 - VW  - Output: 150 Ohm resistor -> LED -> GND
 * 6 - VL  - GND
 * 7 - CS  - Arduino pin 4
 * 8 - VCC - 5V
 *
 **/


#include <DigiPotX9Cxxx.h>

DigiPot pot(3,2,4);
String inString = "";    // string to hold input

void setup() {
  Serial.begin(9600);
  pot.reset();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // send an intro:
  Serial.println(pot.get());
  Serial.println("\n\nString toInt():");
  Serial.println();
}

void loop(){
  inscom();

}

void inscom() {
  // Read serial input:
  while (Serial.available() > 0) {
    int wew;
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      wew=inString.toInt();
      pot.set(wew);
      Serial.println(pot.get());
      // clear the string for new input:
      inString = "";
    }
  }
}
