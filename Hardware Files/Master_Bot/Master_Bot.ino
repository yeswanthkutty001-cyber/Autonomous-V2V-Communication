// ================= MOTOR PINS =================
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

// ================= MOTOR FUNCTIONS =================

void forward()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopMotors()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ================= SETUP =================

void setup()
{
  Serial.begin(115200);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("Vehicle Starting in 3 seconds...");

  delay(3000);   // wait 3 seconds

  Serial.println("Moving Forward");

  forward();     // move forward
  delay(3000);   // run for 3 seconds

  Serial.println("Stopping");

  stopMotors();  // stop motors
}

// ================= LOOP =================

void loop()
{
  // Nothing here (runs only once)
}