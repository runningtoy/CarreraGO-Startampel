#include <Arduino.h>

#include <Adafruit_NeoPixel.h>
#define BUZZER_PIN 0  //define pin of the buzzer
#define LEDDATA_PIN 1
#define STRIPSIZE 10 // Limited by max 256 bytes ram. At 3 bytes/LED you get max ~85 pixels

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIPSIZE, LEDDATA_PIN, NEO_GRB + NEO_KHZ800);
//Adafruit_NeoPixel pixels = Adafruit_NeoPixel(STRIPSIZE, LEDDATA_PIN, NEO_RGB + NEO_KHZ800);

//uint32_t color_yellow = pixels.Color(255,255,0);
//uint32_t color_red = strip.Color(255,0,0);
//uint32_t color_RED = strip.Color(0,255,0);
//uint32_t color_off =strip.Color(0,0,0);

#define BLACK 0x000000
uint32_t GREEN=pixels.Color(255,0,0);
uint32_t RED=pixels.Color(0,255,0);
uint32_t YELLOW=pixels.Color(255,255,0);
#define WHITE 0xFFFFff

void(* resetDigispark) (void) = 0;		//https://digistump.com/board/index.php?topic=1520.0
void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);
void raceContoll();
void whiteStar(uint8_t wait);

void setup() {
	/**
	 *-------------
	 * https://digistump.com/board/index.php/topic,1060.msg12633.html#msg12633
	 * https://hartmut-waller.info/arduinoblog/attachinterrupt/
	 * https://external-preview.redd.it/TYZn3qn-ahh3mKAZOWJB6FTfsCWslBe1Hl8e9vax4wQ.png?auto=webp&s=04e0bd8f585e1eec9d3b0469d84e9a453e37e55b
	 * Interrupt auf Pin2/Int0 setzen
	 *-------------
	 pinMode(2, INPUT);
	 attachInterrupt(0, resetDigispark, FALLING); 
	 **/



	//-------------
	// init LEDs 
	//-------------
	pixels.begin();
	pixels.setBrightness(80); // set accordingly
	pixels.show(); // Initialize all pixels to 'off'





	//-------------
	// start traffic light
	//-------------
	raceContoll();
	pixels.setBrightness(40); // set accordingly
}

void loop() {
	//-------------
	// idle mode
	//-------------
	whiteStar(200);
}

void whiteStar(uint8_t wait)
{
	for (int whiteLed = 0; whiteLed < pixels.numPixels(); whiteLed = whiteLed + 1)
	{
		// Turn our current led on to white, then show the leds
		pixels.setPixelColor(whiteLed, WHITE);
		pixels.show();
		// Wait a little bit
		delay(wait);
		// Turn our current led back to black for the next loop around
		pixels.setPixelColor(whiteLed, BLACK);
		pixels.show();
	}
}

void rainbow(uint8_t wait) {
	uint16_t i, j;
	for(j=0; j<256; j++) {
		for(i=0; i<pixels.numPixels(); i++) {
//			pixels.setPixelColor(i, Wheel((i+j) & 255));
			pixels.setPixelColor(i, Wheel(j));
		}
		pixels.show();
		delay(wait);
	}
}
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if(WheelPos < 85) {
		return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	}else if(WheelPos < 170) {
		WheelPos -= 85;
		return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}



#define BEEP_DURATION 80
#define BUZZER_FREQ 100
#define TIME_FCT 10
void raceContoll(){
	//-------------
	// prepare
	//-------------
	// tone(BUZZER_PIN, BUZZER_FREQ, BEEP_DURATION);	//signal start with buzzer beep
	pixels.fill(YELLOW);		//all led yellow for 10s
	pixels.show();
	delay(500*TIME_FCT);
	pixels.clear();	//all led out for 5s
	pixels.show();
	delay(500*TIME_FCT);
	//-------------
	// countdown 
	//-------------
	for(int i=0; i<pixels.numPixels()/2; i++) {
		delay(100*TIME_FCT);
		pixels.setPixelColor(i, RED);
		pixels.setPixelColor(pixels.numPixels()-1-i, RED);
		pixels.show();
		tone(BUZZER_PIN, BUZZER_FREQ, 2 * BEEP_DURATION);	//beep as each row up (beep is twice the normal duration)
	}
	//-------------
	// change to RED
	//-------------
	delay(random(500, 1200));	//delay for another, random amount
	//at start turn off all red led and turn on RED lights
	pixels.fill(GREEN);
	pixels.show();
	tone(BUZZER_PIN, BUZZER_FREQ, 1000);	//beep buzzer for two seconds...
	delay(2000);

	//-------------
	// turn of lights and wait for some time
	//-------------
	pixels.clear();
	pixels.show();
	delay(1000*TIME_FCT);	//wait before starting idle animation
}