#include <Arduino.h>

//includes :
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//CAN :
#include <cpp_header_gen/can.hpp>

//Servos :
#include <Servo.h>


/***** Stepper *****/
#define BTN_PIN   2

#define DIR_PIN   4
#define STEP_PIN  6
#define EN_PIN    8

#define TOUCH_SPEED 120

bool
stepper_direction_clockwise = false,
stepper_enable_state = false;

uint8_t stepper_speed = 120;
uint16_t nb_steps, cpt_steps;

/***** Servo *****/
Adafruit_PWMServoDriver pca = Adafruit_PWMServoDriver(0x55);

#define SERVOMIN 150  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600  // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 1000    // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2000    // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// Customized manually
// First value is closed claw angle
// Second is open claw angle
double servo_claws_angles[5][2] = {
  {30.0, 80.0},
  {120.0, 90.0},
  {90.0, 50.0},
  {95.0, 50.0},
  {90.0, 50.0}
};
double servo_arm_angles[2] = {125.0, 60.0};

void setServoAngle(uint8_t n, double degrees) {
  // Serial.print(n);
  // Serial.println(degrees);
  double pulse = map(degrees, 0, 180, SERVOMIN, SERVOMAX);
  // Serial.print(pulse);
  // Serial.println(" pulses");
  pca.setPWM(n, 0, pulse);
}

/***** CAN *****/
CanHandler canHandler;


void setup() {
  canHandler.setup();

  // Serial.begin(115200);
  // Serial.setTimeout(100);
  // Serial.println("##### PCA tester #####");
  // Serial.println("Enter:");
  // Serial.println("\t'A' to set angle.");
  // Serial.println("\t'N' to pass to next servo.");

  
  /***** Stepper *****/
  digitalWrite(EN_PIN, HIGH);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  /***** Servo *****/
  Wire.begin();

  pca.begin();
  pca.setPWMFreq(1600);
  pca.setOscillatorFrequency(27000000);
  pca.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
}

void loop() {

  std::vector<int> frame = canHandler.read();
  if (!frame.empty()) {
    switch(frame[0]) {
      case 0:   // PING
        canHandler.send(PONG, 3, 0);
        canHandler.flush();
        break;
      case 44:  // SERVO ANGLE
        if (frame[1] == 0xff) {
          Wire.begin();

          pca.begin();
          pca.setPWMFreq(1600);
          pca.setOscillatorFrequency(27000000);
          pca.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
        }
        else {
          setServoAngle(frame[1], (double) frame[2]);
        }
        break;
      case 45:  // STEPPER PARAMS
        stepper_enable_state = frame[1];
        digitalWrite(EN_PIN, !stepper_enable_state);
        stepper_direction_clockwise = frame[2];
        digitalWrite(DIR_PIN, stepper_direction_clockwise);
        stepper_speed = frame[3];
        break;
      case 46:  // STEPPER STEPS
        nb_steps = frame[1];

        for (cpt_steps=0; cpt_steps<nb_steps; cpt_steps++) {
          if (stepper_direction_clockwise && !digitalRead(BTN_PIN)) {
            break;
          }
          digitalWrite(STEP_PIN, HIGH);
          delayMicroseconds(3);
          digitalWrite(STEP_PIN, LOW);
          delayMicroseconds(60L * 1000000L / (200L * stepper_speed));
        }
        canHandler.send(END_STEP, cpt_steps >> 8, cpt_steps & 0xff);
        canHandler.flush();
        break;
    }
  }
  delay(10);

  // for (uint8_t n=0; n<5; n++) {
  //   double angle = 60;
  //   setServoAngle(n, angle);
  //   bool not_next = true;
  //   while(not_next) {
  //     if (Serial.available()) {
  //       char cmd = Serial.read();
  //       double new_angle;
  //       switch(cmd) {
  //         case 'A':
  //           new_angle = Serial.parseFloat();
  //           if (new_angle) {
  //             angle = new_angle;
  //           }
  //           setServoAngle(n, angle);
  //           break;
  //         case 'N':
  //           not_next = false;
  //           break;
  //       }
  //     }
  //     delay(10);
  //   }
  // }


  // put your main code here, to run repeatedly:
  // digitalWrite(13, 1);
  // delay(500);
  // digitalWrite(13, 0);

  // for (uint16_t angle = 0; angle < 180; angle++)
  // {
  //   setServoAngle(0, angle);
  //   setServoAngle(1, angle);
  // }

  // delay(500);
  // for (uint16_t angle = 180; angle > 0; angle--)
  // {
  //   setServoAngle(0, angle);
  //   setServoAngle(1, angle);
  // }

  // delay(500);
}
