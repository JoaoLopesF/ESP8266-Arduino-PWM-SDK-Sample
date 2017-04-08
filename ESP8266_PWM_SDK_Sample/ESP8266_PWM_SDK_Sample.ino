/*
 * PWM_SDK_SAMPLE
 *  	The PWM of Arduino Esp8266 have issues about "flickering"
 * 		This solution uses the PWM of Expressif SDK and
 * 		a new solution of PWM - see https://github.com/StefanBruens/ESP8266_new_pwm
 *
 * 		Attention!  - To use this new solution You have put the file "pwm.c" together at your ".ino" file
 * 					- You can use 8 PWM, but not in GPIO16 (D0)
 * 					- After changes in PWM, you must call "pwm_start" to commit this changes
 * 					- This PWM uses the period to set dutys: 100% -> 5000, 10% -> 500 (for default period)
 *
 * 		This sample dimmer the leds in D5 and D6
 */

// Include pf Arduino

#include "Arduino.h"

// Includes of Expressif SDK

extern "C"{
	#include "pwm.h"
	#include "user_interface.h"
}

////// PWM

// Period of PWM frequency -> default of SDK: 5000 -> * 200ns ^= 1 kHz

#define PWM_PERIOD 5000

// PWM channels

#define PWM_CHANNELS 2

// PWM setup (choice all pins that you use PWM)

uint32 io_info[PWM_CHANNELS][3] = {
	// MUX, FUNC, PIN
//	{PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5,   5}, // D1
//	{PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4,   4}, // D2
//	{PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0,   0}, // D3
//	{PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2,   2}, // D4
	{PERIPHS_IO_MUX_MTMS_U,  FUNC_GPIO14, 14}, // D5
	{PERIPHS_IO_MUX_MTDI_U,  FUNC_GPIO12, 12}, // D6
//	{PERIPHS_IO_MUX_MTCK_U,  FUNC_GPIO13, 13}, // D7
//	{PERIPHS_IO_MUX_MTDO_U,  FUNC_GPIO15 ,15}, // D8
											   // D0 - not have PWM :-(
};

// PWM initial duty: all off

uint32 pwm_duty_init[PWM_CHANNELS];

// Dimmer variables

int16_t duty = 0;
int16_t step = 1;

// Setup

void setup()
{
	// Initialize the serial

	Serial.begin (230400);

	// Set pins (Important! All Pins must be initialized, the PWM SDK not works without this

	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);

	digitalWrite(D1, LOW);
	digitalWrite(D2, LOW);
	digitalWrite(D3, LOW);
	digitalWrite(D4, LOW);
	digitalWrite(D5, LOW);
	digitalWrite(D6, LOW);
	digitalWrite(D7, LOW);
	digitalWrite(D8, LOW);

	////// Initialize the PWM

	// Initial duty -> all off

	for (uint8_t channel = 0; channel < PWM_CHANNELS; channel++) {
		pwm_duty_init[channel] = 0;
	}

	// Period

	uint32_t period = PWM_PERIOD;

	// Initialize

	pwm_init(period, pwm_duty_init, PWM_CHANNELS, io_info);

	// Commit

	pwm_start();

}

// Loop

void loop()
{

	// Dimmer the leds

	if (step > 0 && duty >= 5000) {
		step = -1;
	} else if (step < 0 && duty <= 0) {
		step = 1;
	}

	duty+=step;

	// Set the PWM (note the pwm_start after all changes)

	pwm_set_duty(duty, 0);
	pwm_set_duty(duty, 1);

	pwm_start(); // commit

	// Debug serial

	if (duty % 100 == 0) {
		Serial.print("* duty: ");
		Serial.println(duty);
	}
	delay(5);
}
