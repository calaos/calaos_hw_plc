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
LIBS:special
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
Sheet 2 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 3750 1600 2    60   Input ~ 0
in5
Text GLabel 3750 1750 2    60   Input ~ 0
in6
Text GLabel 3750 1900 2    60   Input ~ 0
in7
Text GLabel 3750 2050 2    60   Input ~ 0
in8
Text GLabel 10700 2500 2    60   Input ~ 0
in6
Text GLabel 10250 2400 2    60   Input ~ 0
in5
Text GLabel 10700 5350 2    60   Input ~ 0
in4
Text GLabel 10250 5250 2    60   Input ~ 0
in3
Text GLabel 10700 5150 2    60   Input ~ 0
in2
Text GLabel 10250 5050 2    60   Input ~ 0
in1
Text GLabel 10700 2700 2    60   Input ~ 0
in8
Text GLabel 10250 2600 2    60   Input ~ 0
in7
Text GLabel 3750 2200 2    60   Input ~ 0
in9
Text GLabel 3750 2350 2    60   Input ~ 0
in10
Text GLabel 3750 2500 2    60   Input ~ 0
in11
Text GLabel 3750 2650 2    60   Input ~ 0
in12
Text GLabel 10650 3100 2    60   Input ~ 0
in12
Text GLabel 10300 3000 2    60   Input ~ 0
in11
Text GLabel 10300 2800 2    60   Input ~ 0
in9
Text GLabel 10650 2900 2    60   Input ~ 0
in10
Text GLabel 3750 1000 2    60   Input ~ 0
in1
Text GLabel 3750 1150 2    60   Input ~ 0
in2
Text GLabel 3750 1300 2    60   Input ~ 0
in3
Text GLabel 3750 1450 2    60   Input ~ 0
in4
Text GLabel 3750 2800 2    60   Input ~ 0
in13
Text GLabel 3750 2950 2    60   Input ~ 0
in14
Text GLabel 3750 3100 2    60   Input ~ 0
in15
Text GLabel 3750 3250 2    60   Input ~ 0
in16
Text GLabel 10300 5450 2    60   Input ~ 0
in13
Text GLabel 10650 5550 2    60   Input ~ 0
in14
Text GLabel 10300 5650 2    60   Input ~ 0
in15
$Comp
L PCF8574A U7
U 1 1 572B2AA7
P 9400 5450
F 0 "U7" H 9050 6050 50  0000 L CNN
F 1 "PCF8574A" H 9500 6050 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 9400 5450 60  0001 C CNN
F 3 "" H 9400 5450 60  0000 C CNN
	1    9400 5450
	1    0    0    -1  
$EndComp
Text GLabel 10650 5750 2    60   Input ~ 0
in16
$Comp
L PCF8574A U8
U 1 1 572B2AAF
P 9400 2800
F 0 "U8" H 9050 3400 50  0000 L CNN
F 1 "PCF8574A" H 9500 3400 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 9400 2800 60  0001 C CNN
F 3 "" H 9400 2800 60  0000 C CNN
	1    9400 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 572B2AD2
P 9400 3500
F 0 "#PWR032" H 9400 3250 50  0001 C CNN
F 1 "GND" H 9400 3350 50  0000 C CNN
F 2 "" H 9400 3500 60  0000 C CNN
F 3 "" H 9400 3500 60  0000 C CNN
	1    9400 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 572B2AD8
P 9400 6150
F 0 "#PWR033" H 9400 5900 50  0001 C CNN
F 1 "GND" H 9400 6000 50  0000 C CNN
F 2 "" H 9400 6150 60  0000 C CNN
F 3 "" H 9400 6150 60  0000 C CNN
	1    9400 6150
	1    0    0    -1  
$EndComp
Text HLabel 8900 2400 0    60   Input ~ 0
I2C_SCL
Text HLabel 8350 2500 0    60   Input ~ 0
I2C_SDA
Text HLabel 8900 5050 0    60   Input ~ 0
I2C_SCL
Text HLabel 8350 5150 0    60   Input ~ 0
I2C_SDA
Text HLabel 8600 3200 0    60   Input ~ 0
INT
Text HLabel 8700 5850 0    60   Input ~ 0
INT
$Comp
L GND #PWR034
U 1 1 572AA068
P 8750 2950
F 0 "#PWR034" H 8750 2700 50  0001 C CNN
F 1 "GND" H 8750 2800 50  0000 C CNN
F 2 "" H 8750 2950 60  0000 C CNN
F 3 "" H 8750 2950 60  0000 C CNN
	1    8750 2950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 572AAB50
