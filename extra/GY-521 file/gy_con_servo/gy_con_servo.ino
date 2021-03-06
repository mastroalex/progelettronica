#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>

Servo servomotor; // inizializziamo il servo


float tempmpu = 0; // temperatura MPU5060
float angle = 0;  //angolo lungo x MPU5060
int t1 = 0; // timer per la stampa dei valori
int pausa = 400 ; // pausa per il serial print
const int servopin = 9; // pin per il servo
const int angolopolso = 75; // definiamo l'angolo di massima rotazione del polso per la funzione map
int pos = 0; // poszione servo

MPU6050 mpu6050(Wire);

void setup() {

  Serial.begin(9600);

  servomotor.attach(servopin); // servo sul pin servopin

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  t1 = millis();
}

void loop() {
  mpu6050.update();
  tempmpu = mpu6050.getTemp(); // prende la temperatura
  angle = mpu6050.getAngleZ(); // prende l'angolo lungo x
  pos = map((int)angle, -angolopolso, angolopolso, 0, 180); // mappiamo la funzione dai valori letti dall IMU nel range del servo
  if (millis() > 3000 ) { // mettiamo un blocco al motore nel mentre che IMU fa la calibrazione
    servomotor.write(pos);
  }
  if (millis() - t1 > pausa) {
    Serial.print("anglez : ");
    Serial.print(angle);
    Serial.print("\t temp : ");
    Serial.println(tempmpu);
  }
  t1 = millis();
}
