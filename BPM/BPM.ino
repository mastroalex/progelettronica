#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int Pulsepin = 0;

PulseSensorPlayground pulseSensor; 

void setup() {
  Serial.begin(9600); 
  pulseSensor.analogInput(Pulsepin);
  pulseSensor.begin();
  }

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
  if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
  Serial.print("BPM: "); // Print phrase "BPM: "
  Serial.println(myBPM); // Print the value inside of myBPM.
  }
  delay(10);
 }
 
