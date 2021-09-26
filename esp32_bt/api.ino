//untuk sensor api
int checkFlame() {
  flame1 = analogRead(flamepin[0]);//membaca sinyal analog dari pin sensor 0
  flame2 = analogRead(flamepin[1]);
  flame3 = analogRead(flamepin[2]);
  flame4 = analogRead(flamepin[3]);
  flame5 = analogRead(flamepin[4]);
  Serial.println("Api");
  Serial.print(flame1);
  Serial.print("  ");
  Serial.print(flame2);
  Serial.print("  ");
  Serial.print(flame3);
  Serial.print("  ");
  Serial.print(flame4);
  Serial.print("  ");
  Serial.println(flame5);
  
  if (flame3 >= flame2 && flame3 >= flame4) {// return 1 jika sensor ditengah mendeteksi api
    return 1;
  }
  else if (flame2 > flame3 || flame1 > flame3) {// return 0 jika api di kiri
    return 0;
  }
  else if (flame4 > flame3 || flame5 > flame3 ) {// return 2 jika api di kanan
    return 2;  
  }
}
