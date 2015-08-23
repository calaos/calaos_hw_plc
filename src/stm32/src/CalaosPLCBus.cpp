#include "CalaosPLCBus.h"
#include "crc16.h"

struct plc_bus_header {
	uint16_t slave_id;
	uint16_t payload_length;
};

int CalaosPLCBus::write_message(uint16_t slave_id, uint8_t *buf, uint16_t len)
{	
	ssize_t ret;
	uint16_t crc = 0, i;
	struct plc_bus_header hdr = {slave_id, len};
	uint8_t *ptr = (uint8_t *) &hdr;

	/* Send the header */
	for(i = 0; i < sizeof(struct plc_bus_header); i++) {
		ret = bus_serial.putc(ptr[i]);
		if (ret != 0)
			return CALAOS_PLC_BUS_WRITE_ERR;
	}
	crc = crc16(crc, &hdr, sizeof(struct plc_bus_header));

	/* Send the message */
	for(i = 0; i < len; i++) {
		ret = bus_serial.putc(buf[i]);
		if (ret != 0)
			return CALAOS_PLC_BUS_WRITE_ERR;
	}
	crc = crc16(crc, buf, len);
	
	ptr = (uint8_t *) &crc;
	/* Finally, send the CRC */
	for(i = 0; i < sizeof(crc); i++) {
		ret = bus_serial.putc(ptr[i]);
		if (ret != 0)
			return CALAOS_PLC_BUS_WRITE_ERR;
	}

	return 0;
}

int CalaosPLCBus::read_single_message(uint16_t slave_id, void *buf, uint16_t buf_len, uint16_t *read_len)
{
	Timer t;
	int status = 0, ret;
	uint16_t len = 0, *expected_crc16;

	/* Wait to receive a first char and handle timeout */
	t.start();
	while (!bus_serial.readable()) {
		if (t.read_ms() > REQUEST_TIMEOUT_MSEC) {
			t.stop();
			return CALAOS_PLC_BUS_TIMEOUT;
		}
	}

	t.start();
	while (1) {
		/* Read any char if available */
		while (bus_serial.readable()) {
			ret = bus_serial.getc();
			if (ret < 0) {
				t.stop();
				return CALAOS_PLC_BUS_READ_ERR;
			}
			in_buffer[len++] = ret;
			t.reset();
		}
		if (t.read_us() > INTER_FRAME_SILENCE_USEC)
			break;
	}
	expected_crc16 = (uint16_t *) &in_buffer[len - 3];

	if (crc16(0, in_buffer, len - 3) != *expected_crc16)
		status = CALAOS_PLC_BUS_CRC_ERR;

	t.stop();
	return status;
}

int CalaosPLCBus::read_message(uint16_t slave_id, void *buf, uint16_t buf_len, uint16_t *read_len)
{
	int ret, i;

	for (i = 0; i < MAX_BUS_TRIALS; i++) {
		ret = read_message(slave_id, buf, buf_len, read_len);
		if (ret == 0)
			return 0;
		/* Actually, we might consider a timeout as a direct failure for faster discovery */
	}
	
	return ret;
}
