#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(9);
}

void loop() {
//  servo1.write(90);
     for (int i = 0; i < 180; i++) {
       servo1.write(i);
       delay(20);
     }
     delay(200);
     for (int i = 180; i >= 0; i--) {
       servo1.write(i);
       delay(20);
     }
     delay(200);
}
