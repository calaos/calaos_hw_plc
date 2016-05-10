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
P 3050 1600
F 0 "U1" H 3200 2200 70  0000 C CNN
F 1 "74HC595" H 3050 1000 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 3050 1600 60  0001 C CNN
F 3 "" H 3050 1600 60  0000 C CNN
	1    3050 1600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR022
U 1 1 5729AB4A
P 2350 2000
F 0 "#PWR022" H 2350 1750 50  0001 C CNN
F 1 "GND" H 2350 1850 50  0000 C CNN
F 2 "" H 2350 2000 60  0000 C CNN
F 3 "" H 2350 2000 60  0000 C CNN
	1    2350 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5729AB50
P 2350 3600
F 0 "#PWR023" H 2350 3350 50  0001 C CNN
F 1 "GND" H 2350 3450 50  0000 C CNN
F 2 "" H 2350 3600 60  0000 C CNN
F 3 "" H 2350 3600 60  0000 C CNN
	1    2350 3600
	1    0    0    -1  
$EndComp
Text GLabel 4100 1150 2    60   Input ~ 0
out1
Text GLabel 4400 1250 2    60   Input ~ 0
out2
Text GLabel 4100 1350 2    60   Input ~ 0
out3
Text GLabel 4400 1450 2    60   Input ~ 0
out4
Text GLabel 4100 1550 2    60   Input ~ 0
out5
Text GLabel 4400 1650 2    60   Input ~ 0
out6
Text GLabel 4100 1750 2    60   Input ~ 0
out7
Text GLabel 4400 1850 2    60   Input ~ 0
out8
Text GLabel 4050 2750 2    60   Input ~ 0
out9
Text GLabel 4400 2850 2    60   Input ~ 0
out10
Text GLabel 4050 2950 2    60   Input ~ 0
out11
Text GLabel 4400 3050 2    60   Input ~ 0
out12
Text GLabel 4050 3150 2    60   Input ~ 0
out13
Text GLabel 4400 3250 2    60   Input ~ 0
out14
Text GLabel 4050 3350 2    60   Input ~ 0
out15
Text GLabel 4400 3450 2    60   Input ~ 0
out16
$Comp
L 74HC595 U2
U 1 1 5729ABCE
P 3050 3200
F 0 "U2" H 3200 3800 70  0000 C CNN
F 1 "74HC595" H 3050 2600 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 3050 3200 60  0001 C CNN
F 3 "" H 3050 3200 60  0000 C CNN
	1    3050 3200
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR024
U 1 1 5729ABD5
P 2750 850
F 0 "#PWR024" H 2750 700 50  0001 C CNN
F 1 "+5V" H 2750 990 50  0000 C CNN
F 2 "" H 2750 850 60  0000 C CNN
F 3 "" H 2750 850 60  0000 C CNN
	1    2750 850 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR025
U 1 1 5729ABDB
P 4450 2500
F 0 "#PWR025" H 4450 2350 50  0001 C CNN
F 1 "+5V" H 4450 2640 50  0000 C CNN
F 2 "" H 4450 2500 60  0000 C CNN
F 3 "" H 4450 2500 60  0000 C CNN
	1    4450 2500
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR026
U 1 1 5729ABE8
P 2200 1550
F 0 "#PWR026" H 2200 1400 50  0001 C CNN
F 1 "+5V" H 2200 1690 50  0000 C CNN
F 2 "" H 2200 1550 60  0000 C CNN
F 3 "" H 2200 1550 60  0000 C CNN
	1    2200 1550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR027
U 1 1 5729ABEE
P 1950 3050
F 0 "#PWR027" H 1950 2900 50  0001 C CNN
F 1 "+5V" H 1950 3190 50  0000 C CNN
F 2 "" H 1950 3050 60  0000 C CNN
F 3 "" H 1950 3050 60  0000 C CNN
	1    1950 3050
	1    0    0    -1  
$EndComp
Text HLabel 1850 1150 0    60   Input ~ 0
SRDATA
Text HLabel 1750 1350 0    60   Input ~ 0
SRCLK
Text HLabel 1800 1650 0    60   Input ~ 0
SRLatch
$Comp
L ULN2803 U10
U 1 1 57307CE9
P 9250 1500
F 0 "U10" H 9400 2050 60  0000 C CNN
F 1 "ULN2803" H 9500 1950 60  0000 C CNN
F 2 "Housings_DIP:DIP-18__300" H 9250 1500 60  0001 C CNN
F 3 "" H 9250 1500 60  0000 C CNN
	1    9250 1500
	1    0    0    -1  
