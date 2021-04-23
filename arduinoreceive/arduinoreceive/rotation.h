#ifndef rotation
#define rotation

#include <Servo.h>

#include "servoclamp.h"

Servo servomotor; // inizializziamo il servo
const int servopin = 9; // pin per il servo
float angle;
int pos = 0;
const int angolopolso = 75; // definiamo l'angolo di massima rotazione del polso per la funzione map


void pos_servo(float angle) {
  int pos = map((int)angle, -angolopolso, angolopolso, 0, 180); // mappiamo la funzione dai valori letti dall IMU nel range del servo
  if (millis() > 1000 ) { // mettiamo un blocco al motore nel mentre che IMU fa la calibrazione
    servomotor.write(pos);
  }

}

void pos_servo2(int angle) {
  int pos = map((int)angle, -angolopolso, angolopolso, 0, 180); // mappiamo la funzione dai valori letti dall IMU nel range del servo
  if (millis() > 1000 ) { // mettiamo un blocco al motore nel mentre che IMU fa la calibrazione
    servomotor.write(pos);
  }

}
#endif
