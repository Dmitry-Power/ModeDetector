#include <BoardDevices.h>
#include <stdio.h>
#include <string.h>

const char ENTER [] ={10, 13, 0};
int GetACpp( int qva)
{                                     		   0        1     2        3      4       5       6       7        8        9
	static const int Q_VS_UV[] = { 768,   766,  761,  753,  742,  728,  709,  689,   668,  645,
													621,   596,   571,  547, 523,  498,  475,   452,  430,  409,
													424,   403,   382,  363, 344,   322, 307,   290,  273,  257,
													241,   226,   211,  197, 182,   169, 155,   142,  129,  117,
													105,   93,       81,    69,   59,     48,   37,     27,   16,	  7,    5, 0};
													
	static const int FACTOR = ( 1000 * 47 ) / (120 + 47); //uVpp on input AD8314 per mVpp out of GSS120 
	int  ret;
	bool isCmp = false;										  
	int i;
	for(  i  = 0; i < 50 && isCmp == false;)
		isCmp = ( qva > Q_VS_UV[i++] )? true : false;
	--i;												
	if( i > 0 && i < 50 )	
		ret = FACTOR * i  - (FACTOR  * (qva -  Q_VS_UV[i])) / ( Q_VS_UV[i-1] - Q_VS_UV[i]);
	else
		ret = i * FACTOR;	
	return ret; // uVpp on input AD8314
}

int main ()
{
	AbstractBuffOut* utx	= GetUARTtx0();
	AbstractPinOut* dcLeds[] = { GetDCLevLED0(), GetDCLevLED1(), GetDCLevLED2(), GetDCLevLED3(), GetDCLevLED4(), GetDCLevLED5(), GetDCLevLED6(), GetDCLevLED7()};
	AbstractPinOut* acLeds[] = { GetACLevLED0(), GetACLevLED1(), GetACLevLED2(), GetACLevLED3(), GetACLevLED4(), GetACLevLED5(), GetACLevLED6(), GetACLevLED7()};
	AbstractPinOut* yellowLed = GetYellowLED();
	AbstractPinOut* greenLed = GetGreenLED();

	AbstractWordIn* adVin = GetVin_ADC();
	AbstractWordIn* adDC = GetDC_ADC();
	AbstractWordIn* adAC = GetAC_ADC();

	char buf[256];
	int qAC, vAC , qDC, vDC, tmp, vPovIn;
	int acVsDc;
	while (true)
	{
		qDC = 0;
		qAC = 0;
		for(int i = 0; i <1000; ++i)
		{ 
			DelayUs(500);
			qDC += (int) adDC->Read();
			DelayUs(500);
			tmp = (int)adAC->Read();
			qAC = ( tmp > qAC )? tmp : qAC;
		}
		vAC = GetACpp(qAC );
		vDC =  (3000 * (qDC  / 1024)) / 31; // vDC uV on input ad8541

		if ( qDC > 5000)
		{
			if ( vAC > vDC)
				acVsDc = 100;
			else
				acVsDc = 100 * vAC  / ( 2 * vDC );
		}
		else
			acVsDc = 0;
		qDC /= 1000;
		for (int i = 0; i < 8; ++i)
		{
			acLeds[i]->Send( (acVsDc > ( i + 1) * 2 )? true : false );
			dcLeds[i]->Send( (qDC > 113 * (i +1) )? true : false);
		}
		vPovIn = (int) adVin->Read() * 6000 / 1023;
		yellowLed->Send ( ( vAC > 750 )? true : false); 
		sprintf ( buf, " Vin = %dmV    qDc = %d = %duV, qAC = %d = %duV,  ACvsDC %d ", 
										vPovIn,         qDC,      vDC,          qAC,  vAC,          acVsDc ); 
		strcat( buf, ENTER);
		utx->Send( buf); 
		if(vPovIn > 4100)
			greenLed->Toggle();
		else
			greenLed->Clear();
	}
}

