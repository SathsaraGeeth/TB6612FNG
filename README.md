# Driver for TB6612FNG

This driver supports the TB6612FNG, a dual H-Bridge motor driver IC, designed to control DC motors, stepper motors, or other inductive loads such as solenoids. The TB6612FNG offers various features including low ON-resistor transistors, power-saving standby modes, and built-in protection circuits.

The driver supports both **STM32 HAL** and **Linux** environments, allowing it to be used on a variety of platforms such as STM32 microcontrollers and Raspberry Pi or other Linux-based systems.

## Features

- **Power Supply Voltage**: VM = 15 V (Max)
- **Output Current**: IOUT = 1.2 A (average) / 3.2 A (peak)
- **Output Low ON Resistor**: 0.5Ω (upper + lower, Typ. @ VM ≥ 5 V)
- **Standby Mode**: Power save mode
- **Modes**: CW (Clockwise), CCW (Counter-clockwise), Short Brake, and Stop mode
- **Built-in Protection**: Thermal shutdown and low voltage detection
- **Versatile Load Support**: Can control motors, solenoids, and other inductive loads

## Pinout

- **IN1, IN2**: Input pins for controlling the motor direction (CW/CCW).
- **PWM**: Pulse-width modulation pin for controlling motor speed.
- **STBY**: Standby pin for putting the driver in low-power mode.

## Usage

The TB6612FNG driver allows you to control two separate loads (e.g., motors) using four primary functions: **CW**, **CCW**, **Short Brake**, and **Stop**.

You can use this driver on both STM32-based systems (using STM32 HAL) and Linux-based systems (such as Raspberry Pi using the `wiringPi` library). The driver requires initialization of the pins, setting the load configuration, and using PWM for speed control.

### STM32 HAL Example

The following example demonstrates how to use the TB6612FNG driver on an STM32 microcontroller:

```c
#include "stm32f4xx_hal.h"
#include "tb6612.h"

// Define the GPIO pins and PWM for STM32
#define IN1_PIN GPIO_PIN_0
#define IN2_PIN GPIO_PIN_1
#define PWM_PIN GPIO_PIN_2
#define STBY_PIN GPIO_PIN_3
#define GPIO_PORT GPIOA

// HAL functions to set pins and start PWM
void set_pin(int pin, int state) {
    if (state) {
        HAL_GPIO_WritePin(GPIO_PORT, pin, GPIO_PIN_SET);
    } else {
        HAL_GPIO_WritePin(GPIO_PORT, pin, GPIO_PIN_RESET);
    }
}

void start_pwm(int pwm, int frequency) {
    // Initialize PWM using HAL library (PWM setup is omitted for brevity)
    // Example: Set the PWM frequency and start the timer
}

void noop(int time) {
    // Implement a delay using HAL library
    HAL_Delay(time / 1000000); // Convert ns to ms
}

int main(void) {
    // HAL Initialization
    HAL_Init();
    
    // GPIO and PWM initialization (assuming this is already done in CubeMX or manually)
    // Set up GPIO for IN1, IN2, PWM, STBY pins
    
    // Initialize the driver
    tb6612_driver driver;
    tb6612_driver_init(&driver);
    
    // Initialize load1 and load2
    load load1 = {IN1_PIN, IN2_PIN, PWM_PIN, {0, 0}};
    load_init(&load1);
    
    // Update load settings
    load_settings new_settings = {50000, 0};  // FPWM = 50kHz, INV_POL = 0
    update_load_settings(&load1, &new_settings);
    
    // Short brake the load
    load_short_break(&load1);
    
    // Stop the load
    load_stop(&load1);
    
    // Turn off the driver
    tb6612_driver_off(&driver);
    
    while (1) {
        // Main loop (e.g., periodically control the motor)
    }
}
```

### Linux Example (rpi)

This example demonstrates how to use the TB6612FNG driver on a Raspberry Pi or any other Linux-based system using the wiringPi library:

```c
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>
#include "tb6612.h"

// Define the GPIO pins and PWM for Raspberry Pi (using WiringPi)
#define IN1_PIN 0  // WiringPi pin 0 (BCM GPIO17)
#define IN2_PIN 1  // WiringPi pin 1 (BCM GPIO18)
#define PWM_PIN 2  // WiringPi pin 2 (BCM GPIO27)
#define STBY_PIN 3 // WiringPi pin 3 (BCM GPIO22)

void set_pin(int pin, int state) {
    if (state) {
        digitalWrite(pin, HIGH);
    } else {
        digitalWrite(pin, LOW);
    }
}

void start_pwm(int pwm, int frequency) {
    // Initialize PWM with wiringPi (Assuming PWM setup)
    pwmWrite(pwm, frequency); // Simple example; actual implementation may vary
}

void noop(int time) {
    // Implement a delay in nanoseconds
    usleep(time / 1000);  // Convert ns to us
}

int main(void) {
    // WiringPi Initialization
    if (wiringPiSetup() == -1) {
        printf("WiringPi setup failed\n");
        return -1;
    }

    // Set up GPIO pins
    pinMode(IN1_PIN, OUTPUT);
    pinMode(IN2_PIN, OUTPUT);
    pinMode(PWM_PIN, PWM_OUTPUT);
    pinMode(STBY_PIN, OUTPUT);

    // Initialize the driver
    tb6612_driver driver;
    tb6612_driver_init(&driver);
    
    // Initialize load1 and load2
    load load1 = {IN1_PIN, IN2_PIN, PWM_PIN, {0, 0}};
    load_init(&load1);
    
    // Update load settings
    load_settings new_settings = {50000, 0};  // FPWM = 50kHz, INV_POL = 0
    update_load_settings(&load1, &new_settings);
    
    // Short brake the load
    load_short_break(&load1);
    
    // Stop the load
    load_stop(&load1);
    
    // Turn off the driver
    tb6612_driver_off(&driver);
    
    while (1) {
        // Main loop (e.g., periodically control the motor)
    }

    return 0;
}
```

## Datasheets

- [TB6612FNG Datasheet](https://toshiba.semicon-storage.com/info/TB6612FNG_datasheet_en_20141001.pdf?did=10660&prodName=TB6612FNG)

This README.md was written by ChatGPT.