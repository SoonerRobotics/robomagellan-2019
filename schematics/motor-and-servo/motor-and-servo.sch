EESchema Schematic File Version 4
LIBS:motor-and-servo-cache
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
L power:GND #PWR?
U 1 1 5C50EF35
P 6600 4900
F 0 "#PWR?" H 6600 4650 50  0001 C CNN
F 1 "GND" H 6605 4727 50  0000 C CNN
F 2 "" H 6600 4900 50  0001 C CNN
F 3 "" H 6600 4900 50  0001 C CNN
	1    6600 4900
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C50EF6C
P 6700 2700
F 0 "#PWR?" H 6700 2550 50  0001 C CNN
F 1 "VCC" H 6717 2873 50  0000 C CNN
F 2 "" H 6700 2700 50  0001 C CNN
F 3 "" H 6700 2700 50  0001 C CNN
	1    6700 2700
	1    0    0    -1  
$EndComp
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5C50EFAA
P 6500 3800
F 0 "A1" H 6500 5450 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 6500 5300 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 6650 2850 50  0001 L CNN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 6500 2800 50  0001 C CNN
	1    6500 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 2700 6700 2800
Wire Wire Line
	6600 4900 6600 4850
Wire Wire Line
	6500 4800 6500 4850
Wire Wire Line
	6500 4850 6600 4850
Connection ~ 6600 4850
Wire Wire Line
	6600 4850 6600 4800
$Comp
L RF:NRF24L01_Breakout U2
U 1 1 5C50F0C2
P 4650 5400
F 0 "U2" H 5128 5378 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 5128 5287 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 4800 6000 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 4650 5300 50  0001 C CNN
	1    4650 5400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5150 5100 5850 5100
Wire Wire Line
	5150 5600 5350 5600
Wire Wire Line
	5350 5600 5350 4100
Wire Wire Line
	5350 4100 6000 4100
NoConn ~ 5150 5700
Wire Wire Line
	5150 5400 5400 5400
Wire Wire Line
	5400 5400 5400 4200
Wire Wire Line
	5400 4200 6000 4200
Text GLabel 6600 2700 1    50   Input ~ 0
3V3
Wire Wire Line
	6600 2700 6600 2800
Text GLabel 4650 4700 1    50   Input ~ 0
3V3
Wire Wire Line
	4650 4700 4650 4800
$Comp
L power:GND #PWR?
U 1 1 5C50F6CD
P 4650 6100
F 0 "#PWR?" H 4650 5850 50  0001 C CNN
F 1 "GND" H 4655 5927 50  0000 C CNN
F 2 "" H 4650 6100 50  0001 C CNN
F 3 "" H 4650 6100 50  0001 C CNN
	1    4650 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4650 6100 4650 6000
$Comp
L roboamgellan:ThreePinCon U3
U 1 1 5C50FB3E
P 7850 3550
F 0 "U3" H 8077 3351 50  0000 L CNN
F 1 "ThreePinCon" H 8077 3260 50  0000 L CNN
F 2 "" H 7850 3550 50  0001 C CNN
F 3 "" H 7850 3550 50  0001 C CNN
	1    7850 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3800 7700 3800
$Comp
L power:VCC #PWR?
U 1 1 5C50FD60
P 7600 3700
F 0 "#PWR?" H 7600 3550 50  0001 C CNN
F 1 "VCC" V 7618 3827 50  0000 L CNN
F 2 "" H 7600 3700 50  0001 C CNN
F 3 "" H 7600 3700 50  0001 C CNN
	1    7600 3700
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C50FD7A
P 7600 3900
F 0 "#PWR?" H 7600 3650 50  0001 C CNN
F 1 "GND" V 7605 3772 50  0000 R CNN
F 2 "" H 7600 3900 50  0001 C CNN
F 3 "" H 7600 3900 50  0001 C CNN
	1    7600 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	7600 3900 7700 3900
Wire Wire Line
	7600 3700 7700 3700
Text Notes 7800 3550 0    50   ~ 0
Three Pin Connector goes to servo.\nVCC (Pin 1) is white wire.\nA0 (Pin 2) is purple wire.\nGND (Pin 3) is purple wire.
$Comp
L robomagellan:motor-controller U1
U 1 1 5C587F8A
P 3400 2250
F 0 "U1" H 3400 2265 50  0000 C CNN
F 1 "motor-controller" H 3400 2174 50  0000 C CNN
F 2 "" H 3400 2250 50  0001 C CNN
F 3 "" H 3400 2250 50  0001 C CNN
	1    3400 2250
	-1   0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C58808C
