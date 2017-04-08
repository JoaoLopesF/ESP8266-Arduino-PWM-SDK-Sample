#ESP8266 Arduino - PWM SDK Sample

## Stop Arduino's ESP8266 AnalogWrite PWM  "flickering"!

## Contents
 - [About](#about)
 - [Wishlist](#wishlist)
 - [Releases](#releases)

## About

The PWM of Arduino Esp8266 have issues about "flickering"

Depending value of AnalogWrite, causes flickering of output.

If you want dimmer an LED, you can see "flickering: :-(

Have any sources in internet about this, as:

    - https://github.com/esp8266/Arduino/issues/836

I not have sucess with analogWrites, so I go to PWM of Expressif ESP8266 SDK.
This Have issues too :-(

But have the solution: see in: https://github.com/StefanBruens/ESP8266_new_pwm

But I not found Arduino sample to use this

This sample is to show how use the PWM SDK

Attention!  
 - To use this new solution You have put the file "pwm.c" together at your ".ino" file
 - You can use 8 PWM, but not in GPIO16 (D0)
 - After changes in PWM, you must call "pwm_start" to commit this changes
 - This PWM uses the period to set dutys: 100% -> 5000, 10% -> 500 (for default period)

 This sample dimmer the leds in D5 and D6

## Wishlist
- Make a library for this

## Releases
#### 1.0.0
- First version
