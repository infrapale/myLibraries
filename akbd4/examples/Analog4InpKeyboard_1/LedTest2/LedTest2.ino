/*
   LedTest
*/

#include <Arduiono.h>
#include <SimpleTimer.h> 
#include <led_blink.h>



const int LED =  13;   
led_blink leds;
SimpleTimer timer;

void setup(void) {
  leds.begin();
  Serial.begin(9600);

  pinMode(LED, OUTPUT);  
  timer.setInterval(100, loop100ms);
}


//void set_led

void loop100ms(void){
   leds.run();
}

void loop() {
  timer.run();
    
  
}

