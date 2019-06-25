#pragma once
#include "Component.h"
#include "Console.h"
#include <vector>
#include <string>
class Frauenbach :
	public Component
{
	std::string local_frauenbachPath{ "/usr/share/donau-tool/frauenbach/fbDE" };
public:
	Frauenbach();
	~Frauenbach();

	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
	void execute();
};

