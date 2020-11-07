#include <UC_ADC.h>
#include <LPC2148_ADC_Regs.h>

UC_ADC::UC_ADC( unsigned char adcGroup, unsigned char adcChan)
{
	adGr = adcGroup;
	adCh = adcChan;
	if(adGr == 0)
	{
		AD0CR &= ~(1 << 21); //PowerDown mode	
		AD0CR &= ~0xff00;
		AD0CR |= 14 << 8;// 4MHz work adcClock at 60 MHz input ADCClock 
		AD0CR &= ~0xf0000;
		AD0CR |= 1 << 16;// burst conversion 10bit
		AD0CR &= ~(7 << 26);//START == 000
		AD0CR |= 1 << 21; //PowerON
		AD0CR |= 1 << adCh;		
		dataRg = ADC0_DATA_REGS[adCh];
	}
	else 	if(adGr == 1)
	{
		AD1CR &= ~(1 << 21); //PowerDown mode	
		AD1CR &= ~0xff00;
		AD1CR |= 14 << 8;// 4MHz work adcClock at 60 MHz input ADCClock 
		AD1CR &= ~0xf0000;
		AD1CR |= 1 << 16;// burst conversion 10bit
		AD1CR &= ~(7 << 26);//START == 000
		AD1CR |= 1 << 21; //PowerON
		AD1CR |= 1 << adCh;		
		dataRg = ADC1_DATA_REGS[adCh];
	}
}

unsigned long UC_ADC::Read()
{
	return (*dataRg >> 6) & 0x3ff;
}

