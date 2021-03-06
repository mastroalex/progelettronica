#ifndef  radiolib
#define  radiolib

#include <Arduino.h>
#include "rotation.h"
#include "servoclamp.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7, 8); //CE, CSN

const byte address[6] = "00001";
char text[32] = "";


float tempmpu ;

int BPM ;


String valore;
String valore1;
String valore2;
String valore3;
String valore4;


void myradiosetup() {
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void radionuovo() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    //    Serial.println(text);

    if (text[0] == 'T') {
      Serial.print("Temperatura: ");
      valore = "";
      for (int i = 1; i < 32; i++) {
        valore = valore + String(text[i]);
      }
      tempmpu = valore.toFloat();
      Serial.println(tempmpu);
    }
    else if (text[0] == 'A') {
      valore1 = "";
      Serial.print("Angolo: ");
      for (int i = 1; i < 32; i++) {
        valore1 = valore1 + String(text[i]);
      }
      angle = valore1.toFloat();
      Serial.println(angle);
    }
    else if (text[0] == 'M') {
      Serial.print("Average: ");
      valore2 = "";
      for (int i = 1; i < 32; i++) {
        valore2 = valore2 + String(text[i]);
      }
      average = valore2.toInt();
      Serial.println(average);
    }
    else if (text[0] == 'B') {
      Serial.print("BPM: ");
      valore3 = "";
      for (int i = 1; i < 32; i++) {
        valore3 = valore3 + String(text[i]);
      }
      BPM = valore3.toInt();
      Serial.println(BPM);
    }
    else if (text[0] == 'S') {
      Serial.print("Soglia: ");
      valore4 = "";
      for (int i = 1; i < 32; i++) {
        valore4 = valore4 + String(text[i]);
      }
      soglia = valore4.toInt();
      Serial.println(soglia);
    }
  }
}



//    switch (text[0]) {
//      case 'T':
//        Serial.print("Temperatura: ");
//         for (int i = 1; i < 32; i++) {
//          valore = valore + String(text[i]);
//        }
//        tempmpu = valore.toFloat();
//        Serial.println(tempmpu);
//        break;
//      case 'A':
//        Serial.print("Angolo: ");
//        for (int i = 1; i < 32; i++) {
//          valore1 = valore1 + String(text[i]);
//        }
//        angle = valore1.toFloat();
//        Serial.println(angle);
//        break;
//      case 'M':
//        Serial.print("Average: ");
//        for (int i = 1; i < 32; i++) {
//          valore2 = valore2 + String(text[i]);
//        }
//        average = valore2.toFloat();
//        Serial.println(average);
//        break;
//    }




#endif
