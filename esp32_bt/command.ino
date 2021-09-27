/*
  file untuk menyimpan perintah yang dijalankan pada
  void loop.
*/
void walk(String arah, int waktu) {
  elapsedMillis timer;
  while (timer < waktu && buttonVal != 1) {
    if (arah == "maju") {
      maju();
      //Serial.println("Maju");
    }
    else if (arah == "mundur") {
      mundur();
      //Serial.println("Mundur");
    }
    else if (arah == "left") {
      rotateLeft();
      //Serial.println("kiri");
    }
    else if (arah == "right") {
      rotateRight();
      //Serial.println("kanan");
    }
    else if (arah == "rightTinggi") {
      rotateRightTinggi();
      //Serial.println("kanan");
    }
    else if (arah == "leftTinggi") {
      rotateLeftTinggi();
      //Serial.println("kanan");
    }
    else if (arah == "tinggi") {
      tinggi();
      //Serial.println("tinggi");
    }
    else if (arah == "mundurTinggi") {
      mundurTinggi();
      //Serial.println("tinggi");
    }
    buttonVal = digitalRead(BUTTON);
  }
}
