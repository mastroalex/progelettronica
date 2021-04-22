#ifndef  btserial
#define  btserial
#include "rotation.h"
#include "servoclamp.h"

#include <SoftwareSerial.h>

int rxPin = 3;
int txPin = 2;
SoftwareSerial bluetooth(rxPin, txPin);

String message; //string that stores the incoming message

unsigned long t7 = 0;

void bt() {

  while (bluetooth.available()) {
    message += char(bluetooth.read());
  }
  if (millis()-t7<1000) {
    if (!bluetooth.available()) {
      if (message != "") { //if data is available
        Serial.println(message); //show the data
        message = ""; //clear the data
      }
    }
      bluetooth.print(soglia);
    t7=millis();
  }
}

#endif
