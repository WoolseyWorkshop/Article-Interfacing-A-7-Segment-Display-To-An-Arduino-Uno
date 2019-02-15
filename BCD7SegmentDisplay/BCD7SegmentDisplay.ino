// BCD7SegmentDisplay - BCD7SegmentDisplay.ino
//
// Description:
// Implements a counter that is displayed on a common anode 7-segment display
// driven through a BCD To 7-Segment Decoder/Driver (74LS47) IC.  The count is
// reset to 0 when a button is pressed.
//
// Circuit:
// Momentary push button connected to pin 2.
// Common anode 7-segment display connected through 74LS47 IC to pins 3-6.
//
// Created by John Woolsey on 01/30/2019.
// Copyright © 2019 Woolsey Workshop.  All rights reserved.


// Pin Mapping
const byte button = 2;  // momentary push button, fires interrupt service routine
const byte bcdA   = 3;  // binary coded decimal (BCD) least significant bit (LSB) for 74LS47 A input pin
const byte bcdB   = 4;
const byte bcdC   = 5;
const byte bcdD   = 6;  // binary coded decimal (BCD) most significant bit (MSB) for 74LS47 D input pin


// Global Variables
byte count = 0;  // display counter


void setup() {
   // Pin configuration
   pinMode(button, INPUT_PULLUP);  // utilize microprocessor's internal pull-up resistor
   pinMode(bcdA, OUTPUT);
   pinMode(bcdB, OUTPUT);
   pinMode(bcdC, OUTPUT);
   pinMode(bcdD, OUTPUT);

   // Initialize interrupt service routine
   // Calls resetCount() function when button is pressed,
   // i.e., the button pin value falls from high to low.
#ifdef ARDUINO_AVR_UNO_WIFI_REV2
   attachInterrupt(button, resetCount, FALLING);
#else
   attachInterrupt(digitalPinToInterrupt(button), resetCount, FALLING);
#endif
}


void loop() {
   displayWrite(count);         // update display
   count++;                     // increase counter
   if (count == 10) count = 0;  // reset to 0 if count exceeds 9
   delay(1000);                 // wait one second
}


// Resets counter and display to 0
void resetCount() {
   count = 0;        // reset counter
   displayWrite(0);  // reset display
}


// Writes value to display using binary coded decimal
void displayWrite(byte value) {
#ifdef ARDUINO_AVR_UNO_WIFI_REV2
   digitalWrite(bcdA, PinStatus(bitRead(value, 0)));  // BCD LSB
   digitalWrite(bcdB, PinStatus(bitRead(value, 1)));
   digitalWrite(bcdC, PinStatus(bitRead(value, 2)));
   digitalWrite(bcdD, PinStatus(bitRead(value, 3)));  // BCD MSB
#else
   digitalWrite(bcdA, bitRead(value, 0));  // BCD LSB
   digitalWrite(bcdB, bitRead(value, 1));
   digitalWrite(bcdC, bitRead(value, 2));
   digitalWrite(bcdD, bitRead(value, 3));  // BCD MSB
#endif
}
