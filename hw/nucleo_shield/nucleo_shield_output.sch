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
L 74HC595 U1
U 1 1 5729AB42
P 2200 1500
F 0 "U1" H 2350 2100 70  0000 C CNN
F 1 "74HC595" H 2200 900 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 1500 60  0001 C CNN
F 3 "" H 2200 1500 60  0000 C CNN
	1    2200 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 5729AB4A
P 1500 1900
F 0 "#PWR048" H 1500 1650 50  0001 C CNN
F 1 "GND" H 1500 1750 50  0000 C CNN
F 2 "" H 1500 1900 60  0000 C CNN
F 3 "" H 1500 1900 60  0000 C CNN
	1    1500 1900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 5729AB50
P 1500 3500
F 0 "#PWR049" H 1500 3250 50  0001 C CNN
F 1 "GND" H 1500 3350 50  0000 C CNN
F 2 "" H 1500 3500 60  0000 C CNN
F 3 "" H 1500 3500 60  0000 C CNN
	1    1500 3500
	1    0    0    -1  
$EndComp
Text GLabel 3250 1050 2    60   Input ~ 0
out1
Text GLabel 3550 1150 2    60   Input ~ 0
out2
Text GLabel 3250 1250 2    60   Input ~ 0
out3
Text GLabel 3550 1350 2    60   Input ~ 0
out4
Text GLabel 3250 1450 2    60   Input ~ 0
out5
Text GLabel 3550 1550 2    60   Input ~ 0
out6
Text GLabel 3250 1650 2    60   Input ~ 0
out7
Text GLabel 3550 1750 2    60   Input ~ 0
out8
Text GLabel 3200 4250 2    60   Input ~ 0
out9
Text GLabel 3550 4350 2    60   Input ~ 0
out10
Text GLabel 3200 4450 2    60   Input ~ 0
out11
Text GLabel 3550 4550 2    60   Input ~ 0
out12
Text GLabel 3200 4650 2    60   Input ~ 0
out13
Text GLabel 3550 4750 2    60   Input ~ 0
out14
Text GLabel 3200 4850 2    60   Input ~ 0
out15
Text GLabel 3550 4950 2    60   Input ~ 0
out16
$Comp
L 74HC595 U2
U 1 1 5729ABCE
P 2200 3100
F 0 "U2" H 2350 3700 70  0000 C CNN
F 1 "74HC595" H 2200 2500 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 3100 60  0001 C CNN
F 3 "" H 2200 3100 60  0000 C CNN
	1    2200 3100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR050
U 1 1 5729ABD5
P 1900 750
F 0 "#PWR050" H 1900 600 50  0001 C CNN
F 1 "+5V" H 1900 890 50  0000 C CNN
F 2 "" H 1900 750 60  0000 C CNN
F 3 "" H 1900 750 60  0000 C CNN
	1    1900 750 
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR051
U 1 1 5729ABDB
P 3600 2400
F 0 "#PWR051" H 3600 2250 50  0001 C CNN
F 1 "+5V" H 3600 2540 50  0000 C CNN
F 2 "" H 3600 2400 60  0000 C CNN
F 3 "" H 3600 2400 60  0000 C CNN
	1    3600 2400
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR052
U 1 1 5729ABE8
P 1350 1450
F 0 "#PWR052" H 1350 1300 50  0001 C CNN
F 1 "+5V" H 1350 1590 50  0000 C CNN
F 2 "" H 1350 1450 60  0000 C CNN
F 3 "" H 1350 1450 60  0000 C CNN
	1    1350 1450
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR053
U 1 1 5729ABEE
P 1100 2950
F 0 "#PWR053" H 1100 2800 50  0001 C CNN
F 1 "+5V" H 1100 3090 50  0000 C CNN
F 2 "" H 1100 2950 60  0000 C CNN
F 3 "" H 1100 2950 60  0000 C CNN
	1    1100 2950
	1    0    0    -1  
$EndComp
Text HLabel 1000 1050 0    60   Input ~ 0
SRDATA
Text HLabel 900  1250 0    60   Input ~ 0
SRCLK
Text HLabel 950  1550 0    60   Input ~ 0
SRLatch
$Comp
L ULN2803 U10
U 1 1 57307CE9
P 7150 1250
F 0 "U10" H 7300 1800 60  0000 C CNN
F 1 "ULN2803" H 7400 1700 60  0000 C CNN
F 2 "Housings_DIP:DIP-18__300" H 7150 1250 60  0001 C CNN
F 3 "" H 7150 1250 60  0000 C CNN
	1    7150 1250
	1    0    0    -1  