$EndComp
$Comp
L ULN2803 U9
U 1 1 57307D12
P 9200 3050
F 0 "U9" H 9350 3600 60  0000 C CNN
F 1 "ULN2803" H 9450 3500 60  0000 C CNN
F 2 "Housings_DIP:DIP-18__300" H 9200 3050 60  0001 C CNN
F 3 "" H 9200 3050 60  0000 C CNN
	1    9200 3050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 57307D6B
P 9250 2000
F 0 "#PWR028" H 9250 1750 50  0001 C CNN
F 1 "GND" H 9250 1850 50  0000 C CNN
F 2 "" H 9250 2000 60  0000 C CNN
F 3 "" H 9250 2000 60  0000 C CNN
	1    9250 2000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR029
U 1 1 57307D82
P 9200 3550
F 0 "#PWR029" H 9200 3300 50  0001 C CNN
F 1 "GND" H 9200 3400 50  0000 C CNN
F 2 "" H 9200 3550 60  0000 C CNN
F 3 "" H 9200 3550 60  0000 C CNN
	1    9200 3550
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR030
U 1 1 57307DA1
P 9250 1000
F 0 "#PWR030" H 9250 850 50  0001 C CNN
F 1 "+24V" H 9250 1140 50  0000 C CNN
F 2 "" H 9250 1000 60  0000 C CNN
F 3 "" H 9250 1000 60  0000 C CNN
	1    9250 1000
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR031
U 1 1 57307DBF
P 9200 2550
F 0 "#PWR031" H 9200 2400 50  0001 C CNN
F 1 "+24V" H 9200 2690 50  0000 C CNN
F 2 "" H 9200 2550 60  0000 C CNN
F 3 "" H 9200 2550 60  0000 C CNN
	1    9200 2550
	1    0    0    -1  
$EndComp
Text GLabel 8700 1850 0    60   Input ~ 0
out1
Text GLabel 8300 1750 0    60   Input ~ 0
out2
Text GLabel 8700 1650 0    60   Input ~ 0
out3
Text GLabel 8300 1550 0    60   Input ~ 0
out4
Text GLabel 8700 1450 0    60   Input ~ 0
out5
Text GLabel 8300 1350 0    60   Input ~ 0
out6
Text GLabel 8700 1250 0    60   Input ~ 0
out7
Text GLabel 8300 1150 0    60   Input ~ 0
out8
Text GLabel 8700 3400 0    60   Input ~ 0
out9
Text GLabel 8300 3300 0    60   Input ~ 0
out10
Text GLabel 8700 3200 0    60   Input ~ 0
out11
Text GLabel 8300 3100 0    60   Input ~ 0
out12
Text GLabel 8700 3000 0    60   Input ~ 0
out13
Text GLabel 8300 2900 0    60   Input ~ 0
out14
Text GLabel 8700 2800 0    60   Input ~ 0
out15
Text GLabel 8250 2700 0    60   Input ~ 0
out16
$Comp
L CONN_01X10 P10
U 1 1 5730818B
P 6100 4900
F 0 "P10" H 6100 5450 50  0000 C CNN
F 1 "CONN_OUTH1" V 6200 4900 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 6100 4900 60  0001 C CNN
F 3 "" H 6100 4900 60  0000 C CNN
	1    6100 4900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P11
U 1 1 573081DD
P 6100 6450
F 0 "P11" H 6100 7000 50  0000 C CNN
F 1 "CONN_OUTH2" V 6200 6450 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 6100 6450 60  0001 C CNN
F 3 "" H 6100 6450 60  0000 C CNN
	1    6100 6450
	1    0    0    -1  
