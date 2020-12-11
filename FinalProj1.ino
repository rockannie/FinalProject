#include "pitches.h"

//define the song notes in an array in order, my ex. is the start of 'Mary had a little lamb'
//NOTE: replacing all #'s with proper wiring, they are placeholders 
int notes[] = {NOTE_C3, NOTE_C3, NOTE_D3, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_E3, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_D3, 
NOTE_D3, NOTE_E3, NOTE_C3, NOTE_C3, NOTE_C3, NOTE_D3, NOTE_D3, NOTE_E3, NOTE_G3, NOTE_E3, NOTE_C3, NOTE_A3, 
NOTE_D3, NOTE_F3, NOTE_E3, NOTE_C3, NOTE_C4, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_B3, NOTE_G3, NOTE_C4, 
NOTE_C4, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_G3, NOTE_F3, NOTE_E3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_B3, NOTE_C4,
NOTE_A3, NOTE_D3, NOTE_E3, NOTE_C3};

int counter = 0;

//define buzzer
const int buzzerPin = 11;

//define pins for shift register
const int dataPin = 2;
const int clockPin = 4;
const int latchPin = 3;

//define a byte of leds for the register
byte leds = 0;

//define several different IDs for inputs/outputs, replace #'s with correct wiring
const int buttonPin1 = 5; //HIGHC 8
const int buttonPin2 = 6; //B   7
const int buttonPin3 = 7; //A   6
const int buttonPin4 = 8; //G   5
const int buttonPin5 = 9; //F   4
const int buttonPin6 = 10; //E  3
const int buttonPin7 = 12; //D  2
const int buttonPin8 = 13; //C  1


//sort buttons into array
int buttons[] = {buttonPin8, buttonPin8, buttonPin7, buttonPin7, buttonPin6, buttonPin4, buttonPin6, buttonPin8,
buttonPin8, buttonPin8, buttonPin7, buttonPin7, buttonPin6, buttonPin8, buttonPin8, buttonPin8, buttonPin7, 
buttonPin7, buttonPin6, buttonPin4, buttonPin6, buttonPin8, buttonPin3, buttonPin7, buttonPin5, buttonPin6, 
buttonPin8, buttonPin1, buttonPin1, buttonPin3, buttonPin1, buttonPin2, buttonPin2, buttonPin4, buttonPin1, 
buttonPin1, buttonPin3, buttonPin1, buttonPin2, buttonPin4, buttonPin5, buttonPin6, buttonPin5, buttonPin4, 
buttonPin3, buttonPin2, buttonPin1, buttonPin3, buttonPin7, buttonPin6, buttonPin8};

int ledvalues[] = {0, 0, 1, 1, 2, 4, 2, 0, 0, 0, 1, 1, 2, 0, 0, 0, 1, 1, 2, 4, 2, 0, 5, 1, 3, 2, 0, 7, 7, 5,
7, 6, 6, 4, 7, 7, 5, 7, 6, 4, 3, 2, 3, 4, 5, 6, 7, 5, 1, 2, 0};


void setup() {
  Serial.begin(9600);
  //set up buttons
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  pinMode(buttonPin8, INPUT_PULLUP);
  //setup shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}


void loop() {
  //updateShiftRegister();
  while (counter < 50)
  {
      //Serial.println(counter);
      bitSet(leds, ledvalues[counter]);
      updateShiftRegister();
      int currentButton = buttons[counter];
      int buttonPressed = digitalRead(currentButton);
      if(buttonPressed == 0)
      {
          //Serial.println(buttonPressed);
          tone(buzzerPin, notes[counter], 1000);
          bitClear(leds, ledvalues[counter]);
          updateShiftRegister();
          counter++;
          delay(1000);
      }
   }
} 

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
