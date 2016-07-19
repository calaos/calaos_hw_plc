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
$Comp
L LTV-847 U3
U 1 1 5728E3C5
P 1900 1400
F 0 "U3" H 1700 2100 50  0000 L CNN
F 1 "LTV-847" H 1900 2100 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 1700 800 50  0000 L CIN
F 3 "" H 1900 1300 50  0000 L CNN
	1    1900 1400
	1    0    0    -1  
$EndComp
Text GLabel 900  800  0    60   Input ~ 0
inh1
Text GLabel 900  1100 0    60   Input ~ 0
inh2
Text GLabel 900  1400 0    60   Input ~ 0
inh3
Text GLabel 900  1700 0    60   Input ~ 0
inh4
Text GLabel 850  3200 0    60   Input ~ 0
inh5
Text GLabel 850  4100 0    60   Input ~ 0
inh8
$Comp
L LTV-847 U4
U 1 1 5728E41E
P 1850 3800
F 0 "U4" H 1650 4500 50  0000 L CNN
F 1 "LTV-847" H 1850 4500 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 1650 3200 50  0000 L CIN
F 3 "" H 1850 3700 50  0000 L CNN
	1    1850 3800
	1    0    0    -1  
$EndComp
Text GLabel 850  3800 0    60   Input ~ 0
inh7
Text GLabel 850  3500 0    60   Input ~ 0
inh6
$Comp
L R R5
U 1 1 5728E427
P 1150 3200
F 0 "R5" V 1230 3200 50  0000 C CNN
F 1 "R" V 1150 3200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 3200 30  0001 C CNN
F 3 "" H 1150 3200 30  0000 C CNN
	1    1150 3200
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5728E42E
P 1150 3500
F 0 "R6" V 1230 3500 50  0000 C CNN
F 1 "R" V 1150 3500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 3500 30  0001 C CNN
F 3 "" H 1150 3500 30  0000 C CNN
	1    1150 3500
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5728E435
P 1150 3800
F 0 "R7" V 1230 3800 50  0000 C CNN
F 1 "R" V 1150 3800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 3800 30  0001 C CNN
F 3 "" H 1150 3800 30  0000 C CNN
	1    1150 3800
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 5728E43C
P 1150 4100
F 0 "R8" V 1230 4100 50  0000 C CNN
F 1 "R" V 1150 4100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 4100 30  0001 C CNN
F 3 "" H 1150 4100 30  0000 C CNN
	1    1150 4100
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5728E443
P 1200 1700
F 0 "R4" V 1280 1700 50  0000 C CNN
F 1 "R" V 1200 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1130 1700 30  0001 C CNN
F 3 "" H 1200 1700 30  0000 C CNN
	1    1200 1700
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5728E44A
P 1200 1400
F 0 "R3" V 1280 1400 50  0000 C CNN
F 1 "R" V 1200 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1130 1400 30  0001 C CNN
F 3 "" H 1200 1400 30  0000 C CNN
	1    1200 1400
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5728E451
P 1200 1100
F 0 "R2" V 1280 1100 50  0000 C CNN
F 1 "R" V 1200 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1130 1100 30  0001 C CNN
F 3 "" H 1200 1100 30  0000 C CNN
	1    1200 1100
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5728E458
P 1200 800
F 0 "R1" V 1280 800 50  0000 C CNN
F 1 "R" V 1200 800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1130 800 30  0001 C CNN
F 3 "" H 1200 800 30  0000 C CNN
	1    1200 800 
	0    1    1    0   
$EndComp
Text GLabel 1400 2200 0    60   Input ~ 0
GND_24V
Text GLabel 1350 4650 0    60   Input ~ 0
GND_24V
Text GLabel 850  6500 0    60   Input ~ 0
inh9
Text GLabel 850  5900 0    60   Input ~ 0
inh12
$Comp
L LTV-847 U5
U 1 1 5728E4F1
P 1850 6200
F 0 "U5" H 1650 6900 50  0000 L CNN
F 1 "LTV-847" H 1850 6900 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 1650 5600 50  0000 L CIN
F 3 "" H 1850 6100 50  0000 L CNN
	1    1850 6200
	1    0    0    -1  
