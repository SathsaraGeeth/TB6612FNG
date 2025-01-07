#include <pigpio.h>
#include "tb6612fng.h"
#include <stdio.h>
#include <unistd.h>

#define AIN1 12
#define AIN2 16
#define APWM 18
#define STBY 20

void set_pin(int pin, int state);
void start_pwm(int pin, int frequency);
void noop(int time);

int main(){
    if (gpioInitialise() < 0) {
        printf("GPIO initialization failed!\n");
        return 1;
    }

    // setup gpio pins
    gpioSetMode(AIN1, PI_OUTPUT);
    gpioSetMode(AIN2, PI_OUTPUT);
    gpioSetMode(APWM, PI_OUTPUT);
    gpioSetMode(STBY, PI_OUTPUT);
    
    // initialize driver and load
    tb6612fng_driver driver;
    load loadA = {AIN1, AIN2, APWM, {0, 0}};
    
    // init driver and load
    tb6612fng_driver_init(&driver);
    load_init(&loadA);

    gpioTerminate();
    return 0;
}

void set_pin(int pin, int state){
    gpioWrite(pin, state);
}

void start_pwm(int pin, int frequency){
    int pwm_val = 0; // to test
    gpioPWM(pin, pwm_val);
}

void noop(int time){
    usleep(time / 1000);
}
