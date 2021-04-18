#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7,8);  //CE, CSN
const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
  
}

void loop() {
  const char text0[] = "tempmpu = 25.5";
  radio.write(&text0, sizeof(text0));
  const char text1[] = "angle = 90";
  radio.write(&text1, sizeof(text1));
  const char text2[] = "average = 300";
  radio.write(&text2, sizeof(text2));
  const char text3[] = "BPM = 70";
  delay(500);
  radio.write(&text3, sizeof(text3));
  const char text4[] = "soglia = 250";
  radio.write(&text4, sizeof(text4));
  delay(1000);
}
