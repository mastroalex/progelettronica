# prog_elettronica
## Progetto elettronica
### Table of contents
* [Introduction](#introduction)
* [Prerequisites](#prerequisites)
* [Getting started](#getting-started)
* [Authors](#authors)

### Introduction 
The idea of the project is to show the concept and how to controls gripper and rotation via sensor signals. The structure is very simple and made in full of maker and DIY philosophy, only with recycled objects. 
An example in the following figure.

<img src="https://github.com/mastroalex/progelettronica/blob/main/cad/Untitled.JPG" alt="structure" width="400"/> <img src="https://github.com/mastroalex/progelettronica/blob/main/cad/Untitled3.JPG" alt="structure" width="400"/> 

The gripper has been further simplified but the same project could be realized by purchasing a robot gripper.


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
A servomotor is a rotary actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration. It consists of a suitable motor coupled to a sensor for position feedback. It also requires a relatively sophisticated controller, often a dedicated module designed specifically for use with servomotors.

Microservo SG90 is used. It can rotate approximately 180 degrees (90 in each direction) and works just like the standard kinds but smaller.

<img src="https://github.com/mastroalex/progelettronica/blob/main/servo/sg90.png" alt="servo_control" width="250"/>

Position "0" (1.5 ms pulse) is middle, "90" (~2ms pulse) is middle, is all the way to the right, "-90" (~1ms pulse) is all the way to the left.
The Servo library is used to control the servo motor.
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
