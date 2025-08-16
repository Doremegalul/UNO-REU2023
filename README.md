Welcome to the REU page of Minh and Will.

This project demonstrates an IoT distance measurement system using an ultrasonic sensor, RGB LED, and buzzer on a Raspberry Pi.

- IoT.c: Implements the logic for measuring distance with an ultrasonic sensor (Trig and Echo pins). Based on the measured distance, it dynamically adjusts:
  - RGB LED colors (closer = red spectrum, farther = green/purple)
  - Buzzer frequency (closer = higher tone, farther = silent)
- Uses WiringPi, softPwm, and softTone libraries for hardware control.

- wiringPi.h: The WiringPi library header, providing Arduino-like APIs for Raspberry Pi GPIO, PWM, and interrupts. It defines pin modes, constants, function prototypes, and hardware-specific helpers.

Together, these files create an interactive proximity alert system: when objects are detected within 50 cm, the buzzer beeps and LED color shifts as a visual/audio warning.
