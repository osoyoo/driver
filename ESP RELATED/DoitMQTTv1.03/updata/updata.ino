#define PINLED 2 
#define PINKEY 3

#define MAX_PACKETSIZE 512

//uartdata
char buffUart[MAX_PACKETSIZE];
unsigned int buffUartIndex = 0;
unsigned long preUartTick = 0;


void parseUartPackage(char *p, size_t len) {
	if(strcmp(p,"ledon") == 0){
	    digitalWrite(PINLED, 1);
	    Serial.println("turn on led");
	}
	else if(strcmp(p,"ledoff") == 0){
	    digitalWrite(PINLED, 0);
	    Serial.println("turn off led");
	}
}

/*
  检查串口是否有数据
*/
void doUartTick()
{
	if (Serial.available() > 0)
	{
		uint8_t t = Serial.read();
		buffUart[buffUartIndex++] = t ;
		preUartTick = millis();
		if (buffUartIndex >= MAX_PACKETSIZE - 1) {
			buffUartIndex = MAX_PACKETSIZE - 2;
			preUartTick = preUartTick - 200;
		}
	}
	if (buffUartIndex > 0 && (millis() - preUartTick >= 100))
	{	//data ready
		buffUart[buffUartIndex] = 0x00;
		Serial.flush();
		parseUartPackage(buffUart, buffUartIndex);
		buffUartIndex = 0;
	}
}

/*
  * 发送数据到串口
 */
void sendUART(char *p, size_t len)
{
	Serial.write(p, len);
	delay(50);
}

/*
  * 发送数据到串口
 */
void sendUART(char *p)
{
	Serial.write(p, strlen(p));
	delay(50);
}

/*
 * 检查用户按键，判断是短按或者长按
*/
void doKeyTick()
{
	static char keyCnt = 0;
	static  unsigned long preTick = millis();

	if (millis() - preTick < 10 ) return;

	preTick = millis();

	if (keyCnt >= 200)
	{	//长按
		keyCnt = 0;
		Serial.println("\r\nLong Press key");
	}
	else if (keyCnt >= 5 && digitalRead(PINKEY) == 1)
	{	//短按
		keyCnt = 0;
		Serial.println("\r\nShort Press key");
	}	

	if (digitalRead(PINKEY) == 0) keyCnt++;
	else keyCnt = 0;
}

void setup()
{
	Serial.begin(115200);
	pinMode(PINKEY,INPUT_PULLUP);
	pinMode(PINLED,OUTPUT);
}

void loop()
{
	doKeyTick();
	doUartTick();
}