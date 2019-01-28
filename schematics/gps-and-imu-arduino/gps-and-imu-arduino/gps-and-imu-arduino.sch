EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5C4F7135
P 5150 3400
F 0 "A1" H 5150 2314 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 5150 2223 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5300 2450 50  0001 L CNN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 5150 2400 50  0001 C CNN
	1    5150 3400
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C4F7211
P 5350 2350
F 0 "#PWR?" H 5350 2200 50  0001 C CNN
F 1 "VCC" H 5367 2523 50  0000 C CNN
F 2 "" H 5350 2350 50  0001 C CNN
F 3 "" H 5350 2350 50  0001 C CNN
	1    5350 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 2400 5350 2350
$Comp
L New_Library:gps-module U1
U 1 1 5C4F7ADF
P 6750 2800
F 0 "U1" H 7177 2446 50  0000 L CNN
F 1 "gps-module" H 7177 2355 50  0000 L CNN
F 2 "" H 6750 2800 50  0001 C CNN
F 3 "" H 6750 2800 50  0001 C CNN
	1    6750 2800
	1    0    0    -1  
$EndComp
$Comp
L New_Library:imu-module J1
U 1 1 5C4F7B65
P 6700 3850
F 0 "J1" H 6725 3915 50  0000 C CNN
F 1 "imu-module" H 6725 3824 50  0000 C CNN
F 2 "" H 6700 3850 50  0001 C CNN
F 3 "" H 6700 3850 50  0001 C CNN
	1    6700 3850
	1    0    0    -1  
$EndComp
$EndSCHEMATC
