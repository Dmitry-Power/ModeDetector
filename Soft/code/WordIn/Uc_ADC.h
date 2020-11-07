#ifndef UC_ADC_H
#define UC_ADC_H
#include <AbstractWordIn.h>

class UC_ADC : public AbstractWordIn
{
public:
	UC_ADC (unsigned char adcGroup, unsigned char adcChan);
	virtual  unsigned long  Read();
	virtual ~UC_ADC() {}
private:
	unsigned char adGr, adCh;
	volatile unsigned long*  dataRg;
};

#endif

