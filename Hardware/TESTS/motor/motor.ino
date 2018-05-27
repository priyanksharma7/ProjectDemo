/*
  Description:
    Turn on motor at the specified speed
*/

#define motorIN1Pin 5  // IN1
#define motorIN2Pin 4  // IN2
#define motorIN3Pin 10  // IN3
#define motorIN4Pin 9 // IN4
#define motorENAPin 3  // ENA
#define motorENBPin 11 // ENB

void MotorSetup() {
  pinMode(motorIN3Pin, OUTPUT);  // Right Back
  pinMode(motorIN4Pin, OUTPUT);  // Right Front
  pinMode(motorIN1Pin, OUTPUT);  // Left  Back
  pinMode(motorIN2Pin, OUTPUT);  // Left  Front
  pinMode(motorENAPin, OUTPUT);  // Left  PWM
  pinMode(motorENBPin, OUTPUT);  // Right PWM
}

void MotorSetSpeed(int s) {
  int speedL, speedR;
  speedL = speedR = s;
  speedL = speedR * 1.05;
  if (s == 0) {
    digitalWrite(motorIN1Pin, HIGH);
    digitalWrite(motorIN2Pin, HIGH);
    digitalWrite(motorIN3Pin, HIGH);
    digitalWrite(motorIN4Pin, HIGH);
    digitalWrite(motorENBPin, LOW);
    digitalWrite(motorENAPin, LOW);
    Serial.println("Motor Stopped");
  } else {
    digitalWrite(motorIN1Pin,LOW);      // Set direction
    digitalWrite(motorIN2Pin,HIGH);     // Set direction
    digitalWrite(motorIN3Pin,LOW);      // Set direction
    digitalWrite(motorIN4Pin,HIGH);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.print("Motor speed set to: ");
    Serial.println(s);
  }
}
void reverse()
{
    int speedL, speedR;
    speedL = speedR = 80;
    digitalWrite(motorIN1Pin,HIGH);      // Set direction
    digitalWrite(motorIN2Pin,LOW);     // Set direction
    digitalWrite(motorIN3Pin,HIGH);      // Set direction
    digitalWrite(motorIN4Pin,LOW);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.print("Motor speed set to: ");
    Serial.println(speedL);
}
void left()
{
    int speedL, speedR;
    speedL = speedR = 50;
    digitalWrite(motorIN1Pin,LOW);      // Set direction
    digitalWrite(motorIN2Pin,HIGH);     // Set direction
    digitalWrite(motorIN3Pin,LOW);      // Set direction
    digitalWrite(motorIN4Pin,LOW);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.print("Motor speed set to: ");
    Serial.println(speedL);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  MotorSetup();
}

void loop() {
  // Change motor speed below
  for (int i=0; i <= 255; i++){
    reverse();
    delay(100);
  }
}
