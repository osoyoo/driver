/*
welcome use KeDeiTFT
*/
#ifndef 	_KeDei_CONFIG_H_
#define		_KeDei_CONFIG_H_

#define   _ALL_MODULE_

#define  _24INCH_MODULE_  
#define  ROTATE_0

#ifdef _35INCH_MODULE_
#undef _24INCH_MODULE_
#endif


#ifdef _ALL_MODULE_
#define  _24INCH_MODULE_
#define  _35INCH_MODULE_
#endif

#ifdef ROTATE_90
#undef ROTATE_0
#endif

#ifdef ROTATE_180
#undef ROTATE_0
#endif

#ifdef ROTATE_270
#undef ROTATE_0
#endif

#define  _MODULE_1_   0  
#define  _MODULE_2_   1  
#define  _MODULE_3_   2   

//LCD GPIO
#define		RST	A4
#define		CS	A0
#define		RS	A1
#define		WR	A2
#define		RD	A3

#define		D0	8
#define		D1	9
#define		D2	2
#define		D3	3
#define		D4	4
#define		D5	5
#define		D6	6
#define		D7	7


//TS  GPIO
#define		XP	A1	
#define		XM	5	
#define		YP	A2	
#define		YM	6

#define _cmd(x)		cmd(~x)
#define ww_data(x)	w_data(~x)

#ifdef ROTATE_0||ROTATE_180
	#define		XXX	240
	#define		YYY	320
#endif

#ifdef ROTATE_90||ROTATE_270
	#define		XXX	320
	#define		YYY	240
#endif


extern unsigned char   MODULE;

#endif