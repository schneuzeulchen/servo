//www.elegoo.com
//2020 modified by gean1022 
#include <Servo.h>
Servo myservo;
#define trigger 11 // Arduino Pin an HC-SR04 Trig
#define echo 10    // Arduino Pin an HC-SR04 Echo
float a;
float z;


void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(10, INPUT);

}
void loop() {
  a = getEntfernung();

  if (a < 20) z = a;

  int pos = mapfloat(z, 5, 20, 0, 180);
  Serial.println(pos);
  
  myservo.write(pos);// move servos to center position -> 90°
  delay(20);

}



int mapfloat(float eingabe, float in_min, float in_max, float out_min, float out_max ) {
  if(eingabe<in_min) eingabe = in_min;
  if(eingabe>in_max) eingabe = in_max;
  return ((eingabe - in_min) / (in_max - in_min) * (out_max - out_min)) + out_min;
}



//Pinbelegung des Sensors am Arduino

// Entfernung in cm über gewöhnlichen Ultraschallsensor mit Echo und Trigger messen
float getEntfernung()
{
  float entfernung = 0;
  float zeit = 0;

  digitalWrite(trigger, LOW);
  delayMicroseconds(3);
  noInterrupts();
  digitalWrite(trigger, HIGH); //Trigger Impuls 10 us
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  zeit = pulseIn(echo, HIGH); // Echo-Zeit messen
  interrupts();
  zeit = (zeit / 2); // Zeit halbieren
  entfernung = zeit / 29.1; // Zeit in Zentimeter umrechnen
  return (entfernung);

}
