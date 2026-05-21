#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <unistd.h> 
#include <wiringSerial.h>

int main(){
  int fd;

  if((fd = serialOpen("/dev/ttyS0",9600)) < 0){
    fprintf(stderr, "Unable to open serial device: %s\n", strerror (errno));
    return 1;
  }
  if(wiringPiSetup() == -1){
    fprintf(stderr, "Unable to start WiringPi: %s\n", strerror (errno));
    return 1;
  }
  while(1){
  for(int i=0; i<100; i++){
    printf("%c", serialGetchar(fd));
  }
  sleep(1);
  }
  return(0);
}
