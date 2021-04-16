#include <OneWire.h>
#include <DallasTemperature.h>


OneWire oneWire(sensor_bus_pin);         //definiamo l'oggetto che serve per gestire la comunicazione (pin 5)                                       
DallasTemperature temp(&oneWire);         //passiamo il canale di comunicazione alla libreria Dallas

//la temperatura la scriviamo in una variabile di tipo float

float tc    //temperatura in gradi

void setup(); {
  Serial.begin(9600);
  temp.begin();            //inizializziamo la temperatura (inizializziamo la comunicazione)
}

void loop(); {
  temp.requestTemperatures();   //invio comando per leggere temperatura

//per estrarre le temperature scriviamo

  tc = temp.getTempCByIndex(0);           //ci restituisce la temmperatura in celsius  
  Serial.print(tc);
  Serial.println(" C ");                   // \t per fare la tabulazione
  delay(1000);
}         
