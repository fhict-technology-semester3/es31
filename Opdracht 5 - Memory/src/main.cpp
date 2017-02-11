#include "Arduino.h"

void PrintAdresses();
void aa();
void bb();
void cc();
void dd();
void DumpStack();

//Global vars for memory locations
extern char *__data_start;
extern char *__data_end;

extern char *__bss_start;
extern char *__bss_end;

extern char *__heap_start;
extern char *__heap_end;

extern char *__stack_start;
extern char *__stack_end;

// Vars to show where they get placed in memory
uint8_t data = 1;
uint8_t bss;
int a = 0;
unsigned char array[100];
int j = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Program has started");
  //PrintAdresses();

  aa();
  Serial.print("Stack dump: ");
  for (int i = 0; i < j; i++) {
    Serial.print((int)array[i], HEX); Serial.print(" ");
  }
  Serial.println();

  void (*pf_aa)() = aa;
  Serial.print("aa: ");
  Serial.print((int)pf_aa, HEX); Serial.print(" ");
  Serial.println((int)pf_aa << 1, HEX);

  void (*pf_bb)() = bb;
  Serial.print("bb: ");
  Serial.print((int)pf_bb, HEX); Serial.print(" ");
  Serial.println((int)pf_bb << 1, HEX);

  void (*pf_cc)() = cc;
  Serial.print("cc: ");
  Serial.print((int)pf_cc, HEX); Serial.print(" ");
  Serial.println((int)pf_cc << 1, HEX);

  void (*pf_dd)() = dd;
  Serial.print("dd: ");
  Serial.print((int)pf_dd, HEX); Serial.print(" ");
  Serial.println((int)pf_dd << 1, HEX);
}

void loop() {
}

void PrintAdresses() {
  uint8_t stack = 1;

  Serial.println("Data:");
  Serial.println((int)&__data_start, HEX);
  Serial.println((int)&__data_end, HEX);

  Serial.println("Bss:");
  Serial.println((int)&__bss_start, HEX);
  Serial.println((int)&__bss_end, HEX);

  Serial.println("Heap:");
  Serial.println((int)&__heap_start, HEX);
  Serial.println((int)&__heap_end, HEX);

  Serial.println("SP:");
  Serial.println(SP, HEX);

  Serial.println("RAMEND:");
  Serial.println((int)RAMEND, HEX);

  Serial.print("Var on stack: ");
  Serial.println((int)&stack, HEX);

  Serial.print("Var on data: ");
  Serial.println((int)&data, HEX);

  Serial.print("Var on bss: ");
  Serial.println((int)&bss, HEX);

  uint8_t *heap = new uint8_t;
  Serial.print("Var on heap: ");
  Serial.println((int)&heap, HEX);
}

void aa() {
  volatile char _c = 0x11;
  bb();
}
void bb() {
  volatile char _c = 0x22;
  cc();
}
void cc() {
  volatile char _c = 0x33;
  dd();
}
void dd() {
  volatile char _c = 0x44;
  DumpStack();
}

void DumpStack() {
  for (char * i = (char*)(SP-1); (int)i <= RAMEND; i++) {
    array[j] = *i;
    j++;
  }
}
