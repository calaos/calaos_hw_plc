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
L Nucleo-F411RE-CN10 CN101
U 1 1 56658743
P 9600 1850
F 0 "CN101" H 9600 2850 60  0000 C CNN
F 1 "Nucleo-F411RE-CN10" H 9700 800 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x19" H 9600 -50 60  0001 C CNN
F 3 "" H 9600 -50 60  0000 C CNN
	1    9600 1850
	1    0    0    -1  
$EndComp
$Comp
L Nucleo-F411RE-CN7 CN71
U 1 1 56658787
P 7300 1850
F 0 "CN71" H 7300 2850 60  0000 C CNN
F 1 "Nucleo-F411RE-CN7" H 7100 750 60  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x19" H 7550 1800 60  0001 C CNN
F 3 "" H 7550 1800 60  0000 C CNN
	1    7300 1850
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U1
U 1 1 566589DD
P 8350 3950
F 0 "U1" H 8500 4550 70  0000 C CNN
F 1 "74HC595" H 8350 3350 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 8350 3950 60  0001 C CNN
F 3 "" H 8350 3950 60  0000 C CNN
	1    8350 3950
	1    0    0    -1  
$EndComp
$Comp
L 74HC595 U2
U 1 1 56658CF9
P 8350 5550
F 0 "U2" H 8500 6150 70  0000 C CNN
F 1 "74HC595" H 8350 4950 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 8350 5550 60  0001 C CNN
F 3 "" H 8350 5550 60  0000 C CNN
	1    8350 5550
	1    0    0    -1  
$EndComp
Text GLabel 8950 2050 0    60   Input ~ 0
SRLatch
Text GLabel 6950 4000 0    60   Input ~ 0
SRLatch
Text GLabel 10350 1950 2    60   Input ~ 0
SRCLK
$Comp
L GND #PWR01
U 1 1 56697602
P 7650 4350
F 0 "#PWR01" H 7650 4100 50  0001 C CNN
F 1 "GND" H 7650 4200 50  0000 C CNN
F 2 "" H 7650 4350 60  0000 C CNN
F 3 "" H 7650 4350 60  0000 C CNN
	1    7650 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 56697632
P 7650 5950
F 0 "#PWR02" H 7650 5700 50  0001 C CNN
F 1 "GND" H 7650 5800 50  0000 C CNN
F 2 "" H 7650 5950 60  0000 C CNN
F 3 "" H 7650 5950 60  0000 C CNN
	1    7650 5950
	1    0    0    -1  
$EndComp
Text GLabel 6900 3700 0    60   Input ~ 0
SRCLK
$Comp
L GND #PWR03
U 1 1 56699180
P 10850 1950
F 0 "#PWR03" H 10850 1700 50  0001 C CNN
F 1 "GND" H 10850 1800 50  0000 C CNN
F 2 "" H 10850 1950 60  0000 C CNN
F 3 "" H 10850 1950 60  0000 C CNN
	1    10850 1950
	1    0    0    -1  
$EndComp
Text GLabel 10400 1150 2    60   Input ~ 0
SRDATA
Text GLabel 6950 3500 0    60   Input ~ 0
SRDATA
$Comp
L LTV-847 U3
U 1 1 56A613FA
P 3000 1700
F 0 "U3" H 2800 2400 50  0000 L CNN
F 1 "LTV-847" H 3000 2400 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2800 1100 50  0000 L CIN
F 3 "" H 3000 1600 50  0000 L CNN
	1    3000 1700
	1    0    0    -1  
$EndComp
Text GLabel 4450 3500 2    60   Input ~ 0
in5
Text GLabel 4450 3800 2    60   Input ~ 0
in6
Text GLabel 4450 4100 2    60   Input ~ 0
in7
Text GLabel 4450 4400 2    60   Input ~ 0
in8
Text GLabel 4400 1300 2    60   Input ~ 0
in1
Text GLabel 4400 1600 2    60   Input ~ 0
in2
Text GLabel 4400 1900 2    60   Input ~ 0
in3
Text GLabel 4400 2200 2    60   Input ~ 0
in4
Text GLabel 7850 2750 2    60   Input ~ 0
in6
Text GLabel 8150 2650 2    60   Input ~ 0
in5
Text GLabel 7850 2550 2    60   Input ~ 0
in4
Text GLabel 8150 2450 2    60   Input ~ 0
in3
Text GLabel 7850 2350 2    60   Input ~ 0
in2
Text GLabel 8150 2250 2    60   Input ~ 0
in1
Text GLabel 6350 2750 0    60   Input ~ 0
in8
Text GLabel 6050 2650 0    60   Input ~ 0
in7
Text GLabel 9400 3500 2    60   Input ~ 0
out1
Text GLabel 9700 3600 2    60   Input ~ 0
out2
Text GLabel 9400 3700 2    60   Input ~ 0
out3
Text GLabel 9700 3800 2    60   Input ~ 0
out4
Text GLabel 9400 3900 2    60   Input ~ 0
out5
Text GLabel 9700 4000 2    60   Input ~ 0
out6
Text GLabel 9400 4100 2    60   Input ~ 0
out6
Text GLabel 9700 4200 2    60   Input ~ 0
out7
Text GLabel 9350 5100 2    60   Input ~ 0
out8
Text GLabel 9700 5200 2    60   Input ~ 0
out9
Text GLabel 9350 5300 2    60   Input ~ 0
out10
Text GLabel 9700 5400 2    60   Input ~ 0
out11
Text GLabel 9350 5500 2    60   Input ~ 0
out12
Text GLabel 9700 5600 2    60   Input ~ 0
out13
Text GLabel 9350 5700 2    60   Input ~ 0
out14
Text GLabel 9700 5800 2    60   Input ~ 0
out15
$Comp
L R R10
U 1 1 56A63457
P 3400 4650
F 0 "R10" V 3480 4650 50  0000 C CNN
F 1 "R" V 3400 4650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3330 4650 30  0001 C CNN
F 3 "" H 3400 4650 30  0000 C CNN
	1    3400 4650
	1    0    0    -1  
