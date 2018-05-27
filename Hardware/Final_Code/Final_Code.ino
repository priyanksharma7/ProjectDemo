//FULLY FUNCTIONAL CAR.

#define motorIN1Pin 5  // IN1
#define motorIN2Pin 4  // IN2
#define motorIN3Pin 10  // IN3
#define motorIN4Pin 9 // IN4
#define motorENAPin 3  // ENA
#define motorENBPin 11 // ENB

#define usTrigPin1 12    // Ultrasound Trig Pin
#define usEchoPin1 13    // Ultrasound Echo Pin
#define usTrigPin2 6    // Ultrasound Trig Pin
#define usEchoPin2 2    // Ultrasound Echo Pin
#define usTrigPin3 8    // Ultrasound Trig Pin
#define usEchoPin3 7    // Ultrasound Echo Pin

void UsSetup() {
  pinMode(usTrigPin1, OUTPUT);
  pinMode(usEchoPin1, INPUT);
  pinMode(usTrigPin2, OUTPUT);
  pinMode(usEchoPin2, INPUT);
  pinMode(usTrigPin3, OUTPUT);
  pinMode(usEchoPin3, INPUT);
}

//Return distance from 3 ulstrasound sensors in cm or max value (400) if out of range

float UsGetDistance() {
  float duration, dist;
  
  // Send out ultrasound trigger
  digitalWrite(usTrigPin1, LOW); 
  delayMicroseconds(1);
 
  digitalWrite(usTrigPin1, HIGH);
  delayMicroseconds(2);
  digitalWrite(usTrigPin1, LOW);

  // Wait for ultrasound echo
  duration = pulseIn(usEchoPin1, HIGH);

  // Compute distance
  dist =  (duration / 2) * 0.0344;
  
  return dist;
}
float UsGetDistanceL() {
  float duration, dist;
  
  // Send out ultrasound trigger
  digitalWrite(usTrigPin2, LOW); 
  delayMicroseconds(1);
 
  digitalWrite(usTrigPin2, HIGH);
  delayMicroseconds(2);
  digitalWrite(usTrigPin2, LOW);

  // Wait for ultrasound echo
  duration = pulseIn(usEchoPin2, HIGH);

  // Compute distance
  dist =  (duration / 2) * 0.0344;
  
  return dist;
}
float UsGetDistanceR() {
  float duration, dist;
  
  // Send out ultrasound trigger
  digitalWrite(usTrigPin3, LOW); 
  delayMicroseconds(1);
 
  digitalWrite(usTrigPin3, HIGH);
  delayMicroseconds(2);
  digitalWrite(usTrigPin3, LOW);

  // Wait for ultrasound echo
  duration = pulseIn(usEchoPin3, HIGH);

  // Compute distance
  dist =  (duration / 2) * 0.0344;
  
  return dist;
}

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
  // The left and right wheels are inbalance due to physical limitation.
  // Slightly adjust the values between left/right to suit your car.
  // Remember: a higher value makes the motor spins faster.
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
    speedL = speedR = 150;
    digitalWrite(motorIN1Pin,HIGH);      // Set direction
    digitalWrite(motorIN2Pin,LOW);     // Set direction
    digitalWrite(motorIN3Pin,HIGH);      // Set direction
    digitalWrite(motorIN4Pin,LOW);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.println("We are in reverse().");
}
void right()
{
    int speedL, speedR;
    speedL = speedR = 150;
    digitalWrite(motorIN1Pin,LOW);      // Set direction
    digitalWrite(motorIN2Pin,LOW);     // Set direction
    digitalWrite(motorIN3Pin,LOW);      // Set direction
    digitalWrite(motorIN4Pin,HIGH);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.println("We are in right().");
}
void left()
{
    int speedL, speedR;
    speedL = speedR = 150;
    digitalWrite(motorIN1Pin,LOW);      // Set direction
    digitalWrite(motorIN2Pin,HIGH);     // Set direction
    digitalWrite(motorIN3Pin,LOW);      // Set direction
    digitalWrite(motorIN4Pin,LOW);     // Set direction
    analogWrite(motorENAPin,speedL);         // Control speed with PWM
    analogWrite(motorENBPin,speedR);         // Control speed with PWM
    Serial.println("We are in left().");
}

void right_turn()
{
  right();
  delay(500); // Delay 1 second
  MotorSetSpeed(100);
  delay(500); // Delay 1 second
  left();
  delay(500); // Delay 1 second
}

void left_turn()
{
  left();
  delay(500); // Delay 1 second
  MotorSetSpeed(100);
  delay(500); // Delay 1 second
  right();
  delay(500); // Delay 1 second
}


int ComputeSpeed(float distance, float distanceL, float distanceR) {
  // Compute the desired motor speed and store in the variable motorSpeed
  int motorSpeed;
  int speedMin = 150;
  int speedMax = 200;

  if (distanceR < 20)
  {
    MotorSetSpeed(0);
    left_turn();
    return 180;
  }
  if (distanceL < 20)
  {
    MotorSetSpeed(0);
    right_turn();
    return 180;
  }
  if (distance >= 20)
  {
    if (distanceL < 20 && distanceR < 20)
      motorSpeed = speedMin;
    else if (distanceR < 20)
    {
      MotorSetSpeed(0);
      left_turn();
    }
    else if (distanceL < 20)
    {
      MotorSetSpeed(0);
      right_turn();
    }
    else
    {
      motorSpeed = speedMax;
    }
  }
  else if (distance >= 8 && distance < 20)
  {
    if (distanceL > 20)
    {
      MotorSetSpeed(0);
      left_turn();
    }
    else if (distanceR > 20)
    {
      MotorSetSpeed(0);
      right_turn();
    }
    else
    {
      reverse();
      delay(800);
      if (distanceL > distanceR)
      {
        left();
      }
      else
      {
        right();
      }
      delay(500);
    }
  }
  else
  {
    reverse();
    delay(800);
    if (distanceL > distanceR)
    {
      left();
    }
    else
    {
      right();
    }
    delay(500);
  }
  return motorSpeed;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  UsSetup();
  MotorSetup();
}
int flag=0;
void loop() {
  // put your main code here, to run repeatedly:
  float distance,distanceL,distanceR;
  int motorSpeed;
  if (Serial.available()) {
    flag = (Serial.read()-'0');
  }
  if (flag)
  {
    // Read distance from Ultrasound Sensor
    distance = UsGetDistance();
    distanceL = UsGetDistanceL();
    distanceR = UsGetDistanceR();
    Serial.print("DistanceS is: ");
    Serial.println(distance);
    Serial.print("DistanceL is: ");
    Serial.println(distanceL);
    Serial.print("DistanceR is: ");
    Serial.println(distanceR);
  
    // Process: compute desired speed based on distance from obstacle
    motorSpeed = ComputeSpeed(distance,distanceL,distanceR);
    
    // Set motor to the speed you've decided on
    MotorSetSpeed(motorSpeed);
  }
  else
    MotorSetSpeed(0);
}
