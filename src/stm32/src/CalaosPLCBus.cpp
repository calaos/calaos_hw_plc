#include "CalaosPLCBus.h"
#include "CalaosPLCBusProtocol.h"
#include "crc16.h"

int CalaosPLCBus::write_message(uint16_t slave_id, uint16_t request_type, uint8_t *buf, uint16_t len)
{	
	ssize_t ret;
	uint16_t crc = 0, i;
	struct cpbp_msg_header hdr = {.slave_id = slave_id, .payload_length = len, .request_type = request_type};
	uint8_t *ptr = (uint8_t *) &hdr;

	/* Send the header */
	for(i = 0; i < sizeof(struct cpbp_msg_header); i++) {
		ret = bus_serial.putc(ptr[i]);
		if (ret != ptr[i])
			return CALAOS_PLC_BUS_WRITE_ERR;
	}
	crc = crc16(crc, &hdr, sizeof(struct cpbp_msg_header));

	/* Send the message */
	for(i = 0; i < len; i++) {
		ret = bus_serial.putc(buf[i]);
		if (ret != buf[i])
			return CALAOS_PLC_BUS_WRITE_ERR;
	}
	crc = crc16(crc, buf, len);
	
	ptr = (uint8_t *) &crc;
	/* Finally, send the CRC */
	for(i = 0; i < sizeof(crc); i++) {
		ret = bus_serial.putc(ptr[i]);
		if (ret != ptr[i])
			return CALAOS_PLC_BUS_WRITE_ERR;
	}
	
	printf("Message sent to slave id %d\r\n", slave_id);

	return 0;
}

int CalaosPLCBus::read_single_message(uint16_t slave_id, uint16_t request_type, void *buf, uint16_t buf_len, uint16_t *read_len)
{
	Timer t;
	int ret;
	struct cpbp_msg_header *hdr;
	uint16_t len = 0, *expected_crc16;

	printf("Starting to wait for slave %d response\r\n", slave_id);

	/* Wait to receive a first char and handle timeout */
	t.start();
	while (!bus_serial.readable()) {
		if (t.read_ms() > CPBP_REQUEST_TIMEOUT_MSEC) {
			t.stop();
			printf("Timeout while waiting answer\r\n");
			return CALAOS_PLC_BUS_TIMEOUT;
		}
	}
	printf("Received data from slave\r\n");

	hdr = (struct cpbp_msg_header *) in_buffer;
	t.reset();
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
		/* Check if we have received the length header */
		if (len >= (offsetof(struct cpbp_msg_header, payload_length) + sizeof(hdr->payload_length)))
			if (len == (sizeof(struct cpbp_msg_header) + hdr->payload_length + CPBP_CRC_SIZE))
				break;

		if (t.read_us() > CPBP_INTER_FRAME_SILENCE_USEC)
			break;
		
	}
	t.stop();

	/* Check the CRC */
	expected_crc16 = (uint16_t *) &in_buffer[len - CPBP_CRC_SIZE - 1];

	if (crc16(0, in_buffer, len - CPBP_CRC_SIZE - 1) != *expected_crc16)
		return CALAOS_PLC_BUS_CRC_ERR;

	if (hdr->slave_id != slave_id)
		return CALAOS_PLC_BUS_SLAVE_ERR;
	if (hdr->request_type != request_type)
		return CALAOS_PLC_BUS_REQUEST_ERR;

	len = len - sizeof(struct cpbp_msg_header) + CPBP_CRC_SIZE;
	memcpy(buf, &in_buffer[sizeof(struct cpbp_msg_header)], len);
	*read_len = len;

	return 0;
}

int CalaosPLCBus::read_message(uint16_t slave_id, uint16_t request_type, void *buf, uint16_t buf_len, uint16_t *read_len)
{
	int ret, i;

	for (i = 0; i < CPBP_MAX_BUS_TRIALS; i++) {
		ret = read_single_message(slave_id, request_type, buf, buf_len, read_len);
		if (ret == 0)
			return 0;
		/* Actually, we might consider a timeout as a direct failure for faster discovery */
	}
	
	return ret;
}

int CalaosPLCBus::parse_discover(CalaosPLCBusSlave *slave, uint8_t *buffer)
{
	struct cpbp_discover_resp *hdr = (struct cpbp_discover_resp *) buffer;
	struct cpbp_cap_desc *cap_desc;
	uint16_t i;

	printf("%d capabilities\r\n", hdr->cap_count);

	cap_desc = (struct cpbp_cap_desc *) &buffer[sizeof(struct cpbp_discover_resp)];
	for (i = 0; i < hdr->cap_count; i++) {
		printf("Capability %d\r\n", cap_desc->type);
		cap_desc++;
	}

	return 0;
}

int CalaosPLCBus::discover()
{
	uint16_t slave_id;
	int ret;
	uint8_t *read_buffer;
	uint16_t read_len;
	CalaosPLCBusSlave *slave;

	read_buffer = new uint8_t[CPBP_MAX_MESSAGE_SIZE];
	if (!read_buffer)
		return 1;
		
	printf("Discovering bus\r\n");

	for(slave_id = 0; slave_id < MAX_SLAVE_NODES; slave_id++) {
		printf("Scanning slave id %d\r\n", slave_id);
		ret = write_message(slave_id, CALAOS_PLC_BUS_REQ_DISCOVER, NULL, 0);
		if (ret != 0) {
			printf("Write returned with err %d\r\n", ret);
			continue;
		}

		ret = read_message(slave_id, CALAOS_PLC_BUS_REQ_DISCOVER, read_buffer, CPBP_MAX_MESSAGE_SIZE, &read_len);
		if (ret != 0)
			continue;

		printf("Slave discovered with id %x\r\n", slave_id);
		slave = new CalaosPLCBusSlave(slave_id);
		parse_discover(slave, read_buffer);
		slaves.push_back(slave);
	}

	delete read_buffer;

	return 0;
}
