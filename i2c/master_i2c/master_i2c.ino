#include <Wire.h>
const int ledPin = 13; 
int ledState; 
void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  Wire.requestFrom(2, 1);    // request 6 bytes from slave device #2

  while(Wire.available())    // slave may send less than requested
  { 
    int c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
    ledState=c;
    
  }

  //delay(500);
  Serial.println();
  digitalWrite(ledPin, ledState);
  
}