$EndComp
$Comp
L ULN2803 U9
U 1 1 57307D12
P 7600 2900
F 0 "U9" H 7750 3450 60  0000 C CNN
F 1 "ULN2803" H 7850 3350 60  0000 C CNN
F 2 "Housings_DIP:DIP-18__300" H 7600 2900 60  0001 C CNN
F 3 "" H 7600 2900 60  0000 C CNN
	1    7600 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR054
U 1 1 57307D6B
P 7150 1750
F 0 "#PWR054" H 7150 1500 50  0001 C CNN
F 1 "GND" H 7150 1600 50  0000 C CNN
F 2 "" H 7150 1750 60  0000 C CNN
F 3 "" H 7150 1750 60  0000 C CNN
	1    7150 1750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR055
U 1 1 57307D82
P 7600 3400
F 0 "#PWR055" H 7600 3150 50  0001 C CNN
F 1 "GND" H 7600 3250 50  0000 C CNN
F 2 "" H 7600 3400 60  0000 C CNN
F 3 "" H 7600 3400 60  0000 C CNN
	1    7600 3400
	1    0    0    -1  
$EndComp
$Comp
L +24V #PWR056
U 1 1 57307DA1
P 7150 750
F 0 "#PWR056" H 7150 600 50  0001 C CNN
F 1 "+24V" H 7150 890 50  0000 C CNN
F 2 "" H 7150 750 60  0000 C CNN
F 3 "" H 7150 750 60  0000 C CNN
	1    7150 750 
	1    0    0    -1  
$EndComp
Text GLabel 6600 1600 0    60   Input ~ 0
out1
Text GLabel 6200 1500 0    60   Input ~ 0
out2
Text GLabel 6600 1400 0    60   Input ~ 0
out3
Text GLabel 6200 1300 0    60   Input ~ 0
out4
Text GLabel 6600 1200 0    60   Input ~ 0
out5
Text GLabel 6200 1100 0    60   Input ~ 0
out6
Text GLabel 6600 1000 0    60   Input ~ 0
out7
Text GLabel 6200 900  0    60   Input ~ 0
out8
Text GLabel 7100 3250 0    60   Input ~ 0
out9
Text GLabel 6700 3150 0    60   Input ~ 0
out10
Text GLabel 7100 3050 0    60   Input ~ 0
out11
Text GLabel 6700 2950 0    60   Input ~ 0
out12
Text GLabel 7100 2850 0    60   Input ~ 0
out13
Text GLabel 6700 2750 0    60   Input ~ 0
out14
Text GLabel 7100 2650 0    60   Input ~ 0
out15
Text GLabel 6650 2550 0    60   Input ~ 0
out16
$Comp
L CONN_01X08 P10
U 1 1 5730818B
P 10300 1400
F 0 "P10" H 10300 1950 50  0000 C CNN
F 1 "CONN_OUTH1" V 10400 1400 50  0000 C CNN
F 2 "w_conn_screw:mors_8p" H 10300 1400 60  0001 C CNN
F 3 "" H 10300 1400 60  0000 C CNN
	1    10300 1400
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P11
U 1 1 573081DD
P 10350 2950
F 0 "P11" H 10350 3500 50  0000 C CNN
F 1 "CONN_OUTH2" V 10450 2950 50  0000 C CNN
F 2 "w_conn_screw:mors_8p" H 10350 2950 60  0001 C CNN
F 3 "" H 10350 2950 60  0000 C CNN
	1    10350 2950
	1    0    0    -1  
