#include <LPC214X.H>

/*
Master operation
The following sequence describes how one should process a data transfer with the SPI
block when it is set up to be the master. This process assumes that any prior data transfer
has already completed.
1. Set the SPI clock counter register to the desired clock rate.
2. Set the SPI control register to the desired settings.
3. Write the data to transmitted to the SPI data register. This write starts the SPI data
transfer.
4. Wait for the SPIF bit in the SPI status register to be set to 1. The SPIF bit will be set
after the last cycle of the SPI data transfer.
5. Read the SPI status register.
6. Read the received data from the SPI data register (optional).
7. Go to step 3 if more data is required to transmit.
*/

void delay(unsigned long time)
{
 	int i, j;
	for(i=0;i<1000;i++)
		for(j=0;j<time;j++);
}

void SPI_init()
{
	
	PINSEL0|=(1<<8)/*SCK*/|(1<<10)/*MISO but not used*/|(1<<12)/*MOSI*/;
	IO0DIR|=(1<<7);//Since Shift Register A;redy working in slave mode therefore no need to SSEL , insted using that pin for controlling ST_CP
	IO0SET|=(1<<7);//ST_CP is storage register clock pulse
	S0SPCR=0x00;
	S0SPCR|=/*Master Mode*/(1<<5)/*LSB first*/|(1<<6);///*Interrupt enabled*/|(1<<7);
	S0SPCCR=0x0F;//As this input must be grater than 8 and a even number
	S0SPINT=(1<<0);
}

void SPI_data(unsigned char data)
{
	IO0SET|=(1<<7);//to shift the data from storage reg of IC
	S0SPDR=data;//data
	while(!(S0SPSR&(1<<7)));//chesecking status if data is ready and transfer is complete
	IO0CLR|=(1<<7);//to shift the data from storage reg of IC
}

int main()
{
	SPI_init();
	while(1)
	{
	SPI_data(0x55);
	delay(10000);
	SPI_data(0xAA);
	delay(10000);
	}
}