$EndComp
$Comp
L R R12
U 1 1 56A636FF
P 3700 4650
F 0 "R12" V 3780 4650 50  0000 C CNN
F 1 "R" V 3700 4650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3630 4650 30  0001 C CNN
F 3 "" H 3700 4650 30  0000 C CNN
	1    3700 4650
	1    0    0    -1  
$EndComp
$Comp
L R R14
U 1 1 56A63739
P 4000 4650
F 0 "R14" V 4080 4650 50  0000 C CNN
F 1 "R" V 4000 4650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3930 4650 30  0001 C CNN
F 3 "" H 4000 4650 30  0000 C CNN
	1    4000 4650
	1    0    0    -1  
$EndComp
$Comp
L R R16
U 1 1 56A63767
P 4300 4650
F 0 "R16" V 4380 4650 50  0000 C CNN
F 1 "R" V 4300 4650 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4230 4650 30  0001 C CNN
F 3 "" H 4300 4650 30  0000 C CNN
	1    4300 4650
	1    0    0    -1  
$EndComp
$Comp
L R R9
U 1 1 56A637CB
P 3400 2450
F 0 "R9" V 3480 2450 50  0000 C CNN
F 1 "R" V 3400 2450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3330 2450 30  0001 C CNN
F 3 "" H 3400 2450 30  0000 C CNN
	1    3400 2450
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 56A63945
P 3700 2450
F 0 "R11" V 3780 2450 50  0000 C CNN
F 1 "R" V 3700 2450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3630 2450 30  0001 C CNN
F 3 "" H 3700 2450 30  0000 C CNN
	1    3700 2450
	1    0    0    -1  
$EndComp
$Comp
L R R13
U 1 1 56A639B1
P 4000 2450
F 0 "R13" V 4080 2450 50  0000 C CNN
F 1 "R" V 4000 2450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 3930 2450 30  0001 C CNN
F 3 "" H 4000 2450 30  0000 C CNN
	1    4000 2450
	1    0    0    -1  
$EndComp
$Comp
L R R15
U 1 1 56A639E9
P 4300 2450
F 0 "R15" V 4380 2450 50  0000 C CNN
F 1 "R" V 4300 2450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4230 2450 30  0001 C CNN
F 3 "" H 4300 2450 30  0000 C CNN
	1    4300 2450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 56A63D29
P 3850 5200
F 0 "#PWR04" H 3850 4950 50  0001 C CNN
F 1 "GND" H 3850 5050 50  0000 C CNN
F 2 "" H 3850 5200 60  0000 C CNN
F 3 "" H 3850 5200 60  0000 C CNN
	1    3850 5200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 56A643CB
P 3850 2900
F 0 "#PWR05" H 3850 2650 50  0001 C CNN
F 1 "GND" H 3850 2750 50  0000 C CNN
F 2 "" H 3850 2900 60  0000 C CNN
F 3 "" H 3850 2900 60  0000 C CNN
	1    3850 2900
	1    0    0    -1  
$EndComp
Text GLabel 2000 1100 0    60   Input ~ 0
inh1
Text GLabel 2000 1400 0    60   Input ~ 0
inh2
Text GLabel 2000 1700 0    60   Input ~ 0
inh3
Text GLabel 2000 2000 0    60   Input ~ 0
inh4
Text GLabel 2000 3300 0    60   Input ~ 0
inh5
Text GLabel 2000 4200 0    60   Input ~ 0
inh8
$Comp
L LTV-847 U4
U 1 1 56A614C5
P 3000 3900
F 0 "U4" H 2800 4600 50  0000 L CNN
F 1 "LTV-847" H 3000 4600 50  0000 L CNN
F 2 "Housings_DIP:DIP-16__300" H 2800 3300 50  0000 L CIN
F 3 "" H 3000 3800 50  0000 L CNN
	1    3000 3900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 56A65119
