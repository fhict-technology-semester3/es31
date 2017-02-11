#define LRED 1
#define LGREEN 2
#define LBLUE 3

uint8_t currentColor = 0;
void setup() {
  pinMode(LRED, OUTPUT);
  pinMode(LGREEN, OUTPUT);
  pinMode(LBLUE, OUTPUT);
}

void loop() {
  digitalWrite(LRED, HIGH);
  digitalWrite(LGREEN, LOW);
  digitalWrite(LBLUE, LOW);
  delay(1000);
  digitalWrite(LRED, LOW);
  digitalWrite(LGREEN, HIGH);
  digitalWrite(LBLUE, LOW);
  delay(1000);
  digitalWrite(LRED, LOW);
  digitalWrite(LGREEN, LOW);
  digitalWrite(LBLUE, HIGH);
  delay(1000);
}



