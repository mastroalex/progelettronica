#ifndef EMGsmooth 
#define EMGsmooth
// Dichiaro le funzioni che mi servono per leggere i battiti

int EMG_pin = A0;
int soglia_pin=A2;
int soglia =0; 

#include <Arduino.h>

// smoothing


const int numReadings = 50;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// threeshold controll

int averagecalc (){
  
//  emg reading and smoothing
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(EMG_pin);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
 
return average;
}

#endif
