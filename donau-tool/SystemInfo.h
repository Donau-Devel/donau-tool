#pragma once
#include "Component.h"
#include "EqualsFileInterpreter.h"
#include "donau-BoxMake.h"
#include <vector>
#include <string>
using namespace DonauUtils;
class SystemInfo :
	public Component
{
	const std::string informationFile{ "/usr/lib/donau-release" };
	EqualsFileInterpreter::EqualsDocument* file;
	BoxMake::Box* window;
public:
	SystemInfo();
	~SystemInfo();

	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
	void execute();
};

