/*
welcome use KeDeiTFT
*/
#include	"KeDei_TP.h"


/*****************************************
 *The function name ： get_xy
 *Function  ： 获取触摸的坐标
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ：2015/4/21
 ****************************************/
void TP::get_xy(void)
{
	tp_x	= 0;
	tp_y	= 0;
	y_val	= 1;
	x_val	= 1;

#ifdef  __AVR_ATmega328P__
	DDRC|=2;
	PORTC|=2;
	DDRD|=0X20;
	PORTB&=0XDF;
	DDRD&=0XBF;
	DDRC&=0XFB;

#else
#endif
	tp_max=analogRead(YP);
	tp_min=tp_max;
	for(tp_i = 0;tp_i < 12;tp_i++)
	{
		temp_x=analogRead(YP);
		if(temp_x > tp_max) tp_max=temp_x;
		if(temp_x < tp_min) tp_min=temp_x;
		tp_x+=temp_x;
		
	}
	if((tp_max-tp_min)>=50) 
		x_val = 0;

	tp_x=(tp_x-tp_max-tp_min)/10;
  if(MODULE == _MODULE_1_)
{
#ifdef  ROTATE_0
	x=(tp_x-104)*24/73;
#endif
}
else
{
	x=(tp_x-109)*32/74;
}

	

#ifdef  __AVR_ATmega328P__	
	DDRC|=4;
	PORTC|=4;
	DDRD|=0X40;
	PORTD&=0XBF;
	DDRD&=0XDF;
	DDRC&=0XFD;

#else
#endif
	
	tp_max=analogRead(XP);
	tp_min=tp_max;
	for(tp_i = 0;tp_i < 12;tp_i++)
	{
		temp_y=analogRead(XP);
		if(temp_y > tp_max) tp_max=temp_y;
		if(temp_y < tp_min) tp_min=temp_y;
		tp_y+=temp_y;
		
	}
	if((tp_max-tp_min)>=50) 
		y_val = 0;
	

	tp_y=(tp_y-tp_max-tp_min)/10;
  if(MODULE == _MODULE_1_)
{
#ifdef  ROTATE_0
	y=(tp_y-70)*32/75;
	
#endif
}
else
{
	y=(tp_y-73)*48/78;
}
/*
		Serial.print(tp_x);
		Serial.print("  ");
		Serial.print(tp_y);
		Serial.print("  ");
		Serial.print(x_val);
		Serial.print("  ");
		Serial.print(y_val);
		Serial.print("  ");
		Serial.print(flag);
		Serial.print("  ");
			Serial.print("\n");

*/
}


/*****************************************
 *The function name ： pen_down
 *Function  ： 检测当前触摸的状态
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ：2015/4/21
 ****************************************/
void TP::pen_down()
{
	pinMode(XP,INPUT_PULLUP);
	pinMode(XM,INPUT);
//	DDRB&=0XFE;
	pinMode(YP,INPUT);
//	DDRC&=0XFD;

	pinMode(YM,OUTPUT);
//	DDRB|=2;
	digitalWrite(YM,LOW);
	digitalWrite(YP,LOW);
//	PORTB&=0XFD;
//	delay(1);

	if(200 > analogRead(XP))
	{
		flag = 1;
		get_xy();
	}
	else flag = 0;
//	DDRB|=3;
//	DDRC|=6;
	pinMode(XP,OUTPUT);
	pinMode(XM,OUTPUT);
	pinMode(YP,OUTPUT);
}
