#ifndef OneWire_h
#define OneWire_h
 
#include <inttypes.h>
#include <stdbool.h>
 
// You can exclude certain features from OneWire.  In theory, this
// might save some space.  In practice, the compiler automatically
// removes unused code (technically, the linker, using -fdata-sections
// and -ffunction-sections when compiling, and Wl,--gc-sections
// when linking), so most of these will not result in any code size
// reduction.  Well, unless you try to use the missing features
// and redesign your program to not need them!  ONEWIRE_CRC8_TABLE
// is the exception, because it selects a fast but large algorithm
// or a small but slow algorithm.
 
// you can exclude onewire_search by defining that to 0
#ifndef ONEWIRE_SEARCH
#define ONEWIRE_SEARCH 1
#endif
 
// You can exclude CRC checks altogether by defining this to 0
#ifndef ONEWIRE_CRC
#define ONEWIRE_CRC 1
#endif

typedef struct onewire_bus onewire_bus_t;

void
onewire_bus_init();
 
onewire_bus_t *
onewire_bus_get_by_name(const char *name);

 
// Perform a 1-Wire reset cycle. Returns 1 if a device responds
// with a presence pulse.  Returns 0 if there is no device or the
// bus is shorted or otherwise held low for more than 250uS
uint8_t onewire_bus_reset(onewire_bus_t *onewire);

// Issue a 1-Wire rom select command, you do the reset first.
void onewire_bus_select(onewire_bus_t *onewire, const uint8_t rom[8]);

// Issue a 1-Wire rom skip command, to address all on bus.
void onewire_bus_skip(onewire_bus_t *onewire);

// Write a byte. If 'power' is one then the wire is held high at
// the end for parasitically powered devices. You are responsible
// for eventually depowering it by calling depower() or doing
// another read or write.
void onewire_bus_write(onewire_bus_t *onewire, uint8_t v, uint8_t power);

void onewire_bus_write_bytes(onewire_bus_t *onewire, const uint8_t *buf, uint16_t count, bool);

// Read a byte.
uint8_t onewire_bus_read(onewire_bus_t *onewire);

void onewire_bus_read_bytes(onewire_bus_t *onewire, uint8_t *buf, uint16_t count);

// Write a bit. The bus is always left powered at the end, see
// note in write() about that.
void onewire_bus_write_bit(onewire_bus_t *onewire, uint8_t v);

// Read a bit.
uint8_t onewire_bus_read_bit(onewire_bus_t *onewire);

// Stop forcing power onto the bus. You only need to do this if
// you used the 'power' flag to write() or used a write_bit() call
// and aren't about to do another read or write. You would rather
// not leave this powered if you don't have to, just in case
// someone shorts your bus.
void onewire_bus_depower(onewire_bus_t *onewire);

#if ONEWIRE_SEARCH
// Clear the search state so that if will start from the beginning again.
void onewire_bus_reset_search(onewire_bus_t *onewire);

// Setup the search to find the device type 'family_code' on the next call
// to search(*newAddr) if it is present.
void onewire_bus_target_search(onewire_bus_t *onewire, uint8_t family_code);

// Look for the next device. Returns 1 if a new address has been
// returned. A zero might mean that the bus is shorted, there are
// no devices, or you have already retrieved all of them.  It
// might be a good idea to check the CRC to make sure you didn't
// get garbage.  The order is deterministic. You will always get
// the same devices in the same order.
uint8_t onewire_bus_search(onewire_bus_t *onewire, uint8_t *newAddr);
#endif

#if ONEWIRE_CRC
// Compute a Dallas Semiconductor 8 bit CRC, these are used in the
// ROM and scratchpad registers.
uint8_t onewire_bus_crc8(const uint8_t *addr, uint8_t len);

#if ONEWIRE_CRC16
// Compute the 1-Wire CRC16 and compare it against the received CRC.
// Example usage (reading a DS2408):
//    // Put everything in a buffer so we can compute the CRC easily.
//    uint8_t buf[13];
//    buf[0] = 0xF0;    // Read PIO Registers
//    buf[1] = 0x88;    // LSB address
//    buf[2] = 0x00;    // MSB address
//    WriteBytes(net, buf, 3);    // Write 3 cmd bytes
//    ReadBytes(net, buf+3, 10);  // Read 6 data bytes, 2 0xFF, 2 CRC16
//    if (!CheckCRC16(buf, 11, &buf[11])) {
//        // Handle error.
//    }     
//          
// @param input - Array of bytes to checksum.
// @param len - How many bytes to use.
// @param inverted_crc - The two CRC16 bytes in the received data.
//                       This should just point into the received data,
//                       *not* at a 16-bit integer.
// @param crc - The crc starting value (optional)
// @return True, iff the CRC matches.
bool onewire_bus_check_crc16(const uint8_t* input, uint16_t len, const uint8_t* inverted_crc, uint16_t crc = 0);

// Compute a Dallas Semiconductor 16 bit CRC.  This is required to check
// the integrity of data received from many 1-Wire devices.  Note that the
// CRC computed here is *not* what you'll get from the 1-Wire network,
// for two reasons:
//   1) The CRC is transmitted bitwise inverted.
//   2) Depending on the endian-ness of your processor, the binary
//      representation of the two-byte return value may have a different
//      byte order than the two bytes you get from 1-Wire.
// @param input - Array of bytes to checksum.
// @param len - How many bytes to use.
// @param crc - The crc starting value (optional)
// @return The CRC16, as defined by Dallas Semiconductor.
uint16_t onewire_bus_crc16(const uint8_t* input, uint16_t len, uint16_t crc = 0);
#endif
#endif
 
#endif
 
