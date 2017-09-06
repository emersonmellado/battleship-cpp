#include <iostream>  
#include "log.h"   

#ifndef INFORMATION_LOG_H
#define INFORMATION_LOG_H

class InformationLog : public Log
{
public:
	InformationLog();
	~InformationLog();
	virtual string SetLogFileName();
	virtual void WriteInFile(string textToSave);
};

#endif