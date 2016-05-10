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
Sheet 4 4
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
P 2400 1300
F 0 "U3" H 2200 2000 50  0000 L CNN
F 1 "LTV-847" H 2400 2000 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 700 50  0000 L CIN
F 3 "" H 2400 1200 50  0000 L CNN
	1    2400 1300
	1    0    0    -1  
$EndComp
Text GLabel 1400 700  0    60   Input ~ 0
inh1
Text GLabel 1400 1000 0    60   Input ~ 0
inh2
Text GLabel 1400 1300 0    60   Input ~ 0
inh3
Text GLabel 1400 1600 0    60   Input ~ 0
inh4
Text GLabel 1350 3100 0    60   Input ~ 0
inh5
Text GLabel 1350 4000 0    60   Input ~ 0
inh8
$Comp
L LTV-847 U4
U 1 1 5728E41E
P 2350 3700
F 0 "U4" H 2150 4400 50  0000 L CNN
F 1 "LTV-847" H 2350 4400 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2150 3100 50  0000 L CIN
F 3 "" H 2350 3600 50  0000 L CNN
	1    2350 3700
	1    0    0    -1  
$EndComp
Text GLabel 1350 3700 0    60   Input ~ 0
inh7
Text GLabel 1350 3400 0    60   Input ~ 0
inh6
$Comp
L R R5
U 1 1 5728E427
P 1650 3100
F 0 "R5" V 1730 3100 50  0000 C CNN
F 1 "R" V 1650 3100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 3100 30  0001 C CNN
F 3 "" H 1650 3100 30  0000 C CNN
	1    1650 3100
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 5728E42E
P 1650 3400
F 0 "R6" V 1730 3400 50  0000 C CNN
F 1 "R" V 1650 3400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 3400 30  0001 C CNN
F 3 "" H 1650 3400 30  0000 C CNN
	1    1650 3400
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 5728E435
P 1650 3700
F 0 "R7" V 1730 3700 50  0000 C CNN
F 1 "R" V 1650 3700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 3700 30  0001 C CNN
F 3 "" H 1650 3700 30  0000 C CNN
	1    1650 3700
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 5728E43C
P 1650 4000
F 0 "R8" V 1730 4000 50  0000 C CNN
F 1 "R" V 1650 4000 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 4000 30  0001 C CNN
F 3 "" H 1650 4000 30  0000 C CNN
	1    1650 4000
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 5728E443
P 1700 1600
F 0 "R4" V 1780 1600 50  0000 C CNN
F 1 "R" V 1700 1600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1600 30  0001 C CNN
F 3 "" H 1700 1600 30  0000 C CNN
	1    1700 1600
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5728E44A
P 1700 1300
F 0 "R3" V 1780 1300 50  0000 C CNN
F 1 "R" V 1700 1300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1300 30  0001 C CNN
F 3 "" H 1700 1300 30  0000 C CNN
	1    1700 1300
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5728E451
P 1700 1000
F 0 "R2" V 1780 1000 50  0000 C CNN
F 1 "R" V 1700 1000 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1000 30  0001 C CNN
F 3 "" H 1700 1000 30  0000 C CNN
	1    1700 1000
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5728E458
P 1700 700
F 0 "R1" V 1780 700 50  0000 C CNN
F 1 "R" V 1700 700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 700 30  0001 C CNN
F 3 "" H 1700 700 30  0000 C CNN
	1    1700 700 
	0    1    1    0   
$EndComp
Text GLabel 1900 2100 0    60   Input ~ 0
GND_24V
Text GLabel 1850 4550 0    60   Input ~ 0
GND_24V
$Comp
L +3.3V #PWR043
U 1 1 5728E4BD
P 3100 3100
F 0 "#PWR043" H 3100 2950 50  0001 C CNN
F 1 "+3.3V" H 3100 3240 50  0000 C CNN
F 2 "" H 3100 3100 60  0000 C CNN
F 3 "" H 3100 3100 60  0000 C CNN
	1    3100 3100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR044
U 1 1 5728E4C3
P 3150 700
F 0 "#PWR044" H 3150 550 50  0001 C CNN
F 1 "+3.3V" H 3150 840 50  0000 C CNN
F 2 "" H 3150 700 60  0000 C CNN
F 3 "" H 3150 700 60  0000 C CNN
	1    3150 700 
	1    0    0    -1  
