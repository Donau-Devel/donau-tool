#include <iostream>
#include <string>
#include <vector>

#include "Component.h"
#include "ControlPanel.h"
#include "Machine.h"
#include "SystemUpdateChecker.h"
#include "About.h"
#include "SystemInfo.h"

//Look familiar?
//
//Yes, this code was ported from donauctl, alongside the component system.
//It works the same way, so if you know how to use donauctl, you will be able to use donau-tool pretty easily too.
//
//Differences:
//* Console may have different functions or the functions may work differently. Please check them before using!
//* donau-tool is meant for all users, thus everything here should be written in such context.

//ToDo: Rework this entire area, use Trie for component lookup

int main(int argc, char* argv[]) {
	std::vector<std::string> args;
	for (unsigned int i = 0; i < argc; i++)
	{
		args.resize(args.size() + 1);
		args.at(args.size() - 1) = argv[i];
	}

	if (args.size() < 2) {
		std::cout << "Type \'donau-tool help\' for help." << "\n";
		return 0;
	}

	std::vector<Component *> availableComponents{ new ControlPanel(), new Machine(args), new SystemUpdateChecker(), new About(), new SystemInfo() };
	if (args.at(1) == "help") {
		if (args.size() < 3) {
			for (Component* c : availableComponents) {
				std::cout << "================================\n";
				c->help();
				std::cout << "================================\n\n";
			}
		}
		else {
			for (unsigned int i = 0; i < availableComponents.size(); i++)
			{
				if (args.at(2) == availableComponents.at(i)->giveReferenceName()) {
					availableComponents.at(i)->help();
					break;
				}
			}
		}

		return 0;
	}
	
	for (unsigned int i = 0; i < availableComponents.size(); i++)
	{
		if (args.at(1) == availableComponents.at(i)->giveReferenceName()) {
			availableComponents.at(i)->execute();
			//Maybe add a function that kills all instances here?
			return 0;
		}
	}

	std::cout << "The component you entered is not valid." << "\n";
		
	return 0;
}