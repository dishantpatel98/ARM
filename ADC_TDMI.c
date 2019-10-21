#include <LPC214x.h>
#include "LCD7TDMI.h"
#include <stdio.h>
#include <math.h>

void adc_init()
{
	PINSEL1|=(1<<28); //AD0.3 select
	AD0CR|=(1<<3)|(1<<16)|(1<<21); // Channel AD0.3 select, Burst enable, ADC operational/on
	AD0CR|=(0x0000FF00);	// CLKDIV = 0xFF
	//AD0INTEN|=(1<<3);
}

void send_string(unsigned char *ch)
{
		while(*ch!='\0')
		{
			send_data(*ch++);
		}
}

void delay_ms()
{
	for(unsigned int i=0; i<100; i++)
	for(unsigned int j=0; j<100; j++)
	{
	}
}

int main()
{
		unsigned int decval,i,data;
		float val; 
		unsigned char volt[16], dig[16];
		init_lcd();
		adc_init();
		while(1){
		send_cmd(0x01);
		send_cmd(0x80);
		while(!(AD0GDR & (1<<31)));
		data=AD0GDR;
		decval=(data>>6)&(0x3FF);
		sprintf(dig, "ADC Value=%d", decval);
		send_string(dig);
		val=decval*(3.3/1024);
		sprintf(volt, "Voltage=%.3fV", val);
		send_cmd(0xC0);
		send_string(volt);
		delay_ms();
	}
}