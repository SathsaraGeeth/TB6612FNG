#ifndef TB6612_H
#define TB6612_H
#include <stdint.h>

/* tb6612fng hardware specs */
#define MAX_FPWM 100000
#define DEAD_TIME 2
#define MAX_LOADS 2

/* pin type */
typedef uint8_t pin_t;

/* weak function to let client implement platform specific gpio control
 * outside the driver. making the driver platform independent.
 *
 * @todo: use function pointers instead
 */
void __attribute__((weak)) set_pin(pin_t pin, int state);
void __attribute__((weak)) start_pwm(pin_t pin, int frequency);
void __attribute__((weak)) noop(int time);

/* main data structure */

typedef struct {
    int FPWM;
    int INV_POL; // 1: reverse the direction, 0: keep the same direction
} load_settings;

typedef struct {
    pin_t IN1;
    pin_t IN2;
    pin_t PWM;
    load_settings settings;
} load;

typedef struct {
    pin_t STBY;
    load loads[MAX_LOADS]; // array of loads
    int num_loads; // available loads
} tb6612fng_driver;



/**
 * @brief Initializes the driver with default settings.
 * 
 * @param driver Pointer to the tb6612fng_driver struct.
 */
void tb6612fng_driver_init(tb6612fng_driver* driver);



/**
 * @brief Add loads to the driver
 *
 * @param driver Pointer to the tb6612fng_driver struct.
 * @param in1, in2, pwm const pin_t gpio pins.
 *
 * @return 0 to indicate success and a negative error to indicate failure.
 */
load add_load(tb6612fng_driver* driver, const pin_t in1, const pin_t in2, const pin_t pwm);



/**
 * @brief Initializes the load on with specified settings.
 * 
 * @param load Pointer to the load struct.
 */
void load_init(load* load);



/**
 * @brief Updates the load's settings.
 *
 * @param load Pointer to the load struct.
 * @param new_settings Pointer to the new settings struct.
 */
void update_load_settings(load* load, load_settings* new_settings);



/**
 * @brief Short brakes the load.
 * 
 * @param load Pointer to the load struct.
 */
void load_short_break(load* load);



/**
 * @brief Stops the load -> OFF(High Impedance).
 * 
 * @param load Pointer to the load struct.
 */
void load_stop(load* load);



/**
 * @brief Forces the TB6612 driver in the standby mode -> OFF(High Impedance).
 * 
 * @param driver Pointer to the TB6612 driver structure.
 */
void tb6612fng_driver_off(tb6612fng_driver* driver);




#endif // TB6612_H
