//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//#include "BluetoothSerial.h" //comment if not using bluetooth
#include <Kinematics.h>
Kinematics k(54, 73);
#include <elapsedMillis.h>
#define BUTTON 33
int buttonVal;
Position p[6];
Angle a[6];
float x[6], y[6], z[6];
int leg; int i = 0;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
const char* ssid = "AWP";
const char* password = "Ariwijayaputra1";
//BluetoothSerial SerialBT;
elapsedMillis legTime, calibrateTime, RGBTime;
int restState;
void setup() {
  Serial.begin(9600);
  otaSetup();

  //SerialBT.begin("Hexapod STIKOM Bali"); //Bluetooth device name uncomment to use bluetooth
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(BUTTON, INPUT_PULLUP);
  rest();
  restState = 1;
}

void loop() {
  ArduinoOTA.handle();
  buttonVal = digitalRead(BUTTON);
  //Serial.println(buttonVal);
  if (buttonVal == LOW) {
    walk("tinggi",5000);
    restState = 0;
  }
  if(rest == 0){
    rest();
    restState = 1;
  }
  
  //  if (SerialBT.available()) {
  //    char input = SerialBT.read();
  //    switch (input)
  //    {
  //      case 'F': {
  //          maju();
  //        };
  //      case 'B': {
  //          mundur();
  //        };
  //      case 'L': {
  //          rotateLeft();
  //        };
  //      case 'R': {
  //          rotateRight();
  //        };
  //      default:
  //        break;
  //    }
  //  }
  //  delay(20);
}
