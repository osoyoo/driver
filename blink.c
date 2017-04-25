/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/    
 * www.osoyoo.com water drop sensor
 * program tutorial :http://osoyoo.com/2016/07/14/motionsensor-pi/
 *  Copyright John Yu
 */
#include <wiringPi.h>  
int main(void)  
{  
	wiringPiSetup() ;  
	pinMode (25, OUTPUT) ;  
	pinMode (24, INPUT) ; 
	for(;;)
	{
		if(digitalRead(24)==HIGH)   
		{
			digitalWrite(25, HIGH) ; delay (10) ;  	 
		}
		else
		{
			digitalWrite(25, LOW) ; delay (10) ; 
		}
	}
}