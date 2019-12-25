#include <KeDei_TFT.h>
#include <KeDei_TP.h>
#include "KeDei_font.h"
#include "KeDei_button.h"

#define backcolor 0xf800
//LCD class object is TFT
TFTLCD TFT;
//Font class object is font
Font  font;
//Touchuscreem TP class object is tp
TP tp;
//Two Button class object is  Button1,Button2
Button  Button1,Button2;
int value =1688;
void setup() {
  //TFT initialization
   TFT.begin();
   //LCD Clear the screen, backcolor
   TFT.clear(backcolor);
   
   
   font.begin();
   //Set the text area for the upper left corner (30, 10), the lower right corner (320,200), the color red, if the color is NULL or R0 G0 B0(black), is also not set text color 
   font.set_txt(5,5,320,200,TFT.RGB_TO_565(255,0,0));
   
   //Set the text font color
   font.set_fontcolor(TFT.RGB_TO_565(0,0,255));
   //Displays a string
   font.lcd_string("KeDeiTFT");
   font.lcd_string("show int number add and reduce");
   
   //Draw the first round button1
   Button1.drawButton(100,100,1,"-");
   //Draw the second round button
   Button2.drawButton(100,250,0,"+");


   font.set_txt(100,180,140,197,TFT.RGB_TO_565(255,0,0));
   font.lcd_int(value);
}

void loop() {
  //check Touch current state detection
  tp.pen_down();
      //The touch screen is touch
      if(tp.flag&&tp.y_val&&tp.x_val)
         //Check whether pressing the first button
        if(Button1.istouch(tp.x,tp.y))
        {
          //Touch screen alway be pressed
           for(;tp.flag;)
           {
             //value add by 9
             value -= 9;
             //clear the text area
            font.set_txt(100,180,140,197,TFT.RGB_TO_565(255,0,0));
             //Displays new value
             font.lcd_int(value);
            // delay(500);
             tp.pen_down();
           }
           //Button to restore the original appearance
           Button1.penup();
        }
        else
        if(Button2.istouch(tp.x,tp.y))
        {
           for(;tp.flag;)
            {
               //value reduce by 9
               value += 9;
               font.set_txt(100,180,140,197,TFT.RGB_TO_565(255,0,0));
               font.lcd_int(value);
              //   delay(500);
               tp.pen_down();
           }
           Button2.penup();
        }
      
}
