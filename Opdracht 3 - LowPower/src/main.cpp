#include "Arduino.h"
#include <avr/sleep.h>
#define LED 13
#define enableCLKPR 0x80
#define secDelay 452000

// Defines for prescaler
#define CLOCK_PRESCALER_1   (0x0)
#define CLOCK_PRESCALER_2   (0x1)
#define CLOCK_PRESCALER_4   (0x2)
#define CLOCK_PRESCALER_8   (0x3)
#define CLOCK_PRESCALER_16  (0x4)
#define CLOCK_PRESCALER_32  (0x5)
#define CLOCK_PRESCALER_64  (0x6)
#define CLOCK_PRESCALER_128 (0x7)
#define CLOCK_PRESCALER_256 (0x8)

void my_delay(uint32_t delay, uint8_t prescaler){
  for (volatile uint32_t i = 0; i < (delay / prescaler); i++) {

  }
}

void setup() {
  pinMode(LED, OUTPUT);
  // Disable the ADC by setting the ADEN bit (bit 7)  of the
  // ADCSRA register to zero.
  ADCSRA &= B01111111;

  // Disable the analog comparator by setting the ACD bit
  // (bit 7) of the ACSR register to one.
  ACSR = B10000000;
  DIDR0 |= 0x3F;
  DIDR1 |= 0x03;
  PRR |= 0xFF;

  // Setup watchdog
  WDTCSR |= _BV(WDIE) | _BV(WDCE);
  WDTCSR &= ~_BV(WDE);
  WDTCSR |= _BV(WDP3) | _BV(WDCE); //set prescaler to 4 seconds

  SMCR = (_BV(SM1) | _BV(SE)); //Power-down mode and enable sleep
  cli();
}

void SetCLKPR(uint8_t x) {
  cli();
  CLKPR = enableCLKPR;
  CLKPR = x;
  sei();
}

void Blink_LED(uint8_t prescaler) {
  PORTB ^= _BV(PB5);
  my_delay(secDelay, pow(2,prescaler));
  PORTB ^= _BV(PB5);
  my_delay(secDelay, pow(2,prescaler));
}

// Code die we gebruikt hebben voor derde deel van de opdracht, meten met verschillende prescaler
void BlinkLedsOnDifferentPreScaler(){
  SetCLKPR(CLOCK_PRESCALER_1);
  Blink_LED(CLOCK_PRESCALER_1);                 // Cant delay with 0, so use 1;

  SetCLKPR(CLOCK_PRESCALER_2);
  Blink_LED(CLOCK_PRESCALER_2);

  SetCLKPR(CLOCK_PRESCALER_4);
  Blink_LED(CLOCK_PRESCALER_4);

  SetCLKPR(CLOCK_PRESCALER_8);
  Blink_LED(CLOCK_PRESCALER_8);

  SetCLKPR(CLOCK_PRESCALER_16);
  Blink_LED(CLOCK_PRESCALER_16);

  SetCLKPR(CLOCK_PRESCALER_32);
  Blink_LED(CLOCK_PRESCALER_32);

  SetCLKPR(CLOCK_PRESCALER_64);
  Blink_LED(CLOCK_PRESCALER_64);

  SetCLKPR(CLOCK_PRESCALER_128);
  Blink_LED(CLOCK_PRESCALER_128);

  SetCLKPR(CLOCK_PRESCALER_256);
  Blink_LED(CLOCK_PRESCALER_256);
}

ISR(WATCHDOG_INTERRUPT)
{
}

void loop() {
  // Loop om led te blinken, en daarna cpu te slapen 
  for (volatile int i = 0; i < 5; i++) {
    Blink_LED(0);
  }
  sleep_cpu();
}
