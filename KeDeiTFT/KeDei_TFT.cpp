/*
welcome use KeDeiTFT
*/
#include	"KeDei_TFT.h"
#include	"KeDei_config.h"

unsigned short x_all,y_all;
unsigned char   MODULE=_MODULE_1_;

void TFTLCD::begin(void)
{
	tft_init();
}

/*****************************************
 *The function name ： cmd
 *Function  ： 向lcd控制器发送控制指令
 *Input  ： LCD指令
 *Output   ： none
 *Author   ：KeDei
 *Time   ：2015/4/21
 ****************************************/
void  TFTLCD::cmd(unsigned char cmd)
{

#ifdef   __AVR_ATmega328P__

	PORTC=(PORTC&0Xf8)|0x08;
	PORTB=(0xfc&PORTB)|(0x03&cmd);
	PORTD=(0x03&PORTD)|(0xfc&cmd);
	PORTC=PORTC|0X04;
	PORTC=PORTC|0X01;	

#else

	digitalWrite(CS,LOW);	
	digitalWrite(RS,LOW);	
	digitalWrite(RD,HIGH);	

	digitalWrite(D0,cmd&0x01);
	digitalWrite(D1,cmd&0x02);
	digitalWrite(D2,cmd&0x04);
	digitalWrite(D3,cmd&0x08);
	digitalWrite(D4,cmd&0x10);
	digitalWrite(D5,cmd&0x20);
	digitalWrite(D6,cmd&0x40);
	digitalWrite(D7,cmd&0x80);

	digitalWrite(WR,LOW);
	digitalWrite(WR,HIGH);	
	digitalWrite(CS,HIGH);
#endif


}

/*****************************************
 *The function name ： w_data
 *Function  ： 向lcd控制器发送数据
 *Input  ： data
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void  TFTLCD::w_data(unsigned char data)
{
#ifdef  __AVR_ATmega328P__
	
	PORTC=(PORTC&0Xfa)|0x0a;
	PORTB=(0xfc&PORTB)|(0x03&data);
	PORTD=(0x03&PORTD)|(0xfc&data);
	PORTC=PORTC|0X04;
	PORTC=PORTC|0X01;	

#else

	digitalWrite(CS,LOW);	
	digitalWrite(RS,HIGH);	
	digitalWrite(RD,HIGH);	

	digitalWrite(D0,data&0x01);
	digitalWrite(D1,data&0x02);
	digitalWrite(D2,data&0x04);
	digitalWrite(D3,data&0x08);
	digitalWrite(D4,data&0x10);
	digitalWrite(D5,data&0x20);
	digitalWrite(D6,data&0x40);
	digitalWrite(D7,data&0x80);

	digitalWrite(WR,LOW);
	digitalWrite(WR,HIGH);	
	digitalWrite(CS,HIGH);
#endif
}


int TFTLCD::r_data(void)
{


#ifdef  __AVR_ATmega328P__22
	
	PORTC=(PORTC&0Xfa)|0x0a;
	PORTB=(0xfc&PORTB)|(0x03&data);
	PORTD=(0x03&PORTD)|(0xfc&data);
	PORTC=PORTC|0X04;
	PORTC=PORTC|0X01;	

#else

	unsigned int data=0;
	pinMode(D0, INPUT);
	pinMode(D1, INPUT);
	pinMode(D2, INPUT);
	pinMode(D3, INPUT);
	pinMode(D4, INPUT);
	pinMode(D5, INPUT);
	pinMode(D6, INPUT);
	pinMode(D7, INPUT);
	
	
	digitalWrite(CS,LOW);
	digitalWrite(RS,HIGH);
	digitalWrite(WR,HIGH);
	digitalWrite(RD,LOW);
	delay(5);
	data=(PINB&0X03)|(PIND&0XFC);
	delay(5);
	digitalWrite(RD,HIGH);
	digitalWrite(CS,HIGH);


	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
#endif
	return(data);

}


/*****************************************
 *The function name ： lcd_clear
 *Function  ： lcd全屏刷新为color颜色
 *Input  ： color
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void TFTLCD::clear(unsigned short color)
{
	int i=320,j=240;
	
	cmd(0x2a);    

  if(MODULE == _MODULE_1_)
{
#ifdef  ROTATE_0||ROTATE_180
	x_all=240;
	y_all=320;
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x00); 
	w_data(0xef);

	cmd(0x2b);    
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x01); 
	w_data(0x3f);
#endif

#ifdef  ROTATE_90||ROTATE_270
	x_all=320;
	y_all=240;
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x01); 
	w_data(0x3f);

	cmd(0x2b);   
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x00); 
	w_data(0xef);
#endif

}
else
{
#ifdef  ROTATE_0||ROTATE_180
	x_all=320;
	y_all=480;
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x01); 
	w_data(0x3f);

	cmd(0x2b);    
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x01); 
	w_data(0xdf);
#endif

#ifdef  ROTATE_90||ROTATE_270
	x_all=480;
	y_all=320;
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x01); 
	w_data(0xdf);

	cmd(0x2b);   
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x00); 
	w_data(0x3f);
#endif

}

	cmd(0x2c); 

	for(i = y_all;i > 0;i--)
		for(j = x_all;j > 0;j--)
	{
			w_data(color>>8);
			w_data(color);
	}
}

void TFTLCD::gpio_init()
{
	pinMode(RST, OUTPUT);
	pinMode(CS, OUTPUT);
	pinMode(RS, OUTPUT);
	pinMode(WR, OUTPUT);
	pinMode(RD, OUTPUT);
	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);

}

/*****************************************
 *The function name ： tft_init
 *Function  ： lcd控制初始化
 *Input  ： none
 *Output   ： none
 *Author   ： KeDei
 *Time   ： 2015/4/21
 ****************************************/
