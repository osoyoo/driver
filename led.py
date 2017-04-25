#turns on and off a light emitting diode(LED) depending on motion sensor

import RPi.GPIO as GPIO  					 #importing the RPi.GPIO module
import time              					 #importing the time module
GPIO.cleanup()		 				       	#to clean up at the end of your script
led_pin = 37             					 #select the pin for the LED
motion_pin = 35          					 #select the pin for the motion sensor
def init():
	GPIO.setmode(GPIO.BOARD) 				 #to specify which pin numbering system
	GPIO.setwarnings(False)   
	GPIO.setup(led_pin,GPIO.OUT)                             #declare the led_pin as an output 
	GPIO.setup(motion_pin,GPIO.IN,pull_up_down=GPIO.PUD_UP)  #declare the motion_pin as an input
	print("-----------------------------------------------------------------------")  

def main():
	while True:
		value=GPIO.input(motion_pin)	
		if value!=0:		                         #to read the value of a GPIO pin
			GPIO.output(led_pin,GPIO.HIGH)                #turn on led
			time.sleep(2)				 #delay 2ms
			print "LED on"                           #print information
		else:
			GPIO.output(led_pin,GPIO.LOW)                #turn off led
			time.sleep(2)				#delay 2ms
			print "LED off"                         #print information

init()
main()
GPIO.cleanup()





