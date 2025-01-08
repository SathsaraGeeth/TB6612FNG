# Driver for TB6612FNG

This driver supports the TB6612FNG, a dual H-Bridge motor driver IC, designed to control DC motors, stepper motors, or other inductive loads such as solenoids. The TB6612FNG offers various features including low ON-resistor transistors, power-saving standby modes, and built-in protection circuits.

The driver is platform independent.

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

## Datasheets

- [TB6612FNG Datasheet](https://toshiba.semicon-storage.com/info/TB6612FNG_datasheet_en_20141001.pdf?did=10660&prodName=TB6612FNG)

This README.md was written by ChatGPT.