P 4100 2500
F 0 "#PWR?" H 4100 2350 50  0001 C CNN
F 1 "VCC" H 4117 2673 50  0000 C CNN
F 2 "" H 4100 2500 50  0001 C CNN
F 3 "" H 4100 2500 50  0001 C CNN
	1    4100 2500
	0    1    -1   0   
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C5880AB
P 4100 3100
F 0 "#PWR?" H 4100 2950 50  0001 C CNN
F 1 "VCC" H 4117 3273 50  0000 C CNN
F 2 "" H 4100 3100 50  0001 C CNN
F 3 "" H 4100 3100 50  0001 C CNN
	1    4100 3100
	0    1    -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C5880C9
P 4100 3800
F 0 "#PWR?" H 4100 3550 50  0001 C CNN
F 1 "GND" H 4105 3627 50  0000 C CNN
F 2 "" H 4100 3800 50  0001 C CNN
F 3 "" H 4100 3800 50  0001 C CNN
	1    4100 3800
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C5880E0
P 4100 2900
F 0 "#PWR?" H 4100 2650 50  0001 C CNN
F 1 "GND" H 4105 2727 50  0000 C CNN
F 2 "" H 4100 2900 50  0001 C CNN
F 3 "" H 4100 2900 50  0001 C CNN
	1    4100 2900
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C5880F3
P 4100 3500
F 0 "#PWR?" H 4100 3250 50  0001 C CNN
F 1 "GND" H 4105 3327 50  0000 C CNN
F 2 "" H 4100 3500 50  0001 C CNN
F 3 "" H 4100 3500 50  0001 C CNN
	1    4100 3500
	0    -1   1    0   
$EndComp
Wire Wire Line
	4100 3800 4000 3800
Wire Wire Line
	4100 3500 4000 3500
Wire Wire Line
	4100 3100 4000 3100
Wire Wire Line
	4100 2900 4000 2900
Wire Wire Line
	4100 2500 4000 2500
Wire Wire Line
	4000 2600 5250 2600
Wire Wire Line
	5250 2600 5250 3500
Wire Wire Line
	5250 3500 6000 3500
Wire Wire Line
	4000 2700 5200 2700
Wire Wire Line
	5200 2700 5200 3600
Wire Wire Line
	5200 3600 6000 3600
Wire Wire Line
	4000 2800 5150 2800
Wire Wire Line
	5150 2800 5150 3700
Wire Wire Line
	5150 3700 6000 3700
Wire Wire Line
	6000 4300 5850 4300
Wire Wire Line
	5850 4300 5850 5100
Wire Wire Line
	6000 4400 5900 4400
Wire Wire Line
	5900 4400 5900 5200
Wire Wire Line
	5900 5200 5150 5200
Wire Wire Line
	5150 5300 5950 5300
Wire Wire Line
	5950 5300 5950 4500
Wire Wire Line
	5950 4500 6000 4500
Wire Wire Line
	4000 3200 4850 3200
Wire Wire Line
	4850 3200 4850 3800
Wire Wire Line
	4850 3800 6000 3800
Wire Wire Line
	4000 3300 4800 3300
Wire Wire Line
	4800 3300 4800 3900
Wire Wire Line
	4800 3900 6000 3900
Wire Wire Line
	4000 3400 4750 3400
Wire Wire Line
	4750 3400 4750 4000
Wire Wire Line
	4750 4000 6000 4000
$Comp
L Motor:Motor_DC M1
U 1 1 5C59D78C
P 1950 2700
F 0 "M1" H 2108 2696 50  0000 L CNN
F 1 "Motor_DC" H 2108 2605 50  0000 L CNN
F 2 "" H 1950 2610 50  0001 C CNN
F 3 "~" H 1950 2610 50  0001 C CNN
	1    1950 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2500 2550 2500
Wire Wire Line
	1950 3000 2650 3000
Wire Wire Line
	2650 3000 2650 2600
Wire Wire Line
	2650 2600 2800 2600
Text GLabel 2700 3100 0    50   Input ~ 0
Servo+
Wire Wire Line
	2700 3100 2800 3100
Text GLabel 2700 3200 0    50   Input ~ 0
Servo-
Wire Wire Line
	2700 3200 2800 3200
$Comp
L Device:Fuse F1
U 1 1 5C5A3A43
P 2400 2500
F 0 "F1" V 2203 2500 50  0000 C CNN
F 1 "10A Fuse" V 2294 2500 50  0000 C CNN
F 2 "" V 2330 2500 50  0001 C CNN
F 3 "~" H 2400 2500 50  0001 C CNN
	1    2400 2500
	0    1    1    0   
$EndComp
Wire Wire Line
	2250 2500 1950 2500
Text GLabel 4000 3700 2    50   Input ~ 0
MotorBattery
$EndSCHEMATC
