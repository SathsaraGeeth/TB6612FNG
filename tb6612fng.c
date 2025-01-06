#include "tb6612.h"
#include <stdio.h>

void (*set_pin)(int pin, int state) = NULL;
void (*start_pwm)(int pwm, int frequency) = NULL;
void (*noop)(int time) = NULL;

void tb6612_driver_init(tb6612_driver* driver){
    load_settings DEFALUT_SETTINGS = {0, 0};
    driver->LOAD1.settings = DEFALUT_SETTINGS;
    driver->LOAD2.settings = DEFALUT_SETTINGS;
    set_pin(driver->STBY, 1);
}
void load_init(load* load){
    if (!load->settings.INV_POL){
        set_pin(load->IN1, 1);
        set_pin(load->IN2, 0);
    } else{
        set_pin(load->IN1, 0);
        set_pin(load->IN2, 1);
    };
    if (load->settings.FPWM <= MAX_FPWM){
        start_pwm(load->PWM, load->load_settings.FPWM);
    } else{
        start_pwm(load->PWM, MAX_FPWM); // if the FPWM is too high cap it at the MAX_FPWM
    }
}
void update_load_settings(load* load, load_settings* new_settings){
    load->settings = *new_settings;
    load_stop(load* load);
    noop(DEAD_TIME);
    load_init(load* load);
}
void load_short_break(load* load){
    load_stop(load* load);
    noop(DEAD_TIME);
    set_pin(load->IN1, 1);
    set_pin(load->IN2, 1);
}
void load_stop(load* load){
    set_pin(load->IN1, 0);
    set_pint(load->IN2, 0);
    set_pin(load->PWM, 1); // or start_pwm(load->PWM, 0); 
}
void tb6612_driver_off(tb6612_driver* driver){
    set_pin(driver->STBY, 0);
}
