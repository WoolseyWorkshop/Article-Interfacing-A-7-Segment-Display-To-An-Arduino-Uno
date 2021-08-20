// BCD7SegmentDisplay - BCD7SegmentDisplay.ino
//
// Description:
// Implements a counter that is displayed on a common anode 7-segment display
// driven through a BCD To 7-Segment Decoder/Driver (74LS47) IC.  The count is
// reset to 0 when a button is pressed.
//
// Circuit:
// - A momentary push button is connected to pin D2.
// - A common anode 7-segment display is connected to pins D3-D6 through a
//   74LS47 IC.
//
// Created by John Woolsey on 01/30/2019.
// Updated by John Woolsey on 08/20/2021.
// Copyright (c) 2019 Woolsey Workshop.  All rights reserved.


// Pin Mapping
const uint8_t Button = 2;  // momentary push button
const uint8_t BCD_A = 3;   // binary coded decimal (BCD) least significant bit (LSB) for 74LS47 A input pin
const uint8_t BCD_B = 4;
const uint8_t BCD_C = 5;
const uint8_t BCD_D = 6;   // binary coded decimal (BCD) most significant bit (MSB) for 74LS47 D input pin


// Global Constants
const unsigned long DisplayPeriod = 1000;  // time between display updates in milliseconds


void setup() {
   // Pin configuration
   pinMode(Button, INPUT_PULLUP);  // utilize microprocessor's internal pull-up resistor
   pinMode(BCD_A, OUTPUT);
   pinMode(BCD_B, OUTPUT);
   pinMode(BCD_C, OUTPUT);
   pinMode(BCD_D, OUTPUT);
}


void loop() {
   static uint8_t count = 0;  // display count
   static unsigned long previousDisplayTime = 0;
   unsigned long currentTime = millis();

   if (digitalRead(Button) == LOW) count = 0;  // reset count if button pressed
   if (currentTime - previousDisplayTime >= DisplayPeriod) {  // check if time to update display
      displayWrite(count);  // update display
      count++;  // increase counter
      if (count == 10) count = 0;  // reset to 0 if count exceeds 9
      previousDisplayTime = currentTime;
   }
}


// Writes value to display using binary coded decimal
void displayWrite(uint8_t value) {
   digitalWrite(BCD_A, bitRead(value, 0));  // BCD LSB
   digitalWrite(BCD_B, bitRead(value, 1));
   digitalWrite(BCD_C, bitRead(value, 2));
   digitalWrite(BCD_D, bitRead(value, 3));  // BCD MSB
}
