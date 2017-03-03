#include <stdlib.h>
#include <util/delay.h>
#include <time.h>

/*  
  These are the frequencies for the different tones
  You can mess around with them if you'd like to try 
  and get different tones playing 
*/
#define BLUE 330
#define YELLOW 277
#define RED 220
#define GREEN 165

#define DING 660
#define BUZZ 69

void setup() {
  // put your setup code here, to run once:
  srand(daylight_seconds(NULL);
  // TODO: set up all the LED pins as outputs

  // TODO: set up all the button pins as inputs

  // TODO: enable the pull-up resistors for the buttons

}

bool isActive(char inPin) {
  // TODO: return true if the button corresponding to the pin is pressed
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

void incorrect(){
  // TODO: You'll want to make incorrect act very similar to correct
  // The main difference is you'll have a different light blink to let them
  // know they're wrong.
  // Instead of playing the DING tone, you should play the BUZZ tone instead.
}

void loop() {
  // put your main code here, to run repeatedly:
  int sLength = 1;
  while (true) {
    unsigned char* sequence = generateSequence(sLength);

    // Don't worry about the game logic, it's already implemented
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


    // TODO: If they got the sequence right (checking the boolean "right"), call the correct function and increment sLength
    // Otherwise, you'll want to call the incorrect function and set sLength back to 1.


    _delay_ms(500);

    delete sequence;
  }
}

// Don't worry about the details for generating the sequence too much
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



