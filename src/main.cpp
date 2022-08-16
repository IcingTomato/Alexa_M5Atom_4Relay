#include <Arduino.h>
#include <M5Atom.h>
#include <WiFi.h>
#include <Wire.h>
#include "Unit_4RELAY.h"
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char THING_ID[]           = ""; //Enter THING ID
const char DEVICE_LOGIN_NAME[]  = ""; //Enter DEVICE ID

const char SSID[]               = "";    //Enter WiFi SSID (name)
const char PASS[]               = "";    //Enter WiFi password
const char DEVICE_KEY[]         = "";    //Enter Secret device password (Secret Key)

UNIT_4RELAY _relay;

int   reconnectFlag = 0;

void onSwitch1Change();
void onSwitch2Change();
void onSwitch3Change();
void onSwitch4Change();

int toggleState_1 = 0; //Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; //Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; //Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; //Define integer to remember the toggle state for relay 4

CloudSwitch switch1;
CloudSwitch switch2;
CloudSwitch switch3;
CloudSwitch switch4;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.setThingId(THING_ID);
  ArduinoCloud.addProperty(switch1, READWRITE, ON_CHANGE, onSwitch1Change);
  ArduinoCloud.addProperty(switch2, READWRITE, ON_CHANGE, onSwitch2Change);
  ArduinoCloud.addProperty(switch3, READWRITE, ON_CHANGE, onSwitch3Change);
  ArduinoCloud.addProperty(switch4, READWRITE, ON_CHANGE, onSwitch4Change);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

void relayOnOff(int relay) {
  switch (relay) {
    case 1:
      if (toggleState_1 == 0) {
        _relay.relayWrite(0, 1); // turn on relay 1
        toggleState_1 = 1;
        Serial.println("Device1 ON");
      }
      else {
        _relay.relayWrite(0, 0); // turn off relay 1
        toggleState_1 = 0;
        Serial.println("Device1 OFF");
      }
      delay(100);
      break;
    case 2:
      if (toggleState_2 == 0) {
        _relay.relayWrite(1, 1); // turn on relay 2
        toggleState_2 = 1;
        Serial.println("Device2 ON");
      }
      else {
        _relay.relayWrite(1, 0); // turn off relay 2
        toggleState_2 = 0;
        Serial.println("Device2 OFF");
      }
      delay(100);
      break;
    case 3:
      if (toggleState_3 == 0) {
        _relay.relayWrite(2, 1); // turn on relay 3
        toggleState_3 = 1;
        Serial.println("Device3 ON");
      } else {
        _relay.relayWrite(2, 0); // turn off relay 3
        toggleState_3 = 0;
        Serial.println("Device3 OFF");
      }
      delay(100);
      break;
    case 4:
      if (toggleState_4 == 0) {
        _relay.relayWrite(3, 1); // turn on relay 4
        toggleState_4 = 1;
        Serial.println("Device4 ON");
      }
      else {
        _relay.relayWrite(3, 0); // turn off relay 4
        toggleState_4 = 0;
        Serial.println("Device4 OFF");
      }
      delay(100);
      break;
    default : break;
  }
}

void doThisOnConnect(){
  /* add your custom code here */
  Serial.println("Board successfully connected to Arduino IoT Cloud");
  M5.dis.drawpix(0, 0x0000f0); // BLUE
}
void doThisOnSync(){
  /* add your custom code here */
  Serial.println("Thing Properties synchronised");
}

void doThisOnDisconnect(){
  /* add your custom code here */
  Serial.println("Board disconnected from Arduino IoT Cloud");
  M5.dis.drawpix(0, 0xff0000); //RED
}

void setup() {
  // Initialize serial and wait for port to open:
  // Wire.begin();
  M5.begin(true, true, true);
  // Serial.begin(115200);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  M5.dis.drawpix(0, 0xff0000);
  delay(1500);

  // Defined in thingProperties.h
  initProperties();
  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::CONNECT, doThisOnConnect);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::SYNC, doThisOnSync);
  ArduinoCloud.addCallback(ArduinoIoTCloudEvent::DISCONNECT, doThisOnDisconnect);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  _relay.begin(&Wire, 26, 32);
  _relay.Init(1);

  _relay.relayAll(0);
}

void loop() {

  ArduinoCloud.update();
}

void onSwitch1Change() {
  //Control the device
  if (switch1 == 1)
  {
    _relay.relayWrite(0, 1);
    Serial.println("Device1 ON");
    toggleState_1 = 1;
  }
  else
  {
    _relay.relayWrite(0, 0);
    Serial.println("Device1 OFF");
    toggleState_1 = 0;
  }
}

void onSwitch2Change() {
  if (switch2 == 1)
  {
    _relay.relayWrite(1, 1);
    Serial.println("Device2 ON");
    toggleState_2 = 1;
  }
  else
  {
    _relay.relayWrite(1, 0);
    Serial.println("Device2 OFF");
    toggleState_2 = 0;
  }
}

void onSwitch3Change() {
  if (switch3 == 1)
  {
    _relay.relayWrite(2, 1);
    Serial.println("Device3 ON");
    toggleState_3 = 1;
  }
  else
  {
    _relay.relayWrite(2, 0);
    Serial.println("Device3 OFF");
    toggleState_3 = 0;
  }
}

void onSwitch4Change() {
  if (switch4 == 1)
  {
    _relay.relayWrite(3, 1);
    Serial.println("Device4 ON");
    toggleState_4 = 1;
  }
  else
  {
    _relay.relayWrite(3, 0);
    Serial.println("Device4 OFF");
    toggleState_4 = 0;
  }
}
