#include "ControlPanel.h"



ControlPanel::ControlPanel() :
	Component()
{
}


ControlPanel::~ControlPanel()
{
}

std::string ControlPanel::giveReferenceName()
{
	return "control";
}

std::string ControlPanel::giveReferenceDescription()
{
	return "Make changes to your System via a Graphical Interface.";
}

std::vector<std::string> ControlPanel::giveReferenceHelp()
{
	std::vector<std::string> helpData{ "This command takes no arguments." };
	return helpData;
}

void ControlPanel::execute()
{
	Console::tryExecuteChmoddedScript(local_controlPanelLaunchPath);
}