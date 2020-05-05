#include <Wire.h>
const int buttonPin = 2;    
const int ledPin = 13; 
int ledState = HIGH;         
int buttonState;            
int lastButtonState = LOW;  
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 10;

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);
}

void loop()
{
  //delay(100);
  button_press();
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  button_press();
  Wire.write(ledState); // respond with message of 6 bytes
                       // as expected by master
}

void button_press() {
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  
  // set the LED:
  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}
