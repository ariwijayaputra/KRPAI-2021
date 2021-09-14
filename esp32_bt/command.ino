void walk(String arah, int waktu) {
  elapsedMillis timer;
  while (timer < waktu && buttonVal != 1) {
    if (arah == "maju") {
      //maju();
      Serial.println("Maju");
    }
    else if (arah == "mundur") {
      //mundur();
      Serial.println("Mundur");
    }
    else if (arah == "left") {
      //rotateLeft();
      Serial.println("kiri");
    }
    else if (arah == "right") {
      //rotateRight();
      Serial.println("kanan");
    }
    buttonVal = digitalRead(BUTTON);
    

  }

}
