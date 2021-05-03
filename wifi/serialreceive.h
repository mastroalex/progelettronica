#ifndef serialreceive
#define serialreceive

float tempmpu;
float angle;
int BPM ;
int soglia;
int average;


String valore;
char lettura[32];
String line = "";
#include <SoftwareSerial.h>
SoftwareSerial Esp_serial(D3, D4);

void analizestring(char lettura[]) {
  if (lettura[0] == 'T') {
    Serial.print("Temperatura: ");
    valore = "";
    for (int i = 1; i < 32; i++) {
      valore = valore + String(lettura[i]);
    }
    tempmpu = valore.toFloat();
    Serial.println(tempmpu);
  }
  else if (lettura[0] == 'A') {
    valore = "";
    Serial.print("Angolo: ");
    for (int i = 1; i < 32; i++) {
      valore = valore + String(lettura[i]);
    }
    angle = valore.toFloat();
    Serial.println(angle);
  }
  else if (lettura[0] == 'M') {
    Serial.print("Media: ");
    valore = "";
    for (int i = 1; i < 32; i++) {
      valore = valore + String(lettura[i]);
    }
    average = valore.toInt();
    Serial.println(average);
  }
  else if (lettura[0] == 'B') {
    Serial.print("Battito: ");
    valore = "";
    for (int i = 1; i < 32; i++) {
      valore = valore + String(lettura[i]);
    }
    BPM = valore.toInt();
    Serial.println(BPM);
  }
  else if (lettura[0] == 'S') {
          Serial.print("Soglia: ");
    valore = "";
    for (int i = 1; i < 32; i++) {
      valore = valore + String(lettura[i]);
    }
    soglia = valore.toInt();
        Serial.println(soglia);
  }
}

void process (String line) {

  // Serial.println(line);
  int str_len = line.length() + 1;
  // Prepare the character array (the buffer)
  char lettura[str_len];
  // Copy it over
  line.toCharArray(lettura, str_len);
  // Serial.println(lettura);
  analizestring(lettura);
}

void decodeserial () {
  if (Esp_serial.available() > 0) {
    char ch = Esp_serial.read();
    if ((ch == '\n') || (ch == '\r')) {
      process(line);
      line = "";
    }
    else {
      line += ch;
    }
  }
}

#endif
