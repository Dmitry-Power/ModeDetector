#ifndef UART_H
#define UART_H
#include <AbstractIO.h>

class UART : public AbstractIOasy
{
public:
	UART(unsigned int uartNum);
	virtual void Tx ( unsigned long data ) ;
	virtual void Tx (const  unsigned char* data, unsigned int sz );
	virtual unsigned long Rx () ;
	virtual bool IsRxReady () ;
	virtual bool IsTxReady () ;
	virtual void SetTxISRAddr ( unsigned long addr );
	virtual void SetRxISRAddr ( unsigned long addr );
	virtual  ~UART(){}
protected:
	void IntEnable(unsigned long addr);
	volatile unsigned char* buff;
	volatile unsigned char* lineStat;
	unsigned int  num;
};

#endif

