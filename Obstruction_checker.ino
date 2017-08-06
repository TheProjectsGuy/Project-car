/*
 * Automatic Break system (Done)
 * Automatic Headlight (Done)
 * 
 */

/*
 * AIM : To make a program that will calculate the distance from wall, then change LED state when anything passes
 */
 
const int LEDBlue = 10,LEDRed = 12,LEDGreen = 11,LEDWhite = 9;
const int USTrig = 6 , USEcho = 7;
const int LDR = 0;
/*
 * Blue light is to show Calculation in process
 * Red light is to show no need to apply brake
 * Green ligh is to show , press brake
 */

double duration , distance, WallDistance = 0;
long int num = 0; //number of observations
void on();
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDBlue , OUTPUT);
  pinMode(LEDRed , OUTPUT);
  pinMode(LEDGreen , OUTPUT);
  pinMode(LEDWhite , OUTPUT);
  pinMode(USEcho , INPUT);
  pinMode(USTrig , OUTPUT);
  //Serial.begin(9600);
  on();

  //calculate the distance from wall
  /*
   * 1) Take readings
   * 2) Take average
   * 3) WallDistance is calculated
   */
  for (int i = 1 ; i <= 40 ; i++)
  { 
    digitalWrite(LEDBlue , HIGH);
    digitalWrite(USTrig , LOW);
    delayMicroseconds(2);
    digitalWrite(USTrig , HIGH);
    delayMicroseconds(10);
    digitalWrite(USTrig , LOW);

    duration = pulseIn (USEcho , HIGH);
    distance = duration / 58; //in cm
    WallDistance += distance; //We'll take AVG reading at the end
    num++;
    delay(50);
    digitalWrite(LEDBlue,LOW);
    delay(50);

    //Serial.println(distance);
    
  }
  WallDistance /= num;
  WallDistance -= 5;
  //Serial.print(WallDistance);
  //Serial.println(" Is the final distance");
}


void loop() {
  // put your main code here, to run repeatedly:

  //Ultrasonic Meter
  digitalWrite(USTrig , LOW);
  delayMicroseconds(2);
  digitalWrite(USTrig , HIGH);
  delayMicroseconds(10);
  digitalWrite(USTrig , LOW);

  duration = pulseIn(USEcho , HIGH);
  distance = duration / 58;

  if (distance < WallDistance)  //Obstacle found
  {
    digitalWrite(LEDRed , HIGH); //Apply brakes
    digitalWrite(LEDGreen , LOW);
  }
  else
  {
    digitalWrite(LEDGreen , HIGH);  
    digitalWrite(LEDRed , LOW);
  }
  if (analogRead(LDR) >= 900)
  {
    digitalWrite(LEDWhite , HIGH);
  }
  else
  {
    digitalWrite(LEDWhite , LOW);
  }
  delay(5);
}

void on()
{
  //show off setup
  for (int i = 1; i<= 2 ;i++)
  {
    digitalWrite(LEDBlue , HIGH);
    digitalWrite(LEDGreen , HIGH);
    digitalWrite(LEDRed , HIGH);
    digitalWrite(LEDWhite , HIGH);
    delay(125);
    digitalWrite(LEDBlue , LOW);
    digitalWrite(LEDGreen , LOW);
    digitalWrite(LEDRed , LOW);
    digitalWrite(LEDWhite , LOW);
    delay(125);
  }
  digitalWrite(LEDRed , HIGH);
  delay(500);
  digitalWrite(LEDBlue , HIGH);
  delay(500);
  digitalWrite(LEDGreen , HIGH);
  delay(500);
  digitalWrite(LEDWhite , HIGH);
  delay(500);
  digitalWrite(LEDBlue , LOW);
  digitalWrite(LEDGreen , LOW);
  digitalWrite(LEDRed , LOW);
  digitalWrite(LEDWhite , LOW);
  delay(500);
  //Enough show off
}

