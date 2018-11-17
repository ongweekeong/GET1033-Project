#include <Arduino.h>
#include <avr/io.h>

#define LDR_PIN A0
#define SERVO_PIN 3
#define LED_PIN 5
#define BUZZER 8
#define TRIG_PIN 9
#define ECHO_PIN 10

//For the music
const int c4 = 261;
const int cS4 = 277;
const int d4 = 294;
const int dS4 = 311;
const int e4 = 329;
const int f4 = 349;
const int fS4 = 370;
const int g4 = 391;
const int gS4 = 415;
const int la4 = 440;
const int laS4 = 455;
const int b4 = 466;
const int c5 = 523;
const int cS5 = 554;
const int d5 = 587;
const int dS5 = 622;
const int e5 = 659;
const int f5 = 698;
const int fS5 = 740;
const int g5 = 784;
const int gS5 = 830;
const int la5 = 880; 
const int laS5 = 932;
const int d6 = 1175;
const int dS6 = 1245;
const int e6 = 1319;
const int f6 = 1397;
const int fS6 = 1480;
 
const int stairWidth = 60;
const int threshold_dist = 50;
const int threshold_LED = 300;
const int threshold_bell = 4;
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

void beep(int note, int duration) {
  //Play tone on buzzerPin
  tone(BUZZER, note, duration);

  delay(1 + duration);
 
  //Stop tone on buzzerPin
  noTone(BUZZER);
}
 
void firstSection() {
  beep(c4, 250);
  beep(d4, 250);    
  beep(dS4, 250);
  beep(f4, 250);
  beep(g4, 250);  
  beep(dS4, 250);
  beep(g4, 500);
  beep(fS4, 250);
  beep(d4, 250);
  beep(fS4, 500);
  beep(f4, 250);
  beep(cS4, 250);
  beep(f4, 500);
  beep(c4, 250);
  beep(d4, 250);    
  beep(dS4, 250);
  beep(f4, 250);
  beep(g4, 250);
  beep(dS4, 250);
  beep(g4, 250);
  beep(c5, 250);
  beep(laS4, 250);
  beep(g4, 250);
  beep(dS4, 250);
  beep(g4, 250);
  beep(laS4, 500);
  delay(500);
}
 
void secondSection() {
  beep(g4, 250);
  beep(la4, 250);    
  beep(b4, 250);
  beep(c5, 250);
  beep(d5, 250);  
  beep(b4, 250);
  beep(d5, 500);
  beep(dS5, 250);
  beep(b4, 250);
  beep(dS5, 500);
  beep(d5, 250);
  beep(b4, 250);
  beep(d5, 500);
  beep(g4, 250);
  beep(la4, 250);    
  beep(b4, 250);
  beep(c5, 250);
  beep(d5, 250);
  beep(b4, 250);
  beep(d5, 500);
  beep(dS5, 250);
  beep(b4, 250);
  beep(dS5, 500);
  beep(d5, 500);
  delay(500);
}

void doorbell(void) {
  //Play first section
  firstSection();
 
  //Play second section
  secondSection();
}

void checkDistance(){
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds (2);
  distance = 0;
  for(int i = 0; i<numReadings; i++) {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    distance += pulseIn(ECHO_PIN, HIGH)*0.034/2;
  }
  avgDistance = distance/numReadings;
  Serial.println(avgDistance);
  if (avgDistance<threshold_dist) {
    directServo(avgDistance);
    if (avgDistance < threshold_bell) {
      doorbell();
    }
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

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
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
