#include <WiFiNINA.h>
#include <MQTT.h>
#include "wifiCredentials.h"
#include "SparkFun_AS7265X.h" //Click here to get the library: http://librarymanager/All#SparkFun_AS7265X
AS7265X sensor;
#include <Wire.h>

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
char cstr[16];
float xPos = 0;
float yPos = 0;

WiFiClient net;
MQTTClient client;
int status = WL_IDLE_STATUS;

unsigned long lastMillis = 0;

void connect() {

  while (!client.connect("arduino", "ironferret579", "3kUUvbNdlPP34cj4")) {
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

int valueA = 0;
int valueB = 0;
int valueC = 0;
int valueD = 0;
int valueE = 0;
int valueF = 0;
int valueG = 0;
int valueH = 0;
int valueR = 0;
int valueI = 0;
int valueS = 0;
int valueJ = 0;
int valueT = 0;
int valueU = 0;
int valueV = 0;
int valueW = 0;
int valueK = 0;
int valueL = 0;

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
  client.begin("ironferret579.cloud.shiftr.io", net);
  client.onMessage(messageReceived);
  connect();

  //setup Spektrograph
  Serial.println("AS7265x Spectral Triad Example");

  if (sensor.begin() == false)
  {
    Serial.println("Sensor does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }

  //Once the sensor is started we can increase the I2C speed
  Wire.setClock(400000);

  sensor.setMeasurementMode(AS7265X_MEASUREMENT_MODE_6CHAN_CONTINUOUS); //All 6 channels on all devices

  sensor.setIntegrationCycles(1);
  //0 seems to cause the sensors to read very slowly
  //1*2.8ms = 5.6ms per reading
  //But we need two integration cycles so 89Hz is aproximately the fastest read rate

  sensor.disableIndicator();

  //Rather than toggle the LEDs with each measurement, turn on LEDs all the time
  sensor.disableBulb(AS7265x_LED_WHITE);
  sensor.disableBulb(AS7265x_LED_IR);
  sensor.disableBulb(AS7265x_LED_UV);

  Serial.println("A,B,C,D,E,F,G,H,R,I,S,J,T,U,V,W,K,L");
}

void loop() {
  client.loop();
  delay(10);

  // check if connected
  if (!client.connected()) {
    connect();
  }
  long startTime = millis();
  //We must wait two integration cycles to get all values
  while (sensor.dataAvailable() == false) {} //Do nothing
  long endTime = millis();

  float readRate = 1000.0 / (endTime - startTime);
  valueA = sensor.getA();
  valueB = sensor.getB();
  valueC = sensor.getC();
  valueD = sensor.getD();
  valueE = sensor.getE();
  valueF = sensor.getF();
  valueG = sensor.getG();
  valueH = sensor.getH();
  valueR = sensor.getR();
  valueI = sensor.getI();
  valueS = sensor.getS();
  valueJ = sensor.getJ();
  valueT = sensor.getT();
  valueU = sensor.getU();
  valueV = sensor.getV();
  valueW = sensor.getW();
  valueK = sensor.getK();
  valueL = sensor.getL();

  // publish a message roughly every second.
  //if (millis() - lastMillis > 500) {
  //lastMillis = millis();
  client.publish("valueA", String(valueA) );
  client.publish("valueB", String(valueB) );
  client.publish("valueC", String(valueC) );
  client.publish("valueD", String(valueD) );
  client.publish("valueE", String(valueE) );
  client.publish("valueF", String(valueF) );
  client.publish("valueG", String(valueG) );
  client.publish("valueH", String(valueH) );
  client.publish("valueR", String(valueR) );
  client.publish("valueI", String(valueI) );
  client.publish("valueS", String(valueS) );
  client.publish("valueJ", String(valueJ) );
  client.publish("valueT", String(valueT) );
  client.publish("valueU", String(valueU) );
  client.publish("valueV", String(valueV) );
  client.publish("valueW", String(valueW) );
  client.publish("valueK", String(valueK) );
  client.publish("valueL", String(valueL) );

  //}


}
