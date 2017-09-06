#include <iostream>  
using std::cout;

#include "log.h"   

#ifndef ERROR_LOG_H
#define ERROR_LOG_H

class ErrorLog : public Log
{
public:
	ErrorLog();
	~ErrorLog();
	virtual string SetLogFileName();
	virtual void WriteInFile(string textToSave);

};

#endif