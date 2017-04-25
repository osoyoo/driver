import RPi.GPIO as GPIO
import time
import os

buzzer = 14
sound = 26
# change these as desired - they're the pins connected from the
# SPI port on the ADC to the Cobbler
SPICLK = 11
SPIMISO = 9
SPIMOSI = 10
SPICS = 8

def init():
         GPIO.setwarnings(False)
         GPIO.setmode(GPIO.BCM)
         GPIO.setup(buzzer,GPIO.OUT)
         #GPIO.output(buzzer,GPIO.HIGH)
         GPIO.setup(sound,GPIO.IN,pull_up_down=GPIO.PUD_UP)
         # set up the SPI interface pins
         GPIO.setup(SPIMOSI, GPIO.OUT)
         GPIO.setup(SPIMISO, GPIO.IN)
         GPIO.setup(SPICLK, GPIO.OUT)
         GPIO.setup(SPICS, GPIO.OUT)
         pass

#buzzer alarm
def alarm():
         GPIO.output(buzzer,GPIO.LOW)
         time.sleep(1)
         GPIO.output(buzzer,GPIO.HIGH)
         time.sleep(1)


#read SPI data from MCP3008(or MCP3204) chip,8 possible adc's (0 thru 7)
def readadc(adcnum, clockpin, mosipin, misopin, cspin):
        if ((adcnum > 7) or (adcnum < 0)):
                return -1
        GPIO.output(cspin, True)	

        GPIO.output(clockpin, False)  # start clock low
        GPIO.output(cspin, False)     # bring CS low

        commandout = adcnum
        commandout |= 0x18  # start bit + single-ended bit
        commandout <<= 3    # we only need to send 5 bits here
        for i in range(5):
                if (commandout & 0x80):
                        GPIO.output(mosipin, True)
                else:
                        GPIO.output(mosipin, False)
                commandout <<= 1
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)

        adcout = 0
        # read in one empty bit, one null bit and 10 ADC bits
        for i in range(12):
                GPIO.output(clockpin, True)
                GPIO.output(clockpin, False)
                adcout <<= 1
                if (GPIO.input(misopin)):
                        adcout |= 0x1

        GPIO.output(cspin, True)
        
        adcout >>= 1       # first bit is 'null' so drop it
        return adcout

# photoresistor connected to adc #0
photo_ch = 0

def main():
         init()
         time.sleep(2)
         print"will detect sonud and light signal"
         while True:
                  photo_value = readadc(photo_ch, SPICLK, SPIMOSI, SPIMISO, SPICS)
                  if (GPIO.input(sound) == False)and (photo_value>=650):  #detected sound signal and light intensity is low
                           print "Alarm!"
                           alarm()
                           time.sleep(1)
                  elif (GPIO.input(sound) == False)and (photo_value<=650):  #detected sound signal,but light intensity is high
                           GPIO.output(buzzer,GPIO.HIGH)
                           print "sound signal is detected ,but light intensity is high!"
                           time.sleep(1)
                  elif (GPIO.input(sound) == True)and (photo_value<=650):
                           GPIO.output(buzzer,GPIO.HIGH)
                           print "sound signal not detected ,light intensity is high!"
                           time.sleep(1)
                  elif (GPIO.input(sound) == True)and (photo_value>=650):
                           GPIO.output(buzzer,GPIO.HIGH)
                           print "sound signal not detected ,light intensity is low!"
                           time.sleep(1)
                           
                  print "light intensity is: " + str("%.1f"%((1024-photo_value)/1024.*100))+"%"
                  
                           
        

if __name__ =='__main__':
         try:
                  main()
         except KeyboardInterrupt:
                  pass
GPIO.cleanup()
                           
