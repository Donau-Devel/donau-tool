#include "Machine.h"



Machine::Machine(std::vector<std::string> args) :
	Component()
{
	this->args = args;
}


Machine::~Machine()
{
}

std::string Machine::giveReferenceName()
{
	return "machine";
}

std::string Machine::giveReferenceDescription()
{
	return "Session options.";
}

std::vector<std::string> Machine::giveReferenceHelp()
{
	std::vector<std::string> helpData{ "shutdown", "Shuts down the machine.", "reboot", "Restarts the machine.", "logout", "Logs out the current user." };
	return helpData;
}

void Machine::execute() {
	if (args.size() < 3) {
		std::cout << "Type \'donau-tool help machine\' for help." << "\n";
		return;
	}

	if (args.at(2) == "shutdown") {
		Console::tryExecuteChmoddedScript(local_scriptPath + "/_shutdown.sh");
		return;
	}

	if (args.at(2) == "reboot") {
		Console::tryExecuteChmoddedScript(local_scriptPath + "/_reboot.sh");
		return;
	}

	if (args.at(2) == "logout") {
		Console::tryExecuteChmoddedScript(local_scriptPath + "/_logout.sh");
		return;
	}

	std::cout << "Type \'donau-tool help machine\' for help." << "\n";
}