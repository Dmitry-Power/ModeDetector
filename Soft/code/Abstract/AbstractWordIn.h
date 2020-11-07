//E:\d2\www\2013Proj\soft\Abstract\AbstractWordIn.h
#ifndef ABSTRACT_WORD_IN_H
#define ABSTRACT_WORD_IN_H

class AbstractRO
{
protected:
	int val;
public:	
	virtual int Read() {return val;}
	virtual ~AbstractRO(){}
};

class AbstractWordIn
{
public:
	virtual  unsigned long  Read() = 0 ;
	virtual  ~AbstractWordIn(){}
};
#endif





