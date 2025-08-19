#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <DabbleESP32.h>
#define MOTOR_SPEED 200
#define TURNING_SPEED 150

int enableRightMotor = 22;
int rightMotorPin1 = 16;
int rightMotorPin2 = 17;

int enableLeftMotor = 23;
int leftMotorPin1 = 18;
int leftMotorPin2 = 19;

const int PWMFreq = 1000; 
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

int motorSpeed = MOTOR_SPEED;
int carDirection = 0;

void setup() {
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);

  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  ledcSetup(rightMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcSetup(leftMotorPWMSpeedChannel, PWMFreq, PWMResolution);
  ledcAttachPin(enableRightMotor, rightMotorPWMSpeedChannel);
  ledcAttachPin(enableLeftMotor, leftMotorPWMSpeedChannel);

  rotateMotor(0, 0);

  Dabble.begin("MyVoiceCar"); 
}

void loop() {
  Dabble.processInput();
  controlWithVoice();
}

void controlWithVoice() {
  if (Terminal.available()) {
    String serialdata = Terminal.readString();
    serialdata.toLowerCase();
    serialdata.trim();

    if (serialdata == "stop") {
      carDirection = 0;
      rotateMotor(0, 0);
    }
    else if (serialdata == "forward") {
      carDirection = 1;
      rotateMotor(motorSpeed, motorSpeed);
    }
    else if (serialdata == "backward" || serialdata == "reverse" || serialdata == "back") {
      carDirection = -1;
      rotateMotor(-motorSpeed, -motorSpeed);
    }
    else if (serialdata == "turn right" || serialdata == "right") {
      if (carDirection == 0) carDirection = 1;
      int turningSpeed = (carDirection == -1 ? -TURNING_SPEED : TURNING_SPEED);
      rotateMotor(-turningSpeed, turningSpeed);
      delay(200);
      rotateMotor(motorSpeed * carDirection, motorSpeed * carDirection);
    }
    else if (serialdata == "turn left" || serialdata == "left") {
      if (carDirection == 0) carDirection = 1;
      int turningSpeed = (carDirection == -1 ? -TURNING_SPEED : TURNING_SPEED);
      rotateMotor(turningSpeed, -turningSpeed);
      delay(200);
      rotateMotor(motorSpeed * carDirection, motorSpeed * carDirection);
    }
    else if (serialdata == "rotate right") {
      if (carDirection == 0) carDirection = 1;
      int turningSpeed = (carDirection == -1 ? -TURNING_SPEED : TURNING_SPEED);
      rotateMotor(-turningSpeed, turningSpeed);
    }
    else if (serialdata == "rotate left") {
      if (carDirection == 0) carDirection = 1;
      int turningSpeed = (carDirection == -1 ? -TURNING_SPEED : TURNING_SPEED);
      rotateMotor(turningSpeed, -turningSpeed);
    }
    else if (serialdata.startsWith("speed ")) {
      serialdata.remove(0, 6);
      int newMotorSpeed = serialdata.toInt();
      if (newMotorSpeed > 0) {
        motorSpeed = constrain(newMotorSpeed, 0, 255);
        rotateMotor(motorSpeed * carDirection, motorSpeed * carDirection);
      }
    }
    
  }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  // Right motor control
  if (rightMotorSpeed < 0) {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  }
  else if (rightMotorSpeed > 0) {
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  }
  else {
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Left motor control
  if (leftMotorSpeed < 0) {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  }
  else if (leftMotorSpeed > 0) {
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  }
  else {
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  ledcWrite(rightMotorPWMSpeedChannel, abs(rightMotorSpeed));
  ledcWrite(leftMotorPWMSpeedChannel, abs(leftMotorSpeed));
}
