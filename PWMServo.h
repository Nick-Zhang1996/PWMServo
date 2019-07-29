#ifndef PWMServo_h
#define PWMServo_h

/*
  PWMServo.h - Hardware Servo Timer Library
  http://arduiniana.org/libraries/pwmservo/
  Original Author: Jim Studt, jim@federated.com

  Modified by Nick Zhang, this version is specific to Teensy 3.5, though it may work on other arm based teensies. 
  This version uses a 300Hz analogwrite frequency for fast servos

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

#include <inttypes.h>

#if defined(__arm__) && defined(TEENSYDUINO)
  #define SERVO_PIN_A 9
  #define SERVO_PIN_B 10
  // all PWM pins supported, but names not defined here...
  // just use the actual PWM pin number with attach()
#endif

class PWMServo
{
  private:
    uint8_t pin;
    float min_us;       // minimum pulse, uS units
    float max_us;       // maximum pulse, uS units
#if defined(__arm__) && defined(TEENSYDUINO)
    static uint32_t attachedpins[]; // 1 bit per digital pin
#endif
  public:
    PWMServo();
    //uint8_t attach(int pinArg) { return attach(pinArg, 544, 2400); }
                             // pulse length for 0 degrees in microseconds, 544uS default
                             // pulse length for 180 degrees in microseconds, 2400uS default
    uint8_t attach(int pinArg, uint16_t min, uint16_t max);
                             // attach to a pin, sets pinMode, returns 0 on failure, won't
                             // position the servo until a subsequent write() happens
    //void detach();
    void writeMicroseconds(float us); //specify pulsewidth, min to max
    //uint8_t attached();
};

#endif
