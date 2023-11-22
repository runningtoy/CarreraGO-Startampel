/*
========================================================================================
  CARRERA STARTAMPEL
----------------------------------------------------------------------------------------
  This variant of the Software is for use with individually adressable LEDs compatible
  to the WS2812B-type ("Neopixels").

  Author:         Moritz Feiler
  Created:        5.November 2023
  YouTube Video:  https://youtu.be/q5Slh3TaYYY
========================================================================================
*/

#include <Adafruit_NeoPixel.h>
#include "colors.h"

#define LED_PIN 32    //Datapin of Neopixels
#define LED_COUNT 10  //Number of LED (max power draw with 10 LED: 10 * 20mA = 200mA)
#define BUZZER_PIN 0  //define pin of the buzzer

#define BRIGHTNESS 80


//declare neopixel object and turn all leds off
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_BGR + NEO_KHZ800);
int ledArray[2][5] = { { 0, 1, 2, 3, 4 }, { 9, 8, 7, 6, 5 } };  //array stores physical layout of LEDs

void setup() {
  pixels.begin();                    // INITIALIZE NeoPixel pixels object (REQUIRED)
  pixels.show();                     // Turn OFF all pixels ASAP
  pixels.setBrightness(BRIGHTNESS);  // Set BRIGHTNESS

  beginCountdown();
}

void loop() {
  //nothing to do here, restart countdown by resetting microcontroller
}


/*
========================================================================================
Countdown
========================================================================================
*/
#define BEEP_DURATION 200
#define BUZZER_FREQ 500

void beginCountdown() {

  tone(BUZZER_PIN, BUZZER_FREQ, BEEP_DURATION);  //signal start with buzzer beep
  pixels.fill(YELLOW);                           //all led yellow for 10s
  pixels.show();
  delay(10000);
  tone(BUZZER_PIN, BUZZER_FREQ, BEEP_DURATION);
  pixels.clear();  //all led out for 5s
  pixels.show();
  delay(5000);


  //begin countdown
  for (int i = 4; i >= 0; i--) {
    //fill one row red every second
    pixels.setPixelColor(ledArray[0][i], RED);
    pixels.setPixelColor(ledArray[1][i], RED);
    pixels.show();

    tone(BUZZER_PIN, BUZZER_FREQ, 2 * BEEP_DURATION);  //beep as each row up (beep is twice the normal duration)
    delay(1000);
  }
  delay(random(100, 800));  //delay for another, random amount

  //at start turn off all red led and turn on green lights
  pixels.fill(GREEN);
  pixels.show();
  tone(BUZZER_PIN, BUZZER_FREQ, 2000);  //beep buzzer for two seconds...
  delay(2000);

  //turn off all LEDs
  pixels.clear();
  pixels.show();
  delay(10
  000);  //wait before starting idle animation
}
