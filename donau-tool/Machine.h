#pragma once
#include "Component.h"
#include "Console.h"
#include <vector>
#include <string>
#include <iostream>
class Machine :
	public Component
{
	std::vector<std::string> args;
	const std::string local_scriptPath{ "/usr/share/donau-tool/machine" };
public:
	Machine(std::vector<std::string>);
	~Machine();

	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
	void execute();
};

