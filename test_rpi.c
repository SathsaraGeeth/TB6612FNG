#include <wiringPi.h>
#include "tb6612fng.h"
#include <stdio.h>
#include <unistd.h>


#define AIN1 32
#define AIN2 36
#define APWM 12
#define STBY 38

void set_pin(pin_t, int state);
void start_pwm(pint_t, int frequency;
void noop(int time);

int main(){
	// setup gpio pins
	pinMode(AIN1, OUTPUT);
	pinMode(AIN2, OUTPUT);
	pinMode(APWM, PWM_OUTPUT);
	pinMode(STBY, OUTPUT);
	
	//intialize driver and load
	tb6612fng_driver driver;
	load loadA = {AIN1, AIN2, PWM_PIN,{0, 0}};
	
	// init driver and load
	tb6612fng_driver_init(&driver);
	load_init(&loadA);

	return 0;
}

void set_pin(pin_t pin, int state){
	if (state){
		digitalWrite(pin, HIGH);
	}else{
		digitalWrite(pin, LOW);
	}
}

void start_pwm(pin_t pin, int frequency){
	pwm_val = 0; // to test
	pwmWrite(pin, pwm_val);
}

void noop(int time){
	usleep(tim/1000);
}
