#include "Component.h"


Component::Component()
{
}


Component::~Component()
{
}

void Component::help()
{
	std::cout << "Name:\t\t" << giveReferenceName() << "\n";
	std::cout << "Description:\t" << giveReferenceDescription() << "\n\n";

	std::cout << "Arguments:\n";
	for (int i = 0; i < giveReferenceHelp().size(); i++)
	{
		std::cout << giveReferenceHelp().at(i) << "\n";
	}
}