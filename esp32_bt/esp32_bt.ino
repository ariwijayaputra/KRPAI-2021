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
//variabel dibawah untuk servo
Position p[6];
Angle a[6];
float x[6], y[6], z[6];
int leg; int i = 0;
int counter = 0;// change counter to = 0 to exit development stage, -1 to development stage
//elapsed millis untuk timer pengganti delay. no delay delay club!
elapsedMillis flameTime, pingTime, colorTime, lorong1;

//variabel untuk sensor api
int vcc = 13;
int flamepin[5] = {32, 35, 34, 39, 36};
int flame1, flame2, flame3, flame4, flame5 = 0;

//untuk sensor jarak
const int pingPin[3] = {2, 4, 16};
long duration, cm[3];

//untuk sensor warna
#define S0 17
#define S1 5
#define S2 18
#define S3 19
#define sensorOut 21
int frequency = 0, red = 0, green = 0, blue = 0;

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
  pinMode(vcc, OUTPUT);
  //SerialBT.begin("Hexapod STIKOM Bali"); //Bluetooth device name uncomment to use bluetooth
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(BUTTON, INPUT_PULLUP);
  delay(2000);
  rest();
  restState = 1;
}

void loop() {
  ArduinoOTA.handle();
  buttonVal = digitalRead(BUTTON);
  digitalWrite(vcc, HIGH);
  //Serial.println(buttonVal);
  if (buttonVal == LOW) {// jika saklar ditekan
    if (counter == -1) {// counter -1 : Testing
      ping();
      while (cm[1] < 170) {
        if (pingTime > 120) {
          ping();
          //          Serial.print("1 :");
          //          Serial.print(cm[0]);
          //          Serial.print("  2 :");
          //          Serial.print(cm[1]);
          //          Serial.print("  3 :");
          //          Serial.println(cm[2]);
          pingTime = 0;
        }
        rotateRight();
      }
    }
    //=============================================================================
    else if (counter == 0) {// counter 0 : menentukan arah awal
      ping();
      //      Serial.print("1 :");
      //      Serial.print(cm[0]);
      //      Serial.print("  2 :");
      //      Serial.print(cm[1]);
      //      Serial.print("  3 :");
      //      Serial.println(cm[2]);
      if (cm[1] < cm[2]) {
        walk("left", 3160);
      }
      else if (cm[1] > cm[2]) {
        walk("right", 3160);
      }
      counter++;
    }
    //===========================================================================
    else if (counter == 1) {// counter 1 : maju sampai kaca
      lorong1 = 0;
      walk("tinggi", 3600);
      ping();
      do {
        if (pingTime > 120) {
          ping();
          //          Serial.print("1 :");
          //          Serial.print(cm[0]);
          //          Serial.print("  2 :");
          //          Serial.print(cm[1]);
          //          Serial.print("  3 :");
          //          Serial.println(cm[2]);
          pingTime = 0;
        }
        if (cm[1] >= 22  && lorong1 < 31500) {
          walk("mundur", 180 * 4);
          walk("rightTinggi", 3060);
          walk("tinggi", 2880);
          lorong1 = lorong1 - 1080;
        }
        if (cm[2] >= 22  && lorong1 < 31500) {
          walk("mundur", 180 * 4);
          walk("leftTinggi", 3060);
          walk("tinggi", 2880);
          lorong1 = lorong1 - 1080;
        }
        if ((cm[1] < 15 || (cm[2] >= 18 && cm[1] < 20)) && lorong1 < 33000) {
          walk("leftTinggi", 540);
          walk("tinggi", 3600);
          lorong1 = lorong1 - 360;
        }
        if ((cm[2] < 15 || (cm[1] >= 18 && cm[2] < 20)) && lorong1 < 33000) {
          walk("rightTinggi", 540);
          walk("tinggi", 3600);
          lorong1 = lorong1 - 360;
        }
        tinggi();
      } while (cm[0] >= 13);
      counter++;
    }
    //===============================================================================
    else if (counter == 2) {// counter 2 : belok kanan, majun lorong 2
      lorong1 = 0;
      ping();
      walk("rightTinggi", 3060 + 180); // Asli 2880
      do {
        if (pingTime > 100) {
          ping();
          pingTime = 0;
        }
        rotateRightTinggi();
      } while (cm[1] <= 169 || cm[0] < 45);
      walk("rightTinggi", 1340);
      walk("tinggi", 7540);
      do {
        if (pingTime > 120) {
          ping();
          //          Serial.print("1 :");
          //          Serial.print(cm[0]);
          //          Serial.print("  2 :");
          //          Serial.print(cm[1]);
          //          Serial.print("  3 :");
          //          Serial.println(cm[2]);
          pingTime = 0;
        }
        if(cm[1]>=38){
          lorong1=50000;
        }
        if (cm[1] >= 18  && lorong1 < 48000) {
          walk("mundur", 180 * 4);
          walk("rightTinggi", 3060);
          walk("tinggi", 2160);
          lorong1 = lorong1 - 720;
        }
        if (cm[2] >= 18  && lorong1 < 48000) {
          walk("mundur", 180 * 4);
          walk("leftTinggi", 3060);
          walk("tinggi", 2160);
          lorong1 = lorong1 - 720;
        }
        if ((cm[1] < 15 || (cm[2] >= 18 && cm[1] < 20)) && lorong1 < 50000) {
          walk("leftTinggi", 540);
          walk("tinggi", 3600);
          lorong1 = lorong1 - 360;
        }
        if ((cm[2] < 15 || (cm[1] >= 18 && cm[2] < 20)) && lorong1 < 50000) {
          walk("rightTinggi", 540);
          walk("tinggi", 3600);
          lorong1 = lorong1 - 360;
        }
        tinggi();
      } while (cm[0] >= 20);
      counter++;
    }
    else if (counter == 3) {// counter 2 : belok kanan, maju
      walk("rightTinggi", 7200);
      while (cm[0] < 100 || cm[2] < 25) { // cm[0] <=170
        rotateRightTinggi();
      }
      //walk("right", 2160);
      counter++;
    }
  }
  if (restState == 0) {
    rest();
    restState = 1;
  }
  if (pingTime > 120) {
    ping();
    Serial.print("1 :");
    Serial.print(cm[0]);
    Serial.print("  2 :");
    Serial.print(cm[1]);
    Serial.print("  3 :");
    Serial.println(cm[2]);
    pingTime = 0;
  }
  if (colorTime > 500) {
    //sensor menyala setiap 500ms
    color();
    if (colorTime > 800) { //500+300 = 800
      //minimal menyala selama 300ms untuk mendapatkan data sensor
      colorTime = 0;
    }
  }
  if (flameTime > 500) {
    Serial.print("flame : ");
    Serial.println(checkFlame());
    flameTime = 0;
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
