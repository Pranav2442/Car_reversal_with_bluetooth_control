#include <SoftwareSerial.h>


SoftwareSerial BT(7, 8); // RX, TX


int M_R_1 = 9;    //right motor wire 1
int M_R_2 = 10;   //right motor wire 2
int M_L_1 = 11;   //left motor wire 1
int M_L_2 = 12;   //left motor wire 2
const int trigPin = 3;
const int echoPin = 2;
const int buzzerPin = 6;

bool brake = true;
long duration;
int distance;

void Forward() {
  Serial.println("Forward");
  BT.println("Forward");
  digitalWrite(M_L_1, 1);
  digitalWrite(M_L_2, 0);
  digitalWrite(M_R_1, 1);
  digitalWrite(M_R_2, 0);
}

void Backward() {
  Serial.println("Backward");
  BT.println("Backward");
  digitalWrite(M_L_1, 0);
  digitalWrite(M_L_2, 1);
  digitalWrite(M_R_1, 0);
  digitalWrite(M_R_2, 1);
}

void Left() {
  Serial.println("Left");
  BT.println("Left");
  digitalWrite(M_L_1, 0);
  digitalWrite(M_L_2, 0);
  digitalWrite(M_R_1, 1);
  digitalWrite(M_R_2, 0);
}

void Right() {
  Serial.println("Right");
  BT.println("Right");
  digitalWrite(M_L_1, 1);
  digitalWrite(M_L_2, 0);
  digitalWrite(M_R_1, 0);
  digitalWrite(M_R_2, 0);
}

void Stop() {
  Serial.println("Stop");
  BT.println("Stop");
  digitalWrite(M_L_1, 0);
  digitalWrite(M_L_2, 0);
  digitalWrite(M_R_1, 0);
  digitalWrite(M_R_2, 0);
}

void setup()
{
  pinMode(M_R_1, OUTPUT);
  pinMode(M_R_2, OUTPUT);
  pinMode(M_L_1, OUTPUT);
  pinMode(M_L_2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  Serial.begin(9600);
  BT.begin(9600);

}

void loop()
{

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance <= 3 && distance >= 1 && brake) {
    tone(buzzerPin, 1000);
    Stop();
    //        delay(4000);
    brake = false;

  } else if (distance > 3) {
    brake = true;
    noTone(buzzerPin);
  }


  if (BT.available() > 0)
  {
    char data = BT.read();
    Serial.println(data);
    BT.println(data);
    if (data == 'w')
    {
      // forward
      Forward();

    }
    else if (data == 'z' && brake)
    {
      // backward
      Backward();

    }
    else if (data == 'a')
    {
      // left
      Left();
    }
    else if (data == 'd')
    {
      // right
      Right();

    }
    else if (data == 's' )
    {
      // stop

      Stop();
    }
  }


}
