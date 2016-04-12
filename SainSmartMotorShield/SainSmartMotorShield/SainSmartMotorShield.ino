/***********************************************************************
* COPYRIGHT (c) 2015 MongoToys Company, Moscow, Idaho
*
*        FILE NAME:	SainSmartMotorShield.ino
*
* FILE DESCRIPTION:	This file contains the functionality to ensure
*					all features of the Adafruit or Sainsmart V1.x shield
*					are functioning.
*					Pins may be used: 4,7,8,12(M1-M4 latch) 
*								      5,6,3,11(M1-M4 pwm)
*									  9,10(servo)
*    FUNCTION LIST: MTCSetmotor 
*
*     GLOBALS READ:	
*
* GLOBALS MODIFIED:
*
***********************************************************************/
#include <AFMotor.h>
#include <Servo.h>
	kk
  
    
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
Servo servo1;
Servo servo2;

const int THROTTLE_OFF = 0;
const int THROTTLE_TEST_SPEED = 127;	//half throttle

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("MTC SainSmartMotorShield.ino");
  
  // turn on servo
  servo1.attach(9);
  servo2.attach(10);

  // turn on motor #2
  motor1.setSpeed(THROTTLE_TEST_SPEED);
  motor2.setSpeed(THROTTLE_TEST_SPEED);
  motor3.setSpeed(THROTTLE_TEST_SPEED);
  motor4.setSpeed(THROTTLE_TEST_SPEED);	
  
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);	
}


void loop() 
{
  /*
  MTCSetmotor(1, 255);
  delay(5000);
  MTCSetmotor(1, 0);
  delay(5000);
  MTCSetmotor(1, -255);
  delay(5000);

  MTCSetmotor(2, -255);
  MTCSetmotor(3, -255);
  MTCSetmotor(4, -255);
  delay(5000); 
  */ 
  Motors on full throttle in arduino, turn em off
  int i;
  Serial.println("M1 0 to 255");
  for (int x = 0; x <= 255; x++)
  {
	Serial.println(x);
	MTCSetmotor(1, x);
	delay(25);
  }

  Serial.println("M1 0 to -255");
  for (int x = 0; x >= -255; x--)
  { 
    Serial.println(x);
    MTCSetmotor(1, x);
	delay(25);
  }

/* 
  MTCSetmotor(1, 0);
  delay(3000);
  MTCSetmotor(1, -128);
  delay(2000);
  MTCSetmotor(1, 128);
  delay(2000);
  MTCSetmotor(1, 0);
  delay(5000);  
 
  Serial.println("M1-M4 Clockwise then CounterClockwise...");
  motor1.setSpeed(127);  
  motor1.run(FORWARD);
  delay(2000);
  motor1.setSpeed(255);  
  motor1.run(FORWARD);
  delay(2000);
  motor1.run(BACKWARD);
  delay(2000);
  motor1.run(RELEASE);
/*

  
  motor2.run(FORWARD);
  delay(2000); 
  motor2.run(BACKWARD);
  delay(2000);
  motor2.run(RELEASE);

  motor3.run(FORWARD);
  delay(2000); 
  motor3.run(BACKWARD);
  delay(2000);
  motor3.run(RELEASE);
  
  motor4.run(FORWARD);
  delay(2000); 
  motor4.run(BACKWARD);
  delay(2000);
  motor4.run(RELEASE);

  Serial.println("Servo1-2 0-90-180");
  servo1.write(0);
  servo2.write(0);
  delay(2000);  
  servo1.write(90);
  servo2.write(90);  
  delay(2000);  
  servo1.write(180);
  servo2.write(180);  
  Serial.println("Test Cycle Complete");  
*/
}

/******************************************************************************
*FUNCTION NAME:	  MTCSetmotor
*
*  DESCRIPTION:   This function initializes the Agilent 34401 DMM.  The GPIB
*				  address is read in from the station data_fil
*
*       INPUTS:   int MotorNumber = 1 to 4 referring to physical Mx shield designation
*				  unsigned int Speed = -255 to +255 determining throttle and direction
*
*      OUTPUTS:   
*
*  RETURN VALUE:  Success = 0;
*
*         NOTES:  A local static array is used to store last values to compare
*				  to in order to negate redundant calls wasting processing time.
*
* -DATE-----NAME-----REVISION HISTORY
* 12/8/15	KLK		 Rev A	
******************************************************************************/
int MTCSetmotor(int MotorNumber, int Speed)
{
	int _speed;
	int _direction;

	//Range needs 0-255, then Set speed
	if (Speed < 0) _speed = Speed*-1;
  else _speed = Speed;
	if (_speed > 255) _speed = 255;
	switch(MotorNumber)
	{
		case 1: motor1.setSpeed(_speed); break;
		case 2: motor2.setSpeed(_speed); break;
		case 3: motor3.setSpeed(_speed); break;
		case 4: motor4.setSpeed(_speed); break;
	}
	
	//Set direction
	if (Speed >= 0)
	{
		Serial.println("Forward");
		_direction = FORWARD;
	}
	else
	{	
		Serial.println("Backward");
		_direction = BACKWARD;
	}
	switch(MotorNumber)
	{
		Serial.println(_direction);
		case 1: motor1.run(_direction); break;
		case 2: motor2.run(_direction); break;
		case 3: motor3.run(_direction); break;
		case 4: motor4.run(_direction); break;
	}	
	return 0;
}
