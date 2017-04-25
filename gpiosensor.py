#Project tutorial URL http://osoyoo.com/?p=804
#Copyright Osoyoo.com

import RPi.GPIO as GPIO
import time

sensor_pin = 38
led_pin = 40

GPIO.setmode(GPIO.BOARD)

GPIO.setup(led_pin,GPIO.OUT)

GPIO.setup(sensor_pin, GPIO.IN)

current_state = 0

try:
    while True:
        time.sleep(0.1)
        current_state = GPIO.input(sensor_pin)
        if current_state == 1:
            print("tilt sensor value is %s" % (current_state))
            GPIO.output(led_pin,True)
        else:
            print("tilt sensor value is %s" % (current_state))
            GPIO.output(led_pin,False)
  
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()