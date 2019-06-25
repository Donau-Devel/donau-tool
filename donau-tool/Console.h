#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

//Look familiar?
//
//Console may have different functions or the functions may work differently. Please check them before using!

class Console
{
public:
	Console();
	~Console();
	static void invokeCall(std::string);
	static void tryClearScreen();
	static void tryExecuteChmoddedScript(std::string);
	static void tryRemoveFile(std::string);
	static void downloadFileWget(std::string, std::string);
	static void showNotification(std::string, std::string);
};

