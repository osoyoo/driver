#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"

#define backcolor 0xf800

//LCD class object is TFT
TFTLCD TFT;
//Font class object is font
Font  font;
//Touchuscreem TP class object is tp
TP tp;

void setup() {
  //TFT initialization
   TFT.begin();
   //LCD Clear the screen, backcolor
   TFT.clear(backcolor);
   
   //Set the text area for the upper left corner (10, 10), the lower right corner (240,200), the color red, if the color is NULL or R0 G0 B0(black), is also not set text color 
   font.set_txt(10,10,240,200,TFT.RGB_TO_565(255,0,0));
   
   //Set the text font color
   font.set_fontcolor(TFT.RGB_TO_565(0,0,255));
   
   //Displays a string
   font.lcd_string("KeDeiTFT ");
   font.lcd_string("Please draw by yourself");

}

void loop() {
     //check Touch current state detection
      tp.pen_down();
      
      //The touch screen is touch
      if(tp.flag&&tp.y_val&&tp.x_val)
          //draw  pixel
         TFT.set_pixl(tp.x,tp.y,TFT.RGB_TO_565(255,255,255));
}
