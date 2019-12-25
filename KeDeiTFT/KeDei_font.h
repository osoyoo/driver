#ifndef   _KeDei_FONT_H_
#define   _KeDei_FONT_H_
#include "KeDei_TFT.h"


#define font_interval	1
class Font{
public:
	void	begin(void);
	void	set_txt(unsigned short x0,unsigned short y0,unsigned short x1,unsigned short y1,unsigned short txt_b_color);
	void 	clear_txt(unsigned short color);
	void	lcd_char(char _data);
	void	set_fontcolor(unsigned short f_color);
	void	lcd_string(char str[]);
	void	lcd_int(int value);

private:
	unsigned short	font_color;
	unsigned short	font_size;
	unsigned short	txt_x0;
	unsigned short	txt_y0;
	unsigned short	txt_x1;
	unsigned short	txt_y1;
	unsigned short	txt_backcolor;
	unsigned short	now_x;
	unsigned short	now_y;
	int				char_i;
	char			buff[16];
	unsigned char	char_m,char_n;

};

extern  Font  font;
#endif