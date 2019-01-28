EESchema Schematic File Version 4
LIBS:kill-switch-cache
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
L Device:Battery BT1
U 1 1 5C48F4FE
P 9200 4200
F 0 "BT1" H 9308 4246 50  0000 L CNN
F 1 "6V" H 9308 4155 50  0000 L CNN
F 2 "" V 9200 4260 50  0001 C CNN
F 3 "~" V 9200 4260 50  0001 C CNN
	1    9200 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C48F700
P 9200 4500
F 0 "#PWR?" H 9200 4250 50  0001 C CNN
F 1 "GND" H 9205 4327 50  0000 C CNN
F 2 "" H 9200 4500 50  0001 C CNN
F 3 "" H 9200 4500 50  0001 C CNN
	1    9200 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4500 9200 4450
$Comp
L power:VCC #PWR?
U 1 1 5C48F7B6
P 9200 3900
F 0 "#PWR?" H 9200 3750 50  0001 C CNN
F 1 "VCC" H 9217 4073 50  0000 C CNN
F 2 "" H 9200 3900 50  0001 C CNN
F 3 "" H 9200 3900 50  0001 C CNN
	1    9200 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 4000 9200 3950
$Comp
L Device:C_Small C1
U 1 1 5C48F890
P 9600 4200
F 0 "C1" H 9692 4246 50  0000 L CNN
F 1 "22p" H 9692 4155 50  0000 L CNN
F 2 "" H 9600 4200 50  0001 C CNN
F 3 "~" H 9600 4200 50  0001 C CNN
	1    9600 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1_Small C3
U 1 1 5C48F9E5
P 10300 4200
F 0 "C3" H 10391 4246 50  0000 L CNN
F 1 "22u" H 10391 4155 50  0000 L CNN
F 2 "" H 10300 4200 50  0001 C CNN
F 3 "~" H 10300 4200 50  0001 C CNN
	1    10300 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 4300 9600 4450
Wire Wire Line
	9600 4450 9200 4450
Connection ~ 9200 4450
Wire Wire Line
	9200 4450 9200 4400
Wire Wire Line
	10300 4300 10300 4450
Wire Wire Line
	10300 4450 9950 4450
Connection ~ 9600 4450
Wire Wire Line
	10300 4100 10300 3950
Wire Wire Line
	10300 3950 9950 3950
Connection ~ 9200 3950
Wire Wire Line
	9200 3950 9200 3900
Wire Wire Line
	9600 4100 9600 3950
Connection ~ 9600 3950
Wire Wire Line
	9600 3950 9200 3950
$Comp
L power:GND #PWR?
U 1 1 5C48FC0B
P 8150 5850
F 0 "#PWR?" H 8150 5600 50  0001 C CNN
F 1 "GND" H 8155 5677 50  0000 C CNN
F 2 "" H 8150 5850 50  0001 C CNN
F 3 "" H 8150 5850 50  0001 C CNN
	1    8150 5850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR?
U 1 1 5C48FD22
P 8250 3700
F 0 "#PWR?" H 8250 3550 50  0001 C CNN
F 1 "VCC" H 8300 3900 50  0000 C CNN
F 2 "" H 8250 3700 50  0001 C CNN
F 3 "" H 8250 3700 50  0001 C CNN
	1    8250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 5850 8150 5800
Wire Wire Line
	8050 5750 8050 5800
Wire Wire Line
	8050 5800 8150 5800
Connection ~ 8150 5800
Wire Wire Line
	8150 5800 8150 5750
$Comp
L power:GND #PWR?
U 1 1 5C49020F
P 5300 6200
F 0 "#PWR?" H 5300 5950 50  0001 C CNN
F 1 "GND" H 5305 6027 50  0000 C CNN
F 2 "" H 5300 6200 50  0001 C CNN
F 3 "" H 5300 6200 50  0001 C CNN
	1    5300 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3750 8150 3650
$Comp
L Switch:SW_Push SW2
U 1 1 5C491E40
P 5800 3300
F 0 "SW2" V 5850 3500 50  0000 R CNN
F 1 "MB" V 5750 3500 50  0000 R CNN
F 2 "" H 5800 3500 50  0001 C CNN
F 3 "" H 5800 3500 50  0001 C CNN
	1    5800 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R1
U 1 1 5C49209B
P 6300 4850
F 0 "R1" V 6095 4850 50  0000 C CNN
F 1 "220" V 6186 4850 50  0000 C CNN
F 2 "" V 6340 4840 50  0001 C CNN
F 3 "~" H 6300 4850 50  0001 C CNN
	1    6300 4850
	0    1    1    0   
