.section __config,"a"
.global __config_start
__config_start:
.incbin "config/defconfig.txt"
__config_end:
.global __config_end
