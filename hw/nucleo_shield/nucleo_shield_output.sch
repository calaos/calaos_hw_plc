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
$Comp
L 74HC595 U1
U 1 1 5729AB42
P 4500 2650
F 0 "U1" H 4650 3250 70  0000 C CNN
F 1 "74HC595" H 4500 2050 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 4500 2650 60  0001 C CNN
F 3 "" H 4500 2650 60  0000 C CNN
	1    4500 2650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5729AB4A
P 3800 3050
F 0 "#PWR012" H 3800 2800 50  0001 C CNN
F 1 "GND" H 3800 2900 50  0000 C CNN
F 2 "" H 3800 3050 60  0000 C CNN
F 3 "" H 3800 3050 60  0000 C CNN
	1    3800 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR013
U 1 1 5729AB50
P 3800 4650
F 0 "#PWR013" H 3800 4400 50  0001 C CNN
F 1 "GND" H 3800 4500 50  0000 C CNN
F 2 "" H 3800 4650 60  0000 C CNN
F 3 "" H 3800 4650 60  0000 C CNN
	1    3800 4650
	1    0    0    -1  
$EndComp
Text GLabel 5550 2200 2    60   Input ~ 0
out1
Text GLabel 5850 2300 2    60   Input ~ 0
out2
Text GLabel 5550 2400 2    60   Input ~ 0
out3
Text GLabel 5850 2500 2    60   Input ~ 0
out4
Text GLabel 5550 2600 2    60   Input ~ 0
out5
Text GLabel 5850 2700 2    60   Input ~ 0
out6
Text GLabel 5550 2800 2    60   Input ~ 0
out7
Text GLabel 5850 2900 2    60   Input ~ 0
out8
Text GLabel 5500 3800 2    60   Input ~ 0
out9
Text GLabel 5850 3900 2    60   Input ~ 0
out10
Text GLabel 5500 4000 2    60   Input ~ 0
out11
Text GLabel 5850 4100 2    60   Input ~ 0
out12
Text GLabel 5500 4200 2    60   Input ~ 0
out13
Text GLabel 5850 4300 2    60   Input ~ 0
out14
Text GLabel 5500 4400 2    60   Input ~ 0
out15
Wire Wire Line
	3800 2800 3800 3050
Wire Wire Line
	3800 4400 3800 4650
Wire Wire Line
	3250 2700 3800 2700
Connection ~ 3350 2700
Wire Wire Line
	3350 2700 3350 4300
Wire Wire Line
	3350 4300 3800 4300
Wire Wire Line
	3200 2400 3800 2400
Connection ~ 3500 2400
Wire Wire Line
	3500 2400 3500 4000
Wire Wire Line
	3500 4000 3800 4000
Wire Wire Line
	5200 3800 5500 3800
Wire Wire Line
	5200 3900 5850 3900
Wire Wire Line
	5200 4000 5500 4000
Wire Wire Line
	5200 4100 5850 4100
Wire Wire Line
	5200 4200 5500 4200
Wire Wire Line
	5200 4300 5850 4300
Wire Wire Line
	5200 4400 5500 4400
Wire Wire Line
	5200 4500 5850 4500
Wire Wire Line
	5200 2900 5850 2900
Wire Wire Line
	5200 2800 5550 2800
Wire Wire Line
	5200 2700 5850 2700
Wire Wire Line
	5550 2600 5200 2600
Wire Wire Line
	5200 2500 5850 2500
Wire Wire Line
	5200 2400 5550 2400
Wire Wire Line
	5200 2300 5850 2300
Wire Wire Line
	5200 2200 5550 2200
Text GLabel 7450 2200 0    60   Input ~ 0
out1
Text GLabel 7850 2300 0    60   Input ~ 0
out2
Text GLabel 7450 2400 0    60   Input ~ 0
out3
Text GLabel 7850 2500 0    60   Input ~ 0
out4
Text GLabel 7450 2600 0    60   Input ~ 0
out5
Text GLabel 7850 2700 0    60   Input ~ 0
out6
Text GLabel 7450 2800 0    60   Input ~ 0
out7
Text GLabel 5850 4500 2    60   Input ~ 0
out16
Text GLabel 7850 2900 0    60   Input ~ 0
out8
Text GLabel 7500 3700 0    60   Input ~ 0
out9
Text GLabel 7950 3800 0    60   Input ~ 0
out10
Text GLabel 7550 3900 0    60   Input ~ 0
out11
Text GLabel 7950 4000 0    60   Input ~ 0
out12
Text GLabel 7550 4100 0    60   Input ~ 0
out13
Text GLabel 7950 4200 0    60   Input ~ 0
out14
Text GLabel 7550 4300 0    60   Input ~ 0
out15
Text GLabel 7950 4400 0    60   Input ~ 0
out16
Wire Wire Line
	7450 2200 8000 2200
Wire Wire Line
	7850 2300 8000 2300
Wire Wire Line
	7450 2400 8000 2400
Wire Wire Line
	7850 2500 8000 2500
Wire Wire Line
	8000 2600 7450 2600
Wire Wire Line
	7850 2700 8000 2700
Wire Wire Line
	8000 2800 7450 2800
Wire Wire Line
	7850 2900 8000 2900