$EndComp
NoConn ~ 5800 5850
$Comp
L MCU_Module:Arduino_Nano_v2.x A1
U 1 1 5C48F32D
P 8050 4750
F 0 "A1" H 8500 3300 50  0000 C CNN
F 1 "Arduino_Nano_v2.x" H 8050 3300 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 8200 3800 50  0001 L CNN
F 3 "https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf" H 8050 3750 50  0001 C CNN
	1    8050 4750
	1    0    0    -1  
$EndComp
$Comp
L RF:NRF24L01_Breakout U1
U 1 1 5C4901B5
P 5300 5550
F 0 "U1" H 4750 4600 50  0000 L CNN
F 1 "NRF24L01_Breakout" H 4900 4600 50  0000 L CNN
F 2 "RF_Module:nRF24L01_Breakout" H 5450 6150 50  0001 L CIN
F 3 "http://www.nordicsemi.com/eng/content/download/2730/34105/file/nRF24L01_Product_Specification_v2_0.pdf" H 5300 5450 50  0001 C CNN
	1    5300 5550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8250 3750 8250 3700
Wire Wire Line
	5300 6200 5300 6150
Wire Wire Line
	5800 5750 7400 5750
Wire Wire Line
	7400 5750 7400 5050
Wire Wire Line
	7400 5050 7550 5050
Wire Wire Line
	5800 5550 7450 5550
Wire Wire Line
	7450 5550 7450 5150
Wire Wire Line
	7450 5150 7550 5150
Text GLabel 5300 4900 1    50   Input ~ 0
3v3
Text GLabel 8150 3650 1    50   Input ~ 0
3v3
Wire Wire Line
	5300 4950 5300 4900
$Comp
L Device:R_US R3
U 1 1 5C4920CD
P 5800 3750
F 0 "R3" H 5732 3704 50  0000 R CNN
F 1 "10k" H 5732 3795 50  0000 R CNN
F 2 "" V 5840 3740 50  0001 C CNN
F 3 "~" H 5800 3750 50  0001 C CNN
	1    5800 3750
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C5447B7
P 5800 3950
F 0 "#PWR?" H 5800 3700 50  0001 C CNN
F 1 "GND" H 5805 3777 50  0000 C CNN
F 2 "" H 5800 3950 50  0001 C CNN
F 3 "" H 5800 3950 50  0001 C CNN
	1    5800 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3950 5800 3900
$Comp
L power:VCC #PWR?
U 1 1 5C5453C9
P 5800 3050
F 0 "#PWR?" H 5800 2900 50  0001 C CNN
F 1 "VCC" H 5817 3223 50  0000 C CNN
F 2 "" H 5800 3050 50  0001 C CNN
F 3 "" H 5800 3050 50  0001 C CNN
	1    5800 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 3100 5800 3050
Wire Wire Line
	5800 5450 7550 5450
Wire Wire Line
	5800 5350 7550 5350
Wire Wire Line
	5800 5250 7550 5250
$Comp
L Switch:SW_Push SW1
U 1 1 5C550621
P 5350 3300
F 0 "SW1" V 5400 3500 50  0000 R CNN
F 1 "LB" V 5300 3500 50  0000 R CNN
F 2 "" H 5350 3500 50  0001 C CNN
F 3 "" H 5350 3500 50  0001 C CNN
	1    5350 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 5C550628
P 5350 3750
F 0 "R2" H 5282 3704 50  0000 R CNN
F 1 "10k" H 5282 3795 50  0000 R CNN
F 2 "" V 5390 3740 50  0001 C CNN
F 3 "~" H 5350 3750 50  0001 C CNN
	1    5350 3750
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C55062F
P 5350 3950
F 0 "#PWR?" H 5350 3700 50  0001 C CNN
F 1 "GND" H 5355 3777 50  0000 C CNN
F 2 "" H 5350 3950 50  0001 C CNN
F 3 "" H 5350 3950 50  0001 C CNN
	1    5350 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3950 5350 3900
$Comp
L power:VCC #PWR?
U 1 1 5C550636
P 5350 3050
F 0 "#PWR?" H 5350 2900 50  0001 C CNN
F 1 "VCC" H 5367 3223 50  0000 C CNN
F 2 "" H 5350 3050 50  0001 C CNN
F 3 "" H 5350 3050 50  0001 C CNN
	1    5350 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 3100 5350 3050
