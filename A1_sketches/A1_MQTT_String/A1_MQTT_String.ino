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
    //Serial.println("could not connect to sensor! Please check your wiring.");
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

  int violet = map(constrain(sensorValues[AS726x_VIOLET], 0, 4000), 0, 4000, 0, 127);
  int blue = map(constrain(sensorValues[AS726x_BLUE], 0, 4000), 0, 4000, 0, 127);
  int green = map(constrain(sensorValues[AS726x_GREEN], 0, 4000), 0, 4000, 0, 127);
  int yellow = map(constrain(sensorValues[AS726x_YELLOW], 0, 4000), 0, 4000, 0, 127);
  int orange = map(constrain(sensorValues[AS726x_ORANGE], 0, 4000), 0, 4000, 0, 127);
  int red = map(constrain(sensorValues[AS726x_RED], 0, 4000), 0, 4000, 0, 127);

  Serial.print(""); Serial.print(sensorValues[AS726x_VIOLET]);
  Serial.print(","); Serial.print(sensorValues[AS726x_BLUE]);
  Serial.print(","); Serial.print(sensorValues[AS726x_GREEN]);
  Serial.print(","); Serial.print(sensorValues[AS726x_YELLOW]);
  Serial.print(","); Serial.print(sensorValues[AS726x_ORANGE]);
  Serial.print(","); Serial.print(sensorValues[AS726x_RED]);
  Serial.println();
  Serial.print(""); Serial.print(violet);
  Serial.print(","); Serial.print(blue);
  Serial.print(","); Serial.print(green);
  Serial.print(","); Serial.print(yellow);
  Serial.print(","); Serial.print(orange);
  Serial.print(","); Serial.print(red);
  Serial.println();


  client.publish("violet", "{\"violet\":" + String(violet) + ",\"blue\":" + String(blue) + ",\"green\":" + String(green) + ",\"yellow\":" + String(yellow) + ",\"orange\":" + String(orange) + ",\"red\":" + String(red) + "}");


}
