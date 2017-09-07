#include <iostream>
#include "informationLog.h" 

using std::cout;
using std::endl;

InformationLog::InformationLog() { }
InformationLog::~InformationLog() { }

string InformationLog::SetLogFileName() {
	return "information.dat";
}

void InformationLog::WriteInFile(string textToSave) 
{	
	FILE * logFile;
	logFile = fopen(SetLogFileName().c_str(), "a");
	fwrite(textToSave.c_str(), 1, textToSave.length(), logFile);
	fwrite("\n", sizeof(char), 1, logFile);
	fclose(logFile);
}