$EndComp
Text GLabel 850  5600 0    60   Input ~ 0
inh11
Text GLabel 850  6200 0    60   Input ~ 0
inh10
$Comp
L R R17
U 1 1 5728E4FA
P 1150 5600
F 0 "R17" V 1230 5600 50  0000 C CNN
F 1 "R" V 1150 5600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 5600 30  0001 C CNN
F 3 "" H 1150 5600 30  0000 C CNN
	1    1150 5600
	0    1    1    0   
$EndComp
$Comp
L R R18
U 1 1 5728E501
P 1150 5900
F 0 "R18" V 1230 5900 50  0000 C CNN
F 1 "R" V 1150 5900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 5900 30  0001 C CNN
F 3 "" H 1150 5900 30  0000 C CNN
	1    1150 5900
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 5728E508
P 1150 6200
F 0 "R19" V 1230 6200 50  0000 C CNN
F 1 "R" V 1150 6200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 6200 30  0001 C CNN
F 3 "" H 1150 6200 30  0000 C CNN
	1    1150 6200
	0    1    1    0   
$EndComp
$Comp
L R R20
U 1 1 5728E50F
P 1150 6500
F 0 "R20" V 1230 6500 50  0000 C CNN
F 1 "R" V 1150 6500 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 1080 6500 30  0001 C CNN
F 3 "" H 1150 6500 30  0000 C CNN
	1    1150 6500
	0    1    1    0   
$EndComp
Text GLabel 1350 7050 0    60   Input ~ 0
GND_24V
Text GLabel 9050 1700 2    60   Input ~ 0
inh1
Text GLabel 9350 1600 2    60   Input ~ 0
inh2
Text GLabel 9050 1500 2    60   Input ~ 0
inh3
Text GLabel 9350 1400 2    60   Input ~ 0
inh4
Text GLabel 9050 1900 2    60   Input ~ 0
inh7
Text GLabel 9350 2000 2    60   Input ~ 0
inh6
Text GLabel 9350 1800 2    60   Input ~ 0
inh8
$Comp
L CONN_01X08 P1
U 1 1 5728E764
P 8550 1750
F 0 "P1" H 8550 2300 50  0000 C CNN
F 1 "CONN_INH1" V 8650 1750 50  0000 C CNN
F 2 "w_conn_screw:mors_8p" H 8550 1750 60  0001 C CNN
F 3 "" H 8550 1750 60  0000 C CNN
	1    8550 1750
	-1   0    0    1   
$EndComp
Text GLabel 9050 2100 2    60   Input ~ 0
inh5
$Comp
L CONN_01X08 P5
U 1 1 5728E770
P 8550 2950
F 0 "P5" H 8550 3450 50  0000 C CNN
F 1 "CONN_INH2" V 8650 2950 50  0000 C CNN
F 2 "w_conn_screw:mors_8p" H 8550 2950 60  0001 C CNN
F 3 "" H 8550 2950 60  0000 C CNN
	1    8550 2950
	-1   0    0    1   
$EndComp
Text GLabel 9450 2600 2    60   Input ~ 0
inh9
Text GLabel 9000 2700 2    60   Input ~ 0
inh10
Text GLabel 9000 2900 2    60   Input ~ 0
inh11
Text GLabel 9450 2800 2    60   Input ~ 0
inh12
Text HLabel 2850 800  2    60   Input ~ 0
in1
Text HLabel 2850 1100 2    60   Input ~ 0
in2
Text HLabel 2850 1400 2    60   Input ~ 0
in3
Text HLabel 2850 1700 2    60   Input ~ 0
in4
Text HLabel 2800 3200 2    60   Input ~ 0
in5
Text HLabel 2800 3500 2    60   Input ~ 0
in6
Text HLabel 2800 3800 2    60   Input ~ 0
in7
Text HLabel 2800 4100 2    60   Input ~ 0
in8
Text HLabel 2900 5600 2    60   Input ~ 0
in9
Text HLabel 2900 5900 2    60   Input ~ 0
in10
Text HLabel 2900 6200 2    60   Input ~ 0
in11
Text GLabel 9450 3000 2    60   Input ~ 0
inh13
Text GLabel 9000 3100 2    60   Input ~ 0
inh14
Text GLabel 9000 3300 2    60   Input ~ 0
inh16
Text GLabel 9450 3200 2    60   Input ~ 0
inh15
Text HLabel 2900 6500 2    60   Input ~ 0
in12
Text GLabel 4100 6450 0    60   Input ~ 0
inh13
Text GLabel 4100 5550 0    60   Input ~ 0
inh16
$Comp
L LTV-847 U6
U 1 1 572A10A3
P 5100 6150
F 0 "U6" H 4900 6850 50  0000 L CNN
F 1 "LTV-847" H 5100 6850 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 4900 5550 50  0000 L CIN
F 3 "" H 5100 6050 50  0000 L CNN
	1    5100 6150
	1    0    0    -1  
