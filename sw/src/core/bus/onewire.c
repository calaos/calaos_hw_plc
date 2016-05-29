/*
Copyright (c) 2007, Jim Studt  (original old version - many contributors since)
 
The latest version of this library may be found at:
  http://www.pjrc.com/teensy/td_libs_OneWire.html
 
OneWire has been maintained by Paul Stoffregen (paul@pjrc.com) since
January 2010.  At the time, it was in need of many bug fixes, but had
been abandoned the original author (Jim Studt).  None of the known
contributors were interested in maintaining OneWire.  Paul typically
works on OneWire every 6 to 12 months.  Patches usually wait that
long.  If anyone is interested in more actively maintaining OneWire,
please contact Paul.
 
Version 2.2:
  Teensy 3.0 compatibility, Paul Stoffregen, paul@pjrc.com
  Arduino Due compatibility, http://arduino.cc/forum/index.php?topic=141030
  Fix DS18B20 example negative temperature
  Fix DS18B20 example's low res modes, Ken Butcher
  Improve reset timing, Mark Tillotson
  Add const qualifiers, Bertrik Sikken
  Add initial value input to crc16, Bertrik Sikken
  Add target_search() function, Scott Roberts
 
Version 2.1:
  Arduino 1.0 compatibility, Paul Stoffregen
  Improve temperature example, Paul Stoffregen
  DS250x_PROM example, Guillermo Lovato
  PIC32 (chipKit) compatibility, Jason Dangel, dangel.jason AT gmail.com
  Improvements from Glenn Trewitt:
  - crc16() now works
  - check_crc16() does all of calculation/checking work.
  - Added read_bytes() and write_bytes(), to reduce tedious loops.
  - Added ds2408 example.
  Delete very old, out-of-date readme file (info is here)
 
Version 2.0: Modifications by Paul Stoffregen, January 2010:
http://www.pjrc.com/teensy/td_libs_OneWire.html
  Search fix from Robin James
    http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1238032295/27#27
  Use direct optimized I/O in all cases
  Disable interrupts during timing critical sections
    (this solves many random communication errors)
  Disable interrupts during read-modify-write I/O
  Reduce RAM consumption by eliminating unnecessary
    variables and trimming many to 8 bits
  Optimize both crc8 - table version moved to flash
 
Modified to work with larger numbers of devices - avoids loop.
Tested in Arduino 11 alpha with 12 sensors.
26 Sept 2008 -- Robin James
http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1238032295/27#27
 
Updated to work with arduino-0008 and to include skip() as of
2007/07/06. --RJL20
 
Modified to calculate the 8-bit CRC directly, avoiding the need for
the 256-byte lookup table to be loaded in RAM.  Tested in arduino-0010
-- Tom Pollard, Jan 23, 2008
 
Jim Studt's original library was modified by Josh Larios.
 
Tom Pollard, pollard@alum.mit.edu, contributed around May 20, 2008
 
Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:
 
The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
Much of the code was inspired by Derek Yerger's code, though I don't
think much of that remains.  In any event that was..
    (copyleft) 2006 by Derek Yerger - Free to distribute freely.
 
The CRC code was excerpted and inspired by the Dallas Semiconductor
sample code bearing this copyright.
//---------------------------------------------------------------------------
// Copyright (C) 2000 Dallas Semiconductor Corporation, All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY,  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL DALLAS SEMICONDUCTOR BE LIABLE FOR ANY CLAIM, DAMAGES
// OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// Except as contained in this notice, the name of Dallas Semiconductor
// shall not be used except as stated in the Dallas Semiconductor
// Branding Policy.
//--------------------------------------------------------------------------
*/
 
#include "onewire.h"
#include "generic_io.h"


#define MAX_1W_BUS	4

static int g_max_onewirebus_id = 0;
static struct onewire_bus *g_onewires[MAX_1W_BUS];

struct onewire_bus {
	gen_io_t *wire;
};	

#if ONEWIRE_SEARCH
    reset_search();
#endif
}
 
 
// Perform the onewire reset function.  We will wait up to 250uS for
// the bus to come high, if it doesn't then it is broken or shorted
// and we return a 0;
//
// Returns 1 if a device asserted a presence pulse, 0 otherwise.
//
uint8_t onewire_reset(void)
{
   uint8_t r;
   uint8_t retries = 125;
 
    wire.input();
    // wait until the wire is high... just in case
    do {
        if (--retries == 0) {
             return 0;
        }
        us_delay(2);
    } while (wire.read() != 1);

    wire.output();
    wire = 0;
    us_delay(480);
    wire.input();
    us_delay(70);
    r = !wire.read();
    us_delay(410);
    return r;
}
 
