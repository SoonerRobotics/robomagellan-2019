EESchema Schematic File Version 4
LIBS:gps-and-imu-cache
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
U 1 1 5C50DBB8
P 5750 3850
F 0 "A1" H 5750 5400 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 5750 5300 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 5900 2900 50  0001 L CNN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 5750 2850 50  0001 C CNN
	1    5750 3850
	1    0    0    -1  
$EndComp
$Comp
L roboamgellan:imu-module U1
U 1 1 5C50DE84
P 7200 3600
F 0 "U1" H 7200 3515 50  0000 C CNN
F 1 "imu-module" H 7200 3424 50  0000 C CNN
F 2 "" H 7200 3600 50  0001 C CNN
F 3 "" H 7200 3600 50  0001 C CNN
	1    7200 3600
	1    0    0    -1  
$EndComp
$Comp
L roboamgellan:gps-module J1
U 1 1 5C50DF27
P 4300 4950
F 0 "J1" H 4269 4035 50  0000 C CNN
F 1 "gps-module" H 4269 4126 50  0000 C CNN
F 2 "" H 4300 4950 50  0001 C CNN
F 3 "" H 4300 4950 50  0001 C CNN
	1    4300 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 4450 5250 4450
Wire Wire Line
	4700 4350 5250 4350
$Comp
L power:VCC #PWR?
U 1 1 5C50E093
P 4800 4650
F 0 "#PWR?" H 4800 4500 50  0001 C CNN
F 1 "VCC" V 4817 4778 50  0000 L CNN
F 2 "" H 4800 4650 50  0001 C CNN
F 3 "" H 4800 4650 50  0001 C CNN
	1    4800 4650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C50E0E5
P 4800 4550
F 0 "#PWR?" H 4800 4300 50  0001 C CNN
F 1 "GND" V 4805 4422 50  0000 R CNN
F 2 "" H 4800 4550 50  0001 C CNN
F 3 "" H 4800 4550 50  0001 C CNN
	1    4800 4550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C50E187
P 5750 4950
F 0 "#PWR?" H 5750 4700 50  0001 C CNN
F 1 "GND" H 5755 4777 50  0000 C CNN
F 2 "" H 5750 4950 50  0001 C CNN
F 3 "" H 5750 4950 50  0001 C CNN
	1    5750 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4950 5750 4900
Wire Wire Line
	5850 4850 5850 4900
Wire Wire Line
	5850 4900 5750 4900
Connection ~ 5750 4900
Wire Wire Line
	5750 4900 5750 4850
$Comp
L power:VCC #PWR?
U 1 1 5C50E1DA
P 5950 2750
F 0 "#PWR?" H 5950 2600 50  0001 C CNN
F 1 "VCC" H 5967 2923 50  0000 C CNN
F 2 "" H 5950 2750 50  0001 C CNN
F 3 "" H 5950 2750 50  0001 C CNN
	1    5950 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 2750 5950 2850
Wire Wire Line
	4800 4650 4700 4650
Wire Wire Line
	4700 4550 4800 4550
NoConn ~ 4700 4250
NoConn ~ 7550 4350
NoConn ~ 7550 4250
NoConn ~ 7550 4150
NoConn ~ 7550 4050
NoConn ~ 6850 4450
$Comp
L power:VCC #PWR?
U 1 1 5C50E5BA
P 6750 3950
F 0 "#PWR?" H 6750 3800 50  0001 C CNN
F 1 "VCC" V 6768 4077 50  0000 L CNN
F 2 "" H 6750 3950 50  0001 C CNN
F 3 "" H 6750 3950 50  0001 C CNN
	1    6750 3950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6750 3950 6850 3950
NoConn ~ 6850 4050
$Comp
L power:GND #PWR?
U 1 1 5C50E6B2
P 6750 4150
F 0 "#PWR?" H 6750 3900 50  0001 C CNN
F 1 "GND" V 6755 4022 50  0000 R CNN
F 2 "" H 6750 4150 50  0001 C CNN
F 3 "" H 6750 4150 50  0001 C CNN
	1    6750 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	6750 4150 6850 4150
Wire Wire Line
	6250 4250 6850 4250
Wire Wire Line
	6250 4350 6850 4350
Text Notes 6350 2700 0    50   ~ 0
VCC and GND are connected to the buck converter.
$EndSCHEMATC