$EndComp
Text GLabel 4100 5850 0    60   Input ~ 0
inh15
Text GLabel 4100 6150 0    60   Input ~ 0
inh14
$Comp
L R R25
U 1 1 572A10AB
P 4400 5550
F 0 "R25" V 4480 5550 50  0000 C CNN
F 1 "R" V 4400 5550 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4330 5550 30  0001 C CNN
F 3 "" H 4400 5550 30  0000 C CNN
	1    4400 5550
	0    1    1    0   
$EndComp
$Comp
L R R26
U 1 1 572A10B1
P 4400 5850
F 0 "R26" V 4480 5850 50  0000 C CNN
F 1 "R" V 4400 5850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4330 5850 30  0001 C CNN
F 3 "" H 4400 5850 30  0000 C CNN
	1    4400 5850
	0    1    1    0   
$EndComp
$Comp
L R R27
U 1 1 572A10B7
P 4400 6150
F 0 "R27" V 4480 6150 50  0000 C CNN
F 1 "R" V 4400 6150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4330 6150 30  0001 C CNN
F 3 "" H 4400 6150 30  0000 C CNN
	1    4400 6150
	0    1    1    0   
$EndComp
$Comp
L R R28
U 1 1 572A10BD
P 4400 6450
F 0 "R28" V 4480 6450 50  0000 C CNN
F 1 "R" V 4400 6450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4330 6450 30  0001 C CNN
F 3 "" H 4400 6450 30  0000 C CNN
	1    4400 6450
	0    1    1    0   
$EndComp
Text GLabel 4600 7000 0    60   Input ~ 0
GND_24V
Text HLabel 6150 5550 2    60   Input ~ 0
in13
Text HLabel 6150 5850 2    60   Input ~ 0
in14
Text HLabel 6150 6150 2    60   Input ~ 0
in15
Text HLabel 6150 6450 2    60   Input ~ 0
in16
$Comp
L GND #PWR042
U 1 1 5731A44E
P 2600 3400
F 0 "#PWR042" H 2600 3150 50  0001 C CNN
F 1 "GND" H 2600 3250 50  0000 C CNN
F 2 "" H 2600 3400 60  0000 C CNN
F 3 "" H 2600 3400 60  0000 C CNN
	1    2600 3400
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 1100 2850 1100
Wire Wire Line
	2200 1400 2850 1400
Wire Wire Line
	2200 1700 2850 1700
Wire Wire Line
	2150 3500 2800 3500
Wire Wire Line
	2150 3800 2800 3800
Wire Wire Line
	2150 4100 2800 4100
Wire Wire Line
	1350 800  1600 800 
Wire Wire Line
	1050 800  900  800 
Wire Wire Line
	900  1100 1050 1100
Wire Wire Line
	1350 1100 1600 1100
Wire Wire Line
	1350 1400 1600 1400
Wire Wire Line
	1050 1400 900  1400
Wire Wire Line
	900  1700 1050 1700
Wire Wire Line
	1350 1700 1600 1700
Wire Wire Line
	1550 3200 1300 3200
Wire Wire Line
	1000 3200 850  3200
Wire Wire Line
	850  3500 1000 3500
Wire Wire Line
	1300 3500 1550 3500
Wire Wire Line
	1550 3800 1300 3800
Wire Wire Line
	850  3800 1000 3800
Wire Wire Line
	850  4100 1000 4100
