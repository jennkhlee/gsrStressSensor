/* 
Jenn (Ka Hyun) Lee 
Professor Leong
ITGM APPLIED PRINCIPLES: PHYSICAL COMPUTING
PROJECT A: GALVANIC SKIN RESPONSE (GSR) SENSOR WEARABLE
LCD VERSION

This code was my original concept with the Crystal LCD display to notify the user's stress.
As outlined in my documentation, I ended up not using this code in my final, but the original
structure of my final program is very similar to this one.

*/

#include <LiquidCrystal.h>

// REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
LiquidCrystal lcd(0,1,8,9,10,11);

// GSR Sensor Input to A0
int GSR = A0;

// Anything higher than this value is considered a high/stressful GSR
int threshold = 3000;
int highThreshold = 4000;


void setup(){

  Serial.begin(9600);

  lcd.begin(16,2);

}



void loop(){

// Adjusting the backlight value manually instead of with the potentiometer
  analogWrite(10, 128);


// Stress label for GSR readings
  lcd.setCursor(1,0);
  lcd.print("stress levels: ");


// "tempVals" is the variable for the raw GSR sensor values
  int tempVals = analogRead(GSR);

// The abs() function converts all negatives into positives for the sake of measurement
  int sensedVals = abs(tempVals);

// "tempGSR" is the variable to hold the "sensedVals" converted into the measurement for human resistance
  int tempGSR = ((1024 + 2*sensedVals)*10000)/(512-sensedVals);

// "gsrReading" variable holds the positive GSR resistance values
  int gsrReading = abs(tempGSR);


// If GSR shows "somewhat stressed"
  if (gsrReading >= threshold){
    
     //Serial.println("TEST MID THRESHOLD");
     
     lcd.clear();

     lcd.setCursor(0,1);
     lcd.print("Take it easy. ");


// If GSR shows "very stressed"
     if (gsrReading >= highThreshold){
      
       //Serial.println("TEST HIGH THRESHOLD");
       
       lcd.clear();
       
       lcd.setCursor(0,1);
       lcd.print("Okay, deep breaths. ");
       
      }
  }


// If GSR is "normal level"
  else{
      
     //Serial.println("TEST LOW THRESHOLD");

     lcd.setCursor(0,1);
     
     lcd.print("Doing great! ");
     
  }


// Delay of 0.75 seconds
  delay(750);

}