$EndComp
Text GLabel 7700 1600 2    60   Input ~ 0
out1h
Text GLabel 8100 1500 2    60   Input ~ 0
out2h
Text GLabel 7700 1400 2    60   Input ~ 0
out3h
Text GLabel 8100 1300 2    60   Input ~ 0
out4h
Text GLabel 7700 1200 2    60   Input ~ 0
out5h
Text GLabel 8100 1100 2    60   Input ~ 0
out6h
Text GLabel 7700 1000 2    60   Input ~ 0
out7h
Text GLabel 8100 900  2    60   Input ~ 0
out8h
Text GLabel 8100 3250 2    60   Input ~ 0
out9h
Text GLabel 8500 3150 2    60   Input ~ 0
out10h
Text GLabel 8100 3050 2    60   Input ~ 0
out11h
Text GLabel 8500 2950 2    60   Input ~ 0
out12h
Text GLabel 8100 2850 2    60   Input ~ 0
out13h
Text GLabel 8500 2750 2    60   Input ~ 0
out14h
Text GLabel 8100 2650 2    60   Input ~ 0
out15h
Text GLabel 8550 2550 2    60   Input ~ 0
out16h
Text GLabel 9600 2600 0    60   Input ~ 0
out9h
Text GLabel 10050 2700 0    60   Input ~ 0
out10h
Text GLabel 9650 2800 0    60   Input ~ 0
out11h
Text GLabel 10050 2900 0    60   Input ~ 0
out12h
Text GLabel 9650 3000 0    60   Input ~ 0
out13h
Text GLabel 10050 3100 0    60   Input ~ 0
out14h
Text GLabel 9650 3200 0    60   Input ~ 0
out15h
Text GLabel 10050 3300 0    60   Input ~ 0
out16h
Text GLabel 9550 1050 0    60   Input ~ 0
out1h
Text GLabel 9950 1150 0    60   Input ~ 0
out2h
Text GLabel 9550 1250 0    60   Input ~ 0
out3h
Text GLabel 9950 1350 0    60   Input ~ 0
out4h
Text GLabel 9550 1450 0    60   Input ~ 0
out5h
Text GLabel 9950 1550 0    60   Input ~ 0
out6h
Text GLabel 9550 1650 0    60   Input ~ 0
out7h
Text GLabel 9950 1750 0    60   Input ~ 0
out8h
$Comp
L CONN_01X10 P2
U 1 1 57326C94
P 5500 4650
F 0 "P2" H 5500 5200 50  0000 C CNN
F 1 "CONN_OUT3" V 5600 4650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 5500 4650 60  0001 C CNN
F 3 "" H 5500 4650 60  0000 C CNN
	1    5500 4650
	1    0    0    -1  
$EndComp
Text GLabel 5000 5100 0    60   Input ~ 0
out17
Text GLabel 4650 5000 0    60   Input ~ 0
out18
Text GLabel 5000 4900 0    60   Input ~ 0
out19
Text GLabel 4650 4800 0    60   Input ~ 0
out20
Text GLabel 5000 4700 0    60   Input ~ 0
out21
Text GLabel 4650 4600 0    60   Input ~ 0
out22
Text GLabel 5000 4500 0    60   Input ~ 0
out23
Text GLabel 4650 4400 0    60   Input ~ 0
out24
Text GLabel 3550 3350 2    60   Input ~ 0
out24
Text GLabel 3550 3150 2    60   Input ~ 0
out22
Text GLabel 3550 2950 2    60   Input ~ 0
out20
Text GLabel 3550 2750 2    60   Input ~ 0
out18
$Comp
L +5V #PWR057
U 1 1 57326A4A
P 950 4650
F 0 "#PWR057" H 950 4500 50  0001 C CNN
F 1 "+5V" H 950 4790 50  0000 C CNN
F 2 "" H 950 4650 60  0000 C CNN
F 3 "" H 950 4650 60  0000 C CNN
	1    950  4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR058
U 1 1 57326A1D
P 1500 5100
F 0 "#PWR058" H 1500 4850 50  0001 C CNN
F 1 "GND" H 1500 4950 50  0000 C CNN
F 2 "" H 1500 5100 60  0000 C CNN
F 3 "" H 1500 5100 60  0000 C CNN
	1    1500 5100
	1    0    0    -1  
$EndComp
Text GLabel 3200 2650 2    60   Input ~ 0
out17
Text GLabel 3200 2850 2    60   Input ~ 0
out19
Text GLabel 3200 3050 2    60   Input ~ 0
out21
Text GLabel 3200 3250 2    60   Input ~ 0
out23
$Comp
L 74HC595 U11
U 1 1 57326A39
P 2200 4700
F 0 "U11" H 2350 5300 70  0000 C CNN
F 1 "74HC595" H 2200 4100 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 4700 60  0001 C CNN
F 3 "" H 2200 4700 60  0000 C CNN
	1    2200 4700
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR059
U 1 1 5733141E
P 3600 5600
F 0 "#PWR059" H 3600 5450 50  0001 C CNN
F 1 "+5V" H 3600 5740 50  0000 C CNN
F 2 "" H 3600 5600 60  0000 C CNN
F 3 "" H 3600 5600 60  0000 C CNN
	1    3600 5600
	1    0    0    -1  
