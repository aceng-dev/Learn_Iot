#include <Arduino.h>

const int trigPin = 5;
const int echoPin = 18;

float readDistanceCM(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH, 30000); 

    if (duration == 0) {
        return -1; 
    }
    float distanceCM = (duration / 2.0) * 0.0343;
    return distanceCM;
}
void setup(){
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    Serial.println("Mulai Membaca Sensor");

}
void loop() {
  float distance = readDistanceCM();

  if (distance < 0) {
    Serial.println("Gagal membaca sensor / di luar jangkauan");
  } else {
    Serial.print("Jarak: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
