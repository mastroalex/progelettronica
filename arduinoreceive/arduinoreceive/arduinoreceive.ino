#include "rotation.h"
#include "servoclamp.h"
#include "radiolib.h"
 #include "serialdecode.h"

#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>

//#include "btserial.h"


void setup() {
  Serial.begin(9600);
  myradiosetup();
  servomotor.attach(servopin); // servo sul pin servopin
  servopinza.attach(pinzapin);
}

void loop() {
//radionuovo(); // riceve tutte le informazioni dal nRF24L01 le stampa per lettura
  radioperbt(); // stampa codificate
  if(controlloapp==0){
  pos_servo(angle);
   pinzacontrol(soglia);
  }
  if(controlloapp==1){
      pos_servo(90);
   pinzacontrol(500);
    }
  decodeserial();
 
  delay(1);
}
