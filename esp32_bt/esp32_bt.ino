
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

//elapsed millis untuk timer pengganti delay. no delay delay club!
elapsedMillis flameTime, pingTime, colorTime;

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
  if (buttonVal == LOW) {    // jika saklar ditekan
    walk("tinggi", 5000);   //jalan tinggi, untuk naik tangga/ arena tidak rata
    //walk("maju", 5000);//jalan biasa
    restState = 0;
  }
  if (restState == 0) {
    rest();
    restState = 1;
  }
  if (pingTime > 120) {
    //    ping();
    //    Serial.print("1 :");
    //    Serial.print(cm[0]);
    //    Serial.print("  2 :");
    //    Serial.print(cm[1]);
    //    Serial.print("  3 :");
    //    Serial.println(cm[2]);
    //    pingTime = 0;
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
    //    Serial.print("flame : ");
    //    Serial.println(checkFlame());
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
