/*
welcome use KeDeiTFT
*/
#ifndef         _KeDei_TFT_H_
#define         _KeDei_TFT_H_
#include		"KeDei_config.h"
#include		"Arduino.h"


class TFTLCD {
public:
		void 	begin(void);
		void    gpio_init(void);
		void 	tft_init(void);
		void 	clear(unsigned short color);
		void	cmd(unsigned char cmd);
		void	w_data(unsigned char data);
		int	r_data(void);


		void 	set_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1);
		void 	v_line(unsigned short x,unsigned short y,unsigned short len,unsigned short color);
		void	h_line(unsigned short x,unsigned short y,unsigned short len,unsigned short color);

		void    draw_area(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short color);
		void 	draw_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short size,unsigned short color);

		void 	set_pixl(unsigned short x,unsigned short y,unsigned short color);
		void    draw_buttom_edge(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size,unsigned short color);
		void	draw_buttom(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short circular_size,unsigned short color);
		unsigned short   RGB_TO_565(unsigned char r,unsigned char g,unsigned char b);


		void	draw_circle(unsigned short x,unsigned short y,unsigned short R,unsigned short color);
		void	draw_ring(unsigned short x,unsigned short y,unsigned short OR,unsigned short IR,unsigned short color);
		void	FillCircle(unsigned short x,unsigned short y,unsigned short R,unsigned short color);

		void    draw_sin(int x,int y,float A,float w,float r,unsigned short color);
		void    draw_pixl(unsigned short x,unsigned short y,unsigned short size,unsigned short color);
		void    Bresenhamline(int x0,int y0,int x1, int y1,int color) ;

private:
	;
};
extern TFTLCD TFT;

#endif
