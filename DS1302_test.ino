// DS1302:  RST pin    -> Arduino Digital 2
//          DAT pin   -> Arduino Digital 3
//          CLK pin  -> Arduino Digital 4
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1302.h>
LiquidCrystal_I2C lcd(0x27,16,2);// if your LCD does not display,change it to 0x27 or other address
//to detect correct LCD i2c address, read http://osoyoo.com/2014/12/07/16x2-i2c-liquidcrystal-displaylcd/

DS1302 rtc(2, 3, 4);
void clockdate() 
{
        lcd.clear();  
        lcd.setCursor(0,0);
        lcd.print(rtc.getDateStr(FORMAT_LONG,FORMAT_LITTLEENDIAN, '/'));// check 1302 library and see FORMAT_BIGENDIAN:2010-01-01;FORMAT_LITTLEENDIAN:01-01-2010
        lcd.setCursor(11,0);
        lcd.print(rtc.getDOWStr());
        lcd.setCursor(14,0);
        lcd.print("    ");
        lcd.setCursor(0, 1) ;
        lcd.print(rtc.getTimeStr());
}

void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.backlight(); 
  rtc.halt(false);
  rtc.writeProtect(false);
  rtc.setDOW(WEDNESDAY);         
  rtc.setTime(11, 47,00);      
  rtc.setDate(27, 7, 2016);    
  rtc.writeProtect(true);
  }

void loop()
{ 
  clockdate();
  delay(1000);
}
