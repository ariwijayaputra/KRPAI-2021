/*
 * file untuk menyimpan coding mengenai servo,
 * mulai dari inisiasi servo, kalibrasi pulse awal,
 * hingga fungsi fungsi untuk mengontrol servo.
 * ruwet gan.
 * penjelasan lebih lengkap menyusul.
 */
int servo[6][3] = {
  {1, 2, 3},//f1,f2,f3
  {4, 5, 6},//e1,e2,e3
  {7, 8, 9},//d1,d2,d3
  {32, 31, 30},//a1,a2,a3
  {29, 28, 27},//b1,b2,b3
  {26, 25, 24}//c1,c2,c3
};

int pulse[6][3] = {
  {1551, 1455, 867},
  {1450, 1567, 874},
  {1564, 1512, 758},
  {1480, 1485, 888},
  {1483, 1466, 755},
  {1514, 1592, 770}
};

void setDeg(int s, float d) {
  int pulse = map(d, 0, 270, 500, 2500);
  Serial.print("#" + String(s) + "P" + String(pulse));
}

void setPulse(int s, int p) {
  Serial.print("#" + String(s) + "P" + String(p));
}

void setPosisi(int leg, float x, float y, float z) {
  if (leg == 0) {
    x = round(x + (0.86 * y));
    y = round(y / 2) * -1;
  }
  else if (leg == 1) {
    y = y * -1;
  }
  else if (leg == 2) {
    x = round(x - (0.86 * y ));
    y = round(y / 2) * -1;
  }
  else if (leg == 3) {
    x = round(x + (0.86 * y));
    y = round(y / 2);
  }
  else if (leg == 5) {
    x = round(x - (0.86 * y));
    y = round(y / 2);
  }
  k.moveToPosition(x, y, z);
  a[leg] = k.getAngles();
  a[leg].theta3 = a[leg].theta3 / 2;
  a[leg].theta2 = a[leg].theta2 + 90;
  a[leg].theta1 = a[leg].theta1 * -1;
  int pulse1 = degToPulse(a[leg].theta1);
  int pulse2 = degToPulse(a[leg].theta2);
  int pulse3 = degToPulse(a[leg].theta3);
  setPulse(servo[leg][1], pulse[leg][1] + pulse1);
  setPulse(servo[leg][2], pulse[leg][2] + pulse2);
  setPulse(servo[leg][0], pulse[leg][0] + pulse3);
}
void rest() {//posisi istirahat
  
  setPosisi(0, 50, 0, -95);//3
  setPosisi(2, 50, 0, -95);
  setPosisi(4, 50, 0, -95);
  setPosisi(1, 50, 0, -95);//1
  setPosisi(3, 50, 0, -95);
  setPosisi(5, 50, 0, -95);
  runAt(1400);
}

int gait[6][3] = {
  /*
          1
    4   3   2
    --------------->
  */
  {50, 10, -75},//1
  {50, 20, -95},//2
  {50, 0, -95},//3
  {50, -20, -95},//4
  {50, 10, -75},//5
  {50, 20, -95},//6
};
int gaitMundurTinggi[6][3] = {
  /*
        1   
     4  3   2
    --------------->
  */
  {65, 0, -45},//1
  {50, -25, -60},//2
  {50, 0, -95},//3
  {50, 25, -95},//4
  {60, 0, -45},//5
  {50, -25, -60},//6
};

int gaitTinggi[6][3] = {
  /*
        1   
     4  3   2
    --------------->
  */
  {65, 0, -45},//1
  {50, 25, -60},//2
  {50, 0, -95},//3
  {50, -25, -95},//4
  {60, 0, -45},//5
  {50, 25, -60},//6
};

int gaitMundur[6][3] = {
  /*
       1
    4   3   2
    --------------->
  */
  {50, -10, -78},//1
  {50, -20, -95},//2
  {50, 0, -95},//3
  {50, 20, -95},//4
  {50, -10, -78},//5
  {50, -20, -95},//6
};
int gaitRotateLeft[6][3] = {//in degrees
  /*
       1
    4   3   2
    --------------->
  */
  {0, 15, 15},
  {11.25, 30, 30},
  {0, 30, 30},
  {-11.25, 30, 30},
  {0, 15, 15},
  {11.25, 30, 30},
};

int gaitRotateRight[6][3] = {//in degrees
  /*
       1
    4   3   2
    --------------->
  */
  {0, 15, 15},
  {-11, 30, 30},
  {0, 30, 30},
  { 11, 30, 30},
  {0, 15, 15},
  {-11, 30, 30},
};

int gaitRotateRightTinggi[6][3] = {//in degrees
  /*
       1
    4   3   2
    --------------->
  */
  {0, -15, -15},
  {-11.25, -10, -10},
  {0, 30, 30},
  { 11.25 , 30, 30},
  {0, -15, -15},
  {-11.25, -10, -10},
};
int gaitRotateLeftTinggi[6][3] = {//in degrees
  /*
       1
    4   3   2
    --------------->
  */
  {0, -15, -15},
  {11.25, -10, -10},
  {0, 30, 30},
  {-11.25, 30, 30},
  {0, -15, -15},
  {-11.25, -10, -10},
};
void test(){
  setPosisi(1, gait[i][0], gait[i][1], gait[i][2]);
  runAt(200);
}

void tinggi(){
  /*
        1
    4   3   2
    --------------->
  */

  if (legTime > 360) {//legtime = runAt + 25
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPosisi(leg, gaitTinggi[i][0], gaitTinggi[i][1], gaitTinggi[i][2]);
        
      }
      else {
        setPosisi(leg, gaitTinggi[i + 2][0], gaitTinggi[i + 2][1], gaitTinggi[i + 2][2]);
      }
    }
    //Serial.println(i);
    runAt(320);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }

  if (i >= 4) {
    i = 0;
  }
}

void maju(){
  /*
        1
    4   3   2
    --------------->
  */

  if (legTime > 180) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPosisi(leg, gait[i][0], gait[i][1], gait[i][2]);
        
      }
      else {
        setPosisi(leg, gait[i + 2][0], gait[i + 2][1], gait[i + 2][2]);
      }
    }
    //Serial.println(i);
    runAt(120);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }

  if (i >= 4) {
    i = 0;
  }
}


void mundurTinggi() {
  /*
        1
    4   3   2
    --------------->
  */

  if (legTime > 360) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPosisi(leg, gaitMundurTinggi[i][0], gaitMundurTinggi[i][1], gaitMundurTinggi[i][2]);
      }
      else {
        setPosisi(leg, gaitMundurTinggi[i + 2][0], gaitMundurTinggi[i + 2][1], gaitMundurTinggi[i + 2][2]);
      }
    }
    runAt(120);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }

  if (i >= 4) {
    i = 0;
  }
}
void mundur() {
  /*
        1
    4   3   2
    --------------->
  */

  if (legTime > 360) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPosisi(leg, gaitMundur[i][0], gaitMundur[i][1], gaitMundur[i][2]);
      }
      else {
        setPosisi(leg, gaitMundur[i + 2][0], gaitMundur[i + 2][1], gaitMundur[i + 2][2]);
      }
    }
    runAt(320);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }

  if (i >= 4) {
    i = 0;
  }
}

void rotateLeft() {
  if (legTime > 180) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateLeft[i][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateLeft[i][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateLeft[i][2]));
      }
      else {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateLeft[i + 2][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateLeft[i + 2][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateLeft[i + 2][2]));
      }
    }
    runAt(120);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }
  if (i >= 4) {
    i = 0;
  }
}

void rotateRight() {
  if (legTime > 180) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateRight[i][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateRight[i][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateRight[i][2]));
      }
      else {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateRight[i + 2][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateRight[i + 2][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateRight[i + 2][2]));
      }
    }
    runAt(120);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }
  if (i >= 4) {
    i = 0;
  }
}
void rotateRightTinggi() {
  if (legTime > 360) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateRightTinggi[i][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateRightTinggi[i][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateRightTinggi[i][2]));
      }
      else {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateRightTinggi[i + 2][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateRightTinggi[i + 2][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateRightTinggi[i + 2][2]));
      }
    }
    runAt(320);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }
  if (i >= 4) {
    i = 0;
  }
}

void rotateLeftTinggi() {
  if (legTime > 360) {//legtime = runAt + 60
    legTime = 0;
    for (int leg = 0; leg < 6; leg++) {
      if (leg % 2 == 0) {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateLeftTinggi[i][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateLeftTinggi[i][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateLeftTinggi[i][2]));
      }
      else {
        setPulse(servo[leg][0], pulse[leg][0] + degToPulse(gaitRotateLeftTinggi[i + 2][0]));
        setPulse(servo[leg][1], pulse[leg][1] + degToPulse(gaitRotateLeftTinggi[i + 2][1]));
        setPulse(servo[leg][2], pulse[leg][2] + degToPulse(gaitRotateLeftTinggi[i + 2][2]));
      }
    }
    runAt(320);//servo speed, semakin kecil semakin cepat. maksimum 160  / 60 degrees
    i++;
  }
  if (i >= 4) {
    i = 0;
  }
}

//void calculate(int x, int y, int z) {
//  k.moveToPosition(x, y, z);
//  p[leg] = k.getPositions();
//  a[leg] = k.getAngles();
//  a[leg].theta3 = a[leg].theta3 / 2 - 60;
//  a[leg].theta2 = a[leg].theta2 + 90;
//  a[leg].theta1 = a[leg].theta1 * -1;
//  int pulse1 = degToPulse(a[leg].theta1);
//  int pulse2 = degToPulse(a[leg].theta2);
//  int pulse3 = degToPulse(a[leg].theta3);
//  terminal.println(a[leg].theta1);
//  terminal.println(a[leg].theta2);
//  terminal.println(a[leg].theta3);
//  terminal.println(pulse1);
//  terminal.println(pulse2);
//  terminal.println(pulse3);
//  terminal.flush();
//}

void runAt(int t) {
  Serial.println("T" + String(t));
}

void calibrate()
{
  setPosisi(0, 60, 0, -30);//1
  setPosisi(2, 60, 0, -30);
  setPosisi(4, 60, 0, -30);
  runAt(500);
  delay(520);
  for (int leg = 0; leg < 6; leg++)
  {
    for (int sendi = 0; sendi < 3; sendi++) {
      setPulse(servo[leg][sendi], pulse[leg][sendi]);
    }
  } runAt(1000); delay(1000);
  setPosisi(1, 60, 0, -30);
  setPosisi(3, 60, 0, -30);//3
  setPosisi(5, 60, 0, -30);
  runAt(500);
  delay(520);
  for (int leg = 0; leg < 6; leg++)
  {
    for (int sendi = 0; sendi < 3; sendi++) {
      setPulse(servo[leg][sendi], pulse[leg][sendi]);
    }
  } runAt(1000); delay(1000);
}

int degToPulse(int deg) {
  int pulse = round(map(deg, -135, 135, -1000, 1000));
  return pulse;
}
