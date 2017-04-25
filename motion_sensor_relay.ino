int relay_1=8;
int relay_2=9;
int motion_sensor=10;
void setup() {
  pinMode(relay_1,OUTPUT);
  pinMode(relay_2,OUTPUT);
  pinMode(motion_sensor,INPUT);
}

void loop() {
  int val;
  val=digitalRead(motion_sensor);
  if(val==1)
  {
    digitalWrite(relay_1,LOW);
    //delay(1000);
    digitalWrite(relay_2,HIGH);
    //delay(1000);
   }
  else
  {
    digitalWrite(relay_1,HIGH);
    digitalWrite(relay_2,LOW);
   }
}