$EndComp
Text GLabel 3550 6550 2    60   Input ~ 0
out32
Text GLabel 3550 6350 2    60   Input ~ 0
out30
Text GLabel 3550 6150 2    60   Input ~ 0
out28
Text GLabel 3550 5950 2    60   Input ~ 0
out26
$Comp
L +5V #PWR060
U 1 1 5733142A
P 1100 6150
F 0 "#PWR060" H 1100 6000 50  0001 C CNN
F 1 "+5V" H 1100 6290 50  0000 C CNN
F 2 "" H 1100 6150 60  0000 C CNN
F 3 "" H 1100 6150 60  0000 C CNN
	1    1100 6150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR061
U 1 1 57331432
P 1500 6700
F 0 "#PWR061" H 1500 6450 50  0001 C CNN
F 1 "GND" H 1500 6550 50  0000 C CNN
F 2 "" H 1500 6700 60  0000 C CNN
F 3 "" H 1500 6700 60  0000 C CNN
	1    1500 6700
	1    0    0    -1  
$EndComp
Text GLabel 3200 5850 2    60   Input ~ 0
out25
Text GLabel 3200 6050 2    60   Input ~ 0
out27
Text GLabel 3200 6250 2    60   Input ~ 0
out29
Text GLabel 3200 6450 2    60   Input ~ 0
out31
$Comp
L 74HC595 U12
U 1 1 57331448
P 2200 6300
F 0 "U12" H 2350 6900 70  0000 C CNN
F 1 "74HC595" H 2200 5700 70  0000 C CNN
F 2 "Housings_DIP:DIP-16__300" H 2200 6300 60  0001 C CNN
F 3 "" H 2200 6300 60  0000 C CNN
	1    2200 6300
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X10 P8
U 1 1 57331532
P 5900 6350
F 0 "P8" H 5900 6900 50  0000 C CNN
F 1 "CONN_OUT4" V 6000 6350 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x10" H 5900 6350 60  0001 C CNN
F 3 "" H 5900 6350 60  0000 C CNN
	1    5900 6350
	1    0    0    -1  
$EndComp
Text GLabel 5050 5900 0    60   Input ~ 0
out32
Text GLabel 5050 6100 0    60   Input ~ 0
out30
Text GLabel 5050 6300 0    60   Input ~ 0
out28
Text GLabel 5050 6500 0    60   Input ~ 0
out26
Text GLabel 5400 6600 0    60   Input ~ 0
out25
Text GLabel 5400 6400 0    60   Input ~ 0
out27
Text GLabel 5400 6200 0    60   Input ~ 0
out29
Text GLabel 5400 6000 0    60   Input ~ 0
out31
$Comp
L +24V #PWR062
U 1 1 57334377
P 7600 2100
F 0 "#PWR062" H 7600 1950 50  0001 C CNN
F 1 "+24V" H 7600 2240 50  0000 C CNN
F 2 "" H 7600 2100 60  0000 C CNN
F 3 "" H 7600 2100 60  0000 C CNN
	1    7600 2100
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR063
U 1 1 576808E1
P 3300 4050
F 0 "#PWR063" H 3300 3900 50  0001 C CNN
F 1 "+5V" H 3300 4190 50  0000 C CNN
F 2 "" H 3300 4050 60  0000 C CNN
F 3 "" H 3300 4050 60  0000 C CNN
	1    3300 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1900 4050 3300 4050
Wire Wire Line
	1900 4150 1900 4050
Wire Wire Line
	950  4650 1500 4650
Wire Wire Line
	1200 1250 1200 6050
Wire Wire Line
	1050 1550 1050 6350
Wire Wire Line
	7600 2400 7600 2100
Wire Wire Line
	5700 5900 5050 5900
Wire Wire Line
	5700 6000 5400 6000
Wire Wire Line
	5700 6100 5050 6100
Wire Wire Line
	5700 6200 5400 6200
Wire Wire Line
	5700 6300 5050 6300
Wire Wire Line
	5700 6400 5400 6400
Wire Wire Line
	5700 6500 5050 6500
Wire Wire Line
	5700 6600 5400 6600
