import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(12, GPIO.OUT)
GPIO.setup(13, GPIO.OUT)
GPIO.setup(19, GPIO.OUT)
GPIO.setwarnings(False)
 
red = GPIO.PWM(12, 50)  # frequency=50Hz
red.start(0)
green = GPIO.PWM(13, 50)  # frequency=50Hz
green.start(0)
blue = GPIO.PWM(19, 50)  # frequency=50Hz
blue.start(0)
try:
    while 1:
        # Fade red LED
        for dc in range(0, 101, 5):
            red.ChangeDutyCycle(dc)
            time.sleep(0.1)
        for dc in range(100, -1, -5):
            red.ChangeDutyCycle(dc)
            time.sleep(0.1)
        # Fade green LED
        for dc in range(0, 101, 5):
            green.ChangeDutyCycle(dc)
            time.sleep(0.1)
        for dc in range(100, -1, -5):
            green.ChangeDutyCycle(dc)
            time.sleep(0.1)
        # Fade blue LED
        for dc in range(0, 101, 5):
            blue.ChangeDutyCycle(dc)
            time.sleep(0.1)
        for dc in range(100, -1, -5):
            blue.ChangeDutyCycle(dc)
            time.sleep(0.1)
except KeyboardInterrupt:
    pass
    p.stop()
    GPIO.cleanup()
