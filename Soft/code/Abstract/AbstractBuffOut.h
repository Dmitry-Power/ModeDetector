#ifndef  ABSTRACT_BUFF_OUT_H
#define ABSTRACT_BUFF_OUT_H

class AbstractBuffOut
{
protected:
	unsigned int buffSz;
	char* buff;
public:
	AbstractBuffOut(unsigned int sz){buffSz = sz; buff = new char[buffSz];}
	virtual bool Send(const char* inp, unsigned int size = 0) = 0;
	virtual bool Router () = 0;
	virtual ~AbstractBuffOut() {delete[] buff;};
};

#endif

