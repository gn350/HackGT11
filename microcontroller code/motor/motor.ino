// Define motor control pins
const int motorPin1 = 12;  // IN1
const int motorPin2 = 13;  // IN2
const int enablePin = 27;  // ENA (PWM)

void setup() {
  // Set pin modes
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  // Start with the motor off
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);

  // pinMode(LED_BUILTIN, OUTPUT);

  // Bluetooth.begin(9600); // Bluetooth module

  Serial.begin(9600);

}

void loop() {

  // Rotate motor forward
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 255);  // Full speed
  Serial.println("printing");
  // digitalWrite(LED_BUILTIN, HIGH);
  delay(5000);  // Run for 2 seconds

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);  // Stop
  // digitalWrite(LED_BUILTIN, LOW);
  delay(1000);  // Pause for 1 second

  // Rotate motor backward
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, 255);  // Full speed
  delay(2000);  // Run for 2 seconds

  // Stop the motor again
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);  // Stop
  delay(1000);  // Pause for 1 second
}



