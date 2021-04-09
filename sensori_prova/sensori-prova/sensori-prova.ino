#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>


Servo servomotor; // inizializziamo il servo
Servo servopinza;

const int pinzapin = 5; // pin servo per la pinza


float tempmpu = 0; // temperatura MPU5060
float angle = 0;  //angolo lungo z MPU5060
int t1 = 0; // timer per la stampa dei valori
int pausa = 400 ; // pausa per il serial print
const int servopin = 9; // pin per il servo
const int angolopolso = 75; // definiamo l'angolo di massima rotazione del polso per la funzione map
const int angolorotservo = 150; // angolo di massima rotazione laterale
const int angolominservo = 3; // angolo minimo del servo
int pos = 0; // poszione servo

MPU6050 mpu6050(Wire);

// emg

#define THRESHOLD 550
#define THRESHOLDMIN 200
#define EMG_pin 0


#define pinzamin 50
#define pinzamax 110

int somma = 0;
int value = 0;

void setup() {

  Serial.begin(9600);
  servopinza.attach(pinzapin); // servo pinza
  servomotor.attach(servopin); // servo sul pin servopin

  Wire.begin(); // avvio e inizializzo il gyro
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  t1 = millis();

}


int sommavec[100];

void loop() {

  mpu6050.update();
  tempmpu = mpu6050.getTemp(); // prende la temperatura

  angle = mpu6050.getAngleZ(); // prende l'angolo lungo x

  pos = map((int)angle, -angolopolso, angolopolso, 0, 180); // mappiamo la funzione dai valori letti dall IMU nel range del servo

  if (millis() > 3000 ) { // mettiamo un blocco al motore nel mentre che IMU fa la calibrazione
    servomotor.write(pos);
  }

  //  emg
  // int value = analogRead(EMG_pin);
  for(int i = 0; i < 100; i++){
    sommavec[i]=analogRead(EMG_pin);
    }
  somma = 0;
  for (int i = 0; i < 100; i++) {
    somma = somma + sommavec[i];
  }
  value = somma / 100;

  if ( value > THRESHOLD) {
    servopinza.write(pinzamax);
  }
  else if (value < THRESHOLD ) {
    servopinza.write(pinzamin);
  }



  if (millis() - t1 > pausa) {
    Serial.print("anglez : ");
    Serial.print(angle);
    Serial.print("\t temp : ");
    Serial.println(tempmpu);
    Serial.print("Value = ");
    Serial.println(value);
    Serial.print("Somma = ");
    Serial.println(somma);
    Serial.print("Emg= ");
    Serial.println(analogRead(EMG_pin));

  }
  t1 = millis();
}