$EndComp
Text GLabel 1350 6400 0    60   Input ~ 0
inh9
Text GLabel 1350 5800 0    60   Input ~ 0
inh12
$Comp
L LTV-847 U5
U 1 1 5728E4F1
P 2350 6100
F 0 "U5" H 2150 6800 50  0000 L CNN
F 1 "LTV-847" H 2350 6800 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2150 5500 50  0000 L CIN
F 3 "" H 2350 6000 50  0000 L CNN
	1    2350 6100
	1    0    0    -1  
$EndComp
Text GLabel 1350 5500 0    60   Input ~ 0
inh11
Text GLabel 1350 6100 0    60   Input ~ 0
inh10
$Comp
L R R17
U 1 1 5728E4FA
P 1650 5500
F 0 "R17" V 1730 5500 50  0000 C CNN
F 1 "R" V 1650 5500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 5500 30  0001 C CNN
F 3 "" H 1650 5500 30  0000 C CNN
	1    1650 5500
	0    1    1    0   
$EndComp
$Comp
L R R18
U 1 1 5728E501
P 1650 5800
F 0 "R18" V 1730 5800 50  0000 C CNN
F 1 "R" V 1650 5800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 5800 30  0001 C CNN
F 3 "" H 1650 5800 30  0000 C CNN
	1    1650 5800
	0    1    1    0   
$EndComp
$Comp
L R R19
U 1 1 5728E508
P 1650 6100
F 0 "R19" V 1730 6100 50  0000 C CNN
F 1 "R" V 1650 6100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 6100 30  0001 C CNN
F 3 "" H 1650 6100 30  0000 C CNN
	1    1650 6100
	0    1    1    0   
$EndComp
$Comp
L R R20
U 1 1 5728E50F
P 1650 6400
F 0 "R20" V 1730 6400 50  0000 C CNN
F 1 "R" V 1650 6400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1580 6400 30  0001 C CNN
F 3 "" H 1650 6400 30  0000 C CNN
	1    1650 6400
	0    1    1    0   
$EndComp
Text GLabel 1850 6950 0    60   Input ~ 0
GND_24V
$Comp
L +3.3V #PWR045
U 1 1 5728E545
P 3100 5500
F 0 "#PWR045" H 3100 5350 50  0001 C CNN
F 1 "+3.3V" H 3100 5640 50  0000 C CNN
F 2 "" H 3100 5500 60  0000 C CNN
F 3 "" H 3100 5500 60  0000 C CNN
	1    3100 5500
	1    0    0    -1  
$EndComp
Text GLabel 6300 1900 2    60   Input ~ 0
GND_24V
Text GLabel 5950 1400 2    60   Input ~ 0
inh1
Text GLabel 6250 1300 2    60   Input ~ 0
inh2
Text GLabel 5950 1200 2    60   Input ~ 0
inh3
Text GLabel 6250 1100 2    60   Input ~ 0
inh4
Text GLabel 5950 1600 2    60   Input ~ 0
inh7
Text GLabel 6250 1700 2    60   Input ~ 0
inh6
Text GLabel 6250 1500 2    60   Input ~ 0
inh8
$Comp
L CONN_01X10 P1
U 1 1 5728E764
P 5450 1550
F 0 "P1" H 5450 2100 50  0000 C CNN
F 1 "CONN_INH1" V 5550 1550 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 5450 1550 60  0001 C CNN
F 3 "" H 5450 1550 60  0000 C CNN
	1    5450 1550
	-1   0    0    1   
$EndComp
Text GLabel 5950 1800 2    60   Input ~ 0
inh5
$Comp
L CONN_01X10 P5
U 1 1 5728E770
P 5450 2750
F 0 "P5" H 5450 3300 50  0000 C CNN
F 1 "CONN_INH2" V 5550 2750 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 5450 2750 60  0001 C CNN
F 3 "" H 5450 2750 60  0000 C CNN
	1    5450 2750
	-1   0    0    1   
