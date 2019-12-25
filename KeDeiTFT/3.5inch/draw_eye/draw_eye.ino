
#include <KeDei_TFT.h>
#include <KeDei_TP.h>

#define backcolor 0xd7dd
TFTLCD TFT;


void setup() {
   Serial.begin(9600);
   TFT.begin();
   TFT.clear(backcolor);
   
  for (int i=320; i>0; i-=8)
  {
    TFT.Bresenhamline(i,0,0, 480-(i*1.5),0x0);
  }

  for (int i=0; i<320; i+=8)
  {
   TFT.Bresenhamline(i,480,318, 480-(i*1.5),0x0);
  }

   TFT.FillCircle(160,240,100,TFT.RGB_TO_565(200,125,64));
    TFT.FillCircle(160,240,30,TFT.RGB_TO_565(0,0,0));
}

void loop() {
     
}
