#pragma once
#include "Component.h"
#include "Console.h"
#include <vector>
#include <string>
class ControlPanel :
	public Component
{
	const std::string local_controlPanelWorkPath{ "/usr/share/donau-tool/control" };
	const std::string local_controlPanelLaunchPath{ local_controlPanelWorkPath + "/fbCP" };
	const std::string local_controlPanelItemsPath{ local_controlPanelWorkPath + "/components" };
public:
	ControlPanel();
	~ControlPanel();

	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
	void execute();
};

