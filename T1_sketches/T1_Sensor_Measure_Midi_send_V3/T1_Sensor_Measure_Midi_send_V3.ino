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
#include "Adafruit_AS726x.h"

//create the object
Adafruit_AS726x ams;



// the MIDI channel number to send messages
const int channel = 1;

// the MIDI virtual cable to use
int cable = 0;

// remember when a note-on message has been sent
int note=0;

//buffer to hold raw values
uint16_t sensorValues[AS726x_NUM_CHANNELS];

void setup() {
//  Serial.begin(9600);
//  while(!Serial);
  
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //begin and make sure we can talk to the sensor
  if(!ams.begin()){
    //Serial.println("could not connect to sensor! Please check your wiring.");
    while(1);
  }
}

void loop() {
  ams.startMeasurement(); //begin a measurement

  bool rdy = false;
  while(!rdy){
    delay(5);
    rdy = ams.dataReady();
  }

   //read the values!
  ams.readRawValues(sensorValues);

  int violet = map(constrain(sensorValues[AS726x_VIOLET],0,4000),0,4000,0,127);
  int blue = map(constrain(sensorValues[AS726x_BLUE],0,4000),0,4000,0,127);
  int green = map(constrain(sensorValues[AS726x_GREEN],0,4000),0,4000,0,127);
  int yellow = map(constrain(sensorValues[AS726x_YELLOW],0,4000),0,4000,0,127);
  int orange = map(constrain(sensorValues[AS726x_ORANGE],0,4000),0,4000,0,127);
  int red = map(constrain(sensorValues[AS726x_RED],0,4000),0,4000,0,127);
  

  usbMIDI.sendControlChange(1, violet, channel, cable);
  usbMIDI.sendControlChange(2, blue, channel, cable);
  usbMIDI.sendControlChange(3, green, channel, cable);
  usbMIDI.sendControlChange(4, yellow, channel, cable);
  usbMIDI.sendControlChange(5, orange, channel, cable);
  usbMIDI.sendControlChange(6, red, channel, cable);
  
  //sendMidi(violet, blue, green, yellow, orange, red);



  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}

void sendMidi(int violet, int blue, int green, int yellow, int orange, int red) {
  usbMIDI.sendControlChange(1, violet, channel, cable);
  usbMIDI.sendControlChange(2, blue, channel, cable);
  usbMIDI.sendControlChange(3, green, channel, cable);
  usbMIDI.sendControlChange(4, yellow, channel, cable);
  usbMIDI.sendControlChange(5, orange, channel, cable);
  usbMIDI.sendControlChange(6, red, channel, cable);
}
