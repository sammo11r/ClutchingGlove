//Include the servo library
#include <Servo.h>

//Declare the variables

//Servo L = left, R = right, T = thumb
int servoLPin = 3;
int servoRPin = 5;
int servoTPin = 6;

Servo servoL; 
Servo servoR;
Servo servoT;

int reading_1;   
int reading_2;  
int reading; 
int thresholdPressure;
int activated;

//Setup 
void setup(void) {

 Serial.begin(9600); //Output for debugging   
 
 servoL.attach(servoLPin); //servo left at digital pin servoLPin
 servoL.write(0); //initial point for servo left

 servoR.attach(servoRPin); //servo right at digital pin servoRPin
 servoR.write(0); //initial point for servo right

 servoT.attach(servoTPin); //servo thumb at digital pin servoTPin
 servoT.write(0); //initial point for servo thumb
 
 activated = 0; //Set activated to 'false'
 
 thresholdPressure = 300; //Set the threshold for the applied pressure

}

//Loop
void loop(void) {
  
  //Get the temperature from the thermistor
  //temperature = getTemperature();
  
  //While the temperature exceeds the threshold,
 // while (temperature >= thresholdTemperature) {
    
    //Return to the zero condition
    //servoL.write(0);
    //servoR.write(0);
    //servoT.write(0);
    
  //}
  
  reading_1 = analogRead(A0); //attached to analog 0
  reading_2 = analogRead(A1); //attached to analog 1
    
  //take the average of reading_1 and reading_2
  reading = (reading_1 + reading_2)/ 2;

  //Print the value from the pressure sensor
  Serial.print("Sensor value = ");
  Serial.println(reading);
    
   while (activated) {
    activated = deActivation();
  }
  
  //Check if the threshold has been reached or the device is already activated
  if (reading >= thresholdPressure) { 

   activated = 1;  //Set the device to the state 'active'

   //Convert from pressure value to degrees for servo
   //int value = map(reading, 0, 1023, 0, 255);
   servoL.write(180);
   servoR.write(180);
   servoT.write(180);

   //Wait 10 miliseconds before applying pressure again
   delay(10);
  
  }

}

//Variable to keep track of time
unsigned long Time;
unsigned long TimeOld = 0;

const unsigned long elapsedOne = 1000; //1 second
const unsigned long elapsedTwo = 2000; //2 seconds

int checkOne;
int checkTwo;
int checkThree;
int thresholdPressureDeact = 1;

//Function to implement the deactivation by not pressing for an extended period of time
int deActivation (void) {
  Time = millis();
  delay(1000);
  
    reading_1 = analogRead(A0); //attached to analog 0
    
    reading = reading_1;
    
    //Perform the first check
    if (reading < thresholdPressureDeact) {
      checkOne = 1;
    }
  
  //Sleep
  delay(1000);

    reading_1 = analogRead(A0); //attached to analog 0
    
    reading = reading_1;

    //Perform the second check    
    if (reading < thresholdPressureDeact) {
      checkTwo = 1;
    }

  //Sleep
  delay(1000);

    reading_1 = analogRead(A0); //attached to analog 0
    
    reading = reading_1;
    
    //Perform the third check
    if (reading < thresholdPressureDeact) {
      checkThree = 1;
    }
  
  if (checkOne == 1 && checkTwo == 1 && checkThree == 1) { //If the user has not pressed for two seconds
    servoL.write(0);
    servoR.write(0);
    servoT.write(0);

    checkOne = 0;
    checkTwo = 0;
    checkThree = 0;
    
    TimeOld = Time;
    return 0; //Deactivate
  }
  
  TimeOld = Time;
  Serial.println(Time,TimeOld);
  
  checkOne = 0;
  checkTwo = 0;
  checkThree = 0;
  
  return 1; //Else, keep activated
  
}