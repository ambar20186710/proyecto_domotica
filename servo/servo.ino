#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(25);  // attaches the servo on pin 25 to the servo object
}

void loop() {
  // Rotate the servo from 0 to 180 degrees
  for (pos = 30; pos <= 160; pos += 1) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  // Pause for a moment at the 180-degree position
  delay(1000); // Adjust the duration as needed

  // Rotate the servo back from 180 to 0 degrees
  for (pos = 160; pos >= 30; pos -= 1) {
    myservo.write(pos);    // tell servo to go to position in variable 'pos'
    delay(15);             // waits 15ms for the servo to reach the position
  }
  // Pause for a moment at the 0-degree position
  delay(1000); // Adjust the duration as needed
}