void TFTLCD::tft_init()
{
	
	gpio_init();

	digitalWrite(RST,HIGH);
	delay(50);
	digitalWrite(RST,LOW);
	delay(100);
	
	digitalWrite(RST,HIGH);
	delay(50);
	digitalWrite(CS,HIGH);
	digitalWrite(RD,HIGH);
	digitalWrite(WR,HIGH);
	delay(10);


#ifdef  _ALL_MODULE_
cmd(0x04);
r_data();
if(r_data() ==133)
{
	if(r_data() ==133)
{
	 MODULE=_MODULE_1_ ;
}
	
}
else
{
#endif

#ifdef  _35INCH_MODULE_
cmd(0xD3);
r_data();
r_data();
if(r_data() ==148)
{
	if(r_data() ==134)
{
	 MODULE=_MODULE_2_ ;
}
	
}
else
{
/*
cmd(0xD0);
r_data();
if(r_data() ==153)
{
	 MODULE=_MODULE_3_ ;
	
}
*/

 MODULE=_MODULE_3_ ;
}
#ifdef  _ALL_MODULE_
}
#endif

//Serial.print(MODULE);
//Serial.print(MODULE);

 
if(MODULE == _MODULE_3_)
{
cmd(0x11); //Sleep Out
delay(12);
cmd(0xB9); //SET password
w_data(0xFF);
w_data(0x83);
w_data(0x57);
cmd(0xB1); //SETPower
w_data(0x00); //STB
w_data(0x11); //VGH = 15V, VGL = -10V
w_data(0x1E); //VSPR = 4.5V
w_data(0x1E); //VSNR = -4.5V
w_data(0xC3);  //AP
w_data(0x77); //FS
cmd(0xB4); //SETCYC
w_data(0x11); //1-dot
w_data(0x40); //RTN
w_data(0x00); //DIV
w_data(0x2A); //N_DUM
w_data(0x2A); //I_DUM
w_data(0x20); //GDON
w_data(0x78); //GDOFF
cmd(0xB6); //VCOMDC
w_data(0x33);
cmd(0xC0); //SETSTBA
w_data(0x70); //N_OPON
w_data(0x70); //I_OPON
w_data(0x00); //STBA
w_data(0x3C);  //STBA
w_data(0xC4);  //STBA
w_data(0x08); //GENON
cmd(0xC2); // Set Gate EQ
w_data(0x00);
w_data(0x08);
w_data(0x04);
cmd(0xCC); //Set Panel
w_data(0x09); //SS_Panel = 1, BGR_Panel = 1
cmd(0xE0); //Set Gamma
w_data(0x00); //VRP0
w_data(0x05); //VRP1
w_data(0x12); //VRP2
w_data(0x21); //VRP3
w_data(0x2C); //VRP4
w_data(0x40); //VRP5
w_data(0x4B); //VRP6
w_data(0x52); //VRP7
w_data(0x47); //VRP8
w_data(0x41); //VRP9
w_data(0x3A); //VRP10
w_data(0x31); //VRP11
w_data(0x2E); //VRP12
w_data(0x29); //VRP13
w_data(0x24); //VRP14
w_data(0x00); //VRP15
w_data(0x00); //VRN0
w_data(0x05); //VRN1
w_data(0x12); //VRN2
w_data(0x21); //VRN3
w_data(0x2C); //VRN4
w_data(0x40); //VRN5
w_data(0x4B); //VRN6
w_data(0x52); //VRN7
w_data(0x47); //VRN8
w_data(0x41); //VRN9
w_data(0x3A); //VRN10
w_data(0x31); //VRN11
w_data(0x2E); //VRN12
w_data(0x29); //VRN13
w_data(0x24); //VRN14
w_data(0x00); //VRN15
w_data(0x00);
w_data(0x01); //GMA_Reload
cmd(0x36); //COLMOD
w_data(0x48); //RGB666
cmd(0x3A); //COLMOD
w_data(0x55); //RGB666
cmd(0x29); //Display On
delay(10);
cmd(0x2C); //Write SRAM Data
}
else
if(MODULE==_MODULE_2_)
{

cmd(0xF1);
w_data(0x36);
w_data(0x04);
w_data(0x00);
w_data(0x3C);
w_data(0x0F);
w_data(0x8F);

cmd(0xF2);
w_data(0x18);
w_data(0xA3);
w_data(0x12);
w_data(0x02);
w_data(0xB2);//32
w_data(0x12);
w_data(0xFF);
w_data(0x10);
w_data(0x00);

cmd(0xF8);
w_data(0x21);
w_data(0x04);


cmd(0xF9);
w_data(0x00);
w_data(0x08);


cmd(0xC0);
w_data(0x13);
w_data(0x10);

cmd(0xC1);
w_data(0x43);
w_data(0x00);

cmd(0xC2);
w_data(0x22);

cmd(0xC5);
w_data(0x00);
w_data(0x4D);
w_data(0x80);

cmd(0xB1);
w_data(0xC0);
w_data(0x11);

cmd(0xB4);
w_data(0x01);//02,03

cmd(0xB6);
w_data(0x00);
w_data(0x42);
w_data(0x3B);

//cmd(0xB7);
//w_data(0x07);

cmd(0xE0);
w_data(0x0F);
w_data(0x1B);
w_data(0x19);
w_data(0x0B);
w_data(0x0F);
w_data(0x08);
w_data(0x46);
w_data(0xB9);
w_data(0x33);
w_data(0x08);
w_data(0x03);
w_data(0x00);
w_data(0x00);
w_data(0x00);
w_data(0x00);

cmd(0xE1);
w_data(0x0F);
w_data(0x3F);
w_data(0x3F);
w_data(0x0F);
w_data(0x1C);
w_data(0x07);
w_data(0x4C);
w_data(0x74);
w_data(0x38);
w_data(0x07);
w_data(0x10);
w_data(0x04);
w_data(0x26);
w_data(0x24);
w_data(0x00);

cmd(0x36);
w_data(0xc8);//08

cmd(0x3A);
w_data(0x55);//66

cmd(0x20);
cmd(0x11);
delay(120);
cmd(0x29);
}
else
#endif
{
#ifdef _24INCH_MODULE_

cmd(0x11);
delay(120); 
cmd(0x36);
w_data(0x00);
cmd(0x3a);
w_data(0x55);
cmd(0xb2);
w_data(0x0c);
w_data(0x0c);
w_data(0x00);
w_data(0x33);
w_data(0x33);
cmd(0xb7);
w_data(0x35);
cmd(0xbb);
w_data(0x2b);
cmd(0xc0);
w_data(0x2c);
cmd(0xc2);
w_data(0x01);
cmd(0xc3);
w_data(0x11);
cmd(0xc4);
w_data(0x20);
cmd(0xc6);
w_data(0x0f);
cmd(0xd0);
w_data(0xa4);
w_data(0xa1);
cmd(0xe0);
w_data(0xd0);
w_data(0x00);
w_data(0x05);
w_data(0x0e);
w_data(0x15);
w_data(0x0d);
w_data(0x37);
w_data(0x43);
w_data(0x47);
w_data(0x09);
w_data(0x15);
w_data(0x12);
w_data(0x16);
w_data(0x19);
cmd(0xe1);
w_data(0xd0);
w_data(0x00);
w_data(0x05);
w_data(0x0d);
w_data(0x0c);
w_data(0x06);
w_data(0x2d);
w_data(0x44);
w_data(0x40);
w_data(0x0e);
w_data(0x1c);
w_data(0x18);
w_data(0x16);
w_data(0x19);
cmd(0x29);
#endif
}

}

