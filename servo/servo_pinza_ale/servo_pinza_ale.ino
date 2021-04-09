#include <Servo.h>

Servo servo1;

void setup() {
  servo1.attach(5);
}

//void loop() {
////    servo1.write(90);
//  for (int i = 50; i < 110; i++) {
//    servo1.write(i);
//    delay(10);
//  }
//  delay(200);
//  for (int i = 110; i >= 50; i--) {
//    servo1.write(i);
//    delay(10);
//  }
//  delay(200);
//}
void loop() {
  servopinza();
}

void servopinza() {
  for (int i = 50; i < 110; i++) {
    servo1.write(i);
    delay(10);
  }
  delay(200);
  for (int i = 110; i >= 50; i--) {
    servo1.write(i);
    delay(10);
  }
}
