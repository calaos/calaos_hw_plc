noinst_PROGRAMS = calaos_plc_io_fw.elf calaos_plc_io_fw.hex

bin_PROGRAMS = calaos_plc_io_fw.elf
calaos_plc_io_fw_elf_SOURCES = startup_stm32f10x_md.s main.c

calaos_plc_io_fw.hex : calaos_plc_io_fw.elf
	$(OBJCOPY) -O ihex -R .eeprom calaos_plc_io_fw.elf calaos_plc_io_fw.hex