//
// Write a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
void onewire_write_bit(uint8_t v)
{
    wire.output();
    if (v & 1) {
        wire = 0;   // drive output low
        us_delay(10);
        wire = 1;   // drive output high
        us_delay(55);
    } else {
        wire = 0;   // drive output low
        us_delay(65);
        wire = 1;   // drive output high
        us_delay(5);
    }
}
 
//
// Read a bit. Port and bit is used to cut lookup time and provide
// more certain timing.
//
uint8_t onewire_read_bit(void)
{
    uint8_t r;
 
    wire.output();
    wire = 0;
    us_delay(1);
    wire.input();
    us_delay(6);
    r = wire.read();
    us_delay(54);
    return r;
}
 
//
// Write a byte. The writing code uses the active drivers to raise the
// pin high, if you need power after the write (e.g. DS18S20 in
// parasite power mode) then set 'power' to 1, otherwise the pin will
// go tri-state at the end of the write to avoid heating in a short or
// other mishap.
//
void onewire_write(uint8_t v, uint8_t power /* = 0 */) {
    uint8_t bitMask;
 
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {
    onewire_write_bit( (bitMask & v)?1:0);
    }
    if ( !power) {
        wire.input();
    }
}
 
void onewire_write_bytes(const uint8_t *buf, uint16_t count, bool power /* = 0 */) {
  for (uint16_t i = 0 ; i < count ; i++)
    write(buf[i]);
  if (!power) {
        wire.input();
  }
}
 
//
// Read a byte
//
uint8_t onewire_read() {
    uint8_t bitMask;
    uint8_t r = 0;
 
    for (bitMask = 0x01; bitMask; bitMask <<= 1) {
    if ( onewire_read_bit()) r |= bitMask;
    }
    return r;
}
 
void onewire_read_bytes(uint8_t *buf, uint16_t count) {
  for (uint16_t i = 0 ; i < count ; i++)
    buf[i] = read();
}
 
//
// Do a ROM select
//
void onewire_select(const uint8_t rom[8])
{
    uint8_t i;
 
    write(0x55);           // Choose ROM
 
    for (i = 0; i < 8; i++) write(rom[i]);
}
 
//
// Do a ROM skip
//
void onewire_skip()
{
    write(0xCC);           // Skip ROM
}
 
void onewire_depower()
{
    wire.input();
}
 
#if ONEWIRE_SEARCH
 
//
// You need to use this function to start a search again from the beginning.
// You do not need to do it for the first search, though you could.
//
void onewire_reset_search()
{
  // reset the search state
  LastDiscrepancy = 0;
  LastDeviceFlag = false;
  LastFamilyDiscrepancy = 0;
  for(int i = 7; ; i--) {
    ROM_NO[i] = 0;
    if ( i == 0) break;
  }
}
 
// Setup the search to find the device type 'family_code' on the next call
// to search(*newAddr) if it is present.
//
void onewire_target_search(uint8_t family_code)
{
   // set the search state to find SearchFamily type devices
   ROM_NO[0] = family_code;
   for (uint8_t i = 1; i < 8; i++)
      ROM_NO[i] = 0;
   LastDiscrepancy = 64;
   LastFamilyDiscrepancy = 0;
   LastDeviceFlag = false;
}
 
