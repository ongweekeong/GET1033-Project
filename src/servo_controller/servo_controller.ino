#include <Arduino.h>
#include <avr/io.h>

#define LDR_PIN A0
#define LED_PIN 5
#define SERVO_PIN 3
#define trigPin 9
#define echoPin 10
 
const int stairWidth = 60;
const int threshold_dist = 100;
const int threshold_LED = 500;
const int upperLim = 2500;
const int lowerLim = 1000;
const int distMultiplier = (upperLim - lowerLim)/threshold_dist;
const int period = 20000;
const int correction = 20;
const int numReadings = 50;

int dutyCycle;
boolean isRising = true;

long duration;
int distance = 0;
int avgDistance;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  dutyCycle = 1000;
  Serial.begin(9600);  
}

void loop() {
  int brightness = getAverageBrightness();
  int LEDBrightness = 0;
  if (brightness < threshold_LED) {
    checkDistance();
  } 
  else{
    digitalWrite(LED_PIN, LOW);
  }
}

void checkDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds (2);
  distance = 0;
  for(int i = 0; i<numReadings; i++) {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    distance += pulseIn(echoPin, HIGH)*0.034/2;
  }
  avgDistance = distance/numReadings;
  if(avgDistance<threshold_dist) {
    directServo(avgDistance);
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
}

void directServo(int dist){
  dutyCycle = distMultiplier*dist + lowerLim;
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(dutyCycle);
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(period - dutyCycle);
}

int getAverageBrightness(void){
  long total = 0;
  int avg = 0;
  for(int i=0; i<numReadings; i++){
    int brightness = analogRead(LDR_PIN);
    int input = 1/(double)brightness * 100000;
    total += input;
  } 
  avg = total/numReadings;
  return avg;
}
