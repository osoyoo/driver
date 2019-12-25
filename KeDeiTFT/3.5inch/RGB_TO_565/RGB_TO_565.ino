#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"

#define backcolor 0X8888
//LCD class object is TFT
TFTLCD TFT;
//Font class object is font
Font  font;
//Touchuscreem TP class object is tp
TP tp;

int value =1688;
void setup() {
  //TFT initialization
   TFT.begin();
   
   //LCD Clear the screen, backcolor
   TFT.clear(backcolor);
   

   //Set the text area for the upper left corner (50, 10), the lower right corner (240,200), the color 0XDDDD, if the color is NULL or R0 G0 B0(black), is also not set text color 
   font.set_txt(15,15,240,200,0X8888);
   
   //Set the text font color
   font.set_fontcolor(TFT.RGB_TO_565(0,0,255));
   //Displays a string
   font.lcd_string("KeDeiTFT");
   font.lcd_string("show RGB to 565");
   
   font.set_txt(15,80,60,125,TFT.RGB_TO_565(255,0,0));
   font.set_txt(70,80,115,125,TFT.RGB_TO_565(255,156,0));
   font.set_txt(125,80,170,125,TFT.RGB_TO_565(255,0,156));
   font.set_txt(180,80,225,125,TFT.RGB_TO_565(255,156,156));
   
   font.set_txt(15,135,60,180,TFT.RGB_TO_565(0,255,0));
   font.set_txt(70,135,115,180,TFT.RGB_TO_565(156,255,0));
   font.set_txt(125,135,170,180,TFT.RGB_TO_565(0,255,156));
   font.set_txt(180,135,225,180,TFT.RGB_TO_565(156,255,156));

   font.set_txt(15,190,60,235,TFT.RGB_TO_565(0,0,255));
   font.set_txt(70,190,115,235,TFT.RGB_TO_565(0,156,255));
   font.set_txt(125,190,170,235,TFT.RGB_TO_565(156,0,255));
   font.set_txt(180,190,225,235,TFT.RGB_TO_565(156,156,255));
  
   font.set_txt(15,245,60,290,TFT.RGB_TO_565(0,255,255));
   font.set_txt(70,245,115,290,TFT.RGB_TO_565(255,255,0));
   font.set_txt(125,245,170,290,TFT.RGB_TO_565(255,0,255));
   font.set_txt(180,245,225,290,TFT.RGB_TO_565(255,255,255));
  
}

void loop() {
  
  
      
}
