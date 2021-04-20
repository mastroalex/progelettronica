#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7, 8); //CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

float tempmpu = 25.5 ;
float angle = 90;
int average = 300;
int BPM = 70;
int soglia = 200;

String pacchetto;


void loop() {
  charfortransmission("T", String(tempmpu));
  charfortransmission("A", String(angle));
  charfortransmission("M", String(average));
  charfortransmission("B", String(BPM));
  charfortransmission("S", String(soglia));
  delay(1000);
}

void charfortransmission(String param, String val) {
  pacchetto = param + String(val);
  Serial.println(pacchetto);
  int str_len = pacchetto.length() + 1;
  char pacchettoinvio[str_len];
  pacchetto.toCharArray(pacchettoinvio, str_len);
  radio.write(&pacchettoinvio, sizeof(pacchettoinvio));
  delay(500);
}