Wire Wire Line
	1300 4100 1550 4100
Wire Wire Line
	1500 1900 1600 1900
Wire Wire Line
	1500 1000 1500 2200
Wire Wire Line
	1600 1600 1500 1600
Connection ~ 1500 1900
Wire Wire Line
	1600 1300 1500 1300
Connection ~ 1500 1600
Wire Wire Line
	1600 1000 1500 1000
Connection ~ 1500 1300
Wire Wire Line
	1450 4300 1550 4300
Wire Wire Line
	1450 3400 1450 4650
Wire Wire Line
	1550 4000 1450 4000
Connection ~ 1450 4300
Wire Wire Line
	1550 3700 1450 3700
Connection ~ 1450 4000
Wire Wire Line
	1550 3400 1450 3400
Connection ~ 1450 3700
Wire Wire Line
	2200 1000 2650 1000
Wire Wire Line
	2350 1000 2350 1900
Wire Wire Line
	2350 1900 2200 1900
Connection ~ 2350 1000
Wire Wire Line
	2200 1600 2350 1600
Connection ~ 2350 1600
Wire Wire Line
	2200 1300 2350 1300
Connection ~ 2350 1300
Wire Wire Line
	2150 3400 2600 3400
Wire Wire Line
	2300 4300 2150 4300
Wire Wire Line
	2300 3400 2300 4300
Connection ~ 2300 3400
Wire Wire Line
	2150 3700 2300 3700
Connection ~ 2300 3700
Wire Wire Line
	2150 4000 2300 4000
Connection ~ 2300 4000
Wire Wire Line
	1500 2200 1400 2200
Wire Wire Line
	1450 4650 1350 4650
Wire Wire Line
	2150 5900 2900 5900
Wire Wire Line
	2150 6200 2900 6200
Wire Wire Line
	2150 6500 2900 6500
Wire Wire Line
	1550 5600 1300 5600
Wire Wire Line
	1000 5600 850  5600
Wire Wire Line
	850  5900 1000 5900
Wire Wire Line
	1300 5900 1550 5900
Wire Wire Line
	1550 6200 1300 6200
Wire Wire Line
	850  6200 1000 6200
Wire Wire Line
	850  6500 1000 6500
Wire Wire Line
	1300 6500 1550 6500
Wire Wire Line
	1450 6700 1550 6700
Wire Wire Line
	1450 5800 1450 7050
Wire Wire Line
	1550 6400 1450 6400
Connection ~ 1450 6700
Wire Wire Line
	1550 6100 1450 6100
Connection ~ 1450 6400
Wire Wire Line
	1550 5800 1450 5800
Connection ~ 1450 6100
Wire Wire Line
	2150 5800 2600 5800
Wire Wire Line
	2300 6700 2150 6700
Wire Wire Line
	2300 5800 2300 6700
Connection ~ 2300 5800
Wire Wire Line
	2150 6100 2300 6100
Connection ~ 2300 6100
Wire Wire Line
	2150 6400 2300 6400
Connection ~ 2300 6400
Wire Wire Line
	1450 7050 1350 7050
Wire Wire Line
	9050 2100 8750 2100
Wire Wire Line
	8750 2000 9350 2000
Wire Wire Line
	9050 1900 8750 1900
Wire Wire Line
	8750 1800 9350 1800
Wire Wire Line
	9050 1700 8750 1700
Wire Wire Line
	8750 1600 9350 1600
Wire Wire Line
	9050 1500 8750 1500
Wire Wire Line
	8750 1400 9350 1400
Wire Wire Line
	9450 2800 8750 2800
Wire Wire Line
	8750 2900 9000 2900
Wire Wire Line
	9450 2600 8750 2600
Wire Wire Line
	8750 2700 9000 2700
Wire Wire Line
	9450 3200 8750 3200
Wire Wire Line
	8750 3300 9000 3300
Wire Wire Line
	9450 3000 8750 3000
Wire Wire Line
	8750 3100 9000 3100
Wire Wire Line
	5400 5550 6150 5550
Wire Wire Line
	5400 6150 6150 6150
Wire Wire Line
	5400 6450 6150 6450
Wire Wire Line
	4800 5550 4550 5550
