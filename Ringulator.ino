/*
   GPL LICENSE v3.0

   Atmega 328 Coil Tester
   https://youtu.be/QBbEYYWiBI8

   Nov 2021 The Lightning Stalker
*/

#include <Wire.h>
#include "rgb_lcd.h"

#define BD 40            // display brightness

#define pinModeInp(pin) DDRD = DDRD & ~(1 << pin) // equivalent to pinMode(thisPin, INPUT)
#define pinModeOut(pin) DDRD = DDRD | (1 << pin)  // likewise but for OUTPUT

rgb_lcd lcd;             // instantiate lcd variable

const byte inputPin = 2; // must be an interrupt capable pin
const byte pulsePin = 3; // pin going to transistor
volatile byte count = 0; // interrupt driven counter variable

void setup() {
  // put your setup code here, to run once:
  pinModeInp(inputPin); // saves 112kb over pinMode()! (?)
  pinModeOut(pulsePin);

  attachInterrupt(digitalPinToInterrupt(inputPin), updateCounter, RISING); // set up ISR

  lcd.begin(16, 2); // 16 character, 2 line display
  lcd.setRGB(BD, BD, BD); // reduce brightness

  // Uncomment here and below for serial output:
  /*  Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pulsePin, LOW); // charge capacitor
  delay(110);
  count = 0;                   // take erasurement
  digitalWrite(pulsePin, HIGH);
  delay(266);

  //  Serial.println(count);
  lcd.clear();
  if (count <= 0) {
    lcd.print("Ringulator v1.0");
    lcd.setCursor(0, 1);
    lcd.print("Listening...");
  }
  else {
    lcd.setCursor(3, 0);
    if (count < 100) lcd.print(' '); // padding of the numerinos
    if (count < 10) lcd.print(' ');
    lcd.print(count);
    lcd.print(" Rings");
  }
}

void updateCounter() {
  // interrupt service routine:
  count++;
}
