#include "Console.h"



//Look familiar?
//
//Console may have different functions or the functions may work differently. Please check them before using!

Console::Console()
{
}


Console::~Console()
{
}

void Console::invokeCall(std::string command)
{
	system(command.c_str());
}

void Console::tryClearScreen()
{
	invokeCall("clear");
}

void Console::tryExecuteChmoddedScript(std::string scriptPath)
{
	invokeCall(scriptPath);
}

void Console::tryRemoveFile(std::string filePath)
{
	invokeCall("rm -rf \"" + filePath + "\"");
}

void Console::downloadFileWget(std::string URL, std::string location)
{
	invokeCall("wget -q \"" + URL + "\" -P \"" + location + "\"");
}

void Console::showNotification(std::string message, std::string icon = "") {
	invokeCall("notify-send \"" + message + "\" --icon=\"" + icon + "\"");
}