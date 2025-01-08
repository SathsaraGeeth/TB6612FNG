#include "tb6612fng.h"
#include <stdio.h>
    /*
     * BEGIN
     * -> define driver ~ use only STBY pin while defining this make life much easier
     * -> add load(s) to the driver ~ use add_load()
     * -> initialize driver ~ pull load inputs to LOW before doing so
     * -> start load(s)
     * -> change load settings if desired
     * -> break load if desired
     * -> stop load if desired
     * -> stop driver ~ pull load inputs to LOW (by stop loads)
     * END
     */

load_settings DEFAULT_SETTINGS = {.DUTY_CYCLE = 1, .FPWM = MAX_FPWM, .INV_POL = 0};

load add_load(tb6612fng_driver* driver, const pin_t in1, const pin_t in2, const pin_t pwm) {
    if (driver->num_loads < MAX_LOADS) {
        set_pin(in1,0);
        set_pin(in2, 0);
        const load load = {.IN1 = in1, .IN2 = in2, .PWM = pwm, .settings = DEFAULT_SETTINGS};
        driver->loads[driver->num_loads] = load;
        driver->num_loads++;
        return load;
    }
    return (load){0}; // return a placeholder default load
}
void tb6612fng_driver_init(tb6612fng_driver* driver){
    set_pin(driver->STBY,1);
}
void load_init(load* load) {
    if (!load->settings.INV_POL){
        set_pin(load->IN1, 1);
        set_pin(load->IN2, 0);
    } else{
        set_pin(load->IN1, 0);
        set_pin(load->IN2, 1);
    }
    if (load->settings.FPWM <= MAX_FPWM){
        start_pwm(load->PWM, load->settings.FPWM, load->settings.DUTY_CYCLE);
    } else{
        start_pwm(load->PWM, MAX_FPWM, load->settings.DUTY_CYCLE); // if the FPWM is too high cap it at the MAX_FPWM
    }
}
void update_load_settings(load* load, load_settings* new_settings){
    load->settings = *new_settings;
    load_stop(load);
    noop(DEAD_TIME); // to prevent penetrating currents
    load_init(load);
}
void load_short_break(load* load){
    load_stop(load);
    noop(DEAD_TIME);  // to prevent penetrating currents
    set_pin(load->IN1, 1);
    set_pin(load->IN2, 1);
}
void load_stop(load* load){
    set_pin(load->IN1, 0);
    set_pin(load->IN2, 0);
    start_pwm(load->PWM, load->settings.FPWM, 1);
}
void tb6612fng_driver_off(tb6612fng_driver* driver){
	set_pin(driver->STBY, 0);
}
