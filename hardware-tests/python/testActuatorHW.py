import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.OUT)
GPIO.setup(24, GPIO.IN,pull_up_down=GPIO.PUD_UP)
GPIO.setwarnings(False)

flag = 0

while 1:
	GPIO.output(23, GPIO.HIGH)
        time.sleep(0.5)
        print GPIO.input(24)
	if GPIO.input(24) != 0  and flag == 0:
		print "ERROR: Lamp broken!"
		flag = 1
	if GPIO.input(24) == 0 and flag == 1:
		print "Lamp OK!"
		flag = 0
	time.sleep(0.5)
	GPIO.output(23, GPIO.LOW)
	time.sleep(1)
