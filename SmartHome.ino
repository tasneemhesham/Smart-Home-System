#include <Servo.h>
#include <LiquidCrystal_I2C.h>

/////////////////////////////////////////////////////////////////////
// PIR - Garage
int pirPin = 12; // Arduino pin the PIR sensor is connected to
int servoPin = 9; // Arduino pin the garage door servo is connected to
int motionStatus = 0; // Variable to store the PIR sensor's motion status (high or low)
int pirState = 0; // Variable to track the state change
Servo scaryServo; // Create servo object to control the garage door servo

/////////////////////////////////////////////////////////////////////
// Gas Sensor
int gasPin = A0;
int buzzerPin = 4;
int gasValue;
int gasThreshold = 250;

////////////////////////////////////////////////////////////////////////
// Ultrasonic - Room
const int trigPin = 10;
const int echoPin = 11;
const int led1 = 13;
long duration;
int distance;

//////////////////////////////////////////////////////////////////////////
// Water Level - LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);

//////////////////////////////////////////////////////////////////////////////
// Ultrasonic - Main Gate
Servo gateServo;   
int gateDistance = 0;

//////////////////////////////////////////////////////////////////////////////
// Solar Tracker - LDR
Servo vertical; // Vertical servo for solar panel adjustment
int ldrPin1 = 8; // Digital pin for LDR 1
int ldrPin2 = 9; // Digital pin for LDR 2
const int verticalMinAngle = 0; // Minimum angle for the vertical servo
const int verticalMaxAngle = 180; // Maximum angle for the vertical servo

void setup() {
  //////////////////////////////////////////////////////////////////
  // PIR
  Serial.begin(9600); // Initialize the serial monitor
  pinMode(pirPin, INPUT); // Set PIR sensor pin as input
  scaryServo.attach(servoPin); // Attach garage door servo to the servo object
  scaryServo.write(0); // Start the servo at 0 degrees
  delay(100); // Give time for the PIR sensor to calibrate (30-60 seconds is best)

  //////////////////////////////////////////////////////////////////
  // Gas Sensor
  pinMode(gasPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

  //////////////////////////////////////////////////////////////////
  // Ultrasonic - Room
  pinMode(trigPin, OUTPUT); // Set the trigPin as an Output
  pinMode(echoPin, INPUT); // Set the echoPin as an Input
  pinMode(led1, OUTPUT);

  //////////////////////////////////////////////////////////////////
  // Water Level - LCD
  lcd.begin();
  lcd.backlight();

  //////////////////////////////////////////////////////////////////
  // Ultrasonic - Main Gate
  gateServo.attach(8); // Attach gate servo to pin 8

  //////////////////////////////////////////////////////////////////
  // Solar Tracker - LDR
  vertical.attach(7); // Attach vertical servo to pin 7
  vertical.write(180); // Set initial position to 180 degrees
  pinMode(ldrPin1, INPUT); // Set LDR pin 1 as input
  pinMode(ldrPin2, INPUT); // Set LDR pin 2 as input
}

void loop() {
  //////////////////////////////////////////////////////////////////
  // PIR Sensor
  motionStatus = digitalRead(pirPin); // Read PIR pin's current output (HIGH or LOW)

  if (motionStatus == HIGH) {
    scaryServo.write(90); // Rotate the servo to 90 degrees
    if (pirState == LOW) {
      Serial.println("Motion Detected"); // Print result to the serial monitor
      pirState = HIGH; // Update the previous state to HIGH
    }
  } else {
    scaryServo.write(0); // Rotate the servo back to 0 degrees
    if (pirState == HIGH) {
      Serial.println("Motion Ended"); // Print result to the serial monitor
      pirState = LOW; // Update the previous state to LOW
    }
  }

  //////////////////////////////////////////////////////////////////
  // Gas Sensor
  gasValue = analogRead(gasPin);
  Serial.print("Analog Reading: ");
  Serial.println(gasValue);
  if (gasValue >= gasThreshold) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("GAS LEAKING");
  } else {
    digitalWrite(buzzerPin, LOW);
    Serial.println("NORMAL");
  }
  delay(1000); // Add a delay to make the output easier to read

  //////////////////////////////////////////////////////////////////
  // Ultrasonic - Room
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance <= 6) {
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }

  Serial.print("Distance: ");
  Serial.println(distance);

  //////////////////////////////////////////////////////////////////
  // Water Level - LCD
  int waterLevelValue = analogRead(A1);
  lcd.setCursor(0, 0);
  lcd.print("Value :");
  lcd.print(waterLevelValue);
  lcd.print("   ");
  Serial.println(waterLevelValue);
  lcd.setCursor(0, 1);
  lcd.print("W Level :");

  if (waterLevelValue == 0) {
    lcd.print("Empty ");
  } else if (waterLevelValue > 1 && waterLevelValue < 350) {
    lcd.print("LOW   ");
  } else if (waterLevelValue > 350 && waterLevelValue < 510) {
    lcd.print("Medium");
  } else if (waterLevelValue > 510) {
    lcd.print("HIGH");
  }

  //////////////////////////////////////////////////////////////////
  // Ultrasonic - Main Gate
  gateDistance = 0.01723 * readUltrasonicDistance(7, 6); // Corrected pin assignment

  if (gateDistance < 2) {
    Serial.print(gateDistance);
    Serial.println(" cm");

    // Move servo to 120 degrees
    for (int pos = 0; pos <= 120; pos += 1) {
      gateServo.write(pos);
      delay(10); // Delay for smooth movement
    }
    delay(500);

    // Move servo back to 0 degrees
    for (int pos = 120; pos >= 0; pos -= 1) {
      gateServo.write(pos);
      delay(10); // Delay for smooth movement
    }
    delay(500);
  } else {
    gateServo.write(0); // Stop servo movement if distance exceeds 11 cm
  }

  //////////////////////////////////////////////////////////////////
  // Solar Tracker - LDR
  // Read light levels from LDRs
  int lightLevel1 = digitalRead(ldrPin1);
  int lightLevel2 = digitalRead(ldrPin2);

  // Calculate the difference between light levels
  int lightDifference = lightLevel1 - lightLevel2;

  // Define servo movement increment
  int movementIncrement = 5;

  // Adjust servo position based on light difference
  if (lightDifference > 0) {
    vertical.write(vertical.read() - movementIncrement); // Move servo forward
    if (vertical.read() < verticalMinAngle) {
      vertical.write(verticalMinAngle); // Ensure it does not go below minimum angle
    }
  } else if (lightDifference < 0) {
    vertical.write(vertical.read() + movementIncrement); // Move servo backward
    if (vertical.read() > verticalMaxAngle) {
      vertical.write(verticalMaxAngle); // Ensure it does not exceed maximum angle
    }
  }

  delay(100); // Adjust delay as needed
}

long readUltrasonicDistance(int triggerPin, int echoPin) {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
