.section __config,"a"
.global __config_start
__config_start:
.incbin CONFIG_PATH
inc_config_terminator:
    .byte 0
__config_end:
.global __config_end
