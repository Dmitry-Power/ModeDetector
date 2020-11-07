#include <Service.h>
#include <LPC214x.h>

void PCfg(unsigned char portNumM, unsigned char portNumL, unsigned char func)
{
	if (portNumM == 0)
	{
		if(portNumL < 16)
		{
			PINSEL0 &= ~(3 << portNumL * 2);
			PINSEL0 |= func << portNumL * 2;
		}
		else
		{
			portNumL -= 16;
			PINSEL1 &= ~(3 << portNumL * 2);
			PINSEL1 |= func << portNumL * 2;
		}
	}
	else if (portNumM == 1)
	{
		if (func == 0)
		{
			if(portNumL < 26)
				PINSEL2 &= ~(1 << 3);
			else
				PINSEL2 &= ~(1 << 2);
		}
		else if (func == 1 )
		{
			if(portNumL < 26)
				PINSEL2 |= 1 << 3;
			else
				PINSEL2 |= 1 << 2;
		}
	}		
}


// /////////////===============Timers

const unsigned long TMR0_BASE_ADDR = 0xE0004000;
const unsigned long TMR1_BASE_ADDR = 0xE0008000;
void  IntervalGenerator(unsigned char nT, unsigned int nClk, unsigned long isrAddr)
{
	unsigned long baseAddr;
	switch(nT)
	{	
		case 0 :
			baseAddr = TMR0_BASE_ADDR;		
			break;
		case 1 : 
			baseAddr = TMR1_BASE_ADDR;	
			break;
		default :
		break;	
	}	
	(*(volatile unsigned long *)(baseAddr + 0x04)) = 2;//T1TCR = 2; // Stop and reset timer.
	(*(volatile unsigned long *)(baseAddr + 0x0C)) = 0;//T1PR  = 0x00; // Set prescaler to zero.
	(*(volatile unsigned long *)(baseAddr + 0x18)) = nClk;//T1MR0 = nClk; // Set Value.
	(*(volatile unsigned long *)baseAddr) = 0xff;//T1IR  = 0xff; // Reset all interrrupt flags.
	(*(volatile unsigned long *)(baseAddr + 0x14)) = 3;//T1MCR = 3; // Timer reset and Interrupt

	switch(nT)
	{	
		case 0 : 
		{
			VICVectAddr4 = isrAddr;
		    VICVectCntl4 = 0x20 | 4;     // use it for Timer 0 Interrupt
		    VICIntEnable |= 0x00000010;  // Enable Timer0 Interrupt
		}
			break;
		case 1 :
		{
			VICVectAddr5 = isrAddr;
		    VICVectCntl5 = 0x20 | 5;                     
		    VICIntEnable |= 0x00000020;                   
		}
			break;
		default:
			break;
	}
	(*(volatile unsigned long *)(baseAddr + 0x04)) = 1;//T1TCR = 1;
}

void TimerStop(unsigned char nT)
{	
	switch(nT)
	{	
		case 0 :	T0TCR  = 0;
			break;
		case 1 : 	T1TCR  = 0;
			break;
		default:
			break;
	}
}

void TimerStart(unsigned char nT)
{
	switch(nT)
	{	
		case 0 :	T0TCR  = 1;
			break;
		case 1 : 	T1TCR  = 1;
			break;
		default:
			break;
	}
}
void TimerReset(unsigned char nT)
{
	switch(nT)
	{	
		case 0 :	T0TCR  = 2;
			break;
		case 1 : 	T1TCR  = 2;
			break;
		default:
			break;
	}
}

