#include<reg51.h>
// P2 data lines
// P1 display enable swithches
int k=0;
unsigned char A[10]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F} ;
int Cntr=0;
void Timer0_ISR() interrupt 1
{

	TR0 = 0;
	TH0= 0xFC;
	TL0= 0x74;
	TF0 = 0;
	TR0 = 1;
	if(Cntr>500)
	{
			k++;
		if(k>=10)
		{
			k=0;
		}
		P2  = ~A[k];
	}
	else
	{
		Cntr++;
	}
}


void main()
{
	
	// initiate timer in mode 1 timer 0
	TMOD = 0x01;/*0b00000000*/
	TH0= 0xFC;
	TL0= 0x74;
	EA  = 1;         	/* Enable global interrupt */
	ET0 = 1; 
	TR0 = 1;//start timer 0
	P1= 0; // enable all 7 seg display
	while(1)
	{
		;
	}
	
}