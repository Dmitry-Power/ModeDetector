#include <BuffIn.h>
#include <lpc24xx.h>

BuffInTxt::BuffInTxt(AbstractIOasy* ifc, unsigned int size, char endSymb, unsigned long addr) : AbstractBuffIn(size)
{
	iIfc = ifc;
	wrPos = rdPos = 0;
	terminator = endSymb;
	fifoRd  = fifoWr = 0;
	if(addr != 0)
		iIfc->SetRxISRAddr(addr);
}

unsigned int BuffInTxt::Get(char* data)
{
	unsigned int ret;
	if(fifoRd == 0)
		ret = 0;
	else
	{	
		 int ePos = fifoRd->GetPos();
		unsigned int posIn, posOut;
		if(ePos < rdPos)
		{
			unsigned int first  = buffSz - rdPos;
			posIn = buffSz;
			for (posOut  = first; posOut > 0;)
				data[--posOut] = buff[--posIn];
			ret = posOut = first +  ePos;
			for ( posIn = ePos; posIn > 0;)
				data[--posOut] = buff[--posIn];
		}
		else
		{
			ret = posOut = ePos - rdPos; 
			for(posIn = ePos; posOut  > 0 ;)
				data[--posOut] = buff[--posIn];
		}
		rdPos = ePos;
		TerminatorList * tmp = fifoRd;
		fifoRd = fifoRd->GetNext();
		delete 		tmp;	
	}
	return ret;
}

void BuffInTxt::Router()
{
	char symb;
	while(iIfc->IsRxReady() != false)
	{
		symb = iIfc->Rx();
		if (symb == terminator)
		{
			TerminatorList* tmp;
			if( fifoRd != 0 )			
			{
				tmp = new TerminatorList ( wrPos, fifoWr, 0 );
				fifoWr->SetNext ( tmp );
				fifoWr = tmp;
			}
			else
			{
				fifoWr = new TerminatorList (wrPos, 0, 0);
				fifoRd = fifoWr;
			}			
		}
		else if(symb >= PRINTABLE)
		{
			buff[wrPos++] = symb;
			wrPos %= buffSz;
		}
	}	
}

unsigned int  BuffInTxt::EchoRouter(char* inp)
{
	char symb;
	unsigned int ret = 0;
	while(iIfc->IsRxReady() != false)
	{
		symb = iIfc->Rx();
		inp[ret++] = symb;
		if (symb == terminator)
		{
			TerminatorList* tmp;
			if(fifoRd != 0)			
			{
				tmp = new TerminatorList(wrPos, fifoWr, 0);
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         		fifoWr->SetNext(tmp);
				fifoWr = tmp;
			}
			else
			{
				fifoWr = new TerminatorList (wrPos, 0, 0);
				fifoRd = fifoWr;
			}			
		}
		else if(symb >= PRINTABLE)
		{
			buff[wrPos++] = symb;
			wrPos %= buffSz;
		}
	}		
	return ret;
}

