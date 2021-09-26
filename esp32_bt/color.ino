
//untuk sensor warna
//deskripsi dalam bahasa inggris. males aku ngubah.

void color() {
  if (RGBTime < 100)
  {
    // Setting red filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Reading the output frequency
    red = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
//    Serial.print("R= ");//printing name
//    Serial.print(red);//printing RED color frequency
//    Serial.print("  ");
    RGBTime = 100;
  }
  else if (RGBTime > 200 && RGBTime < 300)
  {
    // Setting Green filtered photodiodes to be read
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    green = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
//    Serial.print("G= ");//printing name
//    Serial.print(green);//printing RED color frequency
//    Serial.print("  ");
    RGBTime = 300;
  }
  else if (RGBTime > 400 && RGBTime < 500)
  {
    // Setting Blue filtered photodiodes to be read
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Reading the output frequency
    blue = pulseIn(sensorOut, LOW);
    // Printing the value on the serial monitor
//    Serial.print("B= ");//printing name
//    Serial.print(blue);//printing RED color frequency
//    Serial.println("  ");
    RGBTime = 500;
  }
  else if (RGBTime > 600) {
    RGBTime = 0;
  }
}
