//ES31 | Timers and Interrupts | Assignment 2 | Yop Spanjers & Rick van Boxtel | 9-9-2016
#include "Arduino.h"

#define BUTTON11 11
#define SLIDER1 0 //Most right slider.
#define DATA 4
#define LED5 5
#define LED6 6
#define LATCH 7
#define CLOCK 8
unsigned long dotTimer = 0; // Timer to change 8-segment dot state.
unsigned long ledTimer = 0; //Timer to change led
static boolean dotState = false; //8-Segment display dot state On/Off
static boolean led6State = false; //Led state on/off
static boolean led5State = false; //Led state on/off
static boolean slomoState = false; //If true, slomo is on.
uint8_t sliderMapping = 0; // Used to map the slider(potentiometer).
uint8_t slomoTiming = 1; // Used to get the slomo effect when button D11 is pressed (Used so you can change the time of the slomo).
uint8_t previousValueSlider = 0; // Previous Value of the slider(potentiometer). Used to create a smoothing window.

const uint8_t displayCharSet[] =
{
  // Each byte represent one appearance of the 8-segment display
  // Each bit in a byte represent one segment of the 8-segment display
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92,  0x82, 0xF8, 0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
};

void inc_Display() //Everytime this method is called. The 8-segment will display a higher HEX value from 0-F. After F comes 0 again.
{
  static int i = 0;
  uint8_t val = displayCharSet[i]; //Get charset

  if (dotState) //If dotState is true, switch state.
  {
    val = val & ~(_BV(7)); //Change dot state On/Off.
  }
  digitalWrite(LATCH, LOW); // Set latch off
  shiftOut(DATA, CLOCK, MSBFIRST, val); // Shifts out a byte of data one bit at a time. This is the way you write to this 8-segment because it uses a shift register.
  digitalWrite(LATCH, HIGH); // Set latch on again.
  i++; //Used to get the next char.
  i %= sizeof(displayCharSet); // If all chars are displayed. Start over.
}

void blink_LED()
{
  led5State = !led5State; // Change LED state
  digitalWrite(LED5, led5State ? HIGH : LOW); //LED5 On/Off according to led5State
}

void check_Slomotion()
{
    if (slomoState)
  {
    slomoTiming = 10; // Set slomo on.
  }
  else
  {
    slomoTiming = 1; // Set slomo off.
  }
}

void setup()
{
  Serial.begin(9600); //Begin Serial for debugging messages
  pinMode(BUTTON11, INPUT); //Define pinmode. Input pin, because it is a button.
  digitalWrite(BUTTON11, HIGH); //Define this is a sourcing pull-up button.

  //Set pinmodes as output
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(DATA, OUTPUT);

  // Setup interrupts
  cli(); //Clear interrups
  PCMSK0 |= _BV(PCINT3); // Pin Change MaSK register (PCINT3 = Pin11 = Button D11)
  PCIFR |= _BV(PCIF0); // Clear outstanding interrupts.
  PCICR |= _BV(PCIE0); // Pin Change Interrupt Control Register (Set Interrupt on).

  //Set timer1 interrupt at 1Hz
  TCCR1A = 0;// Set entire TCCR1A register to 0
  TCCR1B = 0;// Same for TCCR1B
  TCNT1  = 0;//Initialize counter value to 0

  OCR1A = 0xFFFF; // Timer overflow value.

  TCCR1B |= _BV(WGM12); // Turn on CTC mode
  TCCR1B |= _BV(CS11) | (1 << CS10); // Prescaler 64
  TIMSK1 |= _BV(OCIE1A); //Output Compare Interrupt Enable 1 A
  sei();//Allow interrupts

}
// Timer1 interrupt
// This event gets invoked when the timer has hit the overflow value (OCR1A).
ISR(TIMER1_COMPA_vect)
{
  dotTimer += OCR1A; // DotTimer = dotTimer + Timer.
  ledTimer += OCR1A;// LedTimer = ledTimer + Timer.
  // Convert the sliderMapping value to Seconds
  // (16MHz/64prescaler = 250.000 = 1 Second so 2.500 = 10ms)
  // and add slomo function.
  int64_t SliderToSeconds = ((25000L * sliderMapping) * slomoTiming);


  if (ledTimer >= SliderToSeconds) //If ledTimer value is bigger or equal to SliderToSeconds.
  {
    blink_LED(); //Change LED On/Off
    ledTimer = 0; //Reset the ledTimer.
  }
  if (dotTimer >= 250000) // 16MHz/64prescaler = 250.000 = 1 Second.
  {
    dotTimer = 0; //Reset the dotTimer.
    dotState = !dotState; // Change dot state, gets dealt with in the inc_Display method.
  }
  inc_Display(); //Should always get invoked because the frequency of this event is the same as the frequency of the char changing on the 8-segment display.
}

// Pin interrupt
// This event gets invoked when the value of pin11 has been changed.
ISR(PCINT0_vect)
{
  led6State = !led6State; //Change led state.
  slomoState = !slomoState; //Change slomo state.
  digitalWrite(LED6, led6State ? HIGH : LOW); // Change LED6 On/Off according to led6State.
}

// Main loop
void loop() {
  int currentValueSlider = analogRead(SLIDER1); //Read Slider value
  // Have a margin of 2, because slider was not exact.
  if (currentValueSlider > (previousValueSlider + 2) || currentValueSlider < (previousValueSlider - 2)) {
    sliderMapping = map(currentValueSlider, 0, 1023, 1, 10); //Map the slider so that max is 10 and minimum is 1.
    cli(); //Clear interrups
    OCR1A = map(currentValueSlider, 0, 1023, 2500, 65535); //Map OCR1A
    sei(); //Allow interrupts
    previousValueSlider = currentValueSlider; //Change previousSlider value for the smoothing window.
  }
  check_Slomotion(); //Set slomotion on when D11 is pressed.
}