$EndComp
Text GLabel 9800 1850 2    60   Input ~ 0
out1h
Text GLabel 10200 1750 2    60   Input ~ 0
out2h
Text GLabel 9800 1650 2    60   Input ~ 0
out3h
Text GLabel 10200 1550 2    60   Input ~ 0
out4h
Text GLabel 9800 1450 2    60   Input ~ 0
out5h
Text GLabel 10200 1350 2    60   Input ~ 0
out6h
Text GLabel 9800 1250 2    60   Input ~ 0
out7h
Text GLabel 10200 1150 2    60   Input ~ 0
out8h
Text GLabel 9700 3400 2    60   Input ~ 0
out9h
Text GLabel 10100 3300 2    60   Input ~ 0
out10h
Text GLabel 9700 3200 2    60   Input ~ 0
out11h
Text GLabel 10100 3100 2    60   Input ~ 0
out12h
Text GLabel 9700 3000 2    60   Input ~ 0
out13h
Text GLabel 10100 2900 2    60   Input ~ 0
out14h
Text GLabel 9700 2800 2    60   Input ~ 0
out15h
Text GLabel 10150 2700 2    60   Input ~ 0
out16h
Text GLabel 5350 6000 0    60   Input ~ 0
out9h
Text GLabel 5800 6100 0    60   Input ~ 0
out10h
Text GLabel 5400 6200 0    60   Input ~ 0
out11h
Text GLabel 5800 6300 0    60   Input ~ 0
out12h
Text GLabel 5400 6400 0    60   Input ~ 0
out13h
Text GLabel 5800 6500 0    60   Input ~ 0
out14h
Text GLabel 5400 6600 0    60   Input ~ 0
out15h
Text GLabel 5800 6700 0    60   Input ~ 0
out16h
Text GLabel 5350 4650 0    60   Input ~ 0
out1h
Text GLabel 5750 4750 0    60   Input ~ 0
out2h
Text GLabel 5350 4850 0    60   Input ~ 0
out3h
Text GLabel 5750 4950 0    60   Input ~ 0
out4h
Text GLabel 5350 5050 0    60   Input ~ 0
out5h
Text GLabel 5750 5150 0    60   Input ~ 0
out6h
Text GLabel 5350 5250 0    60   Input ~ 0
out7h
Text GLabel 5750 5350 0    60   Input ~ 0
out8h
$Comp
L GND #PWR032
U 1 1 573085F0
P 5500 4500
F 0 "#PWR032" H 5500 4250 50  0001 C CNN
F 1 "GND" H 5500 4350 50  0000 C CNN
F 2 "" H 5500 4500 60  0000 C CNN
F 3 "" H 5500 4500 60  0000 C CNN
	1    5500 4500
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR033
U 1 1 5730860B
P 4800 6800
F 0 "#PWR033" H 4800 6550 50  0001 C CNN
F 1 "GND" H 4800 6650 50  0000 C CNN
F 2 "" H 4800 6800 60  0000 C CNN
F 3 "" H 4800 6800 60  0000 C CNN
	1    4800 6800
	-1   0    0    1   
$EndComp
$Comp
L +24V #PWR034
U 1 1 573087B8
P 5800 4300
F 0 "#PWR034" H 5800 4150 50  0001 C CNN
F 1 "+24V" H 5800 4440 50  0000 C CNN
F 2 "" H 5800 4300 60  0000 C CNN
F 3 "" H 5800 4300 60  0000 C CNN
	1    5800 4300
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR035
U 1 1 5730884E
P 4500 6900
F 0 "#PWR035" H 4500 6750 50  0001 C CNN
F 1 "+24V" H 4500 7040 50  0000 C CNN
F 2 "" H 4500 6900 60  0000 C CNN
F 3 "" H 4500 6900 60  0000 C CNN
	1    4500 6900
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P2
U 1 1 57326C94
P 8300 5150
F 0 "P2" H 8300 5700 50  0000 C CNN
F 1 "CONN_OUTH1" V 8400 5150 50  0000 C CNN
F 2 "w_conn_screw:mors_10p" H 8300 5150 60  0001 C CNN
F 3 "" H 8300 5150 60  0000 C CNN
	1    8300 5150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 57326CAA
P 7700 4750
F 0 "#PWR039" H 7700 4500 50  0001 C CNN
F 1 "GND" H 7700 4600 50  0000 C CNN
F 2 "" H 7700 4750 60  0000 C CNN
F 3 "" H 7700 4750 60  0000 C CNN
	1    7700 4750
	-1   0    0    1   
$EndComp
Text GLabel 7800 5600 0    60   Input ~ 0
out17
Text GLabel 7450 5500 0    60   Input ~ 0
out18
Text GLabel 7800 5400 0    60   Input ~ 0
out19
Text GLabel 7450 5300 0    60   Input ~ 0
out20
Text GLabel 7800 5200 0    60   Input ~ 0
out21
Text GLabel 7450 5100 0    60   Input ~ 0
out22
Text GLabel 7800 5000 0    60   Input ~ 0
out23
Text GLabel 7450 4900 0    60   Input ~ 0
out24
$Comp
L +5V #PWR040
U 1 1 57326EE3
P 8000 4550
F 0 "#PWR040" H 8000 4400 50  0001 C CNN
F 1 "+5V" H 8000 4690 50  0000 C CNN
F 2 "" H 8000 4550 60  0000 C CNN
F 3 "" H 8000 4550 60  0000 C CNN
	1    8000 4550
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR037
U 1 1 57326A3F
P 4450 4100
F 0 "#PWR037" H 4450 3950 50  0001 C CNN
F 1 "+5V" H 4450 4240 50  0000 C CNN
F 2 "" H 4450 4100 60  0000 C CNN
F 3 "" H 4450 4100 60  0000 C CNN
	1    4450 4100
	1    0    0    -1  
