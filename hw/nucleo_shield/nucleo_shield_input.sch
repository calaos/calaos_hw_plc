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
P 2400 1400
F 0 "U3" H 2200 2100 50  0000 L CNN
F 1 "LTV-847" H 2400 2100 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 800 50  0000 L CIN
F 3 "" H 2400 1300 50  0000 L CNN
	1    2400 1400
	1    0    0    -1  
$EndComp
Text GLabel 1400 800  0    60   Input ~ 0
inh1
Text GLabel 1400 1100 0    60   Input ~ 0
inh2
Text GLabel 1400 1400 0    60   Input ~ 0
inh3
Text GLabel 1400 1700 0    60   Input ~ 0
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
P 1700 1700
F 0 "R4" V 1780 1700 50  0000 C CNN
F 1 "R" V 1700 1700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1700 30  0001 C CNN
F 3 "" H 1700 1700 30  0000 C CNN
	1    1700 1700
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 5728E44A
P 1700 1400
F 0 "R3" V 1780 1400 50  0000 C CNN
F 1 "R" V 1700 1400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1400 30  0001 C CNN
F 3 "" H 1700 1400 30  0000 C CNN
	1    1700 1400
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5728E451
P 1700 1100
F 0 "R2" V 1780 1100 50  0000 C CNN
F 1 "R" V 1700 1100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 1100 30  0001 C CNN
F 3 "" H 1700 1100 30  0000 C CNN
	1    1700 1100
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5728E458
P 1700 800
F 0 "R1" V 1780 800 50  0000 C CNN
F 1 "R" V 1700 800 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 1630 800 30  0001 C CNN
F 3 "" H 1700 800 30  0000 C CNN
	1    1700 800 
	0    1    1    0   
$EndComp
Text GLabel 1900 2200 0    60   Input ~ 0
GND_24V
Text GLabel 1850 4550 0    60   Input ~ 0
GND_24V
Wire Wire Line
	2700 1000 3800 1000
Wire Wire Line
	2700 1300 3800 1300
Wire Wire Line
	2700 1600 3800 1600
Wire Wire Line
	2700 1900 3800 1900
Wire Wire Line
	2650 3300 3800 3300
Wire Wire Line
	2650 3600 3800 3600
Wire Wire Line
	2650 3900 3800 3900
Wire Wire Line
	2650 4200 3800 4200
Wire Wire Line
	1850 800  2100 800 
Wire Wire Line
	1550 800  1400 800 
Wire Wire Line
	1400 1100 1550 1100
Wire Wire Line
	1850 1100 2100 1100
Wire Wire Line
	1850 1400 2100 1400
Wire Wire Line
	1550 1400 1400 1400
Wire Wire Line
	1400 1700 1550 1700
Wire Wire Line
	1850 1700 2100 1700
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
	2000 1900 2100 1900
Wire Wire Line
	2000 1000 2000 2200
Wire Wire Line
	2100 1600 2000 1600
Connection ~ 2000 1900
Wire Wire Line
	2100 1300 2000 1300
Connection ~ 2000 1600
Wire Wire Line
	2100 1000 2000 1000
Connection ~ 2000 1300
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
	2700 800  3150 800 
Wire Wire Line
	2850 800  2850 1700
Wire Wire Line
	2850 1700 2700 1700
Connection ~ 2850 800 
Wire Wire Line
	2700 1400 2850 1400
Connection ~ 2850 1400
Wire Wire Line
	2700 1100 2850 1100
Connection ~ 2850 1100
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
	2000 2200 1900 2200
Wire Wire Line
	1950 4550 1850 4550
$Comp
L +3.3V #PWR045
U 1 1 5728E4BD
P 3100 3100
F 0 "#PWR045" H 3100 2950 50  0001 C CNN
F 1 "+3.3V" H 3100 3240 50  0000 C CNN
F 2 "" H 3100 3100 60  0000 C CNN
F 3 "" H 3100 3100 60  0000 C CNN
	1    3100 3100
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR046
U 1 1 5728E4C3
P 3150 800
F 0 "#PWR046" H 3150 650 50  0001 C CNN
F 1 "+3.3V" H 3150 940 50  0000 C CNN
F 2 "" H 3150 800 60  0000 C CNN
F 3 "" H 3150 800 60  0000 C CNN
	1    3150 800 
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
$Comp
L +3.3V #PWR047
U 1 1 5728E545
P 3100 5500
F 0 "#PWR047" H 3100 5350 50  0001 C CNN
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
Wire Wire Line
	5650 1900 6300 1900
Text GLabel 5950 1800 2    60   Input ~ 0
inh5
Wire Wire Line
	5650 2000 5850 2000
Wire Wire Line
	5850 2000 5850 1900
Connection ~ 5850 1900
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
Text HLabel 3800 1000 2    60   Input ~ 0
in1
Text HLabel 3800 1300 2    60   Input ~ 0
in2
Text HLabel 3800 1600 2    60   Input ~ 0
in3
Text HLabel 3800 1900 2    60   Input ~ 0
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
Wire Wire Line
	6350 2900 5650 2900
Wire Wire Line
	5650 3000 5900 3000
Wire Wire Line
	6350 2700 5650 2700
Wire Wire Line
	5650 2800 5900 2800
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
$Comp
L +3.3V #PWR048
U 1 1 572A10F2
P 6700 4500
F 0 "#PWR048" H 6700 4350 50  0001 C CNN
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
Wire Wire Line
	2650 5700 3800 5700
Wire Wire Line
	6250 5000 7400 5000
$EndSCHEMATC
