/*
 * Dallas' DS1820 family temperature sensor.
 * This library depends on the OneWire library (Dallas' 1-Wire bus protocol implementation)
 * available at <http://developer.mbed.org/users/hudakz/code/OneWire/>
 *
 * Example of use:
 * 
 * #include "DS1820.h"
 *
 * Serial serial(USBTX, USBRX);
 * 
 * int main() {
 *     DS1820  ds1820(PA_9);    // substitute PA_9 with actual mbed pin name connected to the DS1820 data pin
 *
 *     if(ds1820.begin()) {
 *	ds1820.startConversion();
 *	wait(1.0);
 *	while(1) {
 *	    dbg_log("temp = %3.1f\n", ds1820.read());     // read temperature
 *	    ds1820.startConversion();     // start temperature conversion
 *	    wait(1.0);		    // let DS1820 complete the temperature conversion
 *	}
 *    } else
 *	dbg_log("No DS1820 sensor found!\n");
 * }
 *
 * 
 * Note: Don't forget to connect a 4.7k Ohm resistor 
 *       between the DS1820's data pin and the +3.3V pin
 *
 */

#include "utils.h"
#include "ds1820.h"
#include "onewire.h"

#include <stdbool.h>

typedef struct ds1820 {
    onewire_bus_t *onewire;
    bool model_s;
    uint8_t data[12];
    uint8_t addr[8];
} ds1820_t;

void ds1820_set_resolution(ds1820_t *ds, uint8_t res);
void ds1820_start_conversion(ds1820_t *ds);
uint8_t ds1820_read(ds1820_t *ds, float *temp);

/**
 * @brief   Converts a 16-bit signed fixed point value to floating point value
 * @note    The 16-bit unsigned integer represnts actually
 *	  a 16-bit signed fixed point value:
 *	  1 sign bit, 7 integer bits, 8 fractional bits (two’s compliment
 *	  and the LSB of the 16-bit binary number represents 1/256th of a unit).       
 * @param   16-bit unsigned integer
 * @retval  Floating point value
 */
static inline 
float ds1820_to_float(uint16_t word) {
    if (word & 0x8000)
	return (-((float) ((uint16_t) (~word + 1))) / 256.0f);
    else
	return (((float) word) / 256.0f);
}
 
/**
 * @brief   Detects and initializes the actual DS1820 model
 * @note
 * @param
 * @retval  true:   if a DS1820 family sensor was detected and initialized
	    false:  otherwise
 */
bool ds1820_search(ds1820_t *ds) {
	onewire_bus_reset_search(ds->onewire);
	ms_delay(250);

	if(!onewire_bus_search(ds->onewire, ds->addr)) {
		dbg_log("No addresses.\n");
		onewire_bus_reset_search(ds->onewire);
		ms_delay(250);
		return false;
	}

	if(onewire_bus_crc8(ds->addr, 7) != ds->addr[7])
		return false;
 
	// the first ROM byte indicates which chip
	switch(ds->addr[0]) {
	case 0x10:
		ds->model_s = true;
		dbg_log("DS18S20 or old DS1820\n");
		break;

	case 0x28:
		ds->model_s = false;
		dbg_log("DS18B20\n");
		break;

	case 0x22:
		ds->model_s = false;
		dbg_log("DS1822\n");
		break;

	default:
		dbg_log("Device doesn't belong to the DS1820 family\n");
		return false;
	}

	return true;
}

/**
 * @brief   Sets temperature-to-digital conversion resolution.
 * @note    The configuration register allows the user to set the resolution
 *	  of the temperature-to-digital conversion to 9, 10, 11, or 12 bits.
 *	  Defaults to 12-bit resolution for DS18B20.
 *	  DS18S20 allows only 9-bit resolution.
 * @param   res:    Resolution of the temperature-to-digital conversion in bits.
 * @retval
 */
