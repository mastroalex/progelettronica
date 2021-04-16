#include <Servo.h>

#define THRESHOLD 70
#define EMG_pin 0
#define Servopin 6
Servo servo1;
int pos = 90;


void setup() {
 Serial.begin(9600);
 servo1.attach(Servopin);

}

void loop() {
   int value = analogRead(EMG_pin);
   if ( value > THRESHOLD) {
    servo1.write(90);
   }
   else {
    servo1.write(10);
   }
   Serial.println(value);
   delay(500);
}
