#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN 9           // Ultrasonic sensor Trig pin
#define ECHO_PIN 10          // Ultrasonic sensor Echo pin
#define MAX_DISTANCE 200     // Maximum distance in cm
#define RELAY_PUMP_PIN 3     // Relay pin for pump control
#define SOIL_SENSOR_PIN 6    // Soil moisture sensor pin
#define SERVO_PIN 5          // Servo motor control pin
#define BUZZER_PIN 7         // Buzzer control pin

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);
Servo servo;                 // Create servo object

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PUMP_PIN, OUTPUT);    
  pinMode(SOIL_SENSOR_PIN, INPUT);    
  pinMode(BUZZER_PIN, OUTPUT);        

  digitalWrite(RELAY_PUMP_PIN, LOW);  
  digitalWrite(BUZZER_PIN, LOW);      

  servo.attach(SERVO_PIN);            
  servo.write(90);                    
}

void loop() {
  // Measure soil moisture
  int water = digitalRead(SOIL_SENSOR_PIN);  // Read soil moisture sensor signal
  if (water == HIGH) {
    
    digitalWrite(RELAY_PUMP_PIN, LOW);
  } else {
   
    digitalWrite(RELAY_PUMP_PIN, HIGH);
  }

  // Measure distance
  int distance = sonar.ping_cm(); 

  // Output distance to serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // If an object is detected nearby ， move servo to 0 degrees and activate buzzer
  if (distance > 0 && distance <= 20) {
    servo.write(0);           
    tone(BUZZER_PIN, 1000);   
  } 
  // If the object is far away, move servo to 180 degrees and deactivate buzzer
  else if (distance > 20) {
    servo.write(180);         
    noTone(BUZZER_PIN);       
  }

  delay(100); // Delay 100 milliseconds
}