P 2600 4750
F 0 "#PWR06" H 2600 4500 50  0001 C CNN
F 1 "GND" H 2600 4600 50  0000 C CNN
F 2 "" H 2600 4750 60  0000 C CNN
F 3 "" H 2600 4750 60  0000 C CNN
	1    2600 4750
	1    0    0    -1  
$EndComp
Text GLabel 2000 3900 0    60   Input ~ 0
inh7
Text GLabel 2000 3600 0    60   Input ~ 0
inh6
$Comp
L R R5
U 1 1 56A656E7
P 2300 3300
F 0 "R5" V 2380 3300 50  0000 C CNN
F 1 "R" V 2300 3300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 3300 30  0001 C CNN
F 3 "" H 2300 3300 30  0000 C CNN
	1    2300 3300
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 56A657B7
P 2300 3600
F 0 "R6" V 2380 3600 50  0000 C CNN
F 1 "R" V 2300 3600 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 3600 30  0001 C CNN
F 3 "" H 2300 3600 30  0000 C CNN
	1    2300 3600
	0    1    1    0   
$EndComp
$Comp
L R R7
U 1 1 56A657F3
P 2300 3900
F 0 "R7" V 2380 3900 50  0000 C CNN
F 1 "R" V 2300 3900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 3900 30  0001 C CNN
F 3 "" H 2300 3900 30  0000 C CNN
	1    2300 3900
	0    1    1    0   
$EndComp
$Comp
L R R8
U 1 1 56A65833
P 2300 4200
F 0 "R8" V 2380 4200 50  0000 C CNN
F 1 "R" V 2300 4200 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 4200 30  0001 C CNN
F 3 "" H 2300 4200 30  0000 C CNN
	1    2300 4200
	0    1    1    0   
$EndComp
$Comp
L R R4
U 1 1 56A65871
P 2300 2000
F 0 "R4" V 2380 2000 50  0000 C CNN
F 1 "R" V 2300 2000 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 2000 30  0001 C CNN
F 3 "" H 2300 2000 30  0000 C CNN
	1    2300 2000
	0    1    1    0   
$EndComp
$Comp
L R R3
U 1 1 56A65995
P 2300 1700
F 0 "R3" V 2380 1700 50  0000 C CNN
F 1 "R" V 2300 1700 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 1700 30  0001 C CNN
F 3 "" H 2300 1700 30  0000 C CNN
	1    2300 1700
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 56A659D7
P 2300 1400
F 0 "R2" V 2380 1400 50  0000 C CNN
F 1 "R" V 2300 1400 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 1400 30  0001 C CNN
F 3 "" H 2300 1400 30  0000 C CNN
	1    2300 1400
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 56A65A1B
P 2300 1100
F 0 "R1" V 2380 1100 50  0000 C CNN
F 1 "R" V 2300 1100 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 2230 1100 30  0001 C CNN
F 3 "" H 2300 1100 30  0000 C CNN
	1    2300 1100
	0    1    1    0   
$EndComp
Wire Wire Line
	9050 4400 9050 4750
Wire Wire Line
	9050 4750 7600 4750
Wire Wire Line
	7600 4750 7600 5100
Wire Wire Line
	7600 5100 7650 5100
Wire Wire Line
	7650 4100 7650 4350
Wire Wire Line
	7650 5700 7650 5950
Wire Wire Line
	6950 4000 7650 4000
Connection ~ 7200 4000
Wire Wire Line
	7200 4000 7200 5600
Wire Wire Line
	7200 5600 7650 5600
Wire Wire Line
	6900 3700 7650 3700
Connection ~ 7350 3700
Wire Wire Line
	7350 3700 7350 5300
Wire Wire Line
	7350 5300 7650 5300
Wire Wire Line
	10350 1950 10100 1950
Wire Wire Line
	8950 2050 9150 2050
Wire Wire Line
	10100 1850 10850 1850
Wire Wire Line
	10850 1850 10850 1950
Wire Wire Line
	6950 3500 7650 3500
Wire Wire Line
	10100 1150 10400 1150
Wire Wire Line
	3300 1300 4400 1300
Wire Wire Line
	3300 1600 4400 1600
Wire Wire Line
	3300 1900 4400 1900
Wire Wire Line
	3300 2200 4400 2200
Wire Wire Line
	3300 3500 4450 3500
Wire Wire Line
	3300 3800 4450 3800
Wire Wire Line
	3300 4100 4450 4100
Wire Wire Line
	3300 4400 4450 4400
Wire Wire Line
	8150 2250 7600 2250
