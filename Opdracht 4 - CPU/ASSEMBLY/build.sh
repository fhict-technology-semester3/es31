avr-gcc ./$1.s -mmcu=atmega328 -Os -g -o $1.elf -nostdlib
avr-objcopy -O ihex $1.elf $1.hex
avrdude -C "/home/yopspanjers/Software/arduino-1.6.11/hardware/tools/avr/etc/avrdude.conf" -v -patmega328p -carduino -P$2 -b115200 -D -Uflash:w:%1.hex:i
avr-objdump -d $1.elf
