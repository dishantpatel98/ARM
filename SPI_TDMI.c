#include <LPC214X.H>

void spi_data(unsigned char data);

/*void spi_int(void) __irq
{
	static int flag;
	static int i;	
	S0SPINT=(1<<0);

	if(!(IO0SET&(1<<7)))
		IO0SET|=(1<<7);	
	if (flag == 0)	
	{
		IO0SET = 0x80000000;
		flag = 1;
	}
	else
	{
		IO0CLR = 0x80000000;
		flag = 0;
	}
	i=S0SPDR;
	i=S0SPSR;
	VICVectAddr = 0x00;
}*/

int main()
{
	int i, j;	
	PINSEL0|=(1<<8)|(1<<12);
	IO0DIR|=(1<<7)|(1<<6)|(0<<5)|(1<<4);
	S0SPCR|=(1<<5)|(1<<7);
	S0SPCCR=0x0E;
	IO0SET|=(1<<7);
	
	while(1)
	{
		spi_data(0xFF);
		for(i=0;i<10000;i++)
		{
			for(j=0;j<1000;j++)
			{
			}
		}	
		spi_data(0x00);
		for(i=0;i<10000;i++)
		{
			for(j=0;j<1000;j++)
			{
			}
		}
	}
		
}

void spi_data(unsigned char data)
{
	int i;
	IO0CLR|=(1<<7);
	S0SPDR=data;
	IO0SET|=(1<<7);
	i=S0SPDR;
	i=S0SPSR;
}