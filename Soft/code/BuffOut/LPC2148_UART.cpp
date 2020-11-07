#include <UART.h>
#include <LPC2148_UART_Regs.h>
#include <Service.h>
#include <LPC214x.h>

UART::UART(unsigned int uartNum)
{
	num = uartNum;
	if(num == 0)
	{
		PCfg(0, 0, 1);
		PCfg(0, 1, 1);
	}
	else
	{
		PCfg(0, 8, 1);
		PCfg(0, 9, 1); 
	}
	buff = UART_BUFFERS_REG[num];
	lineStat = UART_LSTAT_REG[num];
	*UART_LC_REG [num] = 0x8f;
	*UART_FDR_REG [num] = 0x7c;
	*UART_DLL_REG  [num] = 12; //115200	
	*UART_LC_REG    [num] = 3;
	*UART_FCR_REG [num] |= 0xc1; // fifo enable rx level = 14 characters
}

void UART::IntEnable(unsigned long addr)
{
	switch(num)
	{	
		case 0 : 
		{
			VICVectAddr6 = addr;
			VICVectCntl6 = 0x20 | 6;    
			VICIntEnable |= 0x00000040;
		}
		break;
		case 1 :
		{
			VICVectAddr7 = addr;
			VICVectCntl7 = 0x20 | 7;                     
			VICIntEnable |= 0x00000080;                   
		}		
	}
}

void UART::SetRxISRAddr ( unsigned long addr )	
{
	*UART_IE_REG[num] |=  5;
	IntEnable(addr);
}

void UART::SetTxISRAddr ( unsigned long addr )	
{
	*UART_IE_REG[num] |= 2;
	IntEnable( addr );
}


bool UART::IsRxReady()
{
	return ( (*lineStat & 1) ==  0 )? false : true;
}

void UART::Tx(unsigned long data)
{
	*buff = (unsigned char) data;
}

void UART::Tx (const  unsigned char* data, unsigned int sz ) 
{
	unsigned char tmp;
	for(int i = 0; sz > 0; --sz)
	{
		tmp =  (unsigned char) data[i++];
		*buff = tmp;
	}	
}

bool UART ::IsTxReady()
{
	return ((*lineStat & 1 << 5) ==  0)? false : true;
}
	
unsigned long UART::Rx()
{
	return (unsigned long) *buff;
}


