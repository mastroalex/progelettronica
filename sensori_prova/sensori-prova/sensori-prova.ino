#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>


Servo servomotor; // inizializziamo il servo
Servo servopinza;

const int pinzapin = 3; // pin servo per la pinza


float tempmpu = 0; // temperatura MPU5060
float angle = 0;  //angolo lungo z MPU5060
int t1 = 0; // timer per la stampa dei valori
int pausa = 400 ; // pausa per il serial print
const int servopin = 9; // pin per il servo
const int angolopolso = 75; // definiamo l'angolo di massima rotazione del polso per la funzione map
const int angolorotservo = 150; // angolo di massima rotazione laterale
const int angolominservo = 3; // angolo minimo del servo
int pos = 0; // poszione servo

int bottone = 7;

MPU6050 mpu6050(Wire);

// emg


int EMG_pin = A0;


#define pinzamin 50
#define pinzamax 100

int somma = 0;
int value = 0;


// smoothing


const int numReadings = 50;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

// threeshold controll

long t3 = 0; // contator for controll cycle
long t4 = 20; // pause time for controll cycle
boolean controllo[10]; // vec for controll cycle
boolean stato; // boolean variable fro controll cycle
int i = 0;
int soglia = 150; // valore di soglia per la chiusura della pinza


void setup() {
  Serial.begin(9600);
  Wire.begin(); // avvio e inizializzo il gyro

  mpu6050.begin();
// mpu6050.calcGyroOffsets(true);
  mpu6050.setGyroOffsets(0, 0, 0);

  servopinza.attach(pinzapin); // servo pinza
  servomotor.attach(servopin); // servo sul pin servopin

  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }

  t1 = millis();
//  pinMode(bottone, INPUT);
}



void loop() {
  if (digitalRead(bottone) == HIGH) {
    mpu6050.calcGyroOffsets(true);
    Serial.print("CALC GYRO");
    delay(3000);
  }
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


  mpu6050.update();
  tempmpu = mpu6050.getTemp(); // prende la temperatura

  angle = mpu6050.getAngleZ(); // prende l'angolo lungo x

  pos = map((int)angle, -angolopolso, angolopolso, 0, 180); // mappiamo la funzione dai valori letti dall IMU nel range del servo

  if (millis() > 1000 ) { // mettiamo un blocco al motore nel mentre che IMU fa la calibrazione
    servomotor.write(pos);
  }


  if (millis() - t1 > pausa) {
    Serial.print("anglez : ");
    Serial.print(angle);
    Serial.print("\t temp : ");
    Serial.println(tempmpu);
    Serial.print("Average: ");
    Serial.print(average);
    Serial.print(", Soglia: ");
    Serial.print(soglia);
    Serial.print(", EMG: ");
    Serial.println(analogRead(EMG_pin));
    t1 = millis();
  }


  // closing or opening calmp
  if (average > soglia) {

    servopinza.write(pinzamax);// chiudo la pinza
  }
  if (millis() - t3 < t4) {
    if (average < soglia) {
      controllo[i] = LOW;
    }
    else {
      controllo[i] = HIGH;
    }
    if (i < 10) {
      i++;
    }
    t3 = millis();
  }

  for (int j = 0; j < 10; j++) {
    if (controllo[j] == LOW) {
      stato = LOW;
    }
    else {
      stato = HIGH;
    }
  }
  if (stato == LOW) {
    servopinza.write(pinzamin);// apriamo la pinza
  }

  delay(1);

}