$EndComp
Text GLabel 6350 3100 2    60   Input ~ 0
GND_24V
Text GLabel 6350 2300 2    60   Input ~ 0
inh9
Text GLabel 5900 2400 2    60   Input ~ 0
inh10
Text GLabel 5900 2600 2    60   Input ~ 0
inh11
Text GLabel 6350 2500 2    60   Input ~ 0
inh12
Text HLabel 3800 900  2    60   Input ~ 0
in1
Text HLabel 3800 1200 2    60   Input ~ 0
in2
Text HLabel 3800 1500 2    60   Input ~ 0
in3
Text HLabel 3800 1800 2    60   Input ~ 0
in4
Text HLabel 3800 3300 2    60   Input ~ 0
in5
Text HLabel 3800 3600 2    60   Input ~ 0
in6
Text HLabel 3800 3900 2    60   Input ~ 0
in7
Text HLabel 3800 4200 2    60   Input ~ 0
in8
Text HLabel 3800 5700 2    60   Input ~ 0
in9
Text HLabel 3800 6000 2    60   Input ~ 0
in10
Text HLabel 3800 6300 2    60   Input ~ 0
in11
Text GLabel 6350 2700 2    60   Input ~ 0
inh13
Text GLabel 5900 2800 2    60   Input ~ 0
inh14
Text GLabel 5900 3000 2    60   Input ~ 0
inh16
Text GLabel 6350 2900 2    60   Input ~ 0
inh15
Text HLabel 3800 6600 2    60   Input ~ 0
in12
Text GLabel 4950 5400 0    60   Input ~ 0
inh13
Text GLabel 4950 4500 0    60   Input ~ 0
inh16
$Comp
L LTV-847 U6
U 1 1 572A10A3
P 5950 5100
F 0 "U6" H 5750 5800 50  0000 L CNN
F 1 "LTV-847" H 5950 5800 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 5750 4500 50  0000 L CIN
F 3 "" H 5950 5000 50  0000 L CNN
	1    5950 5100
	1    0    0    -1  
$EndComp
Text GLabel 4950 4800 0    60   Input ~ 0
inh15
Text GLabel 4950 5100 0    60   Input ~ 0
inh14
$Comp
L R R25
U 1 1 572A10AB
P 5250 4500
F 0 "R25" V 5330 4500 50  0000 C CNN
F 1 "R" V 5250 4500 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5180 4500 30  0001 C CNN
F 3 "" H 5250 4500 30  0000 C CNN
	1    5250 4500
	0    1    1    0   
$EndComp
$Comp
L R R26
U 1 1 572A10B1
P 5250 4800
F 0 "R26" V 5330 4800 50  0000 C CNN
F 1 "R" V 5250 4800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5180 4800 30  0001 C CNN
F 3 "" H 5250 4800 30  0000 C CNN
	1    5250 4800
	0    1    1    0   
$EndComp
$Comp
L R R27
U 1 1 572A10B7
P 5250 5100
F 0 "R27" V 5330 5100 50  0000 C CNN
F 1 "R" V 5250 5100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5180 5100 30  0001 C CNN
F 3 "" H 5250 5100 30  0000 C CNN
	1    5250 5100
	0    1    1    0   
$EndComp
$Comp
L R R28
U 1 1 572A10BD
P 5250 5400
F 0 "R28" V 5330 5400 50  0000 C CNN
F 1 "R" V 5250 5400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5180 5400 30  0001 C CNN
F 3 "" H 5250 5400 30  0000 C CNN
	1    5250 5400
	0    1    1    0   
$EndComp
Text GLabel 5450 5950 0    60   Input ~ 0
GND_24V
$Comp
L +3.3V #PWR046
U 1 1 572A10F2
P 6700 4500
F 0 "#PWR046" H 6700 4350 50  0001 C CNN
F 1 "+3.3V" H 6700 4640 50  0000 C CNN
F 2 "" H 6700 4500 60  0000 C CNN
F 3 "" H 6700 4500 60  0000 C CNN
	1    6700 4500
	1    0    0    -1  
$EndComp
Text HLabel 7400 4700 2    60   Input ~ 0
in13
Text HLabel 7400 5000 2    60   Input ~ 0
in14
Text HLabel 7400 5300 2    60   Input ~ 0
in15
Text HLabel 7400 5600 2    60   Input ~ 0
in16
$Comp
L R R9
U 1 1 57319627
P 2950 2200
F 0 "R9" V 3030 2200 50  0000 C CNN
F 1 "R" V 2950 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2880 2200 30  0001 C CNN
F 3 "" H 2950 2200 30  0000 C CNN
	1    2950 2200
	-1   0    0    1   
