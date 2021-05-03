#ifndef dhtread
#define dhtread

#include "DHT.h"
#define DHTTYPE DHT11   // DHT 11
const int DHTPin = D5;
DHT dht(DHTPin, DHTTYPE);
float h;
float t;
unsigned long timea=0;

void letturadht() {
   if (millis() - timea > 500) {
    h = dht.readHumidity();
    t = dht.readTemperature();
    Serial.println(h);
    Serial.println(t);
  timea=millis();
   }
}
#endif