/*****************************************
 *The function name ： set_area
 *Function  ： 选定lcd的刷新的有效区域，区域的左上角为（x0,y0）,
			右下角为（x1,y1）
 *Input  ： （x0,y0）  （x1,y1）
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::set_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1)
{
	cmd(0x2a);    //Set Gamma 
	w_data(x0>>8); 
	w_data(x0); 
	w_data(x1>>8); 
	w_data(x1); 

	cmd(0x2b);    //Set Gamma 
	w_data(y0>>8); 
	w_data(y0); 
	w_data(y1>>8); 
	w_data(y1); 
	cmd(0x2c);  
}

/*****************************************
 *The function name ： v_line
 *Function  ： 在lcd坐标（x,y）上水平画len长度的线段，线段颜色为color
			如果线段超出屏水平的长度，将自动被裁剪
 *Input  ： 坐标（x,y） 长度len  颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::v_line(unsigned short x,unsigned short y,unsigned short len,unsigned short color)
{

	if((y+len)>YYY) len=YYY-y;
	set_area(x,y,x,y+len);

	for(len;len > 0;len--)
	{
			w_data(color>>8);
			w_data(color);
	}
}

/*****************************************
 *The function name ： h_line
 *Function  ： 在lcd坐标（x,y）上垂直画len长度的线段，线段颜色为color
			如果线段超出屏垂直的长度，将自动被裁剪
 *Input  ： 坐标（x,y） 长度len  颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::h_line(unsigned short x,unsigned short y,unsigned short len,unsigned short color)
{

	if((x+len)>XXX) len=XXX-y;
	set_area(x,y,x+len,y);

	for(len;len > 0;len--)
	{
			w_data(color>>8);
			w_data(color);
	}
}

/*****************************************
 *The function name ： draw_area
 *Function  ： 选定lcd有效区域，区域的左上角为（x0,y0）,右下角为（x1,y1），
			刷新一种color的颜色，如果坐标错误将不刷新颜色
 *Input  ： 坐标（x,y） （x1,y1） 颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short color)
{
		unsigned short i,j;
		if(x0 > x1)	return;
		if(y0 > y1) return;
		set_area(x0,y0,x1,y1);
	
		for(i=x1-x0+1;i > 0;i--)
			for(j=y1-y0+1;j > 0;j--)
			{
				w_data(color>>8);
				w_data(color);
			}
}

/*****************************************
 *The function name ： draw_edge
 *Function  ： 选定lcd有效区域，区域的左上角为（x0,y0）,右下角为（x1,y1），
			给区域的边缘刷新边框大小为size的color颜色
 *Input  ： 坐标（x,y） （x1,y1） 边缘大小size  颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short size,unsigned short color)
{
	draw_area(x0,y0,x1,y0+size,color);
	draw_area(x0,y1-size,x1,y1,color);
	draw_area(x0,y0,x0+size,y1,color);
	draw_area(x1-size,y0,x1,y1,color);
}

/*****************************************
 *The function name ： set_pixl
 *Function  ： 在lcd的坐标（x,y）上画一点。点的颜色为color
 *Input  ： 坐标（x,y） 颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void   TFTLCD::set_pixl(unsigned short x,unsigned short y,unsigned short color)
{
	set_area(x,y,x,y);
	w_data(color>>8);
	w_data(color);
}

/*****************************************
 *The function name ： draw_buttom
 *Function  ： 在lcd的左上坐标（x0,y0），右下坐标（x1,y1），圆角半径为circular_size上
			画一个圆角按钮，颜色为color。
 *Input  ： 左上坐标（x0,y0），右下坐标（x1,y1），圆角半径circular_size，颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_buttom(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size,unsigned short color)
{
	if(circular_size)
	{	
		int dx = 0,dy = circular_size;
		int d = 1 - circular_size;                  
		for(;dy >= dx;)                    
		{
			 draw_area(-dy+x0+circular_size,-dx+y0+circular_size,dy+x1-circular_size,-dx+y0+circular_size,color);
			 draw_area(-dy+x0+circular_size,dx+y1-circular_size,dy+x1-circular_size,dx+y1-circular_size,color);
		
			 
		if(d < 0)
			d = d + 2 * dx + 3;                       
		else
		{
			d = d + 2 * (dx - dy) + 5;                  
			dy--;
			draw_area(-dx+x0+circular_size,-dy+y0+circular_size,dx+x1-circular_size,-dy+y0+circular_size,color);
			draw_area(-dx+x0+circular_size,dy+y1-circular_size,dx+x1-circular_size,dy+y1-circular_size,color);

		}
		dx++;                                         
		}
		draw_area(x0,y0+circular_size,x1,y1-circular_size,color);
	}

}

/*****************************************
 *The function name ： draw_buttom_edge
 *Function  ： 在lcd的左上坐标（x0,y0），右下坐标（x1,y1），圆角半径为circular_size上
			画一个圆角按钮边沿，颜色为color。
 *Input  ：  左上坐标（x0,y0），右下坐标（x1,y1），圆角半径circular_size，颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_buttom_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size,unsigned short color)
{
	if(circular_size)
	{	
		int dx = 0,dy = circular_size;
		int d = 1 - circular_size;                  
		for(;dy >= dx;)                    
		{
			set_pixl(-dy+x0+circular_size,-dx+y0+circular_size,color);
			set_pixl(dy+x1-circular_size,-dx+y0+circular_size,color);
			set_pixl(-dy+x0+circular_size,dx+y1-circular_size,color);
			set_pixl(dy+x1-circular_size,dx+y1-circular_size,color);
			set_pixl(-dx+x0+circular_size,-dy+y0+circular_size,color);
			set_pixl(dx+x1-circular_size,-dy+y0+circular_size,color);
			set_pixl(-dx+x0+circular_size,dy+y1-circular_size,color);
			set_pixl(dx+x1-circular_size,dy+y1-circular_size,color);
			 
		if(d < 0)
			d = d + 2 * dx + 3;                       
		else
		{
			d = d + 2 * (dx - dy) + 5;                  
			dy--;
		

		}
		dx++;                                         
		}
		draw_area(x0+circular_size,y0,x1-circular_size,y0,color);
		draw_area(x0+circular_size,y1,x1-circular_size,y1,color);
		draw_area(x0,y0+circular_size,x0,y1-circular_size,color);
		draw_area(x1,y0+circular_size,x1,y1-circular_size,color);
	}

}

/*****************************************
 *The function name ： RGB_TO_565
 *Function  ： 将24位的RGB颜色转换为16位的LCD真彩色
 *Input  ： 三颜色R G B
 *Output  ： 16位的真彩色
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
unsigned short   TFTLCD::RGB_TO_565(unsigned char r,unsigned char g,unsigned char b)
{
 unsigned short _RGB = ((unsigned short)r>>3)<<11;
 
 _RGB |= ((unsigned short)g>>2)<<5;
 
 _RGB |= ((unsigned short)b>>3);
 return _RGB;

}

/*****************************************
 *The function name ： draw_circle
 *Function  ： 在lcd的坐标（x,y）上画半径为R的一个空心圆。圆空心的颜色为color
 *Input  ： 坐标（x,y） 半径R 颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_circle(unsigned short x,unsigned short y,unsigned short R,unsigned short color)
{
	int x0 = 0,y0 = R;
	int d = 1 - R;                  
	for(;y0 >= x0;)                    
	{
	set_pixl(x0+x,y0+y,color);        
	set_pixl(y0+x,x0+y,color);        
	set_pixl(-x0+x,y0+y,color);      
	set_pixl(-y0+x,x0+y,color);       
	set_pixl(-x0+x,-y0+y,color);      
	set_pixl(-y0+x,-x0+y,color);       
	set_pixl(x0+x,-y0+y,color); 
	set_pixl(y0+x,-x0+y,color);  
	if(d < 0)
		d = d + 2 * x0 + 3;                       
	else
	{
		d = d + 2 * (x0 - y0) + 5;                  
		y0--;
		
	}
	x0++;                                         
	}
}


/*****************************************
 *The function name ： draw_ring
 *Function  ： 在lcd的坐标（x,y）上画内半径为IR、外半径为OR的一个圆环。圆环的颜色为color
 *Input  ： 坐标（x,y） 内半径IR 外半径OR 颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::draw_ring(unsigned short x,unsigned short y,unsigned short OR,unsigned short IR,unsigned short color)
{

	/*int i;
	for(i = IR;i <= OR;i++)
		draw_circle(x,y,i,color);

*/
	int x0,y0,x1,y1,value;
	//x0=OR;
	//y0=OR;
	for(y0=0;y0<OR;y0++)
	{
		for(x0=0;x0<OR;x0++)
		{
			value=x0*x0+y0*y0;
			if((value<=(OR*OR))&&(value>=(IR*IR)))
				{
					set_pixl(x-x0,y-y0,color);   
					set_pixl(x-x0,y+y0,color);  
					set_pixl(x+x0,y+y0,color);  
					set_pixl(x+x0,y-y0,color);      
				}	
		}
	}
}