P 8800 5600
F 0 "#PWR035" H 8800 5350 50  0001 C CNN
F 1 "GND" H 8800 5450 50  0000 C CNN
F 2 "" H 8800 5600 60  0000 C CNN
F 3 "" H 8800 5600 60  0000 C CNN
	1    8800 5600
	1    0    0    -1  
$EndComp
$Comp
L PCF8574A U14
U 1 1 5767DB40
P 4950 6200
F 0 "U14" H 4600 6800 50  0000 L CNN
F 1 "PCF8574A" H 5050 6800 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 4950 6200 60  0001 C CNN
F 3 "" H 4950 6200 60  0000 C CNN
	1    4950 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR036
U 1 1 5767DB53
P 4950 6900
F 0 "#PWR036" H 4950 6650 50  0001 C CNN
F 1 "GND" H 4950 6750 50  0000 C CNN
F 2 "" H 4950 6900 60  0000 C CNN
F 3 "" H 4950 6900 60  0000 C CNN
	1    4950 6900
	1    0    0    -1  
$EndComp
Text HLabel 4450 5800 0    60   Input ~ 0
I2C2_SCL
Text HLabel 3900 5900 0    60   Input ~ 0
I2C2_SDA
Text HLabel 4250 6600 0    60   Input ~ 0
INT2
$Comp
L GND #PWR037
U 1 1 5767DB61
P 4350 6350
F 0 "#PWR037" H 4350 6100 50  0001 C CNN
F 1 "GND" H 4350 6200 50  0000 C CNN
F 2 "" H 4350 6350 60  0000 C CNN
F 3 "" H 4350 6350 60  0000 C CNN
	1    4350 6350
	1    0    0    -1  
$EndComp
$Sheet
S 2850 900  550  3800
U 5729E588
F0 "nucleo_shield_input" 60
F1 "nucleo_shield_input.sch" 60
F2 "in1" I R 3400 1000 60 
F3 "in2" I R 3400 1150 60 
F4 "in3" I R 3400 1300 60 
F5 "in4" I R 3400 1450 60 
F6 "in5" I R 3400 1600 60 
F7 "in6" I R 3400 1750 60 
F8 "in7" I R 3400 1900 60 
F9 "in8" I R 3400 2050 60 
F10 "in9" I R 3400 2200 60 
F11 "in10" I R 3400 2350 60 
F12 "in11" I R 3400 2500 60 
F13 "in12" I R 3400 2650 60 
F14 "in13" I R 3400 2800 60 
F15 "in14" I R 3400 2950 60 
F16 "in15" I R 3400 3100 60 
F17 "in16" I R 3400 3250 60 
F18 "in17" I R 3400 3400 60 
F19 "in18" I R 3400 3550 60 
F20 "in19" I R 3400 3700 60 
F21 "in20" I R 3400 3850 60 
F22 "in21" I R 3400 4000 60 
F23 "in22" I R 3400 4150 60 
F24 "in23" I R 3400 4300 60 
F25 "in24" I R 3400 4450 60 
$EndSheet
Text GLabel 6200 5900 2    60   Input ~ 0
in18
Text GLabel 5850 5800 2    60   Input ~ 0
in17
Text GLabel 5850 6000 2    60   Input ~ 0
in19
Text GLabel 6200 6100 2    60   Input ~ 0
in20
Text GLabel 6200 6300 2    60   Input ~ 0
in22
Text GLabel 5850 6200 2    60   Input ~ 0
in21
Text GLabel 5850 6400 2    60   Input ~ 0
in23
Text GLabel 6200 6500 2    60   Input ~ 0
in24
Text GLabel 3750 3550 2    60   Input ~ 0
in18
Text GLabel 3750 3400 2    60   Input ~ 0
in17
Text GLabel 3750 3700 2    60   Input ~ 0
in19
Text GLabel 3750 3850 2    60   Input ~ 0
in20
Text GLabel 3750 4300 2    60   Input ~ 0
in23
Text GLabel 3750 4450 2    60   Input ~ 0
in24
Text GLabel 3750 4150 2    60   Input ~ 0
in22
Text GLabel 3750 4000 2    60   Input ~ 0
in21
Wire Wire Line
	3400 1000 3750 1000
Wire Wire Line
	3750 1150 3400 1150
Wire Wire Line
	3400 1300 3750 1300
Wire Wire Line
	3750 1450 3400 1450
Wire Wire Line
	3400 1600 3750 1600
Wire Wire Line
	3750 1750 3400 1750
Wire Wire Line
	3400 1900 3750 1900
Wire Wire Line
	3750 2050 3400 2050
Wire Wire Line
	3400 2200 3750 2200
Wire Wire Line
	3750 2350 3400 2350
Wire Wire Line
	3400 2500 3750 2500
Wire Wire Line
	3750 2650 3400 2650
Wire Wire Line
	3400 2800 3750 2800