$EndComp
$Comp
L R R12
U 1 1 5731969D
P 3150 2200
F 0 "R12" V 3230 2200 50  0000 C CNN
F 1 "R" V 3150 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3080 2200 30  0001 C CNN
F 3 "" H 3150 2200 30  0000 C CNN
	1    3150 2200
	-1   0    0    1   
$EndComp
$Comp
L R R15
U 1 1 573196E7
P 3350 2200
F 0 "R15" V 3430 2200 50  0000 C CNN
F 1 "R" V 3350 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 2200 30  0001 C CNN
F 3 "" H 3350 2200 30  0000 C CNN
	1    3350 2200
	-1   0    0    1   
$EndComp
$Comp
L R R22
U 1 1 5731972F
P 3550 2200
F 0 "R22" V 3630 2200 50  0000 C CNN
F 1 "R" V 3550 2200 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 2200 30  0001 C CNN
F 3 "" H 3550 2200 30  0000 C CNN
	1    3550 2200
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR047
U 1 1 57319FB5
P 3250 2600
F 0 "#PWR047" H 3250 2350 50  0001 C CNN
F 1 "GND" H 3250 2450 50  0000 C CNN
F 2 "" H 3250 2600 60  0000 C CNN
F 3 "" H 3250 2600 60  0000 C CNN
	1    3250 2600
	1    0    0    -1  
$EndComp
$Comp
L R R10
U 1 1 5731A42B
P 2950 4600
F 0 "R10" V 3030 4600 50  0000 C CNN
F 1 "R" V 2950 4600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2880 4600 30  0001 C CNN
F 3 "" H 2950 4600 30  0000 C CNN
	1    2950 4600
	-1   0    0    1   
$EndComp
$Comp
L R R13
U 1 1 5731A431
P 3150 4600
F 0 "R13" V 3230 4600 50  0000 C CNN
F 1 "R" V 3150 4600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3080 4600 30  0001 C CNN
F 3 "" H 3150 4600 30  0000 C CNN
	1    3150 4600
	-1   0    0    1   
$EndComp
$Comp
L R R16
U 1 1 5731A437
P 3350 4600
F 0 "R16" V 3430 4600 50  0000 C CNN
F 1 "R" V 3350 4600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 4600 30  0001 C CNN
F 3 "" H 3350 4600 30  0000 C CNN
	1    3350 4600
	-1   0    0    1   
$EndComp
$Comp
L R R23
U 1 1 5731A43D
P 3550 4600
F 0 "R23" V 3630 4600 50  0000 C CNN
F 1 "R" V 3550 4600 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 4600 30  0001 C CNN
F 3 "" H 3550 4600 30  0000 C CNN
	1    3550 4600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR048
U 1 1 5731A44E
P 3250 5000
F 0 "#PWR048" H 3250 4750 50  0001 C CNN
F 1 "GND" H 3250 4850 50  0000 C CNN
F 2 "" H 3250 5000 60  0000 C CNN
F 3 "" H 3250 5000 60  0000 C CNN
	1    3250 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 900  3800 900 
Wire Wire Line
	2700 1200 3800 1200
Wire Wire Line
	2700 1500 3800 1500
Wire Wire Line
	2700 1800 3800 1800
Wire Wire Line
	2650 3300 3800 3300
Wire Wire Line
	2650 3600 3800 3600
Wire Wire Line
	2650 3900 3800 3900
Wire Wire Line
	2650 4200 3800 4200
Wire Wire Line
	1850 700  2100 700 
Wire Wire Line
	1550 700  1400 700 
Wire Wire Line
	1400 1000 1550 1000
Wire Wire Line
	1850 1000 2100 1000
Wire Wire Line
	1850 1300 2100 1300
Wire Wire Line
	1550 1300 1400 1300
Wire Wire Line
	1400 1600 1550 1600
Wire Wire Line
	1850 1600 2100 1600
Wire Wire Line
	2050 3100 1800 3100
Wire Wire Line
	1500 3100 1350 3100
