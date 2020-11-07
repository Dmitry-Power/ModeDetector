#ifndef ABSTRACT_METRONOME_H
#define ABSTRACT_METRONOME_H

class  AbstractMetronome
{
public:
	virtual bool CheckAndRun (unsigned int timeUs) = 0;
	virtual bool IsOver() = 0;
	virtual void Start (unsigned int timeUs) = 0;


	virtual ~AbstractMetronome() {}
protected:
	bool isStarted;
};

class  AbstractPWM
{
public:
	virtual void SetD (unsigned int dy) = 0;
	virtual void SetT (unsigned int prd) = 0;
	virtual void SetTD (unsigned int prd, unsigned int dy) = 0;
	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual ~AbstractPWM() { }
protected:
	unsigned int period;
	unsigned int duty;
};

class AbstractPWM_Lim : public AbstractPWM
{
protected:
    unsigned int resi; 
public: 
    virtual void Start() = 0;
		virtual unsigned int Suspend(){Stop(); return resi;}
    virtual void Goo(unsigned int n) = 0;
    virtual unsigned int GetResidue() = 0;
    virtual void IntRoutine() = 0;
    virtual ~AbstractPWM_Lim(){};
};


class AbstractResetCalculator
{
public:
	virtual bool GetWdtNum(unsigned int& num) = 0;
	virtual  bool GetAnyRstNum (unsigned int& num) = 0;
	virtual void ResetCounters() = 0;	
	virtual ~AbstractResetCalculator(){}
};


#endif

