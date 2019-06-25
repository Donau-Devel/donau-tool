#pragma once
#include "Component.h"
#include "donau-XMLParseDX.h";
#include <iostream>
#include <string>

using namespace DonauUtils::XMLParseDX;
class About :
	public Component
{
public:
	About();
	~About();

	//Version numbers
	int majorRelease{ 0 };
	int minorRelease{ 1 };
	int patchRelease{ 2 };

	XMLDocument* local_versionFile = new XMLDocument("/lib/donauctl/sysupdate/local-version.xml");

	void execute();
	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
};

