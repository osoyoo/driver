
/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/    
 * www.osoyoo.com IR remote control smart car
 * program tutorial : http://osoyoo.com/2017/04/16/control-smart-car-with-ir/
 *  Copyright John Yu
 */
#include <IRremote.h>

#define IR_PIN       2 //IR receiver Signal pin connect to Arduino pin 2

#define MOTOR_LEFT1_PIN  5//LEFT MOTOR INPUT 1 connect to L298N IN2 pin
#define MOTOR_LEFT2_PIN  6//LEFT MOTOR INPUT 2 connect to L288N IN1 pin
#define MOTOR_RIGHT1_PIN 9//RIGHT MOTOR INPUT 1 connect to L288N IN3 pin
#define MOTOR_RIGHT2_PIN 10//RIGHT MOTOR INPUT 2 connect to L288N IN4 pin


 #define IR_ADVANCE       0x00FFA857       //code from IR controller "+" button
 #define IR_BACK          0x00FFE01F       //code from IR controller "-" button
 #define IR_RIGHT         0x00FFE21D       //code from IR controller "CH+" button
 #define IR_LEFT          0x00FFA25D       //code from IR controller "CH-" button
 #define IR_STOP          0x00FF629D       //code from IR controller "CH" button
 #define IR_turnsmallleft 0x00FF02FD       //code from IR controller "NEXT" button

enum DS
{
  MANUAL_DRIVE,// manual control working mode
  
}Drive_Status=MANUAL_DRIVE;

enum DN
{ 
  GO_ADVANCE, //go forward
  GO_LEFT, //left turn
  GO_RIGHT,//right turn
  GO_BACK,//backward
  STOP_STOP, 
  DEF
}Drive_Num=DEF;

 IRrecv IR(IR_PIN);  //   IRrecv object  IR get code from IR remoter
 decode_results IRresults;   

bool stopFlag = true;//set stop flag
bool JogFlag = false;
uint16_t JogTimeCnt = 0;
uint32_t JogTime=0;
uint8_t motor_update_flag = 0;

//motor control
 
void go_Advance()  //double-wheel moving forward
{
  if(motor_update_flag ==1) return;
  motor_update_flag = 1;

  analogWrite(MOTOR_LEFT1_PIN, 200);
  analogWrite(MOTOR_LEFT2_PIN, 0);
  analogWrite(MOTOR_RIGHT1_PIN, 200);
  analogWrite(MOTOR_RIGHT2_PIN, 0);
}
void go_Left(int t=0)  //double-wheel left turn
{
  if(motor_update_flag ==2) return;
  motor_update_flag = 2;

  analogWrite(MOTOR_LEFT1_PIN, 0);
  analogWrite(MOTOR_LEFT2_PIN, 200);
  analogWrite(MOTOR_RIGHT1_PIN, 200);
  analogWrite(MOTOR_RIGHT2_PIN, 0);
  delay(t);
}
void go_Right(int t=0)  //double-wheel right turn 
{
  if(motor_update_flag ==3) return;
  motor_update_flag = 3;


  analogWrite(MOTOR_LEFT1_PIN, 200);
  analogWrite(MOTOR_LEFT2_PIN, 0);
  analogWrite(MOTOR_RIGHT1_PIN, 0);
  analogWrite(MOTOR_RIGHT2_PIN, 200);
  delay(t);
}
void go_Back(int t=0)  //double-wheel moving backward
{
  if(motor_update_flag ==4) return;
  motor_update_flag = 4;

  analogWrite(MOTOR_LEFT1_PIN, 0);
  analogWrite(MOTOR_LEFT2_PIN, 200);
  analogWrite(MOTOR_RIGHT1_PIN, 0);
  analogWrite(MOTOR_RIGHT2_PIN, 200);
  delay(t);
}
void stop_Stop()    //double-wheel stop 
{
  if(motor_update_flag ==5) return;
  motor_update_flag = 5;

  analogWrite(MOTOR_LEFT1_PIN, 0);
  analogWrite(MOTOR_LEFT2_PIN, 0);
  analogWrite(MOTOR_RIGHT1_PIN, 0);
  analogWrite(MOTOR_RIGHT2_PIN, 0);
}

 

//detect IR code
void do_IR_Tick()
{
  if(IR.decode(&IRresults))
  {
    if(IRresults.value==IR_ADVANCE)
    {
      Drive_Status=MANUAL_DRIVE;
      Drive_Num=GO_ADVANCE;
    }
    else if(IRresults.value==IR_RIGHT)
    {
      Drive_Status=MANUAL_DRIVE;
        Drive_Num=GO_RIGHT;
    }
    else if(IRresults.value==IR_LEFT)
    {
      Drive_Status=MANUAL_DRIVE;
        Drive_Num=GO_LEFT;
    }
    else if(IRresults.value==IR_BACK)
    {
      Drive_Status=MANUAL_DRIVE;
        Drive_Num=GO_BACK;
    }
    else if(IRresults.value==IR_STOP)
    {
      Drive_Status=MANUAL_DRIVE;
        Drive_Num=STOP_STOP;
    }
    IRresults.value = 0;
    IR.resume();
  }
}

//car control
void do_Drive_Tick()
{
  if(Drive_Status == MANUAL_DRIVE)//set manual work mode
  {
    switch (Drive_Num) 
    {
      case GO_ADVANCE:go_Advance();JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;//if GO_ADVANCE code is detected, then go advance
      case GO_LEFT: go_Left();JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;//if GO_LEFT code is detected, then turn left
      case GO_RIGHT:  go_Right();JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;//if GO_RIGHT code is detected, then turn right
      case GO_BACK: go_Back();JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;//if GO_BACK code is detected, then backward
      case STOP_STOP: stop_Stop();JogTime = 0;break;//stop
      default:break;
    }
    Drive_Num=DEF;
   //keep current moving mode for  200 millis seconds
    if(millis()-JogTime>=200)
    {
      JogTime=millis();
      if(JogFlag == true) 
      {
        stopFlag = false;
        if(JogTimeCnt <= 0) 
        {
          JogFlag = false; stopFlag = true;
        }
        JogTimeCnt--;
      }
      if(stopFlag == true) 
      {
        JogTimeCnt=0;
        stop_Stop();
      }
    }
  }
}
//initialize Arduino pins
void init_GPIO()
{
 
  pinMode(MOTOR_LEFT1_PIN, OUTPUT); 
  pinMode(MOTOR_LEFT2_PIN, OUTPUT); 
  pinMode(MOTOR_RIGHT1_PIN, OUTPUT);  
  pinMode(MOTOR_RIGHT2_PIN, OUTPUT);
  
  stop_Stop();
 
 
  digitalWrite(IR_PIN, HIGH);  
  IR.enableIRIn();     
}

void setup()
{
  Serial.begin(9600); 
  init_GPIO();  
}


void loop()
{
  do_IR_Tick();
  do_Drive_Tick();
}