Wire Wire Line
	1350 3400 1500 3400
Wire Wire Line
	1800 3400 2050 3400
Wire Wire Line
	2050 3700 1800 3700
Wire Wire Line
	1350 3700 1500 3700
Wire Wire Line
	1350 4000 1500 4000
Wire Wire Line
	1800 4000 2050 4000
Wire Wire Line
	2000 1800 2100 1800
Wire Wire Line
	2000 900  2000 2100
Wire Wire Line
	2100 1500 2000 1500
Connection ~ 2000 1800
Wire Wire Line
	2100 1200 2000 1200
Connection ~ 2000 1500
Wire Wire Line
	2100 900  2000 900 
Connection ~ 2000 1200
Wire Wire Line
	1950 4200 2050 4200
Wire Wire Line
	1950 3300 1950 4550
Wire Wire Line
	2050 3900 1950 3900
Connection ~ 1950 4200
Wire Wire Line
	2050 3600 1950 3600
Connection ~ 1950 3900
Wire Wire Line
	2050 3300 1950 3300
Connection ~ 1950 3600
Wire Wire Line
	2700 700  3150 700 
Wire Wire Line
	2850 700  2850 1600
Wire Wire Line
	2850 1600 2700 1600
Connection ~ 2850 700 
Wire Wire Line
	2700 1300 2850 1300
Connection ~ 2850 1300
Wire Wire Line
	2700 1000 2850 1000
Connection ~ 2850 1000
Wire Wire Line
	2650 3100 3100 3100
Wire Wire Line
	2800 4000 2650 4000
Wire Wire Line
	2800 3100 2800 4000
Connection ~ 2800 3100
Wire Wire Line
	2650 3400 2800 3400
Connection ~ 2800 3400
Wire Wire Line
	2650 3700 2800 3700
Connection ~ 2800 3700
Wire Wire Line
	2000 2100 1900 2100
Wire Wire Line
	1950 4550 1850 4550
Wire Wire Line
	2650 6000 3800 6000
Wire Wire Line
	2650 6300 3800 6300
Wire Wire Line
	2650 6600 3800 6600
Wire Wire Line
	2050 5500 1800 5500
Wire Wire Line
	1500 5500 1350 5500
Wire Wire Line
	1350 5800 1500 5800
Wire Wire Line
	1800 5800 2050 5800
Wire Wire Line
	2050 6100 1800 6100
Wire Wire Line
	1350 6100 1500 6100
Wire Wire Line
	1350 6400 1500 6400
Wire Wire Line
	1800 6400 2050 6400
Wire Wire Line
	1950 6600 2050 6600
Wire Wire Line
	1950 5700 1950 6950
Wire Wire Line
	2050 6300 1950 6300
Connection ~ 1950 6600
Wire Wire Line
	2050 6000 1950 6000
Connection ~ 1950 6300
Wire Wire Line
	2050 5700 1950 5700
Connection ~ 1950 6000
Wire Wire Line
	2650 5500 3100 5500
Wire Wire Line
	2800 6400 2650 6400
Wire Wire Line
	2800 5500 2800 6400
Connection ~ 2800 5500
Wire Wire Line
	2650 5800 2800 5800
Connection ~ 2800 5800
Wire Wire Line
	2650 6100 2800 6100
Connection ~ 2800 6100
Wire Wire Line
	1950 6950 1850 6950
Wire Wire Line
	5950 1800 5650 1800
Wire Wire Line
	5650 1700 6250 1700
Wire Wire Line
	5950 1600 5650 1600
Wire Wire Line
	5650 1500 6250 1500
Wire Wire Line
	5950 1400 5650 1400
Wire Wire Line
	5650 1300 6250 1300
Wire Wire Line
	5950 1200 5650 1200
Wire Wire Line
	5650 1100 6250 1100
Wire Wire Line
	5650 1900 6300 1900
Wire Wire Line
	5650 2000 5850 2000
Wire Wire Line
	5850 2000 5850 1900
Connection ~ 5850 1900
Wire Wire Line
	6350 2500 5650 2500
Wire Wire Line
	5650 2600 5900 2600
Wire Wire Line
	5650 3100 6350 3100
Wire Wire Line
	5650 3200 6000 3200
