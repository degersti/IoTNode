#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (4, OUTPUT);
    digitalWrite (4, HIGH);
  return 0 ;
}
