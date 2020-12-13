// T097 Astrid Master 
// 2012-11-11 
// Row1-4: 179 - 409 - 605 - 830
// Col1-4:  0-1-2-3

#include <Arduino.h>
#include <Wire.h> 
#include <SimpleTimer.h> 
#include <akbd4.h>

akbd4 kbd(0,1,2,3);
char key;
int aval;


void setup()
{
  Serial.begin(9600);  // start serial for output
  kbd.begin();
}

void loop()
{
  while(1){
    kbd.scan();
    delay(10);
    key = kbd.read();
    if (key) {
      Serial.println(key,DEC);
    }
  } 
}
