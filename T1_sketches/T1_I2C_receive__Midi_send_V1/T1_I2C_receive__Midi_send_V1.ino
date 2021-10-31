/* Transmit every possible USB MIDI message.  Each time a
   button is pressed, send another message.

   This very long example demonstrates all possible usbMIDI
   message send functions.  It's mostly meant for testing
   and as a reference to easily copy-and-paste the code for
   every message send function.

   A pushbutton (ordinary momentary type) needs to be
   connected between pin 0 and GND.

   You must select MIDI from the "Tools > USB Type" menu

   This example code is in the public domain.
*/

#include <Wire.h>

//sent value from i2c
int i2c_value=2;

// the MIDI channel number to send messages
const int channel = 1;

// the MIDI virtual cable to use
int cable = 0;

// remember when a note-on message has been sent
int note=0;


void setup() {
  pinMode(13, OUTPUT);
//  digitalWrite(13,1);
//  delay(200);
//  digitalWrite(13,0);
//  delay(100);

  Wire.begin(9);
  Wire.onReceive(receiveEvent);

  digitalWrite(13,1);
  delay(3000);
  digitalWrite(13,0);
   delay(100);
}

void loop() {
 if (i2c_value == 15) {
  //send midi message
  sendNextMessage();
  digitalWrite(13,1);
  delay(100);
  digitalWrite(13,0);
   delay(100);
 }

  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void sendNextMessage() {
  usbMIDI.sendControlChange(7, 100, channel, cable);
}


void receiveEvent( int bytes ) {
i2c_value = Wire.read(); // read one character from the I2C
Wire.endTransmission(); // stop transmitting

}
