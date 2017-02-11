/* Augustus 2016 - ES12 Opdracht 1 - Rick van Boxtel en Yop Spanjers */
void setup() {
  Serial.begin(9600);
  PINB |= (_BV(PB2) | _BV(PB4)); //Setup pins input
  DDRD |= (_BV (PD5) |  _BV (PD6) | _BV (PD3)); //Setup pins output
}

void loop() {
  uint8_t D10 = PINB & _BV(PB2);
  uint8_t D12 = PINB & _BV(PB4);
  uint8_t rando = random(0, 15);
  if (D10 <= 0)  {
    PORTD |= _BV(PORTD5);
  }
  else {
    PORTD &= ~_BV(PORTD5);
  }
  if (D12 <= 0)  {
    Serial.println("Hello World!");
    PORTD |= _BV(PORTD6);
  }
  else {
    PORTD &= ~_BV(PORTD6);
  }
  if (D10 + D12 <= 0)  {
    int i;
    for (i = 0; i < 100/rando; i++) {
      PORTD ^= _BV(PORTD3);
      delay(rando);
    }
  }
}
