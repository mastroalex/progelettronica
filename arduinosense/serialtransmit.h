#ifndef serialtransmit
#define serialtransmit

#include "funzioniBPM.h" // battiti
#include "printerfunzioni.h" // stampante
#include "EMGsmooth.h" // lettura emg

unsigned long timex ;
/*
   The circuit:
   RX is digital pin 2 (connect to TX of other device)
   TX is digital pin 3 (connect to RX of other device)

*/
String invio;

#include <SoftwareSerial.h>
SoftwareSerial mySeriale(2, 3); // RX, TX
// includere   mySeriale.begin(9600); nel setup
void trasmitt (String param, String val) {
    invio = param + String(val);
    mySeriale.println(invio);
}


#endif
