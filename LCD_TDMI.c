#include "C:\Users\DESD\Documents\ARM_PROGRAMS\LCD_TDMI\LCD7TDMI.h"
 
 void call ()
 {
	
 
 
 }
int main()
{ int i=0;
	char A[]="JAI JAI GARAVI GUJARAT";
	init_lcd();
	
	send_cmd(0x80);
	//send_cmd(0xc0);
	for (i=0;i<15;i++)
	{
		send_data(A[i]);
	}
	send_cmd(0xc0);
	for (i=15;i<31;i++)
	{	
		if (A[i]=='\0')
		{
			break;
		}
		else 
			{
				send_data(A[i]);
			}
	}
	//send_cmd(0x01);
}

