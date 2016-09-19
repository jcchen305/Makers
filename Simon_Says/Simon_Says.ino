#include <stdlib.h>
#include <util/delay.h>
#include <time.h>

#define BLUE 330
#define YELLOW 277
#define RED 220
#define GREEN 165

#define DING 587
#define BUZZ 69

int tones[4] = {YELLOW, BLUE, GREEN, RED};

void setup() {
  // put your setup code here, to run once:
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  srand(daylight_seconds(NULL));
}

void loop() {
  int sLength = 1;
  while (true) { // Main game loop;
    unsigned char* sequence = generateSequence(sLength);

    while (!isActive(4));

    delete sequence;
    sLength++;
  }

}

bool isActive(char inPin) {
  if (digitalRead(inPin) == 0) {
    return true;
  }
  return false;
}

unsigned char* generateSequence(int sLength) {
  unsigned char* sequence = new unsigned char[sLength];
  for (int i = 0; i < sLength; i++) {
    int temp = rand() % 4;
    sequence[i] = temp + 8;
    digitalWrite(sequence[i], HIGH);
    tone(2, tones[temp]);
    _delay_ms(750);
    digitalWrite(sequence[i], LOW);
    noTone(2);
    _delay_ms(250);
  }
  return sequence;
}

void correct() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(10, HIGH);
    tone(2, DING);
    _delay_ms(200);
    digitalWrite(10, LOW);
    noTone(2);
    _delay_ms(100);
  }
}


void incorrect() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(11, HIGH);
    tone(2, BUZZ);
    _delay_ms(200);
    digitalWrite(11, LOW);
    noTone(2);
    _delay_ms(100);
  }
}

