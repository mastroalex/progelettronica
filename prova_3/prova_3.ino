#define USE_ARDUINO_INTERRUPTS true
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Servo.h>
#include <PulseSensorPlayground.h>

MPU6050 mpu6050(Wire);
Servo servomotor; // inizializziamo il servo
Servo servoclamp;
PulseSensorPlayground pulseSensor; 

float tempmpu = 0; // temperatura MPU5060
float angle = 0;  //angolo lungo z MPU5060
int t1 = 0; // timer per la stampa dei valori
int pausa = 400 ; // pausa per il serial print
const int servopin = 9; // pin per il servo
const int pinzapin = 3; // pin servo per la pinza
const int angolopolso = 75; // definiamo l'angolo di massima rotazione del polso per la funzione map
const int angolorotservo = 150; // angolo di massima rotazione laterale
const int angolominservo = 3; // angolo minimo del servo
int pos = 0; // posizione servo


// emg    

#define EMG_pin 0
#define pinzamin 50
#define pinzamax 110

long t3 = 0;
long t4 = 20;
const int numReadings = 50;
boolean controllo[10];
boolean stato;
int i = 0;
int soglia = 100;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
const int Pulsepin = 1; 
int Signal;



void setup() {

  Serial.begin(9600);
  Wire.begin(); // avvio e inizializzo il gyro
  
  servoclamp.attach(pinzapin); // servo pinza
  servomotor.attach(servopin); // servo sul pin servopin
  
  pulseSensor.analogInput(Pulsepin);
  pulseSensor.begin();
  
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
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
  
  int myBPM = pulseSensor.getBeatsPerMinute(); // Calls function on our pulseSensor object that returns BPM as an "int".
  pulseSensor.sawStartOfBeat(); // Constantly test to see if "a beat happened".
  
  total = total - readings[readIndex];      // subtract the last reading
  readings[readIndex] = analogRead(EMG_pin);    // read from the sensor
  total = total + readings[readIndex];       // add the reading to the total:
  readIndex = readIndex + 1;                // advance to the next position in the array:

  if (readIndex >= numReadings) {        // if we're at the end of the array
     readIndex = 0;                      // wrap around to the beginning:
  }
  
  average = total / numReadings;         // calculate the average
  
  if (millis() - t1 > pausa) {
    Serial.print("anglez : ");
    Serial.print(angle);
    Serial.print("\t temp : ");
    Serial.println(tempmpu);
    Serial.print("BPM: "); // Print phrase "BPM: "
    Serial.println(myBPM); // Print the value inside of myBPM.
    Serial.print(average);
    Serial.print("\t");
    Serial.print(soglia);
    Serial.print("\t");
    Serial.println(analogRead(EMG_pin));
    t1 = millis();
  }
   
  
   if (average > soglia) {
    servoclamp.write(pinzamax);   // chiudo la pinza
  }
    if (average < soglia) {
      controllo[i] = LOW;
    }
    else {
      controllo[i] = HIGH;
    }
    if (i < 10) {
      i++;
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
   servoclamp.write(pinzamin);// apriamo la pinza
  }

  delay(1);        // delay in between reads for stability

}
