#include <wiringPi.h>
#include <stdio.h>
#define ACTUATOR_PIN	4
#define SENSOR_PIN	5

int main (void)
{
  wiringPiSetup ();
  pinMode (ACTUATOR_PIN, OUTPUT);
  pinMode (SENSOR_PIN, INPUT);
  for (;;)
  {
    digitalWrite (ACTUATOR_PIN, !digitalRead(ACTUATOR_PIN));
    delay (250);
    if(!digitalRead(SENSOR_PIN) && digitalRead(ACTUATOR_PIN)){
	printf("LAMP OK\n");
    }
    if(digitalRead(SENSOR_PIN) && digitalRead(ACTUATOR_PIN)){
	printf("LAMP BROKE\n");
    }
    delay (750);
  }
  return 0 ;
}