Wire Wire Line
	4250 5550 4100 5550
Wire Wire Line
	4100 5850 4250 5850
Wire Wire Line
	4550 5850 4800 5850
Wire Wire Line
	4800 6150 4550 6150
Wire Wire Line
	4100 6150 4250 6150
Wire Wire Line
	4100 6450 4250 6450
Wire Wire Line
	4550 6450 4800 6450
Wire Wire Line
	4700 6650 4800 6650
Wire Wire Line
	4700 5750 4700 7000
Wire Wire Line
	4800 6350 4700 6350
Connection ~ 4700 6650
Wire Wire Line
	4800 6050 4700 6050
Connection ~ 4700 6350
Wire Wire Line
	4800 5750 4700 5750
Connection ~ 4700 6050
Wire Wire Line
	5400 5750 5850 5750
Wire Wire Line
	5550 6650 5400 6650
Wire Wire Line
	5550 5750 5550 6650
Connection ~ 5550 5750
Wire Wire Line
	5400 6050 5550 6050
Connection ~ 5550 6050
Wire Wire Line
	5400 6350 5550 6350
Connection ~ 5550 6350
Wire Wire Line
	4700 7000 4600 7000
Wire Wire Line
	2150 5600 2900 5600
Wire Wire Line
	5400 5850 6150 5850
$Comp
L CONN_01X08 P17
U 1 1 5768B004
P 8550 4050
F 0 "P17" H 8550 4550 50  0000 C CNN
F 1 "CONN_INH3" V 8650 4050 50  0000 C CNN
F 2 "w_conn_screw:mors_8p" H 8550 4050 60  0001 C CNN
F 3 "" H 8550 4050 60  0000 C CNN
	1    8550 4050
	-1   0    0    1   
$EndComp
Text GLabel 9450 3700 2    60   Input ~ 0
inh17
Text GLabel 9000 3800 2    60   Input ~ 0
inh18
Text GLabel 9000 4000 2    60   Input ~ 0
inh20
Text GLabel 9450 3900 2    60   Input ~ 0
inh19
Text GLabel 9450 4100 2    60   Input ~ 0
inh21
Text GLabel 9000 4200 2    60   Input ~ 0
inh22
Text GLabel 9000 4400 2    60   Input ~ 0
inh24
Text GLabel 9450 4300 2    60   Input ~ 0
inh23
Wire Wire Line
	9450 3900 8750 3900
Wire Wire Line
	8750 4000 9000 4000
Wire Wire Line
	9450 3700 8750 3700
Wire Wire Line
	8750 3800 9000 3800
Wire Wire Line
	9450 4300 8750 4300
Wire Wire Line
	8750 4400 9000 4400
Wire Wire Line
	9450 4100 8750 4100
Wire Wire Line
	8750 4200 9000 4200
$Comp
L LTV-847 U16
U 1 1 5768DC4F
P 5400 1400
F 0 "U16" H 5200 2100 50  0000 L CNN
F 1 "LTV-847" H 5400 2100 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 5200 800 50  0000 L CIN
F 3 "" H 5400 1300 50  0000 L CNN
	1    5400 1400
	1    0    0    -1  
$EndComp
$Comp
L R R40
U 1 1 5768DC57
P 4700 800
F 0 "R40" V 4780 800 50  0000 C CNN
F 1 "R" V 4700 800 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4630 800 30  0001 C CNN
F 3 "" H 4700 800 30  0000 C CNN
	1    4700 800 
	0    1    1    0   
$EndComp
$Comp
L R R41
U 1 1 5768DC5D
P 4700 1100
F 0 "R41" V 4780 1100 50  0000 C CNN
F 1 "R" V 4700 1100 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4630 1100 30  0001 C CNN
F 3 "" H 4700 1100 30  0000 C CNN
	1    4700 1100
	0    1    1    0   
$EndComp
$Comp
L R R42
U 1 1 5768DC63
P 4700 1400
F 0 "R42" V 4780 1400 50  0000 C CNN
F 1 "R" V 4700 1400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4630 1400 30  0001 C CNN
F 3 "" H 4700 1400 30  0000 C CNN
	1    4700 1400
	0    1    1    0   
