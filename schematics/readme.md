# DONE:

1. gps-and-imu schematic finished.
2. kill-switch schmematic finished.
3. motor-servo schematic finished.

# TODO:

1. make kill-switch-reciever schematic. (will we even have a kill-switch-reciever?)

# NOTES:

## Kicad

1. robomagellan-kicad-library contains:
  a. gps-module (the neo-m8 gps board)
  b. imu-module (the adafruit imu board)
  c. ThreePinCon (a three pin connector to represent the three pins to control the turning servo)
2. there already is a nrf2401 kicad module.

## Drok 7A1160 Dual Motor Drive (L298 Chip)

- Rated output current must be 2x higher than rated power supply.
- When switching between forward/reverse, the motor needs to break more than 0.1 seconds.
- Do not turn the motor at high speed when the module is powered down.
- ENA are the PWM inputs. It must be between 3-6.5V and 0-10kHz, with maximum pulse width of 10us.
- 10A fuse recommended at MOTOR+ outputs.

| IN1 | IN2 |   OUT   |
|:---:|:---:|:-------:|
|  0  |  0  |  Break  |
|  1  |  1  |  Coast  |
|  1  |  0  | Forward |
|  0  |  1  | Reverse |

## Buck Converter

- The buck converter we have has max output 3A. Clockwise increases voltage, counter-clockwise decreases voltage.

## Arduino Nano  

- The Arduino Nano can be powered from the regulated Vin pin (pin 30) with 6V-20V, or the unregulated 5V pin (pin 27) with 5V +/- 0.3V. 
- The 5V pin can be used as an output, but with limited current draw (<500mA or something like that.)
- It is important to put a big capacitor on the power supply output to filter low frequency voltage shifts (such as when a voltage dip when a module is turned on). 
- It is also important to put decoupling capacitors (0.1uF range) as close as possible to modules to filter high frequency small voltage shifts due to the fast clocking microprocessors.
- The nano has 500mA max current draw from usb.
- Documentation: https://store.arduino.cc/usa/arduino-nano

## IMU

- Name: Adafruit 9-DOF Absolute Orientation IMU Fusion Breakout - BNO055
- Amazon link: https://www.amazon.com/Adafruit-Absolute-Orientation-Fusion-Breakout/dp/B017PEIGIG/ref=olp_product_details?_encoding=UTF8&me=&qid=1538237346&sr=8-1
- Adafruit guide: https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/overview

## GPS Module

- Documentation (use with Raspi 2): http://osoyoo.com/2016/10/25/use-rapsberry-pi-to-drive-u-blox-neo-6m-gps-module/
- Guide (use with arduino mega): http://osoyoo.com/2016/10/25/use-mega2560-to-drive-gps/
- Amazon Link: https://www.amazon.com/dp/B01AW5QYES/ref=dp_cerb_3
