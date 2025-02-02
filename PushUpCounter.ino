#include <HCSR04.h>

int bit0 =3 ,bit1 =4,bit2 =5,bit3 =6,bit4 =7,bit5=8, pb =2;
int count =0;
bool blocked = false;
UltraSonicDistanceSensor distanceSensor(10, 9);
int distance = 0;
int leds[6] = {bit0, bit1, bit2, bit3, bit4, bit5};
void SetUpPins (){
  pinMode (bit0, OUTPUT);
  pinMode (bit1, OUTPUT);
  pinMode (bit2, OUTPUT);
  pinMode (bit3, OUTPUT);
  pinMode (bit4, OUTPUT);
  pinMode (bit5, OUTPUT);
  pinMode (pb, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pb), isr, RISING); 
}
void isr() {
   count = 0;
   Serial.println("pb pressed");
   turnOffLEDs();
}
void setup() {
  Serial.begin(9600);
  SetUpPins ();
}

void loop() {
  distance = distanceSensor.measureDistanceCm();
  Serial.println(distance);
  delay(100);
  if (!blocked && distance <= 10) {
     count++;
     updateLEDs();
     blocked = true; // Block further counting until distance is >= 30
     Serial.println(blocked);
     delay(50);
  }
  if (blocked && distance > 10) {
     blocked = false; // Unblock counting
  }
}
void updateLEDs() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], (count >> i) & 1); // Extract and set each bit
  }
}
void turnOffLEDs() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(leds[i], LOW);
  }
}