$EndComp
$Comp
L R R43
U 1 1 5768DC69
P 4700 1700
F 0 "R43" V 4780 1700 50  0000 C CNN
F 1 "R" V 4700 1700 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4630 1700 30  0001 C CNN
F 3 "" H 4700 1700 30  0000 C CNN
	1    4700 1700
	0    1    1    0   
$EndComp
Text GLabel 4900 2250 0    60   Input ~ 0
GND_24V
Text HLabel 6250 4050 2    60   Input ~ 0
in17
Text HLabel 6250 3750 2    60   Input ~ 0
in18
Text HLabel 6250 3450 2    60   Input ~ 0
in19
Text HLabel 6250 3150 2    60   Input ~ 0
in20
Wire Wire Line
	5700 800  6350 800 
Wire Wire Line
	5700 1400 6350 1400
Wire Wire Line
	5700 1700 6350 1700
Wire Wire Line
	5100 800  4850 800 
Wire Wire Line
	4550 800  4400 800 
Wire Wire Line
	4400 1100 4550 1100
Wire Wire Line
	4850 1100 5100 1100
Wire Wire Line
	5100 1400 4850 1400
Wire Wire Line
	4400 1400 4550 1400
Wire Wire Line
	4400 1700 4550 1700
Wire Wire Line
	4850 1700 5100 1700
Wire Wire Line
	5000 1900 5100 1900
Wire Wire Line
	5000 1000 5000 2250
Wire Wire Line
	5100 1600 5000 1600
Connection ~ 5000 1900
Wire Wire Line
	5100 1300 5000 1300
Connection ~ 5000 1600
Wire Wire Line
	5100 1000 5000 1000
Connection ~ 5000 1300
Wire Wire Line
	5700 1000 6150 1000
Wire Wire Line
	5850 1900 5700 1900
Wire Wire Line
	5850 1000 5850 1900
Connection ~ 5850 1000
Wire Wire Line
	5700 1300 5850 1300
Connection ~ 5850 1300
Wire Wire Line
	5700 1600 5850 1600
Connection ~ 5850 1600
Wire Wire Line
	5000 2250 4900 2250
Wire Wire Line
	5700 1100 6350 1100
$Comp
L GND #PWR043
U 1 1 5768DCAF
P 6000 3350
F 0 "#PWR043" H 6000 3100 50  0001 C CNN
F 1 "GND" H 6000 3200 50  0000 C CNN
F 2 "" H 6000 3350 60  0000 C CNN
F 3 "" H 6000 3350 60  0000 C CNN
	1    6000 3350
	-1   0    0    1   
$EndComp
Text GLabel 4400 1700 0    60   Input ~ 0
inh17
Text GLabel 4400 1400 0    60   Input ~ 0
inh18
Text GLabel 4400 1100 0    60   Input ~ 0
inh19
Text GLabel 4400 800  0    60   Input ~ 0
inh20
$Comp
L LTV-847 U15
U 1 1 57690D5C
P 5250 3750
F 0 "U15" H 5050 4450 50  0000 L CNN
F 1 "LTV-847" H 5250 4450 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 5050 3150 50  0000 L CIN
F 3 "" H 5250 3650 50  0000 L CNN
	1    5250 3750
	1    0    0    -1  
$EndComp
$Comp
L R R34
U 1 1 57690D62
P 4550 3150
F 0 "R34" V 4630 3150 50  0000 C CNN
F 1 "R" V 4550 3150 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4480 3150 30  0001 C CNN
F 3 "" H 4550 3150 30  0000 C CNN
	1    4550 3150
	0    1    1    0   
$EndComp
$Comp
L R R37
U 1 1 57690D68
P 4550 3450
F 0 "R37" V 4630 3450 50  0000 C CNN
F 1 "R" V 4550 3450 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4480 3450 30  0001 C CNN
F 3 "" H 4550 3450 30  0000 C CNN
	1    4550 3450
	0    1    1    0   
$EndComp
$Comp
L R R38
U 1 1 57690D6E
P 4550 3750
F 0 "R38" V 4630 3750 50  0000 C CNN
F 1 "R" V 4550 3750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4480 3750 30  0001 C CNN
F 3 "" H 4550 3750 30  0000 C CNN
	1    4550 3750
	0    1    1    0   