/*****************************************
 *The function name ： FillCircle
 *Function  ： 在lcd的坐标（x,y）上画半径R的一个实心圆。实心圆的颜色为color
 *Input  ： 坐标（x,y） 半径R 颜色color
 *Output  ： none
 *作 者  ： KeDei
 *时 间  ： 2015/4/21
 ****************************************/
void TFTLCD::FillCircle(unsigned short x,unsigned short y,unsigned short R,unsigned short color)
{	int x0 = 0,y0 = R;
	int d = 1 - R;                  
	for(;y0 >= x0;)                    
	{
		 draw_area(-y0+x,x0+y,y0+x,x0+y,color);
		 draw_area(-y0+x,-x0+y,y0+x,-x0+y,color);
		 
	if(d < 0)
		d = d + 2 * x0 + 3;                       
	else
	{
		d = d + 2 * (x0 - y0) + 5;                  
		y0--;
		draw_area(-x0+x,-y0+y,x0+x,-y0+y,color);
		draw_area(-x0+x,y0+y,x0+x,y0+y,color);

	}
	x0++;                                         
	}

}


void TFTLCD::draw_pixl(unsigned short x,unsigned short y,unsigned short size,unsigned short color)
{
	unsigned short i,j;
	set_area(x,y,x+size,y+size);
	for(i = size+1;i > 0;i--)
		for(j = size+1;j > 0;j--)
		{
			w_data(color>>8);
			w_data(color);
		}
}

