# Progetto elettronica

## Introduction 
The idea of the project is to show the concept and how to control gripper and rotation via sensor signals. The structure is very simple and made in full of maker and DIY philosophy, only with recycled objects. 
An example in the following figure.

<img src="https://github.com/mastroalex/progelettronica/blob/main/extra/cad/Untitled.JPG" alt="structure" width="400"/> <img src="https://github.com/mastroalex/progelettronica/blob/main/extra/cad/Untitled3.JPG" alt="structure" width="400"/> 

The gripper has been further simplified in different version but the same project could be realized by purchasing a robot gripper. 

One possibility is to make it with two gears by connecting one to the servomotor. this version involves the use of recycled materials to demonstrate the use of the device.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/clamp.png" alt="structure" width="1000"/> 

## Table of contents
- [Progetto elettronica](#progetto-elettronica)
  * [Introduction](#introduction)
  * [Prerequisites](#prerequisites)
  * [Getting started](#getting-started)
  * [How to use](#how-to-use)
    + [GY-521](#gy-521)
    + [Servo](#servo)
    + [EMG Sensor](#emg-sensor)
    + [EMG Electrodes](#emg-electrodes)
    + [DS18B20 Sensor](#ds18b20-sensor)
    + [Sensor testing](#sensor-testing)
  * [Device division](#device-division)
    + [nRF24L01](#nrf24l01)
    + [Arduino Nano for sensing](#arduino-nano-for-sensing)
    + [Arduino Uno for execution](#arduino-uno-for-execution)
  * [Conclusions and future developments](#conclusions-and-future-developments)
  * [Authors](#authors)

## Prerequisites

* Arduino UNO
* GY-521
* EMG Sensor 
* EMG Electrodes
* Microservo motor SG90
* DS18B20 Sensor
* nRF24L01

_________________

* [MPU6050_tockn](https://github.com/Tockn/MPU6050_tockn) - Arduino library for easy communicating with the MPU6050
* nRF24L01 Library 
* Vectorial graphic software


* MySQL server
* Web domain 




## Getting started

## How to use
### GY-521 
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



### Servo 
A servomotor is a rotary actuator or linear actuator that allows for precise control of angular or linear position, velocity and acceleration. It consists of a suitable motor coupled to a sensor for position feedback. It also requires a relatively sophisticated controller, often a dedicated module designed specifically for use with servomotors.

Microservo SG90 is used. It can rotate approximately 180 degrees (90 in each direction) and works just like the standard kinds but smaller.

<img src="https://github.com/mastroalex/progelettronica/blob/main/extra/servo/sg90.png" alt="servo_control" width="250"/>

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

<img src="https://github.com/mastroalex/progelettronica/blob/main/extra/GY-521%20file/gy%2Bservo_bb.png" alt="servo+gy" width="500"/>

### EMG Sensor
EMG (Electromyography) sensor is able to measure a muscle's activity by monitoring the electric potential generated by muscle cells, electromyography has traditionally been used for medical research and diagnosis of neuromuscular disorders, however now EMG sensors are used in robotics and other control systems. It evaluates the health condition of muscles and the nerve cells that control them. These nerve cells are known as motor neurons. They transmit electrical signals that cause muscles to contract and relax. An EMG translates these signals into graphs or numbers, helping doctors to make a diagnosis.
This sensor amplifies and processes the electric activity of a muscle and converts it into an analog signal which can be read by any microcontroller with an analog-to-digital converter like Arduino.
When the muscle under test flexes, the sensors's output voltage increses.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/emgraw-.png" alt="emgraw" width="300"/>


Linked to the sensor via 3,5 mm jack connector there is a cable which is connected on one side to Arduino, while on the other side ends with three snap connectors 
that attach to three electrodes.

Muscle Sensor v3 is used. It needs a positive and negative reference voltage so two 9V batteries are required.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image3.jpg" alt="muscle_sensor" width="300"/>

Surface EMG can be recorded by a pair of electrodes or by a more complex array of multiple
electrodes. More than one electrode is needed because EMG recordings display the potential
difference between two separate electrodes.

As you can read in the datasheet or in schematic, the two electrodes signal enter into an amplifier for instrumentation: 

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/instramp.png" alt="strumental" width="400"/>


Subsequently the signal is rectified:

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/ampl.png" alt="strumental" width="600"/>


And finally it is smoothed:

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/smooth.png" alt="smoothing" width="400"/>

In summary we will have a variable signal with muscle contraction that will be sent to the Arduino A/D converter.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/emgsignal.png" alt="emgsignal" width="400"/>


The muscelsensor V3 is discontinued so we have chosen a copy. This copy of the V3 allows a considerable saving however it has some defects. This sensor outputs a signal without smoothing and full of disturbs.

We also made a vectorial copy (`.svg`) that you can include in fritzing to easily draw the following schemes. This requires respecting the [fritzing standards](https://fritzing.org/learning/tutorials/creating-custom-parts) to design own parts. For more informations [this guide](https://learn.sparkfun.com/tutorials/make-your-own-fritzing-parts/all).


<img src="https://github.com/mastroalex/progelettronica/blob/main/images/emg.png" alt="emg" height="300"/> <img src="https://github.com/mastroalex/progelettronica/blob/main/images/emgvec.png" alt="emg2" height="300"/>


### EMG Electrodes
The electrical activity of a muscle is detected with the help of EMG electrodes. There are differente types of electrodes, surface EMG electrodes are used in this project, in particular the gelled one.
This type of elecrodes contains a gelled electrolytic substance as interface between electrodes and skin. 
Gelled EMG electrodes provide a non invasive technique for measurements and detection of EMG signal, but they are generally used for superficial muscles since they are applied on the skin. 
The EMG electrodes must be positioned appropriately. In particular two EMG electrodes should be placed between the motor unit and the tendinous insertion of the muscle, along the longitudinal midline of the muscle. The distance between the center of the two electrodes should be 1-2 cm. Red snap connector in the middle of muscle body and the green one at one end of the muscle body. 
The third electrode (yellow one) must be placed on an inactive section of the body.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/image5.png" alt="electrodes_placement" width="300"/>

It is also important to do some considerations about emg signals.

The electrical source is the muscle membrane potential of about –90 mV. 
Typical repetition rate of muscle motor unit firing is about 7–20 Hz, depending on the size of the muscle
Measured EMG potentials range between less than 50 μV and up to 30 mV, depending on the muscle under observation. 
**It must be amplified !**

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



 <img src="https://github.com/mastroalex/progelettronica/blob/main/extra/arduino_smoothing/emg-testcompleto1.png" alt="smoothing" width="1000"/>

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
  servoclamp.attach(5);
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
    servoclamp.write(min_servo_angle);   // gripper opening
  }
 }
 ```

### Pulse sensor 

The principle is to make a light shine between your fingers. Most of the light is absorbed or reflected, but some light will pass through our tissues if they are thin enough. When blood is pumped through your body, it gets squeezed into the capillary tissues, and the volume of those tissues increases very slightly. Then, between heart beats, the volume decreases. The change in volume effects the amount of light that will transmit through. This fluctuation is very small, but we can sense it with electronics. Here's how it's done.

We start with a light source and a light detector. Using an Infrared LED, and a photodiode sensor. It's important that the two devices are matched well, so that the light wavelength output from the LED is detected strongly by the photodiode (see below for part numbers). The photodiode is essentially a teeny tiny solar cell, just like the panels on rooftops, but really small. It will generate a small voltage and current when it is blasted with photons. The Infrared LED is what we will use for our photon blaster.

The next thing we need is a way to amplify the tiny signal coming off of the photodiode. Happily enough, the configuration of this circuit is well-known  as a 'Current to Voltage Converter' and it is a classic.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/heartmonitorschm.png" alt="heartmonitorschm" width="500"/>

The photodiode needs to be shielded from ambient light, which generates alot of noise in the signal. 
The waveform here is usable, but as you can see, the pulse signal is distorted by even small movements. Also any misalignment or movement of the IR LED will muddy up the signal.

pulsesensor.com make a Pulse Sensor that is small enough to be worn comfortably in many configurations, and immune to signal noise generated by moving around, or changes in ambient lighting conditions.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/pulsesensor.png" alt="pulse" width="250"/>

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/pulsesensorschem.png" alt="pulsesensorschem" width="800"/>



DESCRIZIONE

DESCRIZIONE

DESCRIZIONE

### DS18B20 Sensor
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

### Sensor testing 

The following circuit shows the test setup for developing the initial code:

<img src="https://github.com/mastroalex/progelettronica/blob/main/extra/sensori_prova/sensori-prova-circuit_bb.png" alt="sensor_testing" width="1000"/>

This configuration of two 9V DC power supplies allows you to have +9 and -9 on the Vs terminals.
It is also possible to use 18V DC power supply and split it in +9V and -9V.

This configuration allowed us to do all the device and code tests. We therefore reworked part of the code by dividing it into the various modules in order to have a more modular system that would allow you to add or remove devices as needed.
From this configuration we started to divide then into a structure determined for monitoring and a structure with actuators.

In the end the sensors that must arrive on the wrist will be joined in a single cable equipped with a connector to connect it to the monitoring structure. 

Everything will be reorganized in a more compact way

## Device division

At this point we have divided the code and the devices. We use an arduino nano to read the sensors and an arduino uno to control the servo motors.

Communication between the two is via radio using two NRF24L01 Single chip 2.4 GHz Transceiver.

### nRF24L01

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/nRF24L01.png" alt="nrf24" width="500"/>

The device has an operating voltage of 1.9V ~ 3.6V, a built-in 2,4GHZ antenna and an operating speed (max) of 2 Mbps. 
The chip is managed by the SPI interface. Through this interface it is possible to access the registers of the chip and modify all its parameters.

This complex operation, however, is facilitated for us by libraries.

```c
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
```

The connection requires several pins:
	
- GND
- Vcc, powers the module  using 3.3V
- CE, Chip Enable, used to enable SPI communication
- CSN, Ship Select Not, pin has to be kept high always, else it will disable the SPI
- SCK,Serial Clock, provides the clock pulse using which the SPI communication works
- MOSI. Master Out Slave In, Connected to MOSI pin of Arduino, for the module to receive data from the arduino
- MISO, Master In Slave Out,Connected to MISO pin of Arduino, for the module to send data from the Arduino
- IRQ, it is an active low pin and is used only if interrupt is required

To use the chip it is necessary to set reading or writing in `setup()`like:

```c
  radio.begin();
  radio.openWritingPipe(address); //for receiving 
//radio.openWritingPipe(address); // for trasmitting
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); //for receiving 
//radio.stopListening();// for trasmitting
```

It is also important to define Chip Enable `CE`and Ship Select Not `CSN`


For the transmission we used a function `charfortransmission()` created ad hoc that allows to concatenate a letter which indicates which data we are transmitting and the value assumed from the corresponding variable. this function is cycled in the `loop()` and continuously called by sending it different parameters depending on the variable. It is then converted into `char` to allow correct transmission with the libraries it uses. 
The receiver has a similar function `radionuovo()` that first analyzes the first character identifying what information is received and then enters the data in the variables of interest, after making the appropriate variable type conversions


### Arduino Nano for sensing 

> Configuration with Arduino nano and sensors on breadboard for testing

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/sensor.png" alt="nanosensor" width="1000"/>


For the arduino dedicated to sensors, the circuit has been modified by adding an LCD display to monitor the parameters and an nRF24L01 for radio transmission. The LCD display is connected with an I2C interface module to simplify communication and cable management. The connection of the sensors has remained the same. The DS18B20 sensor has been temporarily excluded due to incompatibility between the libraries. We will decide later whether to include it again by changing the code. So the temperature of the GY-512 is used although not as accurate.

<img src="https://github.com/mastroalex/progelettronica/blob/main/arduinosense/arduinosense.png" alt="arduinosense" width="1000"/>

An arduino nano was used to make the whole thing more compact. The pin definition remains the same. It is important to remember that there are no dedicated SDa and SCL pins but they are on A4 and A5.

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/nanopinout.jpg" alt="nanopinout" width="500"/>


In the code the elements related to the servo motors have been removed and the rest has been rearranged.

The main code is as follows:

```c
#include <MPU6050_tockn.h>
#include <Wire.h>
#include "funzioniBPM.h" // battiti
#include "printerfunzioni.h" // stampante
#include "EMGsmooth.h" // lettura emg
MPU6050 mpu6050(Wire);
void setup() {
  Serial.begin(9600);
  Wire.begin(); // avvio e inizializzo il gyro
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
}
void loop() {
  average = averagecalc (); // calcolo media EMG
  mpu6050.update();
  tempmpu = mpu6050.getTemp(); // prende la temperatura
  angle = mpu6050.getAngleX(); // prende l'angolo lungo x
  printatore(LOW); // set HIGH to debug EMG with serial plotter
  lcdprint();
  battiti();
  charfortransmission("T", String(tempmpu));
  charfortransmission("A", String(angle));
  charfortransmission("M", String(average));
  charfortransmission("B", String(BPM));
  charfortransmission("S", String(soglia));
  delay(1);
}
```

This main code has been simplified by adding several functions that call external library definitions:
- ` averagecalc() ` has been defined in the `EMGsmooth.h` and is used to calculate the average of the distorted EMG signal
- `printatore(LOW)` it is a special function that can be used to print the EMG signal for the serial plotter in order to debug any problems with the detection. It is usually used to print all values ​​on the serial monitor. It is defined in `printerfunzioni.h`
- `lcdprint()` it is used to print the different values ​​and connected symbols on the LCD display
- `battiti()`it is used to reveal heartbeats and BPM. It has been defined in the `funzioniBPM.h`
- `charfotransmission()`to trasmitting data with relative informations

To maintain the code clear this function was defined in external libraries. 
The `EMGsmooth.h` library it's responsible of smoothing emg signal in order to obtain precision in threshold determination.
The `funzioniBPM.h` library has already been described in the pulse sensor paragraph.
The `printerfunzioni.h` contains the function to print in the serial monitor and in the lcd display. It also contains the definition of the LCD symbol as an arrow or heart.

To create special characters for LCD it is used  [LCD Custom Generator](https://maxpromer.github.io/LCD-Character-Creator/) that allow us to generate a byte custom char with pixel ON/OFF definition. This allows us to use special symbols in addition to ASCII characters by individually defining the on and off pixels in an 5x8 matrix (`byte_matrix`). It is possible to create up to 8 different symbols with the `createChar ()` function of the LiquidCrystal library and print them with `lcd.Write()`. For example for heart symbol:

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/heart.png" alt="LCD" width="150"/>

```
byte heart[] = {
  B00000,
  B11011,
  B10101,
  B10001,
  B01010,
  B00100,
  B00100,
  B00000
};
lcd.createChar(1, heart);
lcd.setCursor(6, 0);
lcd.write(1);
```


<img src="https://github.com/mastroalex/progelettronica/blob/main/images/LCD.png" alt="LCD" width="300"/>

Each library contains all the variables and all the other libraries necessary for their operation. 

We are therefore able to obtain the following values ​​which must be contained to the arduino with the actuators:

- `tempmpu`
- `angle`
- `average`
- `BPM`
- `soglia`



### Arduino Uno for execution

> Configuration with Arduino Uno, servomotors, radio trasmitter and clamp  for testing

<img src="https://github.com/mastroalex/progelettronica/blob/main/images/actuator.png" alt="actuator" width="1000"/>

## GUI

We also found it useful to develop a graphical user interface that allow you to view data or take control of the clamp, both from a computer and from a smartphone.

### Processing and computer app

To develop computer app we use Processing, compatible with MacOs, Windows and Linux.

#### Sliders

In order to control the clamp and the other servo used in this project two sliders have been created on Processing. 
The first sketch created was the one on Arduino, in particular we have used a library which is called Firmata. Firmata is a library that implements the Firmata protocol for standard communication, to make Arduino or more generally a hardware device communicate with various types of peripherals or programs. 
In this project it was used to make Arduino at the service of an external software that is Processing itself. 
In the example section of the Arduino IDE we called ServoFrimata which is one of the example programs that supports as many servos as possible using the Servo library. 
Once the example was opened, it was compiled and uploaded to Arduino. This meant that Arduino could be interfaced by using this comunication protocol with any other software, program o device with the same protocol like Processing.

The code is as follows:

```c
#include <Servo.h>
#include <Firmata.h>

Servo servos[MAX_SERVOS];
byte servoPinMap[TOTAL_PINS];
byte servoCount = 0;

void analogWriteCallback(byte pin, int value)
{
  if (IS_PIN_DIGITAL(pin)) {
    servos[servoPinMap[pin]].write(value);
  }
}

void systemResetCallback()
{
  servoCount = 0;
}

void setup()
{
  byte pin;

  Firmata.setFirmwareVersion(FIRMATA_FIRMWARE_MAJOR_VERSION, FIRMATA_FIRMWARE_MINOR_VERSION);
  Firmata.attach(ANALOG_MESSAGE, analogWriteCallback);
  Firmata.attach(SYSTEM_RESET, systemResetCallback);

  Firmata.begin(9600);
  systemResetCallback();

  // attach servos from first digital pin up to max number of
  // servos supported for the board
  for (pin = 0; pin < TOTAL_PINS; pin++) {
    if (IS_PIN_DIGITAL(pin)) {
      if (servoCount < MAX_SERVOS) {
        servoPinMap[pin] = servoCount;
        servos[servoPinMap[pin]].attach(PIN_TO_DIGITAL(pin));
        servoCount++;
      }
    }
  }
}

void loop()
{
  while (Firmata.available())
    Firmata.processInput();
}
```

In order to use the Firmata protocol on Processing, besides the serial library which is present by default on Arduino, it is necessary to import a library provided by Arduino which includes an Arduino equivalent software object, which represents the physical arduino connected via USB cable to the computer.

```c
import processing.serial.*;
import cc.arduino.*;
Arduino arduino;
Serial serial;
```

No dedicated libraries have been loaded to create the sliders. In fact the elements that create the slider have been drawn with another program and then added as images inside the program folder.

The images were then loaded into the code in this way:

```c
  barra1 = loadImage("barra1.png");
  indicatore1 = loadImage("indicatore1.png");
  barra2 = loadImage("barra2.png");
  indicatore2 = loadImage("indicatore2.png");
```
And than the images were placed on the window:

```c
  image(barra1, x1, y1);
  image(indicatore1, x2, y2);
  image(barra2, x1, y3);
  image(indicatore2, x4, y4);
```

So when the mouse moves along the x coordinate for the length of the slider in the upper half of the graphic window, the symbol which represents the indicator, will follow the mouse simulating the function of the slider. 
While when the muose moves along the x coordinate for the lenght of the slidere in the lower half of the graphic window, the indicator of the second slider will follow the mouse.
Then according to the position of the mouse the `servoWrite` function writes a value to the servo telling to go to the corresponding angle ranging from 0 to 180 degrees.

The code is as follows:

```c
...
if (mousePressed && mouseY < y1+20) {
      float targetX1 = constrain(mouseX, 100, 380);
      float dx = targetX1 - x2;
      x2 += dx * easing;
      arduino.servoWrite(5, constrain(mouseX / 2, 0, 180));
  }
 if (mousePressed && mouseY > y4-10) {
      float targetX2 = constrain(mouseX, 100, 380);
      float dx = targetX2 - x4;
      x4 += dx * easing;
      arduino.servoWrite(9, constrain(mouseX / 2, 0, 180));
  }
  ```
 
 Below the graphic window with the created sliders:
  
  <img src= "https://github.com/mastroalex/progelettronica/blob/main/images/graphics%20window.png" alt = "slider" width = "300"/>
  
#### Bluetooth decode 

#### Code 



### Mobile app

## Data logging and storage


## Conclusions and future developments

## References

- [nRF24L01 Wireless RF Module](https://components101.com/wireless/nrf24l01-pinout-features-datasheet)
- [Arduino Wireless Communication](https://www.youtube.com/watch?v=7rcVeFFHcFM)
- [EMG Circuit for a Microcontroller](http://www.instructables.com/member/Gundanium/?utm_source=pdf&utm_campaign=title)
- [Electromyography(EMG) with MyoWare Muscle Sensor & Arduino](https://how2electronics.com/electromyography-emg-with-myoware-muscle-sensor-arduino/)
- [Muscel Sensor V3 Datasheet](http://www.advancertechnologies.com/p/muscle-sensor-v3.html)
- [pulsesensor.com](https://pulsesensor.com)
- [FIAB elettrodi](https://www.fiab.it/prodotti.php)
- [LCD custom generator](https://maxpromer.github.io/LCD-Character-Creator/)
- [Fritzing standard](https://fritzing.org/learning/tutorials/creating-custom-parts)
- [Make your own fritzing parts](https://learn.sparkfun.com/tutorials/make-your-own-fritzing-parts/all)
- [Arduino smoothing](https://www.arduino.cc/en/Tutorial/BuiltInExamples/Smoothing)
- [Uno pinout guide](https://www.circuito.io/blog/arduino-uno-pinout/)
- [Nano pinout guide](https://www.makerguides.com/arduino-nano/)
- [ESP8266 pinout](https://randomnerdtutorials.com/esp8266-pinout-reference-gpios/)
- [Elettromiografia](https://it.wikipedia.org/wiki/Elettromiografia_ed_elettroneurografia#:~:text=L'elettromiografia%20(EMG)%2C,dal%20punto%20di%20vista%20funzionale.)
- [ECG](https://it.wikipedia.org/wiki/Elettrocardiogramma)
- [Anatomy of The DIY Heart Rate Monitor](https://pulsesensor.com/blogs/news/6326816-anatomy-of-the-diy-heart-rate-monitor) 

## Authors 
