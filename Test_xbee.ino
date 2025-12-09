#include <SoftwareSerial.h>          // Include SoftwareSerial library for communication

SoftwareSerial XBee(10, 11);         // Define SoftwareSerial pins: DOUT = 10, DIN = 11

void setup() {
  Serial.begin(9600);                // Start communication with the PC for debugging
  XBee.begin(115200);                  // Start communication with the XBee module

  randomSeed(analogRead(0));         // Seed the random number generator for varied results
}

void loop() {
  //int randomNumber = random(100);    // Generate a random number between 0 and 255
  for (int i=0; i<101; i++){
  XBee.print(i);          // Send the randomly generated number
  XBee.print("\n");                 

  Serial.print("Sent number: ");     // Debugging output to Serial Monitor
  Serial.println(i);

  delay(1000);                     // Delay between sends to avoid flooding
  }
}