Wire Wire Line
	6000 3200 6000 3100
Connection ~ 6000 3100
Wire Wire Line
	6350 2300 5650 2300
Wire Wire Line
	5650 2400 5900 2400
Wire Wire Line
	6350 2900 5650 2900
Wire Wire Line
	5650 3000 5900 3000
Wire Wire Line
	6350 2700 5650 2700
Wire Wire Line
	5650 2800 5900 2800
Wire Wire Line
	6250 4700 7400 4700
Wire Wire Line
	6250 5300 7400 5300
Wire Wire Line
	6250 5600 7400 5600
Wire Wire Line
	5650 4500 5400 4500
Wire Wire Line
	5100 4500 4950 4500
Wire Wire Line
	4950 4800 5100 4800
Wire Wire Line
	5400 4800 5650 4800
Wire Wire Line
	5650 5100 5400 5100
Wire Wire Line
	4950 5100 5100 5100
Wire Wire Line
	4950 5400 5100 5400
Wire Wire Line
	5400 5400 5650 5400
Wire Wire Line
	5550 5600 5650 5600
Wire Wire Line
	5550 4700 5550 5950
Wire Wire Line
	5650 5300 5550 5300
Connection ~ 5550 5600
Wire Wire Line
	5650 5000 5550 5000
Connection ~ 5550 5300
Wire Wire Line
	5650 4700 5550 4700
Connection ~ 5550 5000
Wire Wire Line
	6250 4500 6700 4500
Wire Wire Line
	6400 5400 6250 5400
Wire Wire Line
	6400 4500 6400 5400
Connection ~ 6400 4500
Wire Wire Line
	6250 4800 6400 4800
Connection ~ 6400 4800
Wire Wire Line
	6250 5100 6400 5100
Connection ~ 6400 5100
Wire Wire Line
	5550 5950 5450 5950
Wire Wire Line
	2650 5700 3800 5700
Wire Wire Line
	6250 5000 7400 5000
Wire Wire Line
	2950 2050 2950 1800
Connection ~ 2950 1800
Wire Wire Line
	3150 2050 3150 1500
Connection ~ 3150 1500
Wire Wire Line
	3350 2050 3350 1200
Connection ~ 3350 1200
Wire Wire Line
	3550 2050 3550 900 
Connection ~ 3550 900 
Wire Wire Line
	2950 2350 2950 2500
Wire Wire Line
	2950 2500 3550 2500
Wire Wire Line
	3550 2500 3550 2350
Wire Wire Line
	3350 2350 3350 2500
Connection ~ 3350 2500
Wire Wire Line
	3150 2350 3150 2500
Connection ~ 3150 2500
Wire Wire Line
	2950 4450 2950 4200
Wire Wire Line
	3150 4450 3150 3900
Wire Wire Line
	3350 4450 3350 3600
Wire Wire Line
	3550 4450 3550 3300
Wire Wire Line
	2950 4750 2950 4900
Wire Wire Line
	2950 4900 3550 4900
Wire Wire Line
	3550 4900 3550 4750
Wire Wire Line
	3350 4750 3350 4900
Connection ~ 3350 4900
Wire Wire Line
	3150 4750 3150 4900
Connection ~ 3150 4900
$Comp
L R R11
U 1 1 5731AB00
P 2950 7000
F 0 "R11" V 3030 7000 50  0000 C CNN
F 1 "R" V 2950 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 2880 7000 30  0001 C CNN
F 3 "" H 2950 7000 30  0000 C CNN
	1    2950 7000
	-1   0    0    1   
$EndComp
$Comp
L R R14
U 1 1 5731AB06
P 3150 7000
F 0 "R14" V 3230 7000 50  0000 C CNN
F 1 "R" V 3150 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3080 7000 30  0001 C CNN
F 3 "" H 3150 7000 30  0000 C CNN
	1    3150 7000
	-1   0    0    1   
$EndComp
$Comp
L R R21
U 1 1 5731AB0C
P 3350 7000
F 0 "R21" V 3430 7000 50  0000 C CNN
F 1 "R" V 3350 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3280 7000 30  0001 C CNN
F 3 "" H 3350 7000 30  0000 C CNN
	1    3350 7000
	-1   0    0    1   
