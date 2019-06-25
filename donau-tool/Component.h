#pragma once
#include <iostream>
#include <vector>
#include <string>
class Component
{
public:
	Component();
	~Component();

	virtual std::string giveReferenceName() = 0;
	virtual std::string giveReferenceDescription() = 0;
	virtual std::vector<std::string> giveReferenceHelp() = 0;
	virtual void execute() = 0;

	void help();
};

