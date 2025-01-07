#include "gpio.h"
#include "tb6612fng.h"
#include <unistd.h>

#define AIN1 12
#define AIN2 16
#define APWM 18
#define STBY_PIN 20

void set_pin(pin_t pin, int state){
    digitalWrite(pin, state);
}

void start_pwm(pin_t pin, int frequency) {
    if (frequency == 0) {
        digitalWrite(pin, 1);
        return;
    }
    int period = 1000000000 / frequency; //in ns
    int half_period = period / 2;
    while (1) {
        digitalWrite(pin, 1);
        noop(half_period);
        digitalWrite(pin, 0);
        noop(half_period);
    }
}

void noop(int time){
    usleep(time / 1000);
}

int main(){
    tb6612fng_driver driver = {.STBY = STBY_PIN};
    load loadA = add_load(&driver, AIN1, AIN2, APWM);
    tb6612fng_driver_init(&driver);

    load_init(&loadA);
    load_settings new_settings = {0.55, 0};
    update_load_settings(&loadA, &new_settings);
    usleep(100000);

    load_settings new_settings1 = {0.33, 1};
    update_load_settings(&loadA, &new_settings1);
    usleep(100000);

    load_stop(&loadA);

    tb6612fng_driver_off(&driver);


    return 0;
}