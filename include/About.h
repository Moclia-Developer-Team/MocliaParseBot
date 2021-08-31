#pragma once

#include "MiraiBotAndInclude.h"

class MocliaBotAbout
{
public:
	std::string botInfo(std::string mahVer, std::string mcppVer);

private:
	typedef struct programMessage
	{
		std::string complier;
		std::string complieTime;
		std::string complieDate;
		std::string compliePlatform;
		std::string supportPlatform;
		std::string progType;
		std::string miraicppVer;
		std::string mahVer;
		std::string progName;
		std::string progAuthor;
		std::string progVer;
	};
};