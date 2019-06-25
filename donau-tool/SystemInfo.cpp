#include "SystemInfo.h"



SystemInfo::SystemInfo() :
	Component()
{
	file = new EqualsFileInterpreter::EqualsDocument(informationFile);

	window = new BoxMake::Box("About Donau", BoxMake::bm_information);
}


SystemInfo::~SystemInfo()
{
	delete file;
	delete window;
}

std::string SystemInfo::giveReferenceName()
{
	return "systeminfo";
}

std::string SystemInfo::giveReferenceDescription()
{
	return "Brings up a GTK+ window with System Information.";
}

std::vector<std::string> SystemInfo::giveReferenceHelp()
{
	std::vector<std::string> helpData{ "This command takes no arguments." };
	return helpData;
}

void SystemInfo::execute()
{
	file->parse(true);
	
	std::vector<std::string> infoData{ file->getTagByName("NAME").getContent(), "Version " + file->getTagByName("VERSION_ID").getContent(), "\n", "Visit " + file->getTagByName("HOME_URL").getContent() + " for more information.", "\n", file->getTagByName("NOTE").getContent() };
	window->setContent(infoData);
	window->show();
}