Wire Wire Line
	3750 2950 3400 2950
Wire Wire Line
	3400 3100 3750 3100
Wire Wire Line
	3750 3250 3400 3250
Wire Wire Line
	8350 2500 8900 2500
Wire Wire Line
	8350 5150 8900 5150
Wire Wire Line
	9900 5050 10250 5050
Wire Wire Line
	9900 5150 10700 5150
Wire Wire Line
	9900 5250 10250 5250
Wire Wire Line
	9900 5350 10700 5350
Wire Wire Line
	9900 2400 10250 2400
Wire Wire Line
	10700 2500 9900 2500
Wire Wire Line
	9900 2600 10250 2600
Wire Wire Line
	9900 2700 10700 2700
Wire Wire Line
	9400 2100 9400 1950
Wire Wire Line
	9400 4750 9400 4650
Wire Wire Line
	8600 3200 8900 3200
Wire Wire Line
	8700 5850 8900 5850
Wire Wire Line
	9900 2800 10300 2800
Wire Wire Line
	9900 2900 10650 2900
Wire Wire Line
	10300 3000 9900 3000
Wire Wire Line
	10650 3100 9900 3100
Wire Wire Line
	9900 5450 10300 5450
Wire Wire Line
	10650 5550 9900 5550
Wire Wire Line
	9900 5650 10300 5650
Wire Wire Line
	10650 5750 9900 5750
Wire Wire Line
	8900 2700 8750 2700
Wire Wire Line
	8750 2700 8750 2950
Wire Wire Line
	8900 2800 8750 2800
Connection ~ 8750 2800
Wire Wire Line
	8750 2900 8900 2900
Connection ~ 8750 2900
Wire Wire Line
	8900 5450 8800 5450
Wire Wire Line
	8800 5450 8800 5600
Wire Wire Line
	8900 5550 8800 5550
Connection ~ 8800 5550
Wire Wire Line
	8900 5350 8800 5350
Wire Wire Line
	3900 5900 4450 5900
Wire Wire Line
	4950 5500 4950 5400
Wire Wire Line
	4250 6600 4450 6600
Wire Wire Line
	4450 6200 4350 6200
Wire Wire Line
	4350 6100 4350 6350
Wire Wire Line
	4450 6300 4350 6300
Connection ~ 4350 6300
Wire Wire Line
	6200 6100 5450 6100
Wire Wire Line
	5850 6000 5450 6000
Wire Wire Line
	5450 5900 6200 5900
Wire Wire Line
	5450 5800 5850 5800
Wire Wire Line
	6200 6500 5450 6500
Wire Wire Line
	5850 6400 5450 6400
Wire Wire Line
	5450 6300 6200 6300
Wire Wire Line
	5450 6200 5850 6200
Wire Wire Line
	3750 3400 3400 3400
Wire Wire Line
	3400 3550 3750 3550
Wire Wire Line
	3750 3700 3400 3700
Wire Wire Line
	3400 3850 3750 3850
Wire Wire Line
	3750 4000 3400 4000
Wire Wire Line
	3400 4150 3750 4150
Wire Wire Line
	3750 4300 3400 4300
Wire Wire Line
	3400 4450 3750 4450
Wire Wire Line
	4450 6100 4350 6100
Connection ~ 4350 6200
$Comp
L +5V #PWR038
U 1 1 5785C417
P 4950 5400
F 0 "#PWR038" H 4950 5250 50  0001 C CNN
F 1 "+5V" H 4965 5573 50  0000 C CNN
F 2 "" H 4950 5400 50  0000 C CNN
F 3 "" H 4950 5400 50  0000 C CNN
	1    4950 5400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR039
U 1 1 5785C4C2
P 9400 4650
F 0 "#PWR039" H 9400 4500 50  0001 C CNN
F 1 "+5V" H 9415 4823 50  0000 C CNN
F 2 "" H 9400 4650 50  0000 C CNN
F 3 "" H 9400 4650 50  0000 C CNN
	1    9400 4650
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR040
U 1 1 5785C566
P 9400 1950
F 0 "#PWR040" H 9400 1800 50  0001 C CNN
F 1 "+5V" H 9415 2123 50  0000 C CNN
F 2 "" H 9400 1950 50  0000 C CNN
F 3 "" H 9400 1950 50  0000 C CNN
	1    9400 1950
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR041
U 1 1 5785F361
P 8800 5350
F 0 "#PWR041" H 8800 5200 50  0001 C CNN
F 1 "+5V" H 8815 5523 50  0000 C CNN
F 2 "" H 8800 5350 50  0000 C CNN
F 3 "" H 8800 5350 50  0000 C CNN
	1    8800 5350
	1    0    0    -1  
$EndComp
$EndSCHEMATC
