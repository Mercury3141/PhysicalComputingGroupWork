#include <WiFiNINA.h>
#include <MQTT.h>

#include "wifiCredentials.h"

#include "Adafruit_AS726x.h"
Adafruit_AS726x ams;

#include <Wire.h>


// remember when a note-on message has been sent
int note = 0;

//buffer to hold raw values
uint16_t sensorValues[AS726x_NUM_CHANNELS];

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
char cstr[16];

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

//unsigned long lastMillis = 0;

void connect() {

  while (!client.connect("arduino", "arduinogang", "GUhW31vL7eAbrIr6")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("You're connected to the MQTT broker!");
  client.subscribe("ledBlink");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
  int blinkVal = constrain(payload.toInt(), 0, 1);
  digitalWrite(LED_BUILTIN, blinkVal);
}

//filter values
float alpha_up = 0.1;
float alpha_down = 0.5;

int upperThreshold = 1400;

float previous_violet = 0;
float current_violet = 0;
float previous_blue = 0;
float current_blue = 0;
float previous_green = 0;
float current_green = 0;
float previous_yellow = 0;
float current_yellow = 0;
float previous_orange = 0;
float current_orange = 0;
float previous_red = 0;
float current_red = 0;

float mapped_violet = 0;
float mapped_blue = 0;
float mapped_green = 0;
float mapped_yellow = 0;
float mapped_orange = 0;
float mapped_red = 0;


void setup() {
  //mqtt shiftr
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  client.begin("arduinogang.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();


  //begin and make sure we can talk to the sensor
  if (!ams.begin()) {
    Serial.println("could not connect to sensor! Please check your wiring.");
    while (1);
  }

}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }

  ams.startMeasurement(); //begin a measurement

  bool rdy = false;
  while (!rdy) {
    delay(5);
    rdy = ams.dataReady();
  }

  //read the values!
  ams.readRawValues(sensorValues);

  float violet = sensorValues[AS726x_VIOLET];
  float blue = sensorValues[AS726x_BLUE];
  float green = sensorValues[AS726x_GREEN];
  float yellow = sensorValues[AS726x_YELLOW];
  float orange = sensorValues[AS726x_ORANGE];
  float red = sensorValues[AS726x_RED];


  // filtering violet
  if (violet > current_violet) {
    current_violet  = alpha_up * violet + (1 - alpha_up) * previous_violet;
  }
  else {
    current_violet  = alpha_down * violet + (1 - alpha_down) * previous_violet;
  }
  previous_violet = current_violet;


  // filtering blue
  if (blue > current_blue) {
    current_blue  = alpha_up * blue + (1 - alpha_up) * previous_blue;
  }
  else {
    current_blue  = alpha_down * blue + (1 - alpha_down) * previous_blue;
  }
  previous_blue = current_blue;


  // filtering green
  if (green > current_green) {
    current_green  = alpha_up * green + (1 - alpha_up) * previous_green;
  }
  else {
    current_green  = alpha_down * green + (1 - alpha_down) * previous_green;
  }
  previous_green = current_green;


  // filtering yellow
  if (yellow > current_yellow) {
    current_yellow  = alpha_up * yellow + (1 - alpha_up) * previous_yellow;
  }
  else {
    current_yellow  = alpha_down * yellow + (1 - alpha_down) * previous_yellow;
  }
  previous_yellow = current_yellow;


  // filtering orange
  if (orange > current_orange) {
    current_orange  = alpha_up * orange + (1 - alpha_up) * previous_orange;
  }
  else {
    current_orange  = alpha_down * orange + (1 - alpha_down) * previous_orange;
  }
  previous_orange = current_orange;


  // filtering red
  if (red > current_red) {
    current_red  = alpha_up * red + (1 - alpha_up) * previous_red;
  }
  else {
    current_red  = alpha_down * red + (1 - alpha_down) * previous_red;
  }
  previous_red = current_red;


//  Serial.print(""); Serial.print(violet);
//  Serial.print(","); Serial.print(current_violet);
//  Serial.print(""); Serial.print(blue);
//  Serial.print(","); Serial.print(current_blue);
//  Serial.print(""); Serial.print(green);
//  Serial.print(","); Serial.print(current_green);
//  Serial.print(""); Serial.print(yellow);
//  Serial.print(","); Serial.print(current_yellow);
//  Serial.print(""); Serial.print(orange);
//  Serial.print(","); Serial.print(current_orange);
//  Serial.print(""); Serial.print(red);
//  Serial.print(","); Serial.print(current_red);
//  Serial.println();

mapped_violet = map((constrain(current_violet,0,upperThreshold)),0,upperThreshold,0,127);
mapped_blue = map((constrain(current_blue,0,upperThreshold)),0,upperThreshold,0,127);
mapped_green = map((constrain(current_green,0,upperThreshold)),0,upperThreshold,0,127);
mapped_yellow = map((constrain(current_yellow,0,upperThreshold)),0,upperThreshold,0,127);
mapped_orange = map((constrain(current_orange,0,upperThreshold)),0,upperThreshold,0,127);
mapped_red = map((constrain(current_red,0,upperThreshold)),0,upperThreshold,0,127);

//MQTT Publisher
  client.publish("spectrums", "{\"violet\":" + String(violet) + ",\"blue\":" + String(blue) + ",\"green\":" + String(green) + ",\"yellow\":" + String(yellow) + ",\"orange\":" + String(orange) + ",\"red\":" + String(red) + "}");
  client.publish("filteredSpectrums", "{\"violet\":" + String(current_violet) + ",\"blue\":" + String(current_blue) + ",\"green\":" + String(current_green) + ",\"yellow\":" + String(current_yellow) + ",\"orange\":" + String(current_orange) + ",\"red\":" + String(current_red) + "}");
  client.publish("violet", String(mapped_violet));
  client.publish("blue", String(mapped_blue));
  client.publish("green", String(mapped_green));
  client.publish("yellow", String(mapped_yellow));
  client.publish("orange", String(mapped_orange));
  client.publish("red", String(mapped_red));

}
