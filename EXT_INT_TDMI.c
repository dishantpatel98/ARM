#include <LPC214X.H>

void ext_int()
{
	IO1DIR= (1<<25);
	IO0DIR=(1<<31); // SET THE DIRECTION OF THE BUZZER is 25 and LED is 31
	VPBDIV = 0x00;  		//VPBDIV GIVES US FREQUENCY WE CAN DIVIDE IT BY CHANGES ITS VALUE
	PINSEL0 = (1<<31);		//SELECT EXTERNAL INTERRUPT PIN
	EXTMODE = (1<<2);				//FOR LEVEL  TRIGGER OR EDGE  TRIGGER OF PARTICULER EINT 2 
	EXTPOLAR = (1<<2);			//CHANGE  ITS POLAIRTY WEATHER RISING EDGE OR FALLING EDGE (INTIALLY IT HAS FALLING EDGE )
	EXTINT = (1<<2);			
}

void External_int(void)__irq          //INTERRUPT SERVICE ROUTINE 
	
  {
	static int i=0;
	
	if(i==0)
	{
		i=1;
		IO1CLR=(1<<25);
		IO0CLR=(1<<31);
		
	}
	else
	{
		i=0;
		IO1SET=(1<<25);
		IO0SET=(1<<31);
	}
	EXTINT |= (1<<2);
	VICVectAddr = 0x00;
}

void int_init()
{
	VICIntEnable = (1<<16);      //ENABLE PARTICULAR SLOT OF INTERRUPT  	
	VICVectCntl0 = 0x20 | 0x10;			//ENABLE INTERRPUT WHERE FIRST FIVE BITS ARE USE FOR 0-32 INTERRUPT WHERE AS 5 BIT IS SET MEANS PARTICULAR TO INTERRUPT IS ACTIVATED   
	VICVectAddr0 = (unsigned)External_int;     // ASSIGNE THE ADDRESS OF THE FUNCTION TO THE PARTIULAR VICvectaddress
}

int main(void)
{
	ext_int();
	int_init();
	while(1);
}
