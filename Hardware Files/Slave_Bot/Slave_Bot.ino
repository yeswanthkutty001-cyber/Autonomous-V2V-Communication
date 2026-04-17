#include <BluetoothSerial.h>
#include <ESP32Servo.h>

// ================= VEHICLE CONFIGURATION =================
#define VEHICLE_ID 1
#define SAFE_DISTANCE 20
#define BROADCAST_INTERVAL 100

// ================= MOTOR PINS =================
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14

// ================= SENSOR PINS =================
#define TRIG 33
#define ECHO 32

// ================= SERVO PIN =================
#define SERVO_PIN 13

// ================= GLOBAL OBJECTS =================
BluetoothSerial BT;
Servo myServo;

// ================= VEHICLE STATE VARIABLES =================
char lastCmd = 'S';
int otherVehicleID = 0;
char otherDirection = 'S';
long otherDistance = 0;
unsigned long lastBroadcastTime = 0;
bool isConnected = false;

// ================= MOTOR CONTROL FUNCTIONS ================= (same as master)
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}

// ================= DISTANCE MEASUREMENT ================= (same)
long getDistance() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIn(ECHO, HIGH, 20000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}

// ================= SERVO SCANNING ================= (same)
int scanEnvironment() {
  myServo.write(0);   delay(250);
  long leftDist  = getDistance();
  myServo.write(180); delay(250);
  long rightDist = getDistance();
  myServo.write(90);  delay(200);
  return (leftDist > rightDist) ? -1 : 1;
}

// ================= COMMUNICATION =================
void sendVehicleData(long distance) {
  if (!isConnected) return;
  BT.print(VEHICLE_ID);
  BT.print(",");
  BT.print(lastCmd);
  BT.print(",");
  BT.println(distance);
}

void receiveVehicleData() {
  if (!isConnected) return;
  while (BT.available()) {
    String msg = BT.readStringUntil('\n');
    msg.trim();
    if (msg.length() < 5) continue;

    int c1 = msg.indexOf(',');
    int c2 = msg.lastIndexOf(',');
    if (c1 <= 0 || c2 <= c1) continue;

    otherVehicleID  = msg.substring(0, c1).toInt();
    otherDirection  = msg.substring(c1 + 1, c2).charAt(0);
    otherDistance   = msg.substring(c2 + 1).toInt();
  }
}

// ================= DECISION ALGORITHM ================= (same)
void decisionLogic(long dist) {
  if (dist > 0 && dist < SAFE_DISTANCE && otherDirection == 'F') {
    Serial.println("Opposite vehicle detected → STOP");
    stopMotors();
    lastCmd = 'S';
    return;
  }

  if (dist > 0 && dist < SAFE_DISTANCE && otherDirection == 'S') {
    Serial.println("Vehicle ahead → STOP (safe distance)");
    stopMotors();
    lastCmd = 'S';
    return;
  }

  if (dist > 0 && dist < SAFE_DISTANCE &&
      otherDistance > 0 && otherDistance < SAFE_DISTANCE) {
    if (VEHICLE_ID > otherVehicleID) {
      Serial.println("Intersection priority → waiting");
      stopMotors();
      lastCmd = 'S';
      return;
    }
  }

  lastCmd = 'F';
  forward();
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90);

  Serial.println("\n===== V2V ROVER (ID " + String(VEHICLE_ID) + ") =====");

  if (!BT.begin("ESP32_Rover")) {   // ← must match name master is looking for
    Serial.println("Bluetooth failed to start!");
    while (1) delay(1000);
  }

  Serial.println("Bluetooth advertising started. Waiting for master...");
}

// ================= LOOP =================
void loop() {
  // Update connection status
  isConnected = BT.hasClient() || BT.connected();

  long dist = getDistance();

  if (isConnected && millis() - lastBroadcastTime >= BROADCAST_INTERVAL) {
    sendVehicleData(dist);
    lastBroadcastTime = millis();
  }

  receiveVehicleData();

  decisionLogic(dist);

  delay(20);
}