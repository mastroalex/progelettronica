# prog_elettronica
## Progetto elettronica
### Table of contents
* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [Getting started](#getting-started)
* [Authors](#authors)

### Introduction 

### Prerequisites

* Arduino UNO
* GY-521
* EMG Sensor 
* EMG Electrodes
* Microservo motor SG90

_________________

* [MPU6050_tockn](https://github.com/Tockn/MPU6050_tockn) - Arduino library for easy communicating with the MPU6050




### Getting started

### How to use
#### GY-521 

#### Servo 

To control servo motor it's used Servo library. 
 ```
#include <Servo.h> 
Servo servo-object-name;
```

Then use the following command to control angle from 0 to 180 degrees.

 ```
servo-object-name.write(degrees);
```
The following diagram includes the connection for both the servo and the IMU.

<img src="https://github.com/mastroalex/progelettronica/blob/main/GY-521%20file/gy%2Bservo_bb.png" alt="servo+gy" width="500"/>

#### EMG 

### Authors 