Wire Wire Line
	7850 2350 7600 2350
Wire Wire Line
	7600 2450 8150 2450
Wire Wire Line
	8150 2650 7600 2650
Wire Wire Line
	7600 2750 7850 2750
Wire Wire Line
	7850 2550 7600 2550
Wire Wire Line
	6050 2650 6600 2650
Wire Wire Line
	6600 2750 6350 2750
Wire Wire Line
	9050 5100 9350 5100
Wire Wire Line
	9050 5200 9700 5200
Wire Wire Line
	9050 5300 9350 5300
Wire Wire Line
	9050 5400 9700 5400
Wire Wire Line
	9050 5500 9350 5500
Wire Wire Line
	9050 5600 9700 5600
Wire Wire Line
	9050 5700 9350 5700
Wire Wire Line
	9050 5800 9700 5800
Wire Wire Line
	9050 4200 9700 4200
Wire Wire Line
	9050 4100 9400 4100
Wire Wire Line
	9050 4000 9700 4000
Wire Wire Line
	9400 3900 9050 3900
Wire Wire Line
	9050 3800 9700 3800
Wire Wire Line
	9050 3700 9400 3700
Wire Wire Line
	9050 3600 9700 3600
Wire Wire Line
	9050 3500 9400 3500
Wire Wire Line
	4300 2300 4300 1300
Connection ~ 4300 1300
Wire Wire Line
	4000 2300 4000 1600
Connection ~ 4000 1600
Wire Wire Line
	3700 2300 3700 1900
Connection ~ 3700 1900
Wire Wire Line
	3400 2300 3400 2200
Connection ~ 3400 2200
Wire Wire Line
	3400 4500 3400 4400
Connection ~ 3400 4400
Wire Wire Line
	3700 4500 3700 4100
Connection ~ 3700 4100
Wire Wire Line
	4000 4500 4000 3800
Connection ~ 4000 3800
Wire Wire Line
	4300 4500 4300 3500
Connection ~ 4300 3500
Wire Wire Line
	3400 4800 3400 5000
Wire Wire Line
	3400 5000 4300 5000
Wire Wire Line
	3700 5000 3700 4800
Connection ~ 3700 5000
Wire Wire Line
	4000 5000 4000 4800
Wire Wire Line
	4300 5000 4300 4800
Connection ~ 4000 5000
Wire Wire Line
	3850 5000 3850 5200
Connection ~ 3850 5000
Wire Wire Line
	3400 2600 3400 2750
Wire Wire Line
	3400 2750 4300 2750
Wire Wire Line
	4300 2750 4300 2600
Wire Wire Line
	4000 2600 4000 2750
Connection ~ 4000 2750
Wire Wire Line
	3700 2600 3700 2750
Connection ~ 3700 2750
Wire Wire Line
	3850 2750 3850 2900
Connection ~ 3850 2750
Wire Wire Line
	2450 1100 2700 1100
Wire Wire Line
	2150 1100 2000 1100
Wire Wire Line
	2000 1400 2150 1400
Wire Wire Line
	2450 1400 2700 1400
Wire Wire Line
	2450 1700 2700 1700
Wire Wire Line
	2150 1700 2000 1700
Wire Wire Line
	2000 2000 2150 2000
Wire Wire Line
	2450 2000 2700 2000
Wire Wire Line
	2700 3300 2450 3300
Wire Wire Line
	2150 3300 2000 3300
Wire Wire Line
	2000 3600 2150 3600
Wire Wire Line
	2450 3600 2700 3600
Wire Wire Line
	2700 3900 2450 3900
Wire Wire Line
	2000 3900 2150 3900
Wire Wire Line
	2000 4200 2150 4200
Wire Wire Line
	2450 4200 2700 4200
$Comp
L GND #PWR07
U 1 1 56A666A3
P 2600 2500
F 0 "#PWR07" H 2600 2250 50  0001 C CNN
F 1 "GND" H 2600 2350 50  0000 C CNN
F 2 "" H 2600 2500 60  0000 C CNN
F 3 "" H 2600 2500 60  0000 C CNN
	1    2600 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2200 2700 2200
Wire Wire Line
	2600 1300 2600 2500
Wire Wire Line
	2700 1900 2600 1900
Connection ~ 2600 2200
Wire Wire Line
	2700 1600 2600 1600
Connection ~ 2600 1900
Wire Wire Line
	2700 1300 2600 1300
Connection ~ 2600 1600
Wire Wire Line
	2700 4400 2600 4400
Wire Wire Line
	2600 3500 2600 4750
Wire Wire Line
	2700 4100 2600 4100
Connection ~ 2600 4400
Wire Wire Line
	2700 3800 2600 3800
Connection ~ 2600 4100
Wire Wire Line
	2700 3500 2600 3500
Connection ~ 2600 3800
$EndSCHEMATC
