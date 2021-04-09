#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int Pulsepin = 0; 

PulseSensorPlayground pulseSensor; 

void setup() {
  Serial.begin(9600); 
  pulseSensor.analogInput(Pulsepin);
 
 
// Double-check the "pulseSensor" object was created and "began" seeing a signal.
  if (pulseSensor.begin()) {
  Serial.println("We created a pulseSensor Object !"); //This prints one time at Arduino power-up, or on Arduino reset.
   }
}

void loop() {
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".

  if (pulseSensor.sawStartOfBeat()) { // Constantly test to see if "a beat happened".
  Serial.println("♥ A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
  Serial.print("BPM: "); // Print phrase "BPM: "
  Serial.println(myBPM); // Print the value inside of myBPM.
  }
  delay(20); // considered best practice in a simple sketch.
}
