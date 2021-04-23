#ifndef servoclamp
#define servoclamp

#include <Servo.h>

#include "rotation.h"

Servo servopinza;

const int pinzapin = 3; // pin servo per la pinza

int soglia ;
int average;
boolean controllo[10]; // vec for controll cycle
boolean stato; // boolean variable fro controll cycle
int i=0;

unsigned long t3 = 0; // contator for controll cycle
unsigned long t4 = 20; // pause time for controll cycle

#define pinzamin 80
#define pinzamax 110

void pinzacontrol (int soglia){
   // closing or opening calmp
  if (average > soglia) {

    servopinza.write(pinzamax);// chiudo la pinza
  }
  if (millis() - t3 > t4) {
    if (average < soglia) {
      controllo[i] = LOW;
    }
    else {
      controllo[i] = HIGH;
    }
    if (i < 10) {
      i++;
    }
    t3 = millis();
  }

  for (int j = 0; j < 10; j++) {
    if (controllo[j] == LOW) {
      stato = LOW;
    }
    else {
      stato = HIGH;
    }
  }
  if (stato == LOW) {
    servopinza.write(pinzamin);// apriamo la pinza
  }
  }

  
void pinzacontrol2 (int angolo_pinza){
   // closing or opening calmp
  int angolo_pinza_map=map(angolo_pinza,0,180,pinzamin, pinzamax);

    servopinza.write(angolo_pinza_map);// chiudo la pinza
  }
  

#endif
