#include <avr/io.h>


LDI r16, 0xFF 	; set all bits in r16 to one
OUT _SFR_IO_ADDR(DDRB), r16 ; set all to output
LDI r16 , 1		; 
LDI r17 , 1		;


main:
CALL clear 		;
CALL led  		;
CALL wait		;
JMP main		;

clear:			; subroutine to clear leds
CBI 0x5, 0x5 	; clear bit 5 in I/O register portB; turn LED 13 off
CBI 0x5, 0x4 	; clear bit 5 in I/O register portB; turn LED 12 off
CBI 0x5, 0x3 	; clear bit 5 in I/O register portB; turn LED 11 off
RET 			; return from subroutine



wait:
LDI r18, 0 		;
LDI r19, 0x09 	;
LDI r20, 0x3D 	;

inner:
	SUBI r18, 100 ;
	SBCI r19, 0 ;
	SBCI r20, 0 ;
	BRCC inner

RET 			;return from subroutune wait




led:
	cp r16, r17		; Compare registers r16 and r17
	BREQ red		;
	BRLO green		; go to green if R16 < R17
	BRGE yellow		; go to green if R16 > R17


	red:
	SBI _SFR_IO_ADDR(PORTB), 3  
	LDI r17 , 0		; set r17 to 2 (yellow)
	RET 			; return from led

	yellow:
	SBI _SFR_IO_ADDR(PORTB), 4  	
	LDI r17 , 2		; set r17 to 2 (green)
	RET 			; return from led

	green:
	SBI _SFR_IO_ADDR(PORTB), 5  
	LDI r17 , 1		; set r17 to 2 (red)
	RET 			; return from led