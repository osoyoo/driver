
#include <KeDei_TFT.h>

#define backcolor 0x001F

//LCD class object is TFT
TFTLCD TFT;

void setup() {
  //TFT initialization
   TFT.begin();
   //LCD Clear the screen, backcolor
   TFT.clear(backcolor);
   
 
   for (int i=0; i<320; i+=5)
  {
    TFT.Bresenhamline( i,0,320, (i*1.5),0xf100);
  }
 
  for (int i=320; i>0; i-=5)
  {
  TFT.Bresenhamline(i,480,0, (i*1.5),0xf100);
  }

  for (int i=320; i>0; i-=5)
  {
    TFT.Bresenhamline(i,0,0, 480-(i*1.5),0x07e0);
  }

  for (int i=0; i<320; i+=5)
  {
   TFT.Bresenhamline(i,480,318, 480-(i*1.5),0x07e0);
  }

}

void loop() {
    
}