$EndComp
$Comp
L R R24
U 1 1 5731AB12
P 3550 7000
F 0 "R24" V 3630 7000 50  0000 C CNN
F 1 "R" V 3550 7000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 3480 7000 30  0001 C CNN
F 3 "" H 3550 7000 30  0000 C CNN
	1    3550 7000
	-1   0    0    1   
$EndComp
Wire Wire Line
	2950 6850 2950 6600
Wire Wire Line
	3150 6850 3150 6300
Wire Wire Line
	3350 6850 3350 6000
Wire Wire Line
	3550 6850 3550 5700
Wire Wire Line
	2950 7150 2950 7300
Wire Wire Line
	2950 7300 3550 7300
Wire Wire Line
	3550 7300 3550 7150
Wire Wire Line
	3350 7150 3350 7300
Connection ~ 3350 7300
Wire Wire Line
	3150 7150 3150 7300
Connection ~ 3150 7300
$Comp
L R R29
U 1 1 5731ACE7
P 6550 6000
F 0 "R29" V 6630 6000 50  0000 C CNN
F 1 "R" V 6550 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6480 6000 30  0001 C CNN
F 3 "" H 6550 6000 30  0000 C CNN
	1    6550 6000
	-1   0    0    1   
$EndComp
$Comp
L R R30
U 1 1 5731ACED
P 6750 6000
F 0 "R30" V 6830 6000 50  0000 C CNN
F 1 "R" V 6750 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6680 6000 30  0001 C CNN
F 3 "" H 6750 6000 30  0000 C CNN
	1    6750 6000
	-1   0    0    1   
$EndComp
$Comp
L R R31
U 1 1 5731ACF3
P 6950 6000
F 0 "R31" V 7030 6000 50  0000 C CNN
F 1 "R" V 6950 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6880 6000 30  0001 C CNN
F 3 "" H 6950 6000 30  0000 C CNN
	1    6950 6000
	-1   0    0    1   
$EndComp
$Comp
L R R32
U 1 1 5731ACF9
P 7150 6000
F 0 "R32" V 7230 6000 50  0000 C CNN
F 1 "R" V 7150 6000 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 7080 6000 30  0001 C CNN
F 3 "" H 7150 6000 30  0000 C CNN
	1    7150 6000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR049
U 1 1 5731ACFF
P 6850 6600
F 0 "#PWR049" H 6850 6350 50  0001 C CNN
F 1 "GND" H 6850 6450 50  0000 C CNN
F 2 "" H 6850 6600 60  0000 C CNN
F 3 "" H 6850 6600 60  0000 C CNN
	1    6850 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 5850 6550 5600
Wire Wire Line
	6750 5850 6750 5300
Wire Wire Line
	6950 5850 6950 5000
Wire Wire Line
	7150 5850 7150 4700
Wire Wire Line
	6550 6150 6550 6300
Wire Wire Line
	6550 6300 7150 6300
Wire Wire Line
	7150 6300 7150 6150
Wire Wire Line
	6950 6150 6950 6300
Connection ~ 6950 6300
Wire Wire Line
	6750 6150 6750 6300
Connection ~ 6750 6300
Connection ~ 3550 3300
Connection ~ 3350 3600
Connection ~ 3150 3900
Connection ~ 2950 4200
Connection ~ 7150 4700
Connection ~ 6950 5000
Connection ~ 6750 5300
Connection ~ 6550 5600
Connection ~ 3550 5700
Connection ~ 3350 6000
Connection ~ 3150 6300
Connection ~ 2950 6600
Wire Wire Line
	3250 5000 3250 4900
Connection ~ 3250 4900
$Comp
L GND #PWR050
U 1 1 57320D19
P 3250 7400
F 0 "#PWR050" H 3250 7150 50  0001 C CNN
F 1 "GND" H 3250 7250 50  0000 C CNN
F 2 "" H 3250 7400 60  0000 C CNN
F 3 "" H 3250 7400 60  0000 C CNN
	1    3250 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 7400 3250 7300
Connection ~ 3250 7300
Wire Wire Line
	6850 6600 6850 6300
Connection ~ 6850 6300
Wire Wire Line
	3250 2500 3250 2600
Connection ~ 3250 2500
$EndSCHEMATC
