#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

RF24 radio(7,8);  //CE, CSN
const byte address[6] = "00001";
int i;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

}

void loop() {
  if (radio.available()) {
    for(i = 0; i < 5; i++){
     char texti[32] = "";
     radio.read(&texti, sizeof(texti));
     Serial.println(texti); 
    }
  }
}
