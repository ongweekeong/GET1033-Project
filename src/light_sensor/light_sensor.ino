#include <Arduino.h>
#include <avr/io.h>

#define LDR_PIN A0
#define LED_PIN 13

void setup() {
  Serial.begin(9600);
  Serial.println("TESTING");
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}
void loop() {
  int brightness = analogRead(LDR_PIN);
  int threshold_val = 650;
  int LEDBrightness = 0;
  Serial.println(brightness);
  if (brightness < threshold_val) {
    LEDBrightness = map(brightness, 0, 1023, 0, 1000);
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(1000-LEDBrightness); // Approximately 10% duty cycle @ 1KHz
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(LEDBrightness);
  } else {
    analogWrite(LED_PIN, 0);
  }
  //delay(500);
}