$EndComp
$Comp
L R R39
U 1 1 57690D74
P 4550 4050
F 0 "R39" V 4630 4050 50  0000 C CNN
F 1 "R" V 4550 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 4480 4050 30  0001 C CNN
F 3 "" H 4550 4050 30  0000 C CNN
	1    4550 4050
	0    1    1    0   
$EndComp
Text GLabel 4750 4600 0    60   Input ~ 0
GND_24V
Text HLabel 6350 800  2    60   Input ~ 0
in21
Text HLabel 6350 1100 2    60   Input ~ 0
in22
Text HLabel 6350 1400 2    60   Input ~ 0
in23
Text HLabel 6350 1700 2    60   Input ~ 0
in24
Wire Wire Line
	5550 3150 6250 3150
Wire Wire Line
	5550 3750 6250 3750
Wire Wire Line
	5550 4050 6250 4050
Wire Wire Line
	4950 3150 4700 3150
Wire Wire Line
	4400 3150 4250 3150
Wire Wire Line
	4250 3450 4400 3450
Wire Wire Line
	4700 3450 4950 3450
Wire Wire Line
	4950 3750 4700 3750
Wire Wire Line
	4250 3750 4400 3750
Wire Wire Line
	4250 4050 4400 4050
Wire Wire Line
	4700 4050 4950 4050
Wire Wire Line
	4850 4250 4950 4250
Wire Wire Line
	4850 3350 4850 4600
Wire Wire Line
	4950 3950 4850 3950
Connection ~ 4850 4250
Wire Wire Line
	4950 3650 4850 3650
Connection ~ 4850 3950
Wire Wire Line
	4950 3350 4850 3350
Connection ~ 4850 3650
Wire Wire Line
	5550 3350 6000 3350
Wire Wire Line
	5700 4250 5550 4250
Wire Wire Line
	5700 3350 5700 4250
Connection ~ 5700 3350
Wire Wire Line
	5550 3650 5700 3650
Connection ~ 5700 3650
Wire Wire Line
	5550 3950 5700 3950
Connection ~ 5700 3950
Wire Wire Line
	4850 4600 4750 4600
Wire Wire Line
	5550 3450 6250 3450
Text GLabel 4250 4050 0    60   Input ~ 0
inh21
Text GLabel 4250 3750 0    60   Input ~ 0
inh22
Text GLabel 4250 3450 0    60   Input ~ 0
inh23
Text GLabel 4250 3150 0    60   Input ~ 0
inh24
Wire Wire Line
	2150 3200 2800 3200
$Comp
L GND #PWR044
U 1 1 5785776E
P 5850 5750
F 0 "#PWR044" H 5850 5500 50  0001 C CNN
F 1 "GND" H 5850 5600 50  0000 C CNN
F 2 "" H 5850 5750 60  0000 C CNN
F 3 "" H 5850 5750 60  0000 C CNN
	1    5850 5750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR045
U 1 1 57857800
P 2600 5800
F 0 "#PWR045" H 2600 5550 50  0001 C CNN
F 1 "GND" H 2600 5650 50  0000 C CNN
F 2 "" H 2600 5800 60  0000 C CNN
F 3 "" H 2600 5800 60  0000 C CNN
	1    2600 5800
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 800  2850 800 
$Comp
L GND #PWR046
U 1 1 57858983
P 6150 1000
F 0 "#PWR046" H 6150 750 50  0001 C CNN
F 1 "GND" H 6150 850 50  0000 C CNN
F 2 "" H 6150 1000 60  0000 C CNN
F 3 "" H 6150 1000 60  0000 C CNN
	1    6150 1000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR047
U 1 1 57858AA2
P 2650 1000
F 0 "#PWR047" H 2650 750 50  0001 C CNN
F 1 "GND" H 2650 850 50  0000 C CNN
F 2 "" H 2650 1000 60  0000 C CNN
F 3 "" H 2650 1000 60  0000 C CNN
	1    2650 1000
	-1   0    0    1   
$EndComp
$EndSCHEMATC
