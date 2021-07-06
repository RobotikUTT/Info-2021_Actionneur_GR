#include <Arduino.h>

//includes :
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//CAN :
// #include "can.h"
// #include "protocol.gen.hpp"

// #include "serial.hpp"

//Servos :
#include <Servo.h>

#include <StepperControl.h>
//Steppers :
#include <PololuA4983.h>

Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x55);

#define SERVOMIN 250  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 500  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1000    // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2000    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

void setServoAngle(uint8_t n, double degrees)
{
  double pulse = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  Serial.print(pulse);
  Serial.println("pulse");
  pca.setPWM(n, 0, pulse);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("PCA test");
  Wire.begin();

  pinMode(13, OUTPUT);

  pca.begin();
  pca.setPWMFreq(1600);
  pca.setOscillatorFrequency(27000000);
  pca.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
}

void loop()
{
  // put your main code here, to run repeatedly:
  digitalWrite(13, 1);
  delay(500);
  digitalWrite(13, 0);

  for (uint16_t angle = 0; angle < 180; angle++)
  {
    setServoAngle(0, angle);
    setServoAngle(1, angle);
  }

  delay(500);
  for (uint16_t angle = 180; angle > 0; angle--)
  {
    setServoAngle(0, angle);
    setServoAngle(1, angle);
  }

  delay(500);
}