//
// Perform a search. If this function returns a '1' then it has
// enumerated the next device and you may retrieve the ROM from the
// onewire_address variable. If there are no devices, no further
// devices, or something horrible happens in the middle of the
// enumeration then a 0 is returned.  If a new device is found then
// its address is copied to newAddr.  Use onewire_reset_search() to
// start over.
//
// --- Replaced by the one from the Dallas Semiconductor web site ---
//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
// Return true  : device found, ROM number in ROM_NO buffer
//        false : device not found, end of search
//
uint8_t onewire_search(uint8_t *newAddr)
{
   uint8_t id_bit_number;
   uint8_t last_zero, rom_byte_number, search_result;
   uint8_t id_bit, cmp_id_bit;
 
   unsigned char rom_byte_mask, search_direction;
 
   // initialize for search
   id_bit_number = 1;
   last_zero = 0;
   rom_byte_number = 0;
   rom_byte_mask = 1;
   search_result = 0;
 
   // if the last call was not the last one
   if (!LastDeviceFlag)
   {
      // 1-Wire reset
      if (!reset())
      {
         // reset the search
         LastDiscrepancy = 0;
         LastDeviceFlag = false;
         LastFamilyDiscrepancy = 0;
         return false;
      }
 
      // issue the search command
      write(0xF0);
 
      // loop to do the search
      do
      {
         // read a bit and its complement
         id_bit = read_bit();
         cmp_id_bit = read_bit();
 
         // check for no devices on 1-wire
         if ((id_bit == 1) && (cmp_id_bit == 1))
            break;
         else
         {
            // all devices coupled have 0 or 1
            if (id_bit != cmp_id_bit)
               search_direction = id_bit;  // bit write value for search
            else
            {
               // if this discrepancy if before the Last Discrepancy
               // on a previous next then pick the same as last time
               if (id_bit_number < LastDiscrepancy)
                  search_direction = ((ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
               else
                  // if equal to last pick 1, if not then pick 0
                  search_direction = (id_bit_number == LastDiscrepancy);
 
               // if 0 was picked then record its position in LastZero
               if (search_direction == 0)
               {
                  last_zero = id_bit_number;
 
                  // check for Last discrepancy in family
                  if (last_zero < 9)
                     LastFamilyDiscrepancy = last_zero;
               }
            }
 
            // set or clear the bit in the ROM byte rom_byte_number
            // with mask rom_byte_mask
            if (search_direction == 1)
              ROM_NO[rom_byte_number] |= rom_byte_mask;
            else
              ROM_NO[rom_byte_number] &= ~rom_byte_mask;
 
            // serial number search direction write bit
            write_bit(search_direction);
 
            // increment the byte counter id_bit_number
            // and shift the mask rom_byte_mask
            id_bit_number++;
            rom_byte_mask <<= 1;
 
            // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
            if (rom_byte_mask == 0)
            {
                rom_byte_number++;
                rom_byte_mask = 1;
            }
         }
      }
      while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7
 
      // if the search was successful then
      if (!(id_bit_number < 65))
      {
         // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
         LastDiscrepancy = last_zero;
 
         // check for last device
         if (LastDiscrepancy == 0)
            LastDeviceFlag = true;
 
         search_result = true;
      }
   }
 
   // if no device found then reset counters so next 'search' will be like a first
   if (!search_result || !ROM_NO[0])
   {
      LastDiscrepancy = 0;
      LastDeviceFlag = false;
      LastFamilyDiscrepancy = 0;
      search_result = false;
   }
   for (int i = 0; i < 8; i++) newAddr[i] = ROM_NO[i];
   return search_result;
  }
 
#endif
 
#if ONEWIRE_CRC
// The 1-Wire CRC scheme is described in Maxim Application Note 27:
// "Understanding and Using Cyclic Redundancy Checks with Maxim iButton Products"
// Compute a Dallas Semiconductor 8 bit CRC directly.
//
uint8_t onewire_crc8(const uint8_t *addr, uint8_t len)
{
    uint8_t crc = 0;
    
    while (len--) {
        uint8_t inbyte = *addr++;
        for (uint8_t i = 8; i; i--) {
            uint8_t mix = (crc ^ inbyte) & 0x01;
            crc >>= 1;
            if (mix) crc ^= 0x8C;
            inbyte >>= 1;
        }
    }
    return crc;
}
#endif


static int
onewire_json_parse_one(json_value* json_onewire)
{
	int length, i;
	json_value *value;
	onewire_bus_t *onewire_bus;
	const char *name;
	char mosi[10], miso[10], sck[10];
	int freq = 1000000;

	onewire_bus = calloc(1, sizeof(struct onewire_bus));
        
        PANIC_ON(g_max_onewire_bus_id == MAX_SPI_BUS, "Too many 1w buses\r\n");

        length = json_onwire->u.object.length;
        for (i = 0; i < length; i++) {
		value = json_onewire->u.object.values[i].value;
		name = json_onewire->u.object.values[i].name;

		if (strcmp(name, "name") == 0) {
			onewirebus->name = strdup(value->u.string.ptr);
		} else if (strcmp(name, "freq") == 0) {
			freq = value->u.integer;
			onewire_bus->wire = gen_io_setup(value->u.string.ptr, 0, GPIO_DIR_OUTPUT, 0);
		}
        }

	debug_puts("Adding 1w bus %s\r\n", spibus->name);
	g_spis[g_max_spi_bus_id++] = spibus;

	return 0;
}


