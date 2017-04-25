#include<wiringPi.h>
int main(void)
{
	wiringPiSetup();
	pinMode(25,OUTPUT);
	pinMode(24,INPUT);
	for(;;)
	{
		if(digitalRead(24)==LOW)
		{
			digitalWrite(25,HIGH);
			delay(50);
			
				
		}	
		else
		digitalWrite(25,LOW);
		delay(50);
	}	
}