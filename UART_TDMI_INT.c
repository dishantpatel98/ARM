#define CR 0x0D
#include<lpc214x.h>
void uart1_isr(void)__irq;
void init_serial(void);
void transmit (int ch);
char  receive (void);
unsigned char test;
void Interrupt_init(void);
char ch;
int main(void)
	{	 char x;
				//char Ptr[]="Hell0 World";
		  
				VPBDIV=0x02;
				init_serial();
       Interrupt_init();
		   
		
		while(1);
		
		
		/*char *ptr1="Hello Dishant\n\r";
char *ptr2="Patel";	

while(*ptr1){
transmit(*ptr1);
	ptr1++;
}

while(*ptr2){
transmit(*ptr2);
	ptr2++;
}
*/


	}
	
	void Interrupt_init(){
	
VICIntEnable=(1<<7); //To enable the UART1

VICVectCntl0=0x20|7;

U1IER=0x01;             //To specify wether to enable uart transmitter or receiver    
	VICVectAddr0=(unsigned long)uart1_isr;
	
	
	}

void init_serial(void)	
			{
					PINSEL0|=(1<<16)|(1<<18);	
					U1LCR=0x00000083;                            //(1<<7)|(1<<0)|(1<<1);
					U1DLL = 183;                                
					U1LCR=0x00000003;                                    //(~(1<<7))|(1<<0)|(1<<1);	
					U1FDR=0xF1; 
					U1FCR=0x01;															//(1<<0);															
				  U1TER|=0x80;  				//(1<<7);
		      
			}

void uart1_isr(void)__irq
{	
	static int i=0;
		
		if(i==0)
		{
			i=1;
			ch=receive();
		}
		else
		{
			i=0;
			transmit(ch);
		}
		VICVectAddr=0x00;
				
}


			
			
			
			void transmit( int ch )
{
		//if (ch=='\n')
			//{	
				//while(!(U1LSR&(1<<5)));
			//	U1THR= CR;				//enter ASCII value
		//	}
				
					while(!(U1LSR&(1<<5))){
					
					}
					 U1THR=ch; //data
	
			
}

char receive ()
{ 
	while( !(U1LSR&(1<<0)));
	return U1RBR;
	
}
 
 