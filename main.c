#include<reg51.h>
sbit D1 =P1^4;
sbit D2 =P1^5;
sbit D3 =P1^6;
sbit D4 =P1^7;

sbit ExPin = P1^1;

//#define Display1On() {D1=1;D2=0;D3=0;D4=0;}
//#define Display2On() {D1=0;D2=1;D3=0;D4=0;}
//#define Display3On() {D1=0;D2=0;D3=1;D4=0;}
//#define Display4On() {D1=0;D2=0;D3=0;D4=1;}
#define Display1On() {D1=0;D2=1;D3=1;D4=1;}
#define Display2On() {D1=1;D2=0;D3=1;D4=1;}
#define Display3On() {D1=1;D2=1;D3=0;D4=1;}
#define Display4On() {D1=1;D2=1;D3=1;D4=0;}
int k=0;
unsigned char A[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F} ;
int Value[4];
int Digit=0;
int counter=0;	
int p=1;
void Timer0_ISR() interrupt 1
{
	ExPin = ~ExPin;
	switch(p)
	{
		case 1:p++;
					Display1On();
					P2= ~A[Value[0]];
			break;
		case 2:p++; 
					Display2On();
					P2= ~A[Value[1]];
		break;
		case 3:p++;
					Display3On();
					P2= ~A[Value[2]];
					
	
		break;
		case 4:p=1;
		Display4On();
					P2= ~A[Value[3]];	
		break;
		
	}
	
//	Display1On();
//					P2= ~A[Value[0]];
//	Display2On();
//					P2= ~A[Value[1]];
//	Display3On();
//					P2= ~A[Value[2]];
//	Display4On();
//					P2= ~A[Value[3]];	
	TR0 = 0;
	TH0= 0x00;
	TL0= 0x02;
	TF0 = 0;
	TR0 = 1;
	
	
	
}
//void delay()
//{
//	int i=0;
//for(i=0;i<1080;i++)	
//	{
//		TH0= 0xE3;
//		TL0= 0x14;
//		TR0 = 1;//start timer 0
//		while(TF0==0);
//		

//	}
//}

void delay()
{
	int i=0,j=0;
	for(i=0;i<400;i++)
		for(j=0;j<200;j++);
}

void main()
{
	TMOD = 0x01;/*0b00000000*/
	TH0= 0xAA;
	TL0= 0xFF;
	EA  = 1;         	/* Enable global interrupt */
	ET0 = 1; 
	TR0 = 1;//start timer 0
	D1=0;
	while(1)
	{
		
		if(counter>9999)
		{
			
			counter =0;
		}
		delay();
		
		Value[0] = counter%10;
		Value[1] = (counter/10)%10;
		Value[2] = (counter/100)%10;
		Value[3] = (counter/1000)%10;
		counter++;
		/*
				k++;
				if(k>=10)
				{
					k=0;
				}
				P2  = ~A[k];*/

	}
	
}