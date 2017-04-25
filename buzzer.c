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
	pinMode (24, OUTPUT) ;//connect to buzzer
	while(1)
	{
		
			digitalWrite(24, LOW) ;
			delay (1000) ;  	 
			digitalWrite(24, LOW) ; 
			delay (1000) ; 	
	}
}