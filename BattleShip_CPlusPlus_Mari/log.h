// Log abstract-base-class definition.
#include <string>

using std::string;

#ifndef LOG_H
#define LOG_H

class Log {

public:
	// pure virtual functions; overridden in derived classes.
	virtual string SetLogFileName() = 0;
	virtual void WriteInFile(string textToSave) = 0;
};

#endif

