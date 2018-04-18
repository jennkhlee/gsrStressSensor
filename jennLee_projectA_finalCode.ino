/* 
Jenn (Ka Hyun) Lee 
Professor Leong
ITGM APPLIED PRINCIPLES: PHYSICAL COMPUTING
PROJECT A: GALVANIC SKIN RESPONSE (GSR) SENSOR WEARABLE
LED VERSION (FINAL)

This is the final code for my Project A utilizing LEDs to notify the user's stress, instead of my
original idea with the LCD display.

*/


#include <FastLED.h>

#define LED_PIN 5
#define NUM_LEDS 3
#define BRIGHTNESS 64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB

// Array to hold the LEDs
CRGB leds[NUM_LEDS];

// GSR Sensor Input to A0;
int GSR = A0;

// Anything higher than this value is considered a high/stressful GSR
int threshold = 3000;
int highThreshold = 4000;


void setup() {

  Serial.begin(9600);

  // Setting up LED strip
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // Setting brightness to 64
  FastLED.setBrightness(BRIGHTNESS);
  
}


void loop() {

// "tempVals" is the variable for the raw GSR sensor values
  int tempVals = analogRead(GSR);

// The abs() function converts all negatives into positives for the sake of measurement
  int sensedVals = abs(tempVals);

// "tempGSR" is the variable to hold the "sensedVals" converted into the measurement for human resistance
  int tempGSR = ((1024 + 2*sensedVals)*10000)/(512-sensedVals);

// "gsrReading" variable holds the positive GSR resistance values
  int gsrReading = abs(tempGSR);

  
  //Serial.println(gsrVal);
  //Serial.println("-");
  //Serial.println(sensorVal);
  
  //FastLED.show();


// If GSR shows "somewhat stressed"
  if (gsrReading >= threshold){
    
     leds[1] = CRGB(255,255,0);
     leds[0] = CRGB(0,0,0);
     leds[2] = CRGB(0,0,0);

// If GSR shows "very stressed"
     if (gsrReading >= highThreshold){
      
        leds[0] = CRGB(0,0,0);
        leds[1] = CRGB(0,0,0);
        leds[2] = CRGB(255,0,0);
      
      }
  }


// If GSR is "normal level"
  else{

     leds[0] = CRGB(0,255,0);
     leds[2] = CRGB(0,0,0);
     leds[1] = CRGB(0,0,0);

  }
  
  FastLED.show();
  delay(750);
  
}


