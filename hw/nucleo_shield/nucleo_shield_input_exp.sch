EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:F411RE
LIBS:w_analog
LIBS:nucleo_shield-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3700 3150 2    60   Input ~ 0
in5
Text GLabel 3700 3300 2    60   Input ~ 0
in6
Text GLabel 3700 3450 2    60   Input ~ 0
in7
Text GLabel 3700 3600 2    60   Input ~ 0
in8
Text GLabel 8600 2400 2    60   Input ~ 0
in6
Text GLabel 8150 2300 2    60   Input ~ 0
in5
Text GLabel 8450 4700 2    60   Input ~ 0
in4
Text GLabel 8000 4600 2    60   Input ~ 0
in3
Text GLabel 8450 4500 2    60   Input ~ 0
in2
Text GLabel 8000 4400 2    60   Input ~ 0
in1
Text GLabel 8600 2600 2    60   Input ~ 0
in8
Text GLabel 8150 2500 2    60   Input ~ 0
in7
Text GLabel 3700 3750 2    60   Input ~ 0
in9
Text GLabel 3700 3900 2    60   Input ~ 0
in10
Text GLabel 3700 4050 2    60   Input ~ 0
in11
Text GLabel 3700 4200 2    60   Input ~ 0
in12
Text GLabel 8550 3000 2    60   Input ~ 0
in12
Text GLabel 8200 2900 2    60   Input ~ 0
in11
Text GLabel 8200 2700 2    60   Input ~ 0
in9
Text GLabel 8550 2800 2    60   Input ~ 0
in10
$Sheet
S 2800 2450 550  2450
U 5729E588
F0 "nucleo_shield_input" 60
F1 "nucleo_shield_input.sch" 60
F2 "in1" I R 3350 2550 60 
F3 "in2" I R 3350 2700 60 
F4 "in3" I R 3350 2850 60 
F5 "in4" I R 3350 3000 60 
F6 "in5" I R 3350 3150 60 
F7 "in6" I R 3350 3300 60 
F8 "in7" I R 3350 3450 60 
F9 "in8" I R 3350 3600 60 
F10 "in9" I R 3350 3750 60 
F11 "in10" I R 3350 3900 60 
F12 "in11" I R 3350 4050 60 
F13 "in12" I R 3350 4200 60 
F14 "in13" I R 3350 4350 60 
F15 "in14" I R 3350 4500 60 
F16 "in15" I R 3350 4650 60 
F17 "in16" I R 3350 4800 60 
$EndSheet
Text GLabel 3700 2550 2    60   Input ~ 0
in1
Text GLabel 3700 2700 2    60   Input ~ 0
in2
Text GLabel 3700 2850 2    60   Input ~ 0
in3
Text GLabel 3700 3000 2    60   Input ~ 0
in4
Wire Wire Line
	3350 2550 3700 2550
Wire Wire Line
	3700 2700 3350 2700
Wire Wire Line
	3350 2850 3700 2850
Wire Wire Line
	3700 3000 3350 3000
Wire Wire Line
	3350 3150 3700 3150
Wire Wire Line
	3700 3300 3350 3300
Wire Wire Line
	3350 3450 3700 3450
Wire Wire Line
	3700 3600 3350 3600
Wire Wire Line
	3350 3750 3700 3750
Wire Wire Line
	3700 3900 3350 3900
Wire Wire Line
	3350 4050 3700 4050
Wire Wire Line
	3700 4200 3350 4200
Text GLabel 3700 4350 2    60   Input ~ 0
in13
Text GLabel 3700 4500 2    60   Input ~ 0
in14
Text GLabel 3700 4650 2    60   Input ~ 0
in15
Text GLabel 3700 4800 2    60   Input ~ 0
in16
Wire Wire Line
	3350 4350 3700 4350
Wire Wire Line
	3700 4500 3350 4500
Wire Wire Line
	3350 4650 3700 4650
Wire Wire Line
	3700 4800 3350 4800
Text GLabel 8050 4800 2    60   Input ~ 0
in13
Text GLabel 8400 4900 2    60   Input ~ 0
in14
Text GLabel 8050 5000 2    60   Input ~ 0
in15
$Comp
L PCF8574A U7
U 1 1 572B2AA7
P 7150 4800
F 0 "U7" H 6800 5400 50  0000 L CNN
F 1 "PCF8574A" H 7250 5400 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 7150 4800 60  0001 C CNN
F 3 "" H 7150 4800 60  0000 C CNN
	1    7150 4800
	1    0    0    -1  
$EndComp
Text GLabel 8400 5100 2    60   Input ~ 0
in16
$Comp
L PCF8574A U8
U 1 1 572B2AAF
P 7300 2700
F 0 "U8" H 6950 3300 50  0000 L CNN
F 1 "PCF8574A" H 7400 3300 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 7300 2700 60  0001 C CNN
F 3 "" H 7300 2700 60  0000 C CNN
	1    7300 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2400 6800 2400
Wire Wire Line
	6100 4500 6650 4500
Wire Wire Line
	7650 4400 8000 4400
Wire Wire Line
	7650 4500 8450 4500
Wire Wire Line
	7650 4600 8000 4600
Wire Wire Line
	7650 4700 8450 4700
Wire Wire Line
	7800 2300 8150 2300
Wire Wire Line
	8600 2400 7800 2400
Wire Wire Line
	7800 2500 8150 2500
Wire Wire Line
	7800 2600 8600 2600
$Comp
L +3.3V #PWR057
U 1 1 572B2AC4
P 7300 1850
F 0 "#PWR057" H 7300 1700 50  0001 C CNN
F 1 "+3.3V" H 7300 1990 50  0000 C CNN
F 2 "" H 7300 1850 60  0000 C CNN
F 3 "" H 7300 1850 60  0000 C CNN
	1    7300 1850
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR058
U 1 1 572B2ACA
P 7150 4000
F 0 "#PWR058" H 7150 3850 50  0001 C CNN
F 1 "+3.3V" H 7150 4140 50  0000 C CNN
F 2 "" H 7150 4000 60  0000 C CNN
F 3 "" H 7150 4000 60  0000 C CNN
	1    7150 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2000 7300 1850
Wire Wire Line
	7150 4100 7150 4000
$Comp
L GND #PWR059
U 1 1 572B2AD2
P 7300 3400
F 0 "#PWR059" H 7300 3150 50  0001 C CNN
F 1 "GND" H 7300 3250 50  0000 C CNN
F 2 "" H 7300 3400 60  0000 C CNN
F 3 "" H 7300 3400 60  0000 C CNN
	1    7300 3400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR060
U 1 1 572B2AD8
P 7150 5500
F 0 "#PWR060" H 7150 5250 50  0001 C CNN
F 1 "GND" H 7150 5350 50  0000 C CNN
F 2 "" H 7150 5500 60  0000 C CNN
F 3 "" H 7150 5500 60  0000 C CNN
	1    7150 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 3100 6800 3100
Wire Wire Line
	6450 5200 6650 5200
Wire Wire Line
	7800 2700 8200 2700
Wire Wire Line
	7800 2800 8550 2800
Wire Wire Line
	8200 2900 7800 2900
Wire Wire Line
	8550 3000 7800 3000
Wire Wire Line
	7650 4800 8050 4800
Wire Wire Line
	8400 4900 7650 4900
Wire Wire Line
	7650 5000 8050 5000
Wire Wire Line
	8400 5100 7650 5100
Text HLabel 6800 2300 0    60   Input ~ 0
I2C_SCL
Text HLabel 6250 2400 0    60   Input ~ 0
I2C_SDA
Text HLabel 6650 4400 0    60   Input ~ 0
I2C_SCL
Text HLabel 6100 4500 0    60   Input ~ 0
I2C_SDA
Text HLabel 6500 3100 0    60   Input ~ 0
INT
Text HLabel 6450 5200 0    60   Input ~ 0
INT
$Comp
L GND #PWR061
U 1 1 572AA068
P 6650 2850
F 0 "#PWR061" H 6650 2600 50  0001 C CNN
F 1 "GND" H 6650 2700 50  0000 C CNN
F 2 "" H 6650 2850 60  0000 C CNN
F 3 "" H 6650 2850 60  0000 C CNN
	1    6650 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 2600 6650 2600
Wire Wire Line
	6650 2600 6650 2850
Wire Wire Line
	6800 2700 6650 2700
Connection ~ 6650 2700
Wire Wire Line
	6650 2800 6800 2800
Connection ~ 6650 2800
$Comp
L GND #PWR062
U 1 1 572AAB50
P 6550 4950
F 0 "#PWR062" H 6550 4700 50  0001 C CNN
F 1 "GND" H 6550 4800 50  0000 C CNN
F 2 "" H 6550 4950 60  0000 C CNN
F 3 "" H 6550 4950 60  0000 C CNN
	1    6550 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4800 6550 4800
Wire Wire Line
	6550 4800 6550 4950
Wire Wire Line
	6650 4900 6550 4900
Connection ~ 6550 4900
$Comp
L +3.3V #PWR063
U 1 1 572AAEDA
P 6550 4700
F 0 "#PWR063" H 6550 4550 50  0001 C CNN
F 1 "+3.3V" H 6550 4840 50  0000 C CNN
F 2 "" H 6550 4700 60  0000 C CNN
F 3 "" H 6550 4700 60  0000 C CNN
	1    6550 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 4700 6550 4700
$EndSCHEMATC
