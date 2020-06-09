#  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
# / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
#| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
# \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
#                  (____/ 
# Osoyoo Model-Pi L298N DC motor driver programming guide
# tutorial url: https://osoyoo.com/2020/03/01/python-programming-tutorial-model-pi-l298n-motor-driver-for-raspberry-pi/

import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM) # GPIO number  in BCM mode
GPIO.setwarnings(False)
#define L298N(Model-Pi motor drive board) GPIO pins
IN1 = 23  #Right motor direction pin
IN2 = 24  #Right motor direction pin
ENA = 18  #Right motor speed pin
IN3 = 27  #Left motor direction pin
IN4 = 22  #Left motor direction pin
ENB = 12  #Left motor speed pin

sensor1= 25 # No.1 sensor from right
sensor2= 9 # No.2 sensor from right
sensor3= 11 # middle sensor
sensor4= 8 # No.2 sensor from left
sensor5= 7 #No.1 sensor from left
sts1=0
sts2=0
sts3=0
sts4=0
sts5=0

# Define motor control  pins as output
GPIO.setup(IN1, GPIO.OUT)   
GPIO.setup(IN2, GPIO.OUT) 
GPIO.setup(ENA, GPIO.OUT) 
GPIO.setup(IN3, GPIO.OUT)   
GPIO.setup(IN4, GPIO.OUT) 
GPIO.setup(ENB, GPIO.OUT) 

GPIO.setup(sensor1, GPIO.IN)   
GPIO.setup(sensor2, GPIO.IN)
GPIO.setup(sensor3, GPIO.IN)   
GPIO.setup(sensor4, GPIO.IN)
GPIO.setup(sensor5, GPIO.IN)   


pwm_Left = GPIO.PWM(ENB, 1000) #set Left motor PWM frequency @1000 hz
pwm_Left.start(25)  #   initial Left motor PWM power @25% of maximum value
pwm_Right = GPIO.PWM(ENA, 1000) #set Right motor PWM frequency @1000 hz
pwm_Right.start(25)   #   initial Right motor PWM power @25% of maximum value

def changespeed(speed):
	pwm_Left.ChangeDutyCycle(speed)
	pwm_Right.ChangeDutyCycle(speed)

def stopcar():
	GPIO.output(IN1, GPIO.LOW)
	GPIO.output(IN2, GPIO.LOW)
	GPIO.output(IN3, GPIO.LOW)
	GPIO.output(IN4, GPIO.LOW)
	
stopcar()

def forward():
	GPIO.output(IN1, GPIO.HIGH)
	GPIO.output(IN2, GPIO.LOW)
	GPIO.output(IN3, GPIO.HIGH)
	GPIO.output(IN4, GPIO.LOW)
	pwm_Left.ChangeDutyCycle(40)
	pwm_Right.ChangeDutyCycle(40)
	#following two lines can be removed if you want car make continuous movement without pause
	#time.sleep(0.25)  
	#stopcar()
	
def backward():
	GPIO.output(IN2, GPIO.HIGH)
	GPIO.output(IN1, GPIO.LOW)
	GPIO.output(IN4, GPIO.HIGH)
	GPIO.output(IN3, GPIO.LOW)
	pwm_Left.ChangeDutyCycle(40)
	pwm_Right.ChangeDutyCycle(40)
	#following two lines can be removed if you want car make continuous movement without pause
	#time.sleep(0.25)  
	#stopcar()
	
def turnRight():
	GPIO.output(IN1, GPIO.LOW)
	GPIO.output(IN2, GPIO.HIGH)
	GPIO.output(IN3, GPIO.HIGH)
	GPIO.output(IN4, GPIO.LOW)
	pwm_Left.ChangeDutyCycle(75)
	pwm_Right.ChangeDutyCycle(0)
	#following two lines can be removed if you want car make continuous movement without pause
	#time.sleep(0.25)  
	#stopcar()
	
def turnLeft():
	GPIO.output(IN1, GPIO.HIGH)
	GPIO.output(IN2, GPIO.LOW)
	GPIO.output(IN3, GPIO.LOW)
	GPIO.output(IN4, GPIO.HIGH)
	pwm_Left.ChangeDutyCycle(0)
	pwm_Right.ChangeDutyCycle(75)	
	#following two lines can be removed if you want car make continuous movement without pause
	#time.sleep(0.25)  
	#stopcar()
	


	
forward()
time.sleep(1)  
stopcar()
time.sleep(0.25)

backward()
time.sleep(1)  
stopcar()
time.sleep(0.25) 

turnLeft()
time.sleep(1)  
stopcar()
time.sleep(0.25)
	
turnRight()
time.sleep(1)  
stopcar()
time.sleep(0.25)