Wire Wire Line
	1500 5850 1500 5400
Wire Wire Line
	1900 5600 3600 5600
Wire Wire Line
	1900 5750 1900 5600
Wire Wire Line
	1100 6150 1500 6150
Wire Wire Line
	2900 6550 3550 6550
Wire Wire Line
	2900 6450 3200 6450
Wire Wire Line
	2900 6350 3550 6350
Wire Wire Line
	2900 6250 3200 6250
Wire Wire Line
	2900 6150 3550 6150
Wire Wire Line
	2900 6050 3200 6050
Wire Wire Line
	2900 5950 3550 5950
Wire Wire Line
	2900 5850 3200 5850
Wire Wire Line
	1200 6050 1500 6050
Wire Wire Line
	1050 6350 1500 6350
Wire Wire Line
	1500 6450 1500 6700
Wire Wire Line
	2900 5400 2900 5150
Wire Wire Line
	1500 5400 2900 5400
Wire Wire Line
	1500 4650 1500 4550
Wire Wire Line
	2900 3350 3550 3350
Wire Wire Line
	2900 3250 3200 3250
Wire Wire Line
	2900 3150 3550 3150
Wire Wire Line
	2900 3050 3200 3050
Wire Wire Line
	2900 2950 3550 2950
Wire Wire Line
	2900 2850 3200 2850
Wire Wire Line
	2900 2750 3550 2750
Wire Wire Line
	2900 2650 3200 2650
Wire Wire Line
	1500 4850 1500 5100
Wire Wire Line
	5300 4400 4650 4400
Wire Wire Line
	5300 4500 5000 4500
Wire Wire Line
	5300 4600 4650 4600
Wire Wire Line
	5300 4700 5000 4700
Wire Wire Line
	5300 4800 4650 4800
Wire Wire Line
	5300 4900 5000 4900
Wire Wire Line
	5300 5000 4650 5000
Wire Wire Line
	5300 5100 5000 5100
Connection ~ 1200 2850
Connection ~ 1050 3150
Wire Wire Line
	1500 1450 1500 1350
Wire Wire Line
	1350 1450 1500 1450
Wire Wire Line
	9950 1750 10100 1750
Wire Wire Line
	10100 1650 9550 1650
Wire Wire Line
	9950 1550 10100 1550
Wire Wire Line
	10100 1450 9550 1450
Wire Wire Line
	9950 1350 10100 1350
Wire Wire Line
	9550 1250 10100 1250
Wire Wire Line
	9950 1150 10100 1150
Wire Wire Line
	9550 1050 10100 1050
Wire Wire Line
	9600 2600 10150 2600
Wire Wire Line
	10050 3300 10150 3300
Wire Wire Line
	10150 3200 9650 3200
Wire Wire Line
	10050 3100 10150 3100
Wire Wire Line
	10150 3000 9650 3000
Wire Wire Line
	10050 2900 10150 2900
Wire Wire Line
	10150 2800 9650 2800
Wire Wire Line
	10050 2700 10150 2700
Wire Wire Line
	8550 2550 8000 2550
Wire Wire Line
	8100 3250 8000 3250
Wire Wire Line
	8000 3150 8500 3150
Wire Wire Line
	8100 3050 8000 3050
Wire Wire Line
	8000 2950 8500 2950
Wire Wire Line
	8100 2850 8000 2850
Wire Wire Line
	8000 2750 8500 2750
Wire Wire Line
	8100 2650 8000 2650
Wire Wire Line
	7700 1600 7550 1600
Wire Wire Line
	7550 1500 8100 1500
Wire Wire Line
	7700 1400 7550 1400
Wire Wire Line
	7550 1300 8100 1300
Wire Wire Line
	7700 1200 7550 1200
Wire Wire Line
	8100 1100 7550 1100
Wire Wire Line
	7700 1000 7550 1000
Wire Wire Line
	8100 900  7550 900 
Wire Wire Line
	6650 2550 7200 2550
Wire Wire Line
	7100 3250 7200 3250
Wire Wire Line
	7200 3150 6700 3150
Wire Wire Line
	7100 3050 7200 3050
Wire Wire Line
	7200 2950 6700 2950
Wire Wire Line
	7100 2850 7200 2850
Wire Wire Line
	7200 2750 6700 2750
Wire Wire Line
	7100 2650 7200 2650
Wire Wire Line
	6600 1600 6750 1600