$Comp
L Switch:SW_Push SW3
U 1 1 5C5569DB
P 6250 3300
F 0 "SW3" V 6300 3500 50  0000 R CNN
F 1 "RB" V 6200 3500 50  0000 R CNN
F 2 "" H 6250 3500 50  0001 C CNN
F 3 "" H 6250 3500 50  0001 C CNN
	1    6250 3300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5C5569E2
P 6250 3750
F 0 "R4" H 6182 3704 50  0000 R CNN
F 1 "10k" H 6182 3795 50  0000 R CNN
F 2 "" V 6290 3740 50  0001 C CNN
F 3 "~" H 6250 3750 50  0001 C CNN
	1    6250 3750
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C5569E9
P 6250 3950
F 0 "#PWR?" H 6250 3700 50  0001 C CNN
F 1 "GND" H 6255 3777 50  0000 C CNN
F 2 "" H 6250 3950 50  0001 C CNN
F 3 "" H 6250 3950 50  0001 C CNN
	1    6250 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5C4F7AC2
P 9950 4200
F 0 "C2" H 10042 4246 50  0000 L CNN
F 1 "22p" H 10042 4155 50  0000 L CNN
F 2 "" H 9950 4200 50  0001 C CNN
F 3 "~" H 9950 4200 50  0001 C CNN
	1    9950 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9950 4100 9950 3950
Connection ~ 9950 3950
Wire Wire Line
	9950 3950 9600 3950
Wire Wire Line
	9950 4300 9950 4450
Connection ~ 9950 4450
Wire Wire Line
	9950 4450 9600 4450
$Comp
L Device:LED_Dual_AAC D1
U 1 1 5C503668
P 6850 4850
F 0 "D1" H 7200 4550 50  0000 C CNN
F 1 "LED_Dual_AAC" H 6850 4550 50  0000 C CNN
F 2 "" H 6850 4850 50  0001 C CNN
F 3 "~" H 6850 4850 50  0001 C CNN
	1    6850 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5C509E9B
P 6050 4950
F 0 "#PWR?" H 6050 4700 50  0001 C CNN
F 1 "GND" H 6055 4777 50  0000 C CNN
F 2 "" H 6050 4950 50  0001 C CNN
F 3 "" H 6050 4950 50  0001 C CNN
	1    6050 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 4750 7550 4750
Wire Wire Line
	6050 4950 6050 4850
Wire Wire Line
	6050 4850 6150 4850
Wire Wire Line
	6250 3950 6250 3900
Text Notes 9000 6400 0    50   ~ 0
C1 is placed across transciver vcc and gnd.\nC2 and C3 are placed across arduino +5V and gnd.\nLB - Left Button\nMB- Middle Button\nRB - Right Button\nthis is with the arduino usb port pointed to the right.\nPush left button to activate D4.\nPush middle button to activate d3.\nPush right button to activate D2.\n
$Comp
L power:VCC #PWR?
U 1 1 5C4FA7F3
P 6250 3050
F 0 "#PWR?" H 6250 2900 50  0001 C CNN
F 1 "VCC" H 6267 3223 50  0000 C CNN
F 2 "" H 6250 3050 50  0001 C CNN
F 3 "" H 6250 3050 50  0001 C CNN
	1    6250 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 3100 6250 3050
Wire Wire Line
	5550 3550 5350 3550
Wire Wire Line
	5350 3550 5350 3600
Wire Wire Line
	5350 3500 5350 3550
Connection ~ 5350 3550
Wire Wire Line
	5800 3500 5800 3550
Wire Wire Line
	6250 3500 6250 3550
Wire Wire Line
	5800 3550 6000 3550
Wire Wire Line
	6000 3550 6000 4450
Connection ~ 5800 3550
Wire Wire Line
	5800 3550 5800 3600
Wire Wire Line
	6000 4450 7550 4450
Wire Wire Line
	5550 4550 7550 4550
Wire Wire Line
	5550 3550 5550 4550
Wire Wire Line
	6250 3550 6450 3550
Wire Wire Line
	6450 3550 6450 4350
Wire Wire Line
	6450 4350 7550 4350
Connection ~ 6250 3550
Wire Wire Line
	6250 3550 6250 3600
Wire Wire Line
	6450 4850 6550 4850
Wire Wire Line
	7300 4950 7150 4950
Wire Wire Line
	7300 4750 7300 4950
Wire Wire Line
	7250 4750 7250 4650
Wire Wire Line
	7250 4650 7550 4650
Wire Wire Line
	7150 4750 7250 4750
$EndSCHEMATC
