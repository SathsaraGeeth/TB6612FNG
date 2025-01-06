#ifndef TB6612_H
#define TB6612_H


#define MAX_FPWM 100000
#define DEAD_TIME 2

/* function pointers for hardware control */
extern void (*set_pin)(int pin, int state); // state -> 1: ON, 0: OFF
extern void (*start_pwm)(int pin, int frequency); // frequency in Hz
/* NOOP */
extern void (*noop)(int time); // time in nano seconds

typedef struct {
    int FPWM;
    int INV_POL; // 1: reverse the direction, 0: keep the same direction
} load_settings;

typedef struct {
    int IN1;
    int IN2;
    int PWM;
    load_settings settings;
} load;

typedef struct {
    load LOAD1;
    load LOAD2;
    int STBY;
} tb6612_driver;

/**
 * @brief Initializes the driver with default settings.
 * 
 * @param driver Pointer to the tb6612_driver struct.
 */
void tb6612_driver_init(tb6612_driver* driver);

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
 * @brief Stops the load -> OFF(High Impedence).
 * 
 * @param load Pointer to the load struct.
 */
void load_stop(load* load);

/**
 * @brief Forces the TB6612 driver in the standby mode -> OFF(High Impedence).
 * 
 * @param driver Pointer to the TB6612 driver structure.
 */
void tb6612_driver_off(tb6612_driver* driver);


#endif // TB6612_H