Wire Wire Line
	6750 1500 6200 1500
Wire Wire Line
	6600 1400 6750 1400
Wire Wire Line
	6750 1300 6200 1300
Wire Wire Line
	6600 1200 6750 1200
Wire Wire Line
	6200 1100 6750 1100
Wire Wire Line
	6600 1000 6750 1000
Wire Wire Line
	6200 900  6750 900 
Wire Wire Line
	2900 2200 2900 1950
Wire Wire Line
	1500 2200 2900 2200
Wire Wire Line
	1500 2650 1500 2200
Wire Wire Line
	1000 1050 1500 1050
Wire Wire Line
	1900 950  1900 750 
Wire Wire Line
	1900 2400 3600 2400
Wire Wire Line
	1900 2550 1900 2400
Wire Wire Line
	1100 2950 1500 2950
Wire Wire Line
	2900 1050 3250 1050
Wire Wire Line
	2900 1150 3550 1150
Wire Wire Line
	2900 1250 3250 1250
Wire Wire Line
	2900 1350 3550 1350
Wire Wire Line
	3250 1450 2900 1450
Wire Wire Line
	2900 1550 3550 1550
Wire Wire Line
	2900 1650 3250 1650
Wire Wire Line
	2900 1750 3550 1750
Wire Wire Line
	2900 4950 3550 4950
Wire Wire Line
	2900 4850 3200 4850
Wire Wire Line
	2900 4750 3550 4750
Wire Wire Line
	2900 4650 3200 4650
Wire Wire Line
	2900 4550 3550 4550
Wire Wire Line
	2900 4450 3200 4450
Wire Wire Line
	2900 4350 3550 4350
Wire Wire Line
	2900 4250 3200 4250
Wire Wire Line
	1200 2850 1500 2850
Connection ~ 1200 1250
Wire Wire Line
	900  1250 1500 1250
Wire Wire Line
	1050 3150 1500 3150
Connection ~ 1050 1550
Wire Wire Line
	950  1550 1500 1550
Wire Wire Line
	1500 3250 1500 3500
Wire Wire Line
	1500 1650 1500 1900
$Comp
L +5V #PWR064
U 1 1 5769D296
P 5050 7000
F 0 "#PWR064" H 5050 6850 50  0001 C CNN
F 1 "+5V" H 5050 7140 50  0000 C CNN
F 2 "" H 5050 7000 60  0000 C CNN
F 3 "" H 5050 7000 60  0000 C CNN
	1    5050 7000
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR065
U 1 1 5769D305
P 5600 7000
F 0 "#PWR065" H 5600 6750 50  0001 C CNN
F 1 "GND" H 5600 6850 50  0000 C CNN
F 2 "" H 5600 7000 60  0000 C CNN
F 3 "" H 5600 7000 60  0000 C CNN
	1    5600 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 6700 5050 6700
Wire Wire Line
	5050 6700 5050 7000
Wire Wire Line
	5600 7000 5600 6800
Wire Wire Line
	5600 6800 5700 6800
$Comp
L +5V #PWR066
U 1 1 5769D8BC
P 4300 3950
F 0 "#PWR066" H 4300 3800 50  0001 C CNN
F 1 "+5V" H 4300 4090 50  0000 C CNN
F 2 "" H 4300 3950 60  0000 C CNN
F 3 "" H 4300 3950 60  0000 C CNN
	1    4300 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR067
U 1 1 5769D8DB
P 4700 3950
F 0 "#PWR067" H 4700 3700 50  0001 C CNN
F 1 "GND" H 4700 3800 50  0000 C CNN
F 2 "" H 4700 3950 60  0000 C CNN
F 3 "" H 4700 3950 60  0000 C CNN
	1    4700 3950
	-1   0    0    1   
$EndComp
Wire Wire Line
	5300 4300 4300 4300
Wire Wire Line
	4300 4300 4300 3950
Wire Wire Line
	4700 3950 4700 4200
Wire Wire Line
	4700 4200 5300 4200
Wire Wire Line
	2900 3550 2900 3950
Wire Wire Line
	2900 3950 1500 3950
Wire Wire Line
	1500 3950 1500 4250
Wire Wire Line
	1500 4450 1200 4450
Connection ~ 1200 4450
Wire Wire Line
	1500 4750 1050 4750
Connection ~ 1050 4750
$EndSCHEMATC
