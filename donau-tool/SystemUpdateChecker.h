#pragma once
#include "Component.h"
#include "Console.h"
#include "donau-XMLParseDX.h"
#include <vector>
#include <string>
#include <iostream>

#include <iostream>
using namespace DonauUtils::XMLParseDX;
class SystemUpdateChecker :
	public Component
{
	const std::string local_versionFile{ "/lib/donauctl/sysupdate/local-version.xml" };
	const std::string local_remoteVersionFilePath{ "/tmp" };
	const std::string local_remoteVersionFile{ local_remoteVersionFilePath + "/remote-version.xml" };
	const std::string local_sourceFile{ "/lib/donauctl/sysupdate/source" };

	std::string remote_downloadAddress{ "" };
	const std::string remote_versionFile{ remote_downloadAddress  + "/remote-version.xml" };
public:
	SystemUpdateChecker();
	~SystemUpdateChecker();

	std::string giveReferenceName();
	std::string giveReferenceDescription();
	std::vector<std::string> giveReferenceHelp();
	void execute();
};

