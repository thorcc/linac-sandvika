#include <Servo.h>
const int potPin = A3;
const int buttonPin = 5;
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int servoPin = 9;

Servo myservo;
int state = 0;
int potVal = 0;
int buttonState;
int lastButtonState = 0;
int servoPos = 0;
int lowDegree;
int highDegree;


// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 100;   // the debounce time; increase if the output flickers
unsigned long time;

bool buttonPressed() {
  bool pressed = false;
  int reading = digitalRead(buttonPin);
  time = millis();
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == 1) {
        pressed = true;
      }
    }
  }
  lastButtonState = reading;
  return pressed;
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  myservo.attach(servoPin);
}

void loop() {

  if (state == 0) {
    potVal = analogRead(potPin);
    lowDegree = map(potVal, 0, 1023, 0, 180);
    myservo.write(lowDegree);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    if (buttonPressed()){
      state++;
    }
  } else if (state == 1) {
    potVal = analogRead(potPin);
    highDegree = map(potVal, 0, 1023, 0, 180);
    myservo.write(highDegree);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    if (buttonPressed()){
      state++;
    }
  } else {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, HIGH);
    myservo.write(lowDegree);
    Serial.print("low: ");
    Serial.print(lowDegree);
    Serial.print("\n");
    delay(100);                
    myservo.write(highDegree);
    Serial.print("high: ");
    Serial.print(highDegree);
    Serial.print("\n");
    delay(100);                 
    if (buttonPressed()){
      state = 0;
    }
  }
}
