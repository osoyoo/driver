/*
welcome use KeDeiTFT

*/
#ifndef         _KeDei_button_H_
#define         _KeDei_button_H_

#include 	"KeDei_config.h"
#include	"KeDei_TFT.h"
#include	"Arduino.h"
#include	"KeDei_font.h"


class  Button 
{
public:
	Button()
	{
	//	x				= 0;
	//	y				= 0;
		//the  button size
		x_size			= 64;
		y_size			= 40;
		//the button  abort color
		edge_up_color	= 0xffff;
		edge_down_color	= 0x6b4d;
		button_color	= 0x4898;
		font_color		= 0xffff;
		//the  botton moder 0--cube_button  1--circle_button
	//	botton_moder	= 1;
	};

	void drawButton(unsigned short _x,unsigned short _y,bool _botton_moder, char *str);
	bool istouch(unsigned short _x,unsigned short _y);
	void pendown(void);
	void penup(void);
	/*if you want  to change the butom size or the color,you can use  the  follow function to achieve your purpose,
	but you  must do it before use the drawbutton() function;also  if you  always change the auto value ,you can change the button() function*/
	void resetsize(unsigned char _x_size,unsigned char _y_size);
	void resetcolor(unsigned short _edge_up_color,unsigned short _edge_down_color,unsigned short _button_color,unsigned short _font_color);
	
private:
	//the  poisition(x,y);
	unsigned short	x;
	unsigned short	y;
	//the  button size
	unsigned char	x_size ;
	unsigned char	y_size ;
	//the  button  abort color
	unsigned short	edge_up_color;
	unsigned short	edge_down_color;
	unsigned short	button_color;
	unsigned short	font_color;
	//the  botton moder 0--cube_button , 1--circle_button
	bool			botton_moder;
	unsigned short	len;
};


#endif
