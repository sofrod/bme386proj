// Include the AccelStepper Library
#include <AccelStepper.h>

// Define step constants
#define FULLSTEP 4
#define HALFSTEP 8

// Creates two instances
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
AccelStepper hStepper(FULLSTEP, 8, 10, 9, 11);
AccelStepper vStepper(HALFSTEP, 4, 6, 5, 7);
int hcount;
int vcount;
bool isBackward;

const int trigPin1 = 3;
const int echoPin1 = 2;
const int trigPin2 = 12;
const int echoPin2 = 13;
const int pixelNumber = 30;
int hmax;
int vmax;
const int hstep = 150;
const int vstep = 1200;
long duration1;
// String distance1;
int distance1;
long duration2;
// String distance2;
int distance2;
int grayscale1;
int grayscale2;
String grayScale2;

void setup()
{
  // set the same for motor 2
  hStepper.setMaxSpeed(2000.0);
  hStepper.setAcceleration(2000.0);
  hStepper.setSpeed(1500);
  hStepper.moveTo(-hstep);

  vStepper.setMaxSpeed(2000.0);
  vStepper.setAcceleration(2000.0);
  vStepper.setSpeed(1500);
  vStepper.moveTo(-vstep);

  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT);  // Sets the echoPin as an Input
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin2, INPUT);  // Sets the echoPin as an Input
  Serial.begin(115200);
  hcount = 0;
  vcount = 0;
  isBackward = false;
  hmax = pixelNumber - 1;
  vmax = (pixelNumber / 2) - 1;
}

void call_sensor1()
{
  digitalWrite(trigPin1, LOW);
  delay(13);

  digitalWrite(trigPin1, HIGH);
  delay(2);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  // distance1 = "*" + String(duration1 * 0.034 / 2);
  distance1 = duration1 * 0.034 / 2;
  grayscale1 = map(distance1, 5, 18, 0, 255);
  if (distance1 > 18)
  {
    grayscale1 = 255;
  }
  else if (distance1 < 5)
  {
    grayscale1 = 0;
  }

  // Serial.print(distance1);
  Serial.print(grayscale1);
}

void call_sensor2()
{
  digitalWrite(trigPin2, LOW);
  delay(13);

  digitalWrite(trigPin2, HIGH);
  delay(2);
  digitalWrite(trigPin2, LOW);

  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;
  // distance2 = "*" + String(duration2 * 0.034 / 2);
  grayscale2 = map(distance2, 10, 18, 0, 255);
  if (distance2 > 18)
  {
    grayscale2 = 255;
  }
  else if (distance2 < 10)
  {
    grayscale2 = 0;
  }
  grayScale2 = "*" + String(grayscale2);

  // Serial.print(distance2);
  Serial.print(grayScale2);
}

void loop()
{
  if (vcount <= vmax)
  {
    while (hcount <= hmax)
    {
      if (hStepper.distanceToGo() == 0)
      {
        hStepper.stop();
        call_sensor1();
        call_sensor2();
        if (isBackward == true)
        {
          hStepper.moveTo(hStepper.currentPosition() + hstep);
        }
        else
        {
          hStepper.moveTo(hStepper.currentPosition() - hstep);
        }
        hcount++;
      }
      hStepper.run();
    }
    vStepper.run();
    // Serial.println(vStepper.currentPosition());
    if (vStepper.distanceToGo() == 0)
    {
      vStepper.stop();
      Serial.print("/");
      vStepper.moveTo(vStepper.currentPosition() - vstep);
      vcount++;
      hcount = 0;
      if (vcount % 2 != 0)
      {
        isBackward = true;
        hStepper.moveTo(hStepper.currentPosition() + hstep);
      }
      else
      {
        isBackward = false;
        hStepper.moveTo(hStepper.currentPosition() - hstep);
      }
    }
  }
}