# prog_elettronica
## Progetto elettronica
### Table of contents
* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [Getting started](#getting-started)
* [Authors](#authors)

### Introduction 
The idea of the project is to show the concept and how to control gripper and rotation via sensor signals. The structure is very simple and made in full of maker and DIY philosophy, only with recycled objects. 
An example in the following figure.

<img src="https://github.com/mastroalex/progelettronica/blob/main/cad/Untitled.JPG" alt="structure" width="400"/> <img src="https://github.com/mastroalex/progelettronica/blob/main/cad/Untitled3.JPG" alt="structure" width="400"/> 

The gripper has been further simplified in different version but the same project could be realized by purchasing a robot gripper.


### Prerequisites

* Arduino UNO
* GY-521
* EMG Sensor 
* EMG Electrodes
* Microservo motor SG90
* DS18B20 Sensor

_________________

* [MPU6050_tockn](https://github.com/Tockn/MPU6050_tockn) - Arduino library for easy communicating with the MPU6050




### Getting started

### How to use
#### GY-521 
GY-521 is a module that manages the MPU-6050 sensor, a chip manufactured by Invensense, which is a IMU (Inertia Measurement Unit) sensor based on MEMS technology that contains a three-axis accelerometer and a three-axis gyroscope embedded in a single chip. This is a 6 DOF (degrees of freedom) IMU sensor so it gives six values as output. It also contains a temperature sensor.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image1.png" alt="orientation_of_axes" width="250"/>

The accelerometer is capable of detecting the angle of inclination along the three axes, while the gyroscope detects the angular velocity around the three axes.
GY-521 module is small in size but it is very accurate, it contains a 16-bit analog to digital conversion hardware for each channel so it captures the x, y, and z channel at the same time.
The sensor uses the I2C protocol for communication.
Two libraries are required one for the I2C and the other for communicating with MPU-6050.
 ```c
 #include <MPU6050_tockn.h>
 MPU6050 mpu6050(Wire);
 #include <Wire.h>
 ```




#### Servo 
A servomotor is a rotary actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration. It consists of a suitable motor coupled to a sensor for position feedback. It also requires a relatively sophisticated controller, often a dedicated module designed specifically for use with servomotors.

Microservo SG90 is used. It can rotate approximately 180 degrees (90 in each direction) and works just like the standard kinds but smaller.

<img src="https://github.com/mastroalex/progelettronica/blob/main/servo/sg90.png" alt="servo_control" width="250"/>

Position "0" (1.5 ms pulse) is middle, "90" (~2ms pulse) is middle, is all the way to the right, "-90" (~1ms pulse) is all the way to the left.
The Servo library is used to control the servo motor.
 ```c
#include <Servo.h> 
Servo servo-object-name;
```

Then use the following command to control angle from 0 to 180 degrees.

 ```c
servo-object-name.write(degrees);
```
The following diagram includes the connection for both the servo and the IMU.

<img src="https://github.com/mastroalex/progelettronica/blob/main/GY-521%20file/gy%2Bservo_bb.png" alt="servo+gy" width="500"/>

#### EMG Sensor
EMG (Electromyography) sensor is able to measure a muscle's activity by monitoring the electric potential generated by muscle cells, electromyography has traditionally
been used for medical research and diagnosis of neuromuscular disorders, however now EMG sensors are used in robotics and other control systems.
This sensor amplifies and processes the electric activity of a muscle and converts it into an analog signal which can be read by any microcontroller with an 
analog-to-digital converter like Arduino.
When the muscle under test flexes, the sensors's output voltage increses.
Linked to the sensor via audio-style connector there is a cable which is connected on one side to Arduino, while on the other side ends with three snap connectors 
that attach to three electrodes.

Muscle Sensor v3 is used. It needs a positive and negative reference voltage so two 9V batteries are required.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image3.jpg" alt="muscle_sensor" width="250"/>

#### EMG Electrodes
The electrical activity of a muscle is detected with the help of EMG electrodes. There are differente types of electrodes, surface EMG electrodes are used in this project,
in particular the gelled one.
This type of elecrodes contains a gelled electrolytic substance as interface between electrodes and skin. 
Gelled EMG electrodes provide a non invasive technique for measurements and detection of EMG signal, but they are generally used for superficial muscles since they are applied 
on the skin. 
The EMG electrodes must be positioned appropriately. In particular two EMG electrodes should be placed between the motor unit and the tendinous insertion of the muscle, along the longitudinal midline of the muscle. The distance between the center of the two electrodes should be 1-2 cm.
The third electrode must be placed on an inactive section of the body.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image5.png" alt="electrodes_placement" width="350"/>

It is also important to do some considerations about emg signals.

Due to the low quality of the emg circuit the analog signal was full of noise. The voltage was only rectified but not very leveled. So we provided to simple smoothing algorithm.

```c

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int inputPin = A0;              // EMG analog pin

void setup() {
    Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}


void loop() {
 
  total = total - readings[readIndex];          // subtract the last reading:
  readings[readIndex] = analogRead(inputPin);   // read from the sensor
  total = total + readings[readIndex];          // add the reading to the total:
  readIndex = readIndex + 1;                    // advance to the next position in the array:

  if (readIndex >= numReadings) {               // if we're at the end of the array
    readIndex = 0;                              // wrap around to the beginning
  }
  average = total / numReadings;                // calculate the average:
                                                // print different data for plotting
  Serial.print(average);
  Serial.print("\t");
  Serial.print(soglia);
  Serial.print("\t");
  Serial.println(analogRead(inputPin));
  delay(1);                                     // delay in between reads for stability
}
 ```


 This is the [Arduino's reference smoothing scritp](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Smoothing/) with little changes made after a long period of testing.



 <img src="https://github.com/mastroalex/progelettronica/blob/main/arduino_smoothing/emg-testcompleto1.png" alt="smoothing" width="1000"/>

 > Smoothed signal (blue), original signal (green), threeshold (red). When the signal is below the threshold the arm is relaxed otherwise it is contracted.

 This smoothed `average` allows us to customize the following control code for the clamp servo.

 ```c
#include <Servo.h>
Servo servoclamp;
long t3 = 0;
long t4 = 20;
boolean controllo[10];
boolean stato;
int i = 0;
int soglia = 350; // Threeshold
// This value derives from a long period of testing. 
// You will need to do several tests 

void setup() {
  servo1.attach(5);
  
  // other code...
  
}

 void loop() {

// other code..

  if (average > soglia) {

    servoclamp.write(max_servo_angle);// gripper closing
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
    // only if the average is below the threshold
    // for a long time is it possible to close the clamp 
    // this allows to avoid problems due to sudden oscillations of the signal
  for (int j = 0; j < 10; j++) {      
    if (controllo[j] == LOW) {      
      stato = LOW;
    }
    else {
      stato = HIGH;
    }
  }
  if (stato == LOW) {
    servoclamp.write(min_servo_angle);   // gripper closing
  }
 }
 ```

#### DS18B20 Sensor
DS18B20 is a digital temperature sensor, which is a sensor capable of measuring the temperature of the environment but also of the ground or to detect temperature in liquids. 
This sensor is available in several sizes, in this project it has been used the one inserted into a waterproof probe. The DS18B20 sensor is much more sensitive than the DHT11 
(temperature and humidity sensor) because it can reach 9 to 12 bit resolution. More with this module it is possibile to add multiple sensors on the same bus, each 
DS18B20 has a unique 64-bit serial code, which allows multiple DS18B20s to function on the same bus.
The protocol used is OneWire protocol which uses a digital pin, from which a bus starts and allows us to communicate with a specific device on the bus knowing the address.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image2.png" alt="temperature_sensor" width="250"/>

Two libraries are required, the first one is the DallasTemperature and the second one is the OneWire library. 

 ```c
#include <DallasTemperature.h>
#include <OneWire.h>
```

### Authors 
