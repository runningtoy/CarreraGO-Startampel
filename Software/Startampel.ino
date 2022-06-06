/*  ----- Carrera Startampel -----
  YouTube Video:  https://youtu.be/q5Slh3TaYYY
  von Moritz Feiler
*/


const int red[5] = {9, 11, 12, 10, 8};  //store pins of red leds in an array
const int green[5] = {2, 3, 4, 5, 6};   //store pins of green leds in an array (one pin corresponds to one column of two green leds each!)
const int buzzer = 13;                  //define pin of the buzzer (pin is not pwm capable, as the buzzer is of the active type)

void setup() {
  //define pins of red and green leds and turn them off (common anode LEDs are switched off by turning them HIGH!)
  for (int i = 0; i < 5; i++) {
    pinMode(red[i], OUTPUT);
    pinMode(green[i], OUTPUT);

    digitalWrite(red[i], HIGH);
    digitalWrite(green[i], HIGH);
  }
}

void loop() {
  int beep_duration = 200;

  //light all red leds and beep buzzer once to signal countdown start
  for (int i = 0; i < 5; i++) {
    digitalWrite(red[i], LOW);
  }
  digitalWrite(buzzer, HIGH);
  delay(beep_duration);
  digitalWrite(buzzer, LOW);

  delay(10000 - beep_duration);

  //after 10 turn all lights off and beep once 
  for (int i = 0; i < 5; i++) {
    digitalWrite(red[i], HIGH);
  }

  digitalWrite(buzzer, HIGH);
  delay(beep_duration);
  digitalWrite(buzzer, LOW);

  delay(5000 - beep_duration);

  //after 5 seconds begin countdown
  for (int i = 0; i < 5; i++) {
    digitalWrite(red[i], LOW);  //each second light one more red led

    digitalWrite(buzzer, HIGH); //beep as each led lights up (beep is twice the normal duration)
    delay(2 * beep_duration);
    digitalWrite(buzzer, LOW);
    delay(1000 - 2 * beep_duration);


  }

  delay(random(100, 800)); //delay for another, random amount 


  //at start turn off all red led and turn on green lights
  
  for (int i = 0; i < 5; i++) {
    digitalWrite(red[i], HIGH);   //red led off
  }
  //as the arduino cannot source enough current to light all leds at the same time, make sure that all red leds are off before switching on the green ones!
  for (int i = 0;i < 5; i++){
    digitalWrite(green[i], LOW);  //green led on
  }

  
  digitalWrite(buzzer, HIGH);     //beep buzzer for two seconds...
  delay(2000);
  digitalWrite(buzzer, LOW);
  delay(2000);

  for (int i = 0; i < 5; i++) {   //then turn off all leds
    digitalWrite(red[i], HIGH);
    digitalWrite(green[i], HIGH);
  }
  while (1); //do nothing
}