Wire Wire Line
	7950 3800 8050 3800
Wire Wire Line
	8050 3900 7550 3900
Wire Wire Line
	7950 4000 8050 4000
Wire Wire Line
	8050 4100 7550 4100
Wire Wire Line
	7950 4200 8050 4200
Wire Wire Line
	8050 4300 7550 4300
Wire Wire Line
	7950 4400 8050 4400
$Comp
L GND #PWR014
U 1 1 5729ABA1
P 7000 2100
F 0 "#PWR014" H 7000 1850 50  0001 C CNN
F 1 "GND" H 7000 1950 50  0000 C CNN
F 2 "" H 7000 2100 60  0000 C CNN
F 3 "" H 7000 2100 60  0000 C CNN
	1    7000 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3700 8050 3700
$Comp
L +5V #PWR015
U 1 1 5729ABA8
P 7000 2000
F 0 "#PWR015" H 7000 1850 50  0001 C CNN
F 1 "+5V" H 7000 2140 50  0000 C CNN
F 2 "" H 7000 2000 60  0000 C CNN
F 3 "" H 7000 2000 60  0000 C CNN
	1    7000 2000
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P3
U 1 1 5729ABAE
P 8200 2450
F 0 "P3" H 8200 3000 50  0000 C CNN
F 1 "CONN_01X10" V 8300 2450 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 8200 2450 60  0001 C CNN
F 3 "" H 8200 2450 60  0000 C CNN
	1    8200 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 2100 8000 2100
Wire Wire Line
	8000 2000 7000 2000
$Comp
L CONN_01X10 P2
U 1 1 5729ABB7
P 8250 4150
F 0 "P2" H 8250 4700 50  0000 C CNN
F 1 "CONN_01X10" V 8350 4150 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 8250 4150 60  0001 C CNN
F 3 "" H 8250 4150 60  0000 C CNN
	1    8250 4150
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR016
U 1 1 5729ABBE
P 7100 4600
F 0 "#PWR016" H 7100 4450 50  0001 C CNN
F 1 "+5V" H 7100 4740 50  0000 C CNN
F 2 "" H 7100 4600 60  0000 C CNN
F 3 "" H 7100 4600 60  0000 C CNN
	1    7100 4600
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR017
U 1 1 5729ABC4
P 7100 4500
F 0 "#PWR017" H 7100 4250 50  0001 C CNN
F 1 "GND" H 7100 4350 50  0000 C CNN
F 2 "" H 7100 4500 60  0000 C CNN
F 3 "" H 7100 4500 60  0000 C CNN
	1    7100 4500
	-1   0    0    1   
$EndComp
Wire Wire Line
	8050 4500 7100 4500
Wire Wire Line
	7100 4600 8050 4600
Wire Wire Line
	3800 2500 2500 2500
Wire Wire Line
	3050 4100 3800 4100
$Comp
L 74HC595 U2
U 1 1 5729ABCE
P 4500 4250
F 0 "U2" H 4650 4850 70  0000 C CNN
F 1 "74HC595" H 4500 3650 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 4500 4250 60  0001 C CNN
F 3 "" H 4500 4250 60  0000 C CNN
	1    4500 4250
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR018
U 1 1 5729ABD5
P 4200 1900
F 0 "#PWR018" H 4200 1750 50  0001 C CNN
F 1 "+5V" H 4200 2040 50  0000 C CNN
F 2 "" H 4200 1900 60  0000 C CNN
F 3 "" H 4200 1900 60  0000 C CNN
	1    4200 1900
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR019
U 1 1 5729ABDB
P 5900 3550
F 0 "#PWR019" H 5900 3400 50  0001 C CNN
F 1 "+5V" H 5900 3690 50  0000 C CNN
F 2 "" H 5900 3550 60  0000 C CNN
F 3 "" H 5900 3550 60  0000 C CNN
	1    5900 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4200 3700 4200 3550
Wire Wire Line
	4200 3550 5900 3550
Wire Wire Line
	4200 2100 4200 1900
Wire Wire Line
	3300 2200 3800 2200
Wire Wire Line
	3800 3800 3800 3350
Wire Wire Line
	3800 3350 5200 3350
Wire Wire Line
	5200 3350 5200 3100
$Comp
L +5V #PWR020
U 1 1 5729ABE8
P 2500 2500
F 0 "#PWR020" H 2500 2350 50  0001 C CNN
F 1 "+5V" H 2500 2640 50  0000 C CNN
F 2 "" H 2500 2500 60  0000 C CNN
F 3 "" H 2500 2500 60  0000 C CNN
	1    2500 2500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR021
U 1 1 5729ABEE
P 3050 4100
F 0 "#PWR021" H 3050 3950 50  0001 C CNN
F 1 "+5V" H 3050 4240 50  0000 C CNN
F 2 "" H 3050 4100 60  0000 C CNN
F 3 "" H 3050 4100 60  0000 C CNN
	1    3050 4100
	1    0    0    -1  
$EndComp
Text HLabel 3300 2200 0    60   Input ~ 0
SRDATA
Text HLabel 3200 2400 0    60   Input ~ 0
SRCLK
Text HLabel 3250 2700 0    60   Input ~ 0
SRLatch
$EndSCHEMATC