$EndComp
Text GLabel 4400 5050 2    60   Input ~ 0
out24
Text GLabel 4400 4850 2    60   Input ~ 0
out22
Text GLabel 4400 4650 2    60   Input ~ 0
out20
Text GLabel 4400 4450 2    60   Input ~ 0
out18
Wire Wire Line
	2350 1750 2350 2000
Wire Wire Line
	2350 3350 2350 3600
Wire Wire Line
	1800 1650 2350 1650
Connection ~ 1900 1650
Wire Wire Line
	1900 3250 2350 3250
Wire Wire Line
	1750 1350 2350 1350
Connection ~ 2050 1350
Wire Wire Line
	2050 2950 2350 2950
Wire Wire Line
	3750 2750 4050 2750
Wire Wire Line
	3750 2850 4400 2850
Wire Wire Line
	3750 2950 4050 2950
Wire Wire Line
	3750 3050 4400 3050
Wire Wire Line
	3750 3150 4050 3150
Wire Wire Line
	3750 3250 4400 3250
Wire Wire Line
	3750 3350 4050 3350
Wire Wire Line
	3750 3450 4400 3450
Wire Wire Line
	3750 1850 4400 1850
Wire Wire Line
	3750 1750 4100 1750
Wire Wire Line
	3750 1650 4400 1650
Wire Wire Line
	4100 1550 3750 1550
Wire Wire Line
	3750 1450 4400 1450
Wire Wire Line
	3750 1350 4100 1350
Wire Wire Line
	3750 1250 4400 1250
Wire Wire Line
	3750 1150 4100 1150
Wire Wire Line
	1950 3050 2350 3050
Wire Wire Line
	2750 2650 2750 2500
Wire Wire Line
	2750 2500 4450 2500
Wire Wire Line
	2750 1050 2750 850 
Wire Wire Line
	1850 1150 2350 1150
Wire Wire Line
	2350 2750 2350 2300
Wire Wire Line
	2350 2300 3750 2300
Wire Wire Line
	3750 2300 3750 2050
Wire Wire Line
	8300 1150 8850 1150
Wire Wire Line
	8700 1250 8850 1250
Wire Wire Line
	8300 1350 8850 1350
Wire Wire Line
	8700 1450 8850 1450
Wire Wire Line
	8850 1550 8300 1550
Wire Wire Line
	8700 1650 8850 1650
Wire Wire Line
	8850 1750 8300 1750
Wire Wire Line
	8700 1850 8850 1850
Wire Wire Line
	8700 2800 8800 2800
Wire Wire Line
	8800 2900 8300 2900
Wire Wire Line
	8700 3000 8800 3000
Wire Wire Line
	8800 3100 8300 3100
Wire Wire Line
	8700 3200 8800 3200
Wire Wire Line
	8800 3300 8300 3300
Wire Wire Line
	8700 3400 8800 3400
Wire Wire Line
	8250 2700 8800 2700
Wire Wire Line
	10200 1150 9650 1150
Wire Wire Line
	9800 1250 9650 1250
Wire Wire Line
	10200 1350 9650 1350
Wire Wire Line
	9800 1450 9650 1450
Wire Wire Line
	9650 1550 10200 1550
Wire Wire Line
	9800 1650 9650 1650
Wire Wire Line
	9650 1750 10200 1750
Wire Wire Line
	9800 1850 9650 1850
Wire Wire Line
	9700 2800 9600 2800
Wire Wire Line
	9600 2900 10100 2900
Wire Wire Line
	9700 3000 9600 3000
Wire Wire Line
	9600 3100 10100 3100
Wire Wire Line
	9700 3200 9600 3200
Wire Wire Line
	9600 3300 10100 3300
Wire Wire Line
	9700 3400 9600 3400
Wire Wire Line
	10150 2700 9600 2700
