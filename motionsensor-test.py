import RPi.GPIO as GPIO
import time

M_pin = 18 #select the pin for motionsensor
B_pin = 26 #select the pin for buzzer

def init():
         GPIO.setwarnings(False)
         GPIO.setmode(GPIO.BCM)
         GPIO.setup(M_pin,GPIO.IN)
         GPIO.setup(B_pin,GPIO.OUT)
         pass

def buzzer():
         while GPIO.input(M_pin):
                  GPIO.output(B_pin,GPIO.LOW)
                  time.sleep(0.5)
                  GPIO.output(B_pin,GPIO.HIGH)
                  time.sleep(0.5)

def detct():
         for i in range(101):
                  if GPIO.input(M_pin):
                           print "Someone is closing!"
                           buzzer()
                  else:
                           GPIO.output(B_pin,GPIO.HIGH)
                           print "Nobody!"
                  time.sleep(2)

time.sleep(5)
init()
detct()

GPIO.cleanup()
