#include <iostream>

using std::cout;
using std::endl;

#include "errorLog.h" 

ErrorLog::ErrorLog() { }
ErrorLog::~ErrorLog() { }

string ErrorLog::SetLogFileName() {
	return "error.dat";
}

void ErrorLog::WriteInFile(string textToSave) {
	FILE * logFile;
	logFile = fopen(SetLogFileName().c_str(), "a");
	fwrite(textToSave.c_str(), 1, textToSave.length(), logFile);
	fwrite("\n", sizeof(char), 1, logFile);
	fclose(logFile);
}