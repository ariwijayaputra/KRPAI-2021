//untuk sensor ultrasonic ping))) 3 pin.
//deskripsi dalam bahasa inggris. males aku ngubah.
int ping() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:

  for (int i = 0; i < 3; i++)
  {
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pingPin[i], OUTPUT);
    digitalWrite(pingPin[i], LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin[i], HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin[i], LOW);

    // The same pin is used to read the signal from the PING))): a HIGH pulse
    // whose duration is the time (in microseconds) from the sending of the ping
    // to the reception of its echo off of an object.
    pinMode(pingPin[i], INPUT);
    duration = pulseIn(pingPin[i], HIGH);

    // convert the time into a distance

    cm[i] = microsecondsToCentimeters(duration);    
    delay(30);
  }
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