void ds1820_set_resolution(ds1820_t *ds, uint8_t res)
{
	uint8_t i;

	// keep resolution within limits
	if(res > 12)
		res = 12;
	if(res < 9)
		res = 9;      
	if(ds->model_s)
		res = 9;
       
	onewire_bus_reset(ds->onewire);
	onewire_bus_skip(ds->onewire);
	onewire_bus_write(ds->onewire, 0xBE, 0);	    // to read Scratchpad
	for(i = 0; i < 9; i++)  // read Scratchpad bytes
		ds->data[i] = onewire_bus_read(ds->onewire);   

	ds->data[4] |= (res - 9) << 5;      // update configuration byte (set resolution)  
	onewire_bus_reset(ds->onewire);
	onewire_bus_skip(ds->onewire);
	onewire_bus_write(ds->onewire, 0x4E, 0);	    // to write into Scratchpad
	for(i = 2; i < 5; i++)  // write three bytes (2nd, 3rd, 4th) into Scratchpad
		onewire_bus_write(ds->onewire, ds->data[i], 0);
}
 
/**
 * @brief   Starts temperature conversion
 * @note    The time to complete the converion depends on the selected resolution:
 *	   9-bit resolution -> max conversion time = 93.75ms
 *	  10-bit resolution -> max conversion time = 187.5ms
 *	  11-bit resolution -> max conversion time = 375ms
 *	  12-bit resolution -> max conversion time = 750ms
 * @param
 * @retval
 */
void ds1820_start_conversion(ds1820_t *ds) {

	onewire_bus_reset(ds->onewire);
	onewire_bus_skip(ds->onewire);
	onewire_bus_write(ds->onewire, 0x44, 0);    //start temperature conversion
}

/**
 * @brief   Reads temperature from chip's scratchpad.
 * @note    Verifies data integrity by calculating cyclic redundancy check (CRC).
 *	  If the calculated CRC dosn't match the one stored in chip's scratchpad register
 *	  the temperature variable is not updated and CRC error code is returned.
 * @param   temp: The temperature variable to be updated by this routine.
 *		(It's passed as reference to floating point.)
 * @retval  error code:
 *	      0 - no errors ('temp' contains the temperature measured)
 *	      1 - sensor not present ('temp' is not updated)
 *	      2 - CRC error ('temp' is not updated)
 */
uint8_t ds1820_read(ds1820_t *ds, float *temp)
{
	uint8_t i;

	onewire_bus_reset(ds->onewire);
	onewire_bus_skip(ds->onewire);
	onewire_bus_write(ds->onewire, 0xBE, 0);	    // to read Scratchpad
	for(i = 0; i < 9; i++)  // reading scratchpad registers
	    ds->data[i] = onewire_bus_read(ds->onewire);
 
	if(onewire_bus_crc8(ds->data, 8) != ds->data[8])    // if calculated CRC does not match the stored one
	    return 2;			   // return with CRC error
 
	// Convert the raw bytes to a 16bit unsigned value
	uint16_t *p_word = (uint16_t *) ds->data;
 
	dbg_log("raw = %#x\n", *p_word);
 
	if(ds->model_s) {
	    *p_word = *p_word << 3;	 // 9 bit resolution,  max conversion time = 750ms
	    if(ds->data[7] == 0x10) {
 
		// "count remain" gives full 12 bit resolution
		*p_word = (*p_word & 0xFFF0) + 12 - ds->data[6];
	    }

	}
	else {
	    uint8_t cfg = (ds->data[4] & 0x60); // default 12bit resolution, max conversion time = 750ms
 
	    // at lower resolution, the low bits are undefined, so let's clear them
	    if(cfg == 0x00)
		*p_word = *p_word &~7;      //  9bit resolution, max conversion time = 93.75ms
	    else
	    if(cfg == 0x20)
		*p_word = *p_word &~3;      // 10bit resolution, max conversion time = 187.5ms
	    else
	    if(cfg == 0x40)
		*p_word = *p_word &~1;      // 11bit resolution, max conversion time = 375ms
 
	}

	// Convert the raw bytes to a 16bit signed fixed point value :
	// 1 sign bit, 7 integer bits, 8 fractional bits (two's compliment
	// and the LSB of the 16bit binary number represents 1/256th of a unit).
	*p_word = *p_word << 4;
	// Convert to floating point value
	*temp = ds1820_to_float(*p_word);
	return 0;   // return with no errors
}

 
