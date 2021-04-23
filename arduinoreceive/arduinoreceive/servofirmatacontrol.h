#ifndef servofirmatacontrol.h
#define servofirmatacontrol.h

#include "rotation.h"
#include "servoclamp.h"
#include "radiolib.h"
#include "serialdecode.h"


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


void myfirmatasetup(){
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



#endif
