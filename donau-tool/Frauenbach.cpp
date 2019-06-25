#include "Frauenbach.h"



Frauenbach::Frauenbach() :
	Component()
{
}


Frauenbach::~Frauenbach()
{
}

std::string Frauenbach::giveReferenceName()
{
	return "frauenbach";
}

std::string Frauenbach::giveReferenceDescription()
{
	return "Force launch the Frauenbach Desktop.";
}

std::vector<std::string> Frauenbach::giveReferenceHelp()
{
	std::vector<std::string> helpData{ "This command takes no arguments." };
	return helpData;
}

void Frauenbach::execute()
{
	Console::tryExecuteChmoddedScript(local_frauenbachPath);
}