void   TFTLCD::draw_sin(int x,int y,float A,float w,float r,unsigned short color)
{
	float i;
	for(i = x;i < 315;i++)
	{
		 draw_pixl(i,A*sin(i/w+r)+y,0,color);
	}
}


void TFTLCD::Bresenhamline(int x0,int y0,int x1, int y1,int color) 
{

	if (y0==y1)
		h_line(x0, y0, x1-x0,color);
	else if (x0==x1)
		v_line(x0, y0, y1-y0,color);
	else
	{
		unsigned int	dx = (x1 > x0 ? x1 - x0 : x0 - x1);
		short			xstep =  x1 > x0 ? 1 : -1;
		unsigned int	dy = (y1 > y0 ? y1 - y0 : y0 - y1);
		short			ystep =  y1 > y0 ? 1 : -1;
		int				col = x0, row = y0;

		if (dx < dy)
		{
			int t = - (dy >> 1);
			while (true)
			{
				//draw_pixl(col, row,1,color);
				set_pixl(col, row,color);
				if (row == y1)
					return;
				row += ystep;
				t += dx;
				if (t >= 0)
				{
					col += xstep;
					t   -= dy;
				}
			} 
		}
		else
		{
			int t = - (dx >> 1);
			while (true)
			{
				//draw_pixl(col, row,1,color);
				set_pixl(col, row,color);
				if (col == x1)
					return;
				col += xstep;
				t += dy;
				if (t >= 0)
				{
					row += ystep;
					t   -= dx;
				}
			} 
		}
	}

     // draw_pixl (x, int(y),1, color); 




}
