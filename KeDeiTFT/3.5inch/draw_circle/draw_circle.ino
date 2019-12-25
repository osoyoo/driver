#include <KeDei_TFT.h>
#include "KeDei_font.h"

#define backcolor 0xf800
TFTLCD TFT;
Font  font;

void setup() {
   TFT.begin();
   TFT.clear(backcolor);
   
   font.set_txt(10,10,200,200,TFT.RGB_TO_565(255,0,0));
   font.set_fontcolor(TFT.RGB_TO_565(0,0,255));
   font.lcd_string("KeDeiTFT");
   font.lcd_string("circle ring fillcircle ");
   
   TFT.draw_circle(45,266,40,TFT.RGB_TO_565(255,255,255));
   TFT.draw_ring(185,110,40,35,TFT.RGB_TO_565(255,255,255));
   
   TFT.FillCircle(45,116,40,TFT.RGB_TO_565(255,255,255));
   TFT.FillCircle(75,146,40,TFT.RGB_TO_565(0,255,0));
   TFT.FillCircle(105,176,40,TFT.RGB_TO_565(0,0,255));
   TFT.FillCircle(135,206,40,TFT.RGB_TO_565(255,0,255));
   TFT.FillCircle(165,236,40,TFT.RGB_TO_565(255,255,0));
   TFT.FillCircle(195,266,40,TFT.RGB_TO_565(155,155,0));
   TFT.FillCircle(225,296,40,TFT.RGB_TO_565(0,255,255));
   TFT.FillCircle(255,326,40,TFT.RGB_TO_565(255,255,255));
}

void loop() {
     
}
