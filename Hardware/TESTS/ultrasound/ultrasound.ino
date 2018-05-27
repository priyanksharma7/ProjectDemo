/*
  Description:
    Reads input from ultrasound sensor and display distance back to host.
*/

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

/* Return distance from ulstrasound sensor in cm 
 */
float UsGetDistance1() {
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
float UsGetDistance2() {
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
float UsGetDistance3() {
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  UsSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  float distance1,distance2,distance3;

  // Read distance from Ultrasound Sensor
  distance1 = UsGetDistance1();
  distance2 = UsGetDistance2();
  distance3 = UsGetDistance3();
  Serial.print("DistanceS is: ");
  Serial.println(distance1);
  Serial.print("DistanceL is: ");
  Serial.println(distance2);
  Serial.print("DistanceR is: ");
  Serial.println(distance3);
}

