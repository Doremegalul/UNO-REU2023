#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>
#include <softPwm.h>
#include <softTone.h>

#define uchar unsigned char

#define Trig    0
#define Echo    1
#define LedPinRed    2
#define LedPinGreen  3
#define LedPinBlue   4
#define BuzPin    5


//led fucntion 1
void ledInit(void)
{
	softPwmCreate(LedPinRed,  0, 100);
	softPwmCreate(LedPinGreen,0, 100);
	softPwmCreate(LedPinBlue, 0, 100);
}
//led function 2
void ledColorSet(uchar r_val, uchar g_val, uchar b_val)
{
	softPwmWrite(LedPinRed,   r_val);
	softPwmWrite(LedPinGreen, g_val);
	softPwmWrite(LedPinBlue,  b_val);
}


void ultraInit(void)
{
	pinMode(Echo, INPUT);
	pinMode(Trig, OUTPUT);
}

float disMeasure(void)
{
	struct timeval tv1;
	struct timeval tv2;
	long time1, time2;
    float dis;

	digitalWrite(Trig, LOW);
	delayMicroseconds(2);

	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);      //发出超声波脉冲
	digitalWrite(Trig, LOW);
								
	while(!(digitalRead(Echo) == 1));
	gettimeofday(&tv1, NULL);           //获取当前时间

	while(!(digitalRead(Echo) == 0));
	gettimeofday(&tv2, NULL);           //获取当前时间

	time1 = tv1.tv_sec * 1000000 + tv1.tv_usec;   //微秒级的时间
	time2  = tv2.tv_sec * 1000000 + tv2.tv_usec;

	dis = (float)(time2 - time1) / 1000000 * 34000 / 2;  //求出距离

	return dis;
}

int main(void)
{
	float dis;

	if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}
	if(softToneCreate(BuzPin) == -1){
		printf("setup softTone failed !");
		return 1; 
	}

	ultraInit();
	ledInit();  //led code
	while(1){
		dis = disMeasure();
		int idis = (int)dis;
		printf("%0.2f cm\n\n",dis);
		if(dis < 50)
		{
			ledColorSet(0+(idis*3),180-(idis*4),180-(idis*4)); //spectrum to red
			softToneWrite(BuzPin, 800-(idis*10)); //buzzer noise and frequency
			
		}
		else
		{
			ledColorSet(0xff,0x00,0xff); //green
			softToneWrite(BuzPin, 0);
		}
		delay(200);

		//ledColorSet(0xff,0x00,0xff); //green
		//ledColorSet(0x00,0xc5,0xcd); //red
	}

	return 0;
}
