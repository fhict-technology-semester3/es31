
"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-gcc" %1.S -mmcu=atmega328 -Os -g -o %1.elf -nostdlib
"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objcopy" -O ihex %1.elf %1.hex
"C:\Program Files (x86)\Arduino\hardware\tools\avr/bin/avrdude" -C "C:\Program Files (x86)\Arduino\hardware\tools\avr/etc/avrdude.conf" -v -patmega328p -carduino -P%2 -b115200 -D -Uflash:w:%1.hex:i 
"C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avr-objdump" -d %1.elf