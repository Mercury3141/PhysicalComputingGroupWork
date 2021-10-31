#include <Wire.h>
#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"

int slaveAddress = 9; // I2C slave
int i2c_Value = 0;

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
char cstr[16];

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

unsigned long lastMillis = 0;

void connect() {

  while (!client.connect("receiver", "ironferret579", "3kUUvbNdlPP34cj4")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("You're connected to the MQTT broker!");
//  client.subscribe("valueA");
//  client.subscribe("valueB");
//  client.subscribe("valueC");
//  client.subscribe("valueD");
//  client.subscribe("valueE");
//  client.subscribe("valueF");
//  client.subscribe("valueG");
//  client.subscribe("valueH");
//  client.subscribe("valueR");
//  client.subscribe("valueI");
//  client.subscribe("valueS");
//  client.subscribe("valueJ");
//  client.subscribe("valueT");
//  client.subscribe("valueU");
//  client.subscribe("valueV");
//  client.subscribe("valueW");
//  client.subscribe("valueK");
//  client.subscribe("valueL");
    
  //i2c transmission
  i2c_Value = 15;
  Serial.println("sending i2c to teensy");
  Wire.beginTransmission(slaveAddress); // transmit to device #9
  Wire.write(i2c_Value); // sends x
  Wire.endTransmission(); // stop transmitting
  Serial.println("sent i2c to teensy");
}

void messageReceived(String &topic, String &payload) {
  Serial.println(topic + ": " + payload);
}

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  
  //mqtt shiftr
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  // once you are connected :
  Serial.println("You're connected to the network");

  //start mqtt
  client.begin("ironferret579.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }


}
