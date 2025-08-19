#define BLYNK_TEMPLATE_ID "TMPL3NV0MiAHM"
#define BLYNK_TEMPLATE_NAME "RobotCar"
#define BLYNK_AUTH_TOKEN "_G4Dh6zJFECx6Jm44JbadH4RR1ynOatn"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>


char ssid[] = "WiFi_SSID";       
char pass[] = "WiFi_Password";   


const int enA = 23;
const int in1 = 18;
const int in2 = 19;
const int enB = 22;
const int in3 = 16;
const int in4 = 17;

const int motorSpeed = 200;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  // PWM setup
  ledcSetup(0, 1000, 8);
  ledcAttachPin(enA, 0);

  ledcSetup(1, 1000, 8);
  ledcAttachPin(enB, 1);

  Serial.println("Connecting to WiFi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

// Movement functions
void moveForward() {
  Serial.println("Moving Forward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void moveBackward() {
  Serial.println("Moving Backward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void turnLeft() {
  Serial.println("Turning Left");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void turnRight() {
  Serial.println("Turning Right");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  ledcWrite(0, motorSpeed);
  ledcWrite(1, motorSpeed);
}

void stopMotors() {
  Serial.println("Stopping");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
}


BLYNK_WRITE(V0) {  
  if (param.asInt()) moveForward(); else stopMotors();
}

BLYNK_WRITE(V1) {  
  if (param.asInt()) moveBackward(); else stopMotors();
}

BLYNK_WRITE(V2) {  
  if (param.asInt()) turnLeft(); else stopMotors();
}

BLYNK_WRITE(V3) {  
  if (param.asInt()) turnRight(); else stopMotors();
}

void loop() {
  Blynk.run();
}
