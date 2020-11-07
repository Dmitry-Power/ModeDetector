#include <BoardDevices.h>
#include <Metronome.h>
#include <BuffIn.h>
#include <BuffOut.h>
#include <UART.h>
#include <PinOut.h>
#include <Service.h>
#include <LPC214x.h>

#include <UC_ADC.h>



AbstractWordIn* GetVin_ADC()
{
	PCfg(0, 15, 3);
	static UC_ADC ad(1, 5);
	return &ad;
}

AbstractWordIn* GetAC_ADC()
{
	PCfg(0, 12, 3);
	static UC_ADC ad(1, 3);
	return &ad;
}

AbstractWordIn* GetDC_ADC()
{
	PCfg(0, 13, 3);
	static UC_ADC ad(1, 4);
	return &ad;
}


AbstractPinOut* GetGreenLED ()
{
	static PinOut p (1, 27);
	return &p;	
}
AbstractPinOut* GetYellowLED ()
{
	static PinOut p (1, 28);
	return &p;	
}

AbstractPinOut* GetDCLevLED7 ()
{
	static PinOut p (0, 9);
	return &p;	
}

AbstractPinOut* GetDCLevLED6 ()
{
	static PinOut p (0, 8);
	return &p;	
}

AbstractPinOut* GetDCLevLED5 ()
{
	static PinOut p (0, 7);
	return &p;	
}

AbstractPinOut* GetDCLevLED4 ()
{
	static PinOut p (0, 5);
	return &p;	
}

AbstractPinOut* GetDCLevLED3 ()
{
	static PinOut p (0, 28);
	return &p;	
}

AbstractPinOut* GetDCLevLED2 ()
{
	static PinOut p (0, 29);
	return &p;	
}

AbstractPinOut* GetDCLevLED1 ()
{
	static PinOut p (0, 22);
	return &p;	
}

AbstractPinOut* GetDCLevLED0 ()
{
	static PinOut p (0, 21);
	return &p;		
}

AbstractPinOut* GetACLevLED7 ()
{
	static PinOut p (1, 21);
	return &p;	
}

AbstractPinOut* GetACLevLED6 ()
{
	static PinOut p (1, 22);
	return &p;	
}

AbstractPinOut* GetACLevLED5 ()
{
	static PinOut p (1, 23);
	return &p;	
}

AbstractPinOut* GetACLevLED4 ()
{
	static PinOut p (1, 24);
	return &p;	
}

AbstractPinOut* GetACLevLED3 ()
{
	static PinOut p (1, 25);
	return &p;	
}

AbstractPinOut* GetACLevLED2 ()
{
	static PinOut p (1, 31);
	return &p;	
}

AbstractPinOut* GetACLevLED1 ()
{
	static PinOut p (1, 17);
	return &p;	
}

AbstractPinOut* GetACLevLED0 ()
{
	static PinOut p (1, 18);
	return &p;	
}


AbstractMetronome* GetClocker()
{
	static Metronome m(0, 0);
	return &m;
}

void DelayMs(unsigned int ms)
{
	GetClocker()->Start(1000 * ms) ;
	while ( GetClocker()->IsOver() == false)
	{
	}
}

void DelayUs(unsigned int us)
{
	
	GetClocker()->Start(us) ;
	while ( GetClocker()->IsOver() == false)
	{
	}
}

__irq void UART0_Isr(void);
__irq void UART1_Isr(void);

static  AbstractIOasy*  GetU0()
{
	static UART u0 (0);
	return &u0;
}

static  AbstractIOasy*  GetU1()
{
	static UART u1 (1);
	return &u1;
}


AbstractBuffOut* GetUARTtx0()
{
	static BuffOut bo0 (GetU0(), 128, (unsigned long) UART0_Isr);
	return &bo0;
}

AbstractBuffOut* GetUARTtx1()
{
	static BuffOut bo1 (GetU1(), 256, (unsigned long) UART1_Isr);
	return &bo1;
}


AbstractBuffIn* GetUARTrx0 ( )
{
	static BuffInTxt bi0(GetU0(),  512, 13, (unsigned long) UART0_Isr);
	return &bi0;
}

AbstractBuffIn* GetUARTrx1()
{
	static BuffInTxt bi1(GetU1(),  128, 13, (unsigned long) UART1_Isr);
	return &bi1;
}


__irq void UART0_Isr(void)
{		
	unsigned short iSrc = U0IIR & 0xf;
	
	if ( ( iSrc == 4 ) || ( iSrc == 0xc )  ) 	
	{
		GetUARTrx0 ( )->Router();
	}
	else if ( iSrc == 2 )	
		GetUARTtx0 ()->Router();
	else if ( iSrc == 6 )
		unsigned long tmp = U0LSR;	
	VICVectAddr = 0;
}

__irq void UART1_Isr(void)
{	
	unsigned short iSrc = U1IIR & 0xf;
	if ( ( iSrc == 4 ) || ( iSrc == 0xc )  ) 	
		GetUARTrx1()->Router();
	else if ( iSrc == 2 )	
		GetUARTtx1()->Router();	
	else if ( iSrc == 6 )
		unsigned long tmp = U1LSR;
	VICVectAddr = 0;
}
