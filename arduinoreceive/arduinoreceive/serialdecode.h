#ifndef serialdecode
#define serialdecode
#include "rotation.h"
#include "servoclamp.h"
#include "radiolib.h"

String testoletto;
boolean controlloapp = 0;
boolean excontrolloapp;
boolean stampacontrollo = 0;

char testolettovec[32];
String testoval = "";
int angolo_pinza;
int angolo_rot;

void decodeserial() { // andiamo a decodificare quanto arriva dal seriale
  if (Serial.available() > 0) {
    testoletto = Serial.readString();
    testoletto.trim();
    Serial.println(testoletto);
  }
  if (testoletto == "C0") {
    controlloapp = 0;
    stampacontrollo = 1;
  }

  if (testoletto == "C1") {
    controlloapp = 1;
    stampacontrollo = 1;
  }

  int str_len = testoletto.length() + 1;
  testoletto.toCharArray(testolettovec, str_len);

  if (testolettovec[0] == 'P') {
    testoval = "";
    for (int i = 1; i < 32; i++) {

      testoval = testoval + String(testolettovec[i]);
    }
    angolo_pinza = testoval.toInt();
    //Serial.println(angolo_pinza);
  }

if (testolettovec[0] == 'R') {
    testoval = "";
    for (int i = 1; i < 32; i++) {

      testoval = testoval + String(testolettovec[i]);
    }
    angolo_rot = testoval.toInt();
  }
}


void radioperbt() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    //    Serial.println(text);

    if (text[0] == 'T') {
      Serial.print("T");
      valore = "";
      for (int i = 1; i < 32; i++) {
        valore = valore + String(text[i]);
      }
      tempmpu = valore.toFloat();
      Serial.println(tempmpu);
    }
    else if (text[0] == 'A') {
      valore1 = "";
      Serial.print("A");
      for (int i = 1; i < 32; i++) {
        valore1 = valore1 + String(text[i]);
      }
      angle = valore1.toFloat();
      Serial.println(angle);
    }
    else if (text[0] == 'M') {
      Serial.print("M");
      valore2 = "";
      for (int i = 1; i < 32; i++) {
        valore2 = valore2 + String(text[i]);
      }
      average = valore2.toInt();
      Serial.println(average);
    }
    else if (text[0] == 'B') {
      Serial.print("B");
      valore3 = "";
      for (int i = 1; i < 32; i++) {
        valore3 = valore3 + String(text[i]);
      }
      BPM = valore3.toInt();
      Serial.println(BPM);
    }
    else if (text[0] == 'S') {
      //      Serial.print("S");
      valore4 = "";
      for (int i = 1; i < 32; i++) {
        valore4 = valore4 + String(text[i]);
      }
      soglia = valore4.toInt();
      //      Serial.println(soglia);
    }
    if (stampacontrollo == '1') {
      Serial.print("C");
      Serial.println(controlloapp);
      !stampacontrollo;
    }
  }

}


#endif
