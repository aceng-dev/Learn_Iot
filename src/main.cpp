  #include <Arduino.h>
  #include <vector>
  using namespace std;

  const int trigPin = 5;
  const int echoPin = 18;

  float tresHoldCM = 2.0;
  vector<float> distanceDataBase;
  float lastDistance = -1000.00;

  float readDistanceCM(){
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      
      long duration = pulseIn(echoPin, HIGH, 20000); 

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
    float delta = distance - lastDistance;
    float absDelta = fabs(delta);
    if (distance < 0) {
      Serial.println("Gagal membaca sensor / di luar jangkauan");
    } else {
      if(absDelta >= tresHoldCM){
        distanceDataBase.push_back(distance);
      
          Serial.print("Data Baru di tambahkan : ");
          Serial.println(distanceDataBase[distanceDataBase.size() - 1]);
        
        lastDistance = distance;
      }else {
        Serial.println("Masih dalam jarak toleransi ");
      }
    }
    delay(500);
  }
