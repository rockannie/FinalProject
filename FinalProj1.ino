#include "pitches.h"

//define the song notes in an array in order, my ex. is the start of 'Mary had a little lamb'
//NOTE: replacing all #'s with proper wiring, they are placeholders 
int notes[] = {NOTE_E3, NOTE_D3, NOTE_C3, NOTE_D3, NOTE_E3, NOTE_E3, NOTE_E3};

//define buzzer
const int buzzerPin = 11;

//define pins for shift register
const int dataPin = 2;
const int clockPin = 4;
const int latchPin = 3;

//define a byte of leds for the register
byte leds = 0;

//define several different IDs for inputs/outputs, replace #'s with correct wiring
const int buttonPin1 = 5;
const int buttonPin2 = 6;
const int buttonPin3 = 7;
const int buttonPin4 = 8;
const int buttonPin5 = 9;
const int buttonPin6 = 10;
const int buttonPin7 = 12;
const int buttonPin8 = 13;

//sort buttons into array
int buttons[] = {buttonPin8, buttonPin7, buttonPin6, buttonPin5, buttonPin4, buttonPin3, buttonPin2, buttonPin1};

//define LEDS
//const int ledPin1 = #;
//const int ledPin2 = #;
//const int ledPin3 = #;
//const int ledPin4 = #;
//const int ledPin5 = #;
//const int ledPin6 = #;
//const int ledPin7 = #;
//const int ledPin8 = #;

//sort leds into array
//int leds[] = {ledPin1, ledPin2, ledPin3, ledPin4, ledPin5, ledPin6, ledPin7, ledPin8};

void setup() {
  Serial.begin(9600);
  //set up buttons
  for (int i = 0; i < sizeof(buttons)-1; i++)
  {
      pinMode(buttons[i], INPUT);
      //pinMode(leds[i], OUTPUT);
  }
  //setup shift register
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  int counter = 0;
  updateShiftRegister();
  while (counter < sizeof(notes)-1)
  {
      bitSet(leds, counter);
      updateShiftRegister();
      //int currentLED = leds[counter];
      //digitalWrite(currentLED, HIGH);
      int currentButton = buttons[counter];
      int buttonPressed = digitalRead(currentButton);
      if(buttonPressed == 1)
      {
          tone(buzzerPin, notes[0], 1000);
          bitClear(leds, counter);
          updateShiftRegister();
          //digitalWrite(currentLED, LOW);
          counter++;
      }else{
          bitClear(leds, counter);
          updateShiftRegister();
          bitSet(leds, counter);
          updateShiftRegister();
          //digitalWrite(currentLED, LOW);
          //digitalWrite(currentLED, HIGH);
      }
  }
}

void updateShiftRegister()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}
