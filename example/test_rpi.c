#include "gpio.h"
#include "../src/tb6612fng.h"
#include <unistd.h>

#define AIN1 12
#define AIN2 16
#define APWM 18
#define STBY_PIN 20

void set_pin(pin_t pin, int state){
    digitalWrite(pin, state);
}

void start_pwm(pin_t pin, int frequency, double duty_cycle) {
    digitalWrite(pin, 1); // for testing purposes <- implement a pwm functionality

}


void noop(int time){
    usleep(time / 1000);
}

int main(){

    // define pinModes
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(APWM, OUTPUT);
    pinMode(STBY_PIN, OUTPUT);

    tb6612fng_driver driver = {.STBY = STBY_PIN};
    load loadA = add_load(&driver, AIN1, AIN2, APWM);
    tb6612fng_driver_init(&driver);

    load_init(&loadA);
    load_settings new_settings = {0.2, 1000, 0};
    update_load_settings(&loadA, &new_settings);
    usleep(100000);

    load_settings new_settings1 = {0.2, 1000, 1};
    update_load_settings(&loadA, &new_settings1);
    usleep(100000);

    load_stop(&loadA);

    tb6612fng_driver_off(&driver);
    return 0;
}
