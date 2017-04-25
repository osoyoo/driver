#!/usr/bin/env python
import RPi.GPIO as GPIO
import time

class Sw40(object):
    """docstring for Senal"""
    def __init__(self, pin , buzzer):
        self.buzzer = buzzer
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.buzzer,GPIO.OUT)
        self.pin = pin
        GPIO.setup(self.pin, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

        GPIO.add_event_detect(self.pin, GPIO.RISING, callback=self.callback, bouncetime=1)
        self.count = 0 

    def callback(self , pin):
        self.count += 1

    def BuzzerOn(self):
        GPIO.output(self.buzzer , 0)

    def BuzzerOff(self):
        GPIO.output(self.buzzer , 1)


def main():
    print"system initialition..."
    sensor = Sw40(21,20)
    print"ok!\n"
    try:
        while True:
            time.sleep(1)
            if sensor.count >=10:
                print"be careful!there are thieves!\n"
                sensor.BuzzerOn()
            else:
                print"it is safe!\n"
                sensor.BuzzerOff()
            sensor.count = 0        

    except KeyboardInterrupt:
        GPIO.cleanup()

if __name__ == '__main__':
    main()


    
