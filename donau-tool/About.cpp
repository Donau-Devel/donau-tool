#include "About.h"



About::About() :
	Component()
{
}


About::~About()
{
	delete local_versionFile;
}

std::string About::giveReferenceName() {
	return "about";
}
std::string About::giveReferenceDescription() {
	return "View general information about your Donau Installation and donauctl.";
}
std::vector<std::string> About::giveReferenceHelp() {
	std::vector<std::string> helpData{ "This command takes no arguments." };
	return helpData;
}

void About::execute() {
	local_versionFile->parse();

	std::cout << "donau-tool\n";
	std::cout << "Manage your Donau Installation root-free.\n";
	std::cout << "Version: " << majorRelease << "." << minorRelease << "." << patchRelease << "\n";

	std::cout << "Donau Version " << local_versionFile->getFirstElementByName("version").getValue() << "\n";
}