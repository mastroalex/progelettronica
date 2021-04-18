#ifndef radioRF 
#define radioRF

#include "funzioniBPM.h" // battiti
#include "printerfunzioni.h" // stampante
#include "EMGsmooth.h" // lettura emg

#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001";
String pacchetto;

void charfortransmission(String param, String val) {
  pacchetto = param + String(val);
  // Serial.println(pacchetto); //only for debug
  int str_len = pacchetto.length() + 1;
  char pacchettoinvio[str_len];
  pacchetto.toCharArray(pacchettoinvio, str_len);
  radio.write(&pacchettoinvio, sizeof(pacchettoinvio));
  delay(50);
}
#endif
