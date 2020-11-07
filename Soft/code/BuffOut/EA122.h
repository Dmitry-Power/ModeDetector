#ifndef EA122_H
#define EA122_H
#include <AbstractBuffOut.h>
#include <fonts_0D.h>

static const unsigned char LINES = 4;
static const unsigned char DISPLAY_LENGH = 122;

struct xEMaskY
{
	unsigned char xe;
	unsigned char lb;
	unsigned char le;
	unsigned long msk;
};


union bsl {
	unsigned char b[4];
	unsigned short w[2];
	unsigned long dw;
} ;

union dData {
	unsigned char bl[DISPLAY_LENGH][LINES];
	unsigned long dw [DISPLAY_LENGH];
} ;

class EA122
{
public:
	EA122();
	virtual int WriteStr(int x, int  y, const char* str, const int font, int pitch, bool isInverted);
	virtual void Erase();
	virtual ~EA122();
private:
	dData dD;
	unsigned char refXb, refXe, refYb, refY;
	void wr(unsigned char msb, unsigned char lsb);
	void clkLeft(void);
	void clkRight(void);
	void on(unsigned char isOn);
	void setPageLeft(unsigned char page);
	void setPageRight(unsigned char page);
	void setTopLine(unsigned char line);
	void setColumn(unsigned char column); 
	void dataWr(unsigned char x, unsigned char y, unsigned char data);	   
	void reset(void);
	void displayIni(void);
	char  eraseMtx(unsigned char xb, xEMaskY coord, bool isInverted);
	xEMaskY writeMtx(unsigned char x, unsigned char  y, const unsigned char* mtx, bool isInverted = false);
	void hardErase();
};

class StringOut_EA122 : public AbstractBuffOut
{
private:
	int xPos, yPos, ptchSz;
	FONT_SET fntType;
	bool IsInv;
	EA122* disp;
public:
	StringOut_EA122 (EA122* display, int x, int  y, FONT_SET font,  int pitch, bool isInverted);
	virtual bool Send(const char* inp, unsigned int size = 0);
	virtual bool Router () { return false;};
	virtual ~StringOut_EA122() {};	
};	

#endif
