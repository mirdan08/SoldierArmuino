#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define minPos 45 // Minimum position of the servo motor
#define servo 9 // Servo motor pin
#define led 7 // LED pin
#define maxPos 110 // Maximum position of the servo motor

#define busy 4 // Pin to check if the player is busy
#define pir 11 // PIR sensor pin
#define tx 2 // Software serial TX pin
#define rx 3 // Software serial RX pin

unsigned long int d, // Current angle of the motor
                  t = 0, // Current timestamp
                  dt; // Time difference
int dStep = 1, // Step for servo motor movement
    currentPirState, // Current state of the PIR sensor
    lastPirState; // Previous state of the PIR sensor

bool movement = false, // True if the PIR sensor detects something
     playerBusy = true; // False if the player is playing something

Servo servoMotor;
SoftwareSerial swSerial(rx, tx);
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);
  Serial.println("start");
  pinMode(servo, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  pinMode(busy, INPUT);
  servoMotor.attach(servo);
  
  swSerial.begin(9600);
  Serial.println("connecting to DFPlayer Mini");
  if (!player.begin(swSerial)) {
    Serial.println("connection failed");
    while (true); // Stay here if connection fails
  }
  Serial.println("connection established");
  player.volume(30); // Set volume to 30
}

void loop() {
  currentPirState = digitalRead(pir);
  playerBusy = digitalRead(busy);
  
  if (currentPirState == HIGH && lastPirState == LOW) { // PIR detected motion
    digitalWrite(led, currentPirState);
    movement = true;
    Serial.println("PIR on");
    if (playerBusy) {
      player.play(1); // Play track 1
      Serial.println("playing sound");
    }
  }
  
  if (currentPirState == LOW && lastPirState == HIGH) { // PIR stopped detecting motion
    digitalWrite(led, currentPirState);
    movement = false;
    Serial.println("PIR off");
  }
  
  dt = millis() - t; // Servo motor movement logic
  if (dt >= 15 && !playerBusy) {
    t = millis();
    d += dStep;
    if (d >= maxPos) {
      d = maxPos;
      dStep = -1; // Reverse direction
      delay(700);
    } else if (d <= minPos) {
      d = minPos;
      dStep = 1; // Change direction
      delay(100);
    }
    servoMotor.write(d); // Move the servo to position d
  }
  
  lastPirState = currentPirState;
}
