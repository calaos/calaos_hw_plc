#include <mbed.h>
#include <list> 
#include "CalaosPLCBus.h"

CalaosPLCBus plcbus(PA_15, PB_7, PC_2);


int main()
{
	plcbus.discover();
}
