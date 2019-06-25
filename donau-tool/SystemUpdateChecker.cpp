#include "SystemUpdateChecker.h"



SystemUpdateChecker::SystemUpdateChecker() :
	Component()
{
	std::ifstream iFile;
	iFile.open(local_sourceFile);

	if (!iFile) {
		std::cout << "ERROR: Missing or not accessible source file! (/lib/donauctl/sysupdate/source)" << "\n";
		exit(0);
	}

	std::getline(iFile, remote_downloadAddress);

	iFile.close();
}


SystemUpdateChecker::~SystemUpdateChecker()
{
}

std::string SystemUpdateChecker::giveReferenceName() {
	return "update-check";
}

std::string SystemUpdateChecker::giveReferenceDescription() {
	return "Checks for new System Software Updates without the need of a root password.";
}

std::vector<std::string> SystemUpdateChecker::giveReferenceHelp() {
	std::vector<std::string> helpData{ "This command takes no arguments." };
	return helpData;
}

void SystemUpdateChecker::execute() {
	Console::downloadFileWget(remote_downloadAddress + remote_versionFile, local_remoteVersionFilePath);

	XMLDocument* localFile = new XMLDocument(local_versionFile);
	XMLDocument* remoteFile = new XMLDocument(local_remoteVersionFile);

	localFile->parse();
	remoteFile->parse();

	if (!(localFile->getFirstElementByName("version").getValue() == remoteFile->getFirstElementByName("version").getValue().erase(remoteFile->getFirstElementByName("version").getValue().find(".onl")))) {
		Console::showNotification("System Software Update available. Go to Control Panel for more information.", "aptdaemon-download");
		std::cout << "An update was found! Log in as root, then execute \'donauctl sysupdate check\'." << "\n";
	}
	else {
		Console::showNotification("Your System is Up-to-Date.", "dialog-info");
		std::cout << "You are Up-To-Date!" << "\n";
	}

	delete localFile;
	delete remoteFile;

	Console::tryRemoveFile(local_remoteVersionFile);
}