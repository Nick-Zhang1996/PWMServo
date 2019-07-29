#include "Arduino.h"
#include "PWMServo.h"

/*
  PWMServo.cpp - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Author: Jim Studt, jim@federated.com
  Copyright (c) 2007 David A. Mellis.  All right reserved.
  renamed to PWMServo by Mikal Hart
  ported to other chips by Paul Stoffregen

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#define NO_ANGLE (0xff)

#if defined(__arm__) && defined(TEENSYDUINO)

uint32_t PWMServo::attachedpins[(NUM_DIGITAL_PINS+31)/32]; // 1 bit per digital pin

PWMServo::PWMServo() : pin(255), angle(NO_ANGLE) {}

uint8_t PWMServo::attach(int pinArg, uint16_t min, uint16_t max)
{
	//Serial.printf("attach, pin=%d, min=%d, max=%d\n", pinArg, min, max);
	if (pinArg < 0 || pinArg >= NUM_DIGITAL_PINS) return 0;
	if (!digitalPinHasPWM(pinArg)) return 0;
	pin = pinArg;
	analogWriteFrequency(pin, 300);
	angle = NO_ANGLE;
	digitalWrite(pin, LOW);
	pinMode(pin, OUTPUT);
	attachedpins[pin >> 5] |= (1 << (pin & 31));
	return 1;
}

void PWMServo::writeMicroseconds(float us)
{
  if (us<min_us) { us = min_us; }
  if (us>max_us) { us = max_us; }

	float duty = us/(1e6/300.0)*65535;
#if TEENSYDUINO >= 137
	noInterrupts();
	uint32_t oldres = analogWriteResolution(16);
	analogWrite(pin, duty);
  // restore resolution
	analogWriteResolution(oldres);
	interrupts();
#endif
}

/*
uint8_t PWMServo::attached()
{
	if (pin >= NUM_DIGITAL_PINS) return 0;
	return (attachedpins[pin >> 5] & (1 << (pin & 31))) ? 1 : 0;
}
*/

#endif


