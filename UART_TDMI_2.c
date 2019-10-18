#define CR 0x0D
#include<lpc214x.h>

void init_serial(void);
void transmit (int ch);
char  receive (void);
unsigned char test;

int main(void)
	{	 char x;
				//char Ptr[]="Hell0 World";
		  char c = 'd';
				VPBDIV=0x02;
				init_serial();
				while(1)
						{ 
						
								
							//		transmit(getchar());
										x=receive();
									transmit(x);
								 
						}
	}

void init_serial(void)	
			{
					PINSEL0|=(1<<16)|(1<<18);	
					U1LCR=0x00000083;                            //(1<<7)|(1<<0)|(1<<1);
					U1DLL = 183;                                
					U1LCR=0x00000003;                                    //(~(1<<7))|(1<<0)|(1<<1);	
					U1FDR=0xF1;                                   //(1<<0);															
				  U1TER|=0x80;                                   //(1<<7);
		
			}


void transmit( int ch )
{
		//if (ch=='\n')
			//{	
				//while(!(U1LSR&(1<<5)));
			//	U1THR= CR;				//enter ASCII value
		//	}
				
					while(!(U1LSR&(1<<5)));
					 U1THR=ch; //data
				
			
}

char receive ()
{ unsigned char ch;
	while( !(U1LSR&(1<<0)));
	ch = U1RBR;
	return ch;
}
 
 