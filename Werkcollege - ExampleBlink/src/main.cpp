#include "Arduino.h"
#include "led.h"
#include "timer.h"

#define LED1 13
#define LED2 6
#define LED3 5

Led* l1;
Led* l2;
Led* l3;

void setup() {
  Serial.begin(9600);
  l1 = new Led(LED1, 0.5);
  l2 = new Led(LED2, 3);
  l3 = new Led(LED3, 5);
}

void loop(){
  l1->Blink();
  l2->Blink();
  l3->Blink();
 }
