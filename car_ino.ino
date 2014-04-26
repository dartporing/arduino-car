
 
 #include <Servo.h> 
const int trigPin = 2;
const int echoPin = 4;
 int rele1 = 12;
int rele2 = 7 ;
 Servo myservo;
 
void setup() {
// initialize serial communication:
Serial.begin(9600);
myservo.attach(9); 
 pinMode(rele1, OUTPUT); 
pinMode(rele2, OUTPUT); 
}
 
void loop()
{
// establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, cm;
 
// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trigPin, OUTPUT);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
 
// Read the signal from the sensor: a HIGH pulse whose
// duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
 
// convert the time into a distance
//inches = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);
//Serial.print(inches);
//Serial.print("in, ");
Serial.print(cm);
Serial.print("cm");
Serial.println();
delay(100);
if ( cm > 80 ) {
 digitalWrite(rele1, HIGH);
  delay(300);
digitalWrite(rele2, HIGH);
myservo.write(60);
}
else if ( cm < 30 ) {
   myservo.write(30); 
   digitalWrite(rele1, LOW);
delay(300);
digitalWrite(rele2, LOW);

   delay(15);

}

else {
   myservo.write(90); 
   delay(15);
  
}
}
 
long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING))), there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}
