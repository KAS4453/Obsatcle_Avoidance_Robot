#include <Servo.h>
Servo Myservo;

#define trigPin 9  // Trig Pin Of HC-SR04
#define echoPin 8  // Echo Pin Of HC-SR04
#define MLa 4      // Left motor 1st pin
#define MLb 5      // Left motor 2nd pin
#define MRa 6      // Right motor 1st pin
#define MRb 7      // Right motor 2nd pin
#define pwm 3      // PWM pin for speed control

long duration, distance;

void setup() {
    Serial.begin(9600);
    pinMode(MLa, OUTPUT); // Set Motor Pins As Output
    pinMode(MLb, OUTPUT);
    pinMode(MRa, OUTPUT);
    pinMode(MRb, OUTPUT);
    pinMode(trigPin, OUTPUT); // Set Trig Pin As Output
    pinMode(echoPin, INPUT);  // Set Echo Pin As Input
    Myservo.attach(10);       // Attach servo to pin 10
    Myservo.write(90);        // Set servo to initial position
}

void loop() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); // Transmit waves for 10us
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH); // Receive reflected waves
    distance = duration / 58.2;        // Calculate distance in cm
    Serial.println(distance);

    if (distance > 30) { // No obstacle
        Myservo.write(90);
        digitalWrite(MRb, HIGH); // Move forward
        digitalWrite(MRa, LOW);
        digitalWrite(MLb, HIGH);
        digitalWrite(MLa, LOW);
        analogWrite(pwm, 150);
    } 
    else if (distance > 0 && distance <= 30) { // Obstacle detected
        digitalWrite(MRb, LOW); // Stop
        digitalWrite(MRa, LOW);
        digitalWrite(MLb, LOW);
        digitalWrite(MLa, LOW);
        delay(100);

        // Scan with servo
        Myservo.write(0);    // Look left
        delay(500);
        Myservo.write(180);  // Look right
        delay(500);
        Myservo.write(90);   // Center position
        delay(500);

        // Move backward
        digitalWrite(MRb, LOW);
        digitalWrite(MRa, HIGH);
        digitalWrite(MLb, LOW);
        digitalWrite(MLa, HIGH);
        analogWrite(pwm, 150);
        delay(500);

        // Stop and turn left
        digitalWrite(MRb, LOW);
        digitalWrite(MRa, LOW);
        digitalWrite(MLb, LOW);
        digitalWrite(MLa, LOW);
        delay(100);

        digitalWrite(MRb, HIGH); // Move left
        digitalWrite(MRa, LOW);
        digitalWrite(MLa, LOW);
        digitalWrite(MLb, HIGH);
        analogWrite(pwm, 150);
        delay(500);
    }
}