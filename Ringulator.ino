/*
   GPL LICENSE v3.0

   MCU Coil Tester
   https://youtu.be/QBbEYYWiBI8

   Nov 2021 The Lightning Stalker
*/

#include <FreqCount.h>   // input pin will depend on MCU, D5 for UNO, see FreqCount docs
#include <Wire.h>
#include "rgb_lcd.h"     // Seed Grove-LCD RGB Backlight

// no calibration factor
#undef TIMER_USE_TIMER2

#define BD 40            // display brightness

#define pinModeInp(pin) DDRD = DDRD & ~(1 << pin) // equivalent to pinMode(thisPin, INPUT)
#define pinModeOut(pin) DDRD = DDRD | (1 << pin)  // likewise but for OUTPUT

rgb_lcd lcd;             // instantiate lcd variable

const byte pulsePin = 2; // pin going to transistor
unsigned long count = 0; // ring count

void setup() {
  // put your setup code here, to run once:
  pinModeOut(pulsePin);  // saves 62 bytes(!)

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

  digitalWrite(pulsePin, LOW);   // charge capacitor
  delay(110);
  digitalWrite(pulsePin, HIGH);  // δ

  FreqCount.begin(226);          // begin count
  while (!FreqCount.available());
  count = FreqCount.read();      // take erasurement
  FreqCount.end();               // switch blanking

  // Begin output routine
  //  Serial.println(count);
  lcd.clear();
  if (count <= 0) {
    lcd.print("Ringulator v1.1");
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
