#include <HCSR04.h>

int A_1 = 3, B_1 = 4, C_1 = 5, D_1 = 6, E_1 = 7, F_1 = 8, G_1 = 9; // Left display (Tens)
int A_2 = A0, B_2 = A1, C_2 = A2, D_2 = A3, E_2 = A4, F_2 = A5, G_2 = 10; // Right display (Ones)

int leftPins[7]  = {A_1, B_1, C_1, D_1, E_1, F_1, G_1}; // Left display (Tens)
int rightPins[7] = {A_2, B_2, C_2, D_2, E_2, F_2, G_2}; // Right display (Ones)

int pb = 2; //pb pin 2
int count =0;
bool blocked = false;
UltraSonicDistanceSensor distanceSensor(12, 13); //echo / trig
int distance = 0;

void isr() {
   count = 0;
   Serial.println("pb pressed");
}
void setup() {
  Serial.begin(9600);
  SetUpPins ();
}

void loop() {
   distance = distanceSensor.measureDistanceCm();
   Serial.print("Distance: ");
   Serial.println(distance);
 //  Serial.print("Distancesensor: ");
 //  Serial.println(distanceSensor.measureDistanceCm());
   delay(100);
   if (!blocked && distance <= 10) {
      count++;
      blocked = true; // Block further counting until distance is > 10
      Serial.println(blocked);
      delay(50);
      Serial.println("+1 count");
   }
  if (blocked && distance > 10) {
     blocked = false; // Unblock counting
  }
     
   displayNumber(count / 10, true);  // Display tens digit
   displayNumber(count % 10, false); // Display ones digit
}
const int numbers[10][7] = {
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW},  // 0
    {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW},      // 1
    {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH},   // 2
    {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH},   // 3
    {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH},    // 4
    {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH},   // 5
    {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH},  // 6
    {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW},     // 7
    {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH}, // 8
    {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH}   // 9
};
void displayNumber(int num, bool isLeft) {
    if (num < 0 || num > 9) return; // Prevent invalid numbers

    // Select segment pin array based on whether it's the left or right display
    int *pins = isLeft ? leftPins : rightPins;

    // Set segments based on the number pattern
    for (int i = 0; i < 7; i++) {
        digitalWrite(pins[i], numbers[num][i]);
    }
}
void SetUpPins (){
  pinMode (pb, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pb), isr, RISING);  

    pinMode(A_1, OUTPUT);
    pinMode(B_1, OUTPUT);
    pinMode(C_1, OUTPUT);
    pinMode(D_1, OUTPUT);
    pinMode(E_1, OUTPUT);
    pinMode(F_1, OUTPUT);
    pinMode(G_1, OUTPUT);

    pinMode(A_2, OUTPUT);
    pinMode(B_2, OUTPUT);
    pinMode(C_2, OUTPUT);
    pinMode(D_2, OUTPUT);
    pinMode(E_2, OUTPUT);
    pinMode(F_2, OUTPUT);
    pinMode(G_2, OUTPUT);
}
