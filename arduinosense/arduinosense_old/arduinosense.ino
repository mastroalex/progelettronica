#include <MPU6050_tockn.h>
#include <Wire.h>
#include "funzioniBPM.h" // battiti
#include "printerfunzioni.h" // stampante
#include "EMGsmooth.h" // lettura emg
#include "radioRF.h" // lettura emg

MPU6050 mpu6050(Wire);
void setup() {
  Serial.begin(9600);
  Wire.begin(); // avvio e inizializzo il gyro
  lcdstart();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  // mpu6050.setGyroOffsets(0, 0, 0);
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {  // initialize all the readings to 0:
    readings[thisReading] = 0;
  }
  t1 = millis();
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
  lcd.begin(); // initialize the LCD
  lcd.backlight();
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(soglia_pin, INPUT);
}
void loop() {
  average = averagecalc (); // calcolo media EMG
  mpu6050.update();
  tempmpu = mpu6050.getTemp(); // prende la temperatura
  angle = mpu6050.getAngleX(); // prende l'angolo lungo x
  printatore(LOW); // set HIGH to debug EMG with serial plotter
  lcdprint();
  battiti();
  soglia = analogRead(soglia_pin);
  charfortransmission("T", String(tempmpu));
  charfortransmission("A", String(angle));
  charfortransmission("M", String(average));
  charfortransmission("B", String(BPM));
  charfortransmission("S", String(soglia));
  delay(1);
}
