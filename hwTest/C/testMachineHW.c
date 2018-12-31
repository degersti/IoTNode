#include <wiringPi.h>
#define LED_RED		26
#define LED_GREEN	23
#define LED_BLUE	24
int main (void)
{
  wiringPiSetup () ;
  pinMode (LED_RED, OUTPUT);
  pinMode (LED_GREEN, OUTPUT);
  pinMode (LED_BLUE, OUTPUT);

  for (;;)
  {
    digitalWrite (LED_RED, HIGH);
    delay (500);
    digitalWrite (LED_RED,  LOW);
    digitalWrite (LED_GREEN, HIGH);
    delay (500);
    digitalWrite (LED_GREEN,  LOW);
    digitalWrite (LED_BLUE, HIGH);
    delay (500);
    digitalWrite (LED_BLUE,  LOW);
  }
  return 0 ;
}
