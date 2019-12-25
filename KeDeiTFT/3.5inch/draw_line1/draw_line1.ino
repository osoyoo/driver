#include <KeDei_TFT.h>

#define backcolor 0x001f

TFTLCD TFT;


void setup() {
   TFT.begin();
   TFT.clear(backcolor);
   
  for (int i=0; i<=480; i+=8)
  {
    TFT.Bresenhamline(0,0,320, i,0xffff);
  }
  
  for (int i=320; i>=0; i-=6)
  {
    TFT.Bresenhamline(0,0,i, 480,0xffff);
  }


  
}

void loop() {
     
}
