/*
welcome use KeDeiTFT
*/
#ifndef 	_KeDei_TP_H_
#define		_KeDei_TP_H_
#include 	"KeDei_config.h"
#include	"Arduino.h"


static int  	a = -270;
static int  	b = 667;
static int  	c = 380;
static int  	d = -190;
static int		e = 600 ;
static int		f = 287;

static char  tp_i=12;
static long  tp_max;
static long  tp_min;
static long  tp_x;
static long  tp_y;
static long  temp_x;
static long  temp_y;

class TP{
public:
	int		x;
	int		y;
	bool	flag;
	bool	x_val;
	bool	y_val;
	
	void	pen_down(void);
	
private:
	char	tp_i;
	long	tp_max;
	long	tp_min;
	long	tp_x;
	long	tp_y;
	long	temp_x;
	long	temp_y;
	void	get_xy(void);

};

extern TP tp;

#endif