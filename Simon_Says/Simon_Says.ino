#include <stdlib.h>
#include <util/delay.h>
#include <time.h>

#define BLUE 330
#define YELLOW 277
#define RED 220
#define GREEN 165

#define DING 660
#define BUZZ 69

int tones[4] = {RED, GREEN, BLUE, YELLOW};

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

    int index = 0;
    bool right = true;
    while(index < sLength && right) {
      for(int i = 4; i < 8; i++) {
        bool flag = false;
        while(isActive(i)) {
          digitalWrite(i+4, HIGH);
          tone(2, tones[i%4]);
          flag = true;
        }
        digitalWrite(i+4, LOW);
        noTone(2);
        if(flag) {
          if((i+4) == sequence[index]) {
            index++;
          }
          else {
            right = false;
          }
        }
      }
    }

    _delay_ms(500);

    if(right) {
      correct();
      sLength++;
    }
    else {
      incorrect();
      sLength = 1;
    }

    _delay_ms(500);

    delete sequence;
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
    digitalWrite(9, HIGH);
    tone(2, DING);
    _delay_ms(200);
    digitalWrite(9, LOW);
    noTone(2);
    _delay_ms(100);
  }
}


void incorrect() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(8, HIGH);
    tone(2, BUZZ);
    _delay_ms(200);
    digitalWrite(8, LOW);
    noTone(2);
    _delay_ms(100);
  }
}

