#ifndef BOARD_DEVICES_H
#define BOARD_DEVICES_H

#include <AbstractMetronome.h>
#include <AbstractBuffOut.h>
#include <AbstractBuffIn.h>
#include <AbstractPinOut.h>
#include <AbstractWordIn.h>

AbstractWordIn* GetVin_ADC();
AbstractWordIn* GetAC_ADC();
AbstractWordIn* GetDC_ADC();

AbstractPinOut* GetACLevLED0 ();
AbstractPinOut* GetACLevLED1 ();
AbstractPinOut* GetACLevLED2 ();
AbstractPinOut* GetACLevLED3 ();
AbstractPinOut* GetACLevLED4 ();
AbstractPinOut* GetACLevLED5 ();
AbstractPinOut* GetACLevLED6 ();
AbstractPinOut* GetACLevLED7 ();

AbstractPinOut* GetDCLevLED0 ();
AbstractPinOut* GetDCLevLED1 ();
AbstractPinOut* GetDCLevLED2 ();
AbstractPinOut* GetDCLevLED3 ();
AbstractPinOut* GetDCLevLED4 ();
AbstractPinOut* GetDCLevLED5 ();
AbstractPinOut* GetDCLevLED6 ();
AbstractPinOut* GetDCLevLED7 ();

AbstractPinOut* GetGreenLED ();
AbstractPinOut* GetYellowLED ();


AbstractBuffIn*  GetUARTrx0 ( );
AbstractBuffOut*  GetUARTtx0 ( );
AbstractBuffIn*  GetUARTrx1 ( );
AbstractBuffOut*  GetUARTtx1 ( );

AbstractMetronome* GetClocker();
void DelayMs(unsigned int ms);
void DelayUs(unsigned int us);

#endif
