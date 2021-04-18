#ifndef printerfunzioni
#define printerfunzioni

#include "funzioniBPM.h"
#include "EMGsmooth.h"

int soglia = 500; // valore di soglia per la chiusura della pinza

float tempmpu = 0; // temperatura MPU5060
float angle = 0;  //angolo lungo z MPU5060

boolean debug; 


unsigned long t1 = 0; // timer per la stampa dei valori
unsigned long pausa = 400 ; // pausa per il serial print


// a liquid crystal displays

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


unsigned long tlcd;
byte heart[] = {
  B00000,
  B11011,
  B10101,
  B10001,
  B01010,
  B00100,
  B00100,
  B00000
};

byte rotate[] = {
  B00000,
  B11100,
  B01101,
  B10101,
  B10001,
  B10001,
  B01110,
  B00000
};

byte deg[] = {
  B00000,
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000
};
//


void lcdprint() {
  if (millis() - tlcd > 100) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.createChar(0, rotate);
    lcd.setCursor(0, 0);
    lcd.write(0);
    lcd.setCursor(1, 0);

    lcd.print (":");
    lcd.print(int(angle)); // solo cifre intere

    lcd.createChar(1, heart);

    lcd.setCursor(6, 0);
    lcd.write(1);
    lcd.print(":");
    lcd.print(BPM);
    lcd.setCursor(12, 0);
    lcd.print(int(tempmpu));
    lcd.createChar(2, deg);
    lcd.setCursor(14, 0);
     lcd.write(2);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("avrg:");
    lcd.print(average);
    lcd.setCursor(8, 1);
    lcd.print("EMG:");
    lcd.print(analogRead(EMG_pin));
    tlcd = millis();
  }
}

void printatore(boolean debug) {

  if (debug == HIGH) {
    if (millis() - t1 > 20) {

      t1 = millis();

      Serial.print(average);
      Serial.print("\t");
      Serial.print(soglia);
      Serial.print("\t");
      Serial.println(analogRead(EMG_pin));
    }
  }
  else {
    if (millis() - t1 > pausa) {

      t1 = millis();

      Serial.print("angle : ");
      Serial.print(angle);
      Serial.print("\t temp : ");
      Serial.print(tempmpu);
      Serial.print("\t Average: ");
      Serial.print(average);
      Serial.print(", Soglia: ");
      Serial.print(soglia);
      Serial.print(", EMG: ");
      Serial.print(analogRead(EMG_pin));
      Serial.print("\t BPM: ");
      Serial.println(BPM);
    }
  }
}

#endif