Wire Wire Line
	5800 6100 5900 6100
Wire Wire Line
	5900 6200 5400 6200
Wire Wire Line
	5800 6300 5900 6300
Wire Wire Line
	5900 6400 5400 6400
Wire Wire Line
	5800 6500 5900 6500
Wire Wire Line
	5900 6600 5400 6600
Wire Wire Line
	5800 6700 5900 6700
Wire Wire Line
	5350 6000 5900 6000
Wire Wire Line
	5350 4650 5900 4650
Wire Wire Line
	5750 4750 5900 4750
Wire Wire Line
	5350 4850 5900 4850
Wire Wire Line
	5750 4950 5900 4950
Wire Wire Line
	5900 5050 5350 5050
Wire Wire Line
	5750 5150 5900 5150
Wire Wire Line
	5900 5250 5350 5250
Wire Wire Line
	5750 5350 5900 5350
Wire Wire Line
	5900 4550 5500 4550
Wire Wire Line
	5500 4550 5500 4500
Wire Wire Line
	5900 6800 4800 6800
Wire Wire Line
	5800 4300 5800 4450
Wire Wire Line
	5800 4450 5900 4450
Wire Wire Line
	4500 6900 5900 6900
Wire Wire Line
	2200 1550 2350 1550
Wire Wire Line
	2350 1550 2350 1450
Wire Wire Line
	2350 3900 3750 3900
Wire Wire Line
	3750 3900 3750 3650
Connection ~ 1900 3250
Connection ~ 2050 2950
Wire Wire Line
	8100 4800 7700 4800
Wire Wire Line
	7700 4800 7700 4750
Wire Wire Line
	8000 4550 8000 4700
Wire Wire Line
	8000 4700 8100 4700
Wire Wire Line
	8100 5600 7800 5600
Wire Wire Line
	8100 5500 7450 5500
Wire Wire Line
	8100 5400 7800 5400
Wire Wire Line
	8100 5300 7450 5300
Wire Wire Line
	8100 5200 7800 5200
Wire Wire Line
	8100 5100 7450 5100
Wire Wire Line
	8100 5000 7800 5000
Wire Wire Line
	8100 4900 7450 4900
$Comp
L +5V #PWR038
U 1 1 57326A4A
P 1950 4650
F 0 "#PWR038" H 1950 4500 50  0001 C CNN
F 1 "+5V" H 1950 4790 50  0000 C CNN
F 2 "" H 1950 4650 60  0000 C CNN
F 3 "" H 1950 4650 60  0000 C CNN
	1    1950 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 1650 1900 4850
Wire Wire Line
	2050 1350 2050 4550
$Comp
L GND #PWR036
U 1 1 57326A1D
P 2350 5200
F 0 "#PWR036" H 2350 4950 50  0001 C CNN
F 1 "GND" H 2350 5050 50  0000 C CNN
F 2 "" H 2350 5200 60  0000 C CNN
F 3 "" H 2350 5200 60  0000 C CNN
	1    2350 5200
	1    0    0    -1  
$EndComp
Text GLabel 4050 4350 2    60   Input ~ 0
out17
Text GLabel 4050 4550 2    60   Input ~ 0
out19
Text GLabel 4050 4750 2    60   Input ~ 0
out21
Text GLabel 4050 4950 2    60   Input ~ 0
out23
Wire Wire Line
	2350 4950 2350 5200
Wire Wire Line
	1900 4850 2350 4850
Wire Wire Line
	2050 4550 2350 4550
Wire Wire Line
	3750 4350 4050 4350
Wire Wire Line
	3750 4450 4400 4450
Wire Wire Line
	3750 4550 4050 4550
Wire Wire Line
	3750 4650 4400 4650
Wire Wire Line
	3750 4750 4050 4750
Wire Wire Line
	3750 4850 4400 4850
Wire Wire Line
	3750 4950 4050 4950
Wire Wire Line
	3750 5050 4400 5050
Wire Wire Line
	1950 4650 2350 4650
$Comp
L 74HC595 U11
U 1 1 57326A39
P 3050 4800
F 0 "U11" H 3200 5400 70  0000 C CNN
F 1 "74HC595" H 3050 4200 70  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm" H 3050 4800 60  0001 C CNN
F 3 "" H 3050 4800 60  0000 C CNN
	1    3050 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2750 4250 2750 4100
Wire Wire Line
	2750 4100 4450 4100
Wire Wire Line
	2350 4350 2350 3900
$EndSCHEMATC
