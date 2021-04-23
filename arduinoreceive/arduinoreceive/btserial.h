#ifndef  btserial
#define  btserial
#include "rotation.h"
#include "servoclamp.h"

#include <SoftwareSerial.h>

int rxPin = 6;
int txPin = 5;
SoftwareSerial bluetooth(rxPin, txPin);

String message; //string that stores the incoming message

unsigned long t7 = 0;

void bt() {
  if (millis() - t7 > 1000) {
//    while (bluetooth.available()) {
//      message += char(bluetooth.read());
//    }
//
//    if (!bluetooth.available()) {
//      if (message != "") { //if data is available
//        Serial.println(message); //show the data
//        message = ""; //clear the data
//      }
//    }
        bluetooth.println(soglia);
    t7 = millis();
  }
}

#endif
