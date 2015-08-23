# Intro

Calaos IO is an electronic board designed to controlled as many I/O as possible. It's intented to replace the wago IO modules in a house. It takes places in the electronic board.
Calaos IO is currently in design phase, and it's far to be complete

Look at calaos Wiki for more informations : http://www.calaos.fr/wiki/en/calaos_io_controller

This repository holds the documentation for the software and protocol parts

# doc

The doc foloder contains the state machine definitions and frame format.

# src/stm32

The src folder contains a prototype for an STM32 master on the RS485 bus
In order to build it, the gcc4mbed submodule must be initialized using 

    git submodule update --init
    
Then to fetch the toolchain:

    cd gcc4mbed
    ./linux_install
    
Note that the compiler should be added in your PATH to be used.

Finally go to the src folder